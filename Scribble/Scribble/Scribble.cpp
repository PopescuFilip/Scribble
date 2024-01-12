#include "Scribble.h"
#include "JoinRoom.h"


Scribble::Scribble(int username, std::string roomCode, QWidget *parent)
    : QMainWindow(parent),
      m_isDrawing(false),
      m_canDraw(false),
      m_guessedCorrectly(false),
      m_userId(username),
      m_roomCode{ roomCode },
      m_drawingArea(QPoint(90, 130), QPoint(1190, 600))
{
    ui.setupUi(this);

    QPixmap background("Images/ScribbleBackground.png");
    background = background.scaled(1280, 720, Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    setPalette(palette);

    setFixedSize(1280, 720);
    setGeometry(140, 70, 2560, 1440);

    connect(ui.ClearWindowButton, SIGNAL(clicked()), this, SLOT(clearWindow()));

    QObject::connect(&m_refreshTimer, &QTimer::timeout, this, &Scribble::refresh);
    m_refreshTimer.setInterval(5000);
    m_refreshTimer.start();
}

Scribble::~Scribble()
{}

void Scribble::mousePressEvent(QMouseEvent* event)
{
    qDebug() << "mouse press";
    if (!m_canDraw)
        return;
    m_isDrawing = true;
    m_lastDrawnPoint = { event->pos().x(), event->pos().y() };
    update();
}

void Scribble::mouseMoveEvent(QMouseEvent* event)
{
    if (!m_canDraw)
        return;
    if (!m_isDrawing)
        return;
    if (!IsInDrawingFrame(event->pos()))
    {
        qDebug() << event->pos() << " outside";
        m_isDrawing = false;
        return;
    }
    qDebug() << event->pos() << " inside";
    Coordinate newPoint { event->pos().x(), event->pos().y() };
    m_drawing.push_back({ m_lastDrawnPoint,newPoint });
    m_lastDrawnPoint = { event->pos().x(), event->pos().y() };
    update();
}

void Scribble::mouseReleaseEvent(QMouseEvent* event)
{
    qDebug() << "mouse release";
    m_isDrawing = false;
}

void Scribble::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QPen pen(Qt::black);
    pen.setWidth(kBrushSize);
    painter.setPen(pen);
    for (const auto& line : m_drawing)
        painter.drawLine(line.first.first, line.first.second, line.second.first, line.second.second);
}

std::string Scribble::DrawingToString()
{
    std::stringstream ss;
    for (size_t i = 0; i < m_drawing.size(); ++i)
    {
        const auto& [firstPoint, secondPoint] = m_drawing[i];
        const auto& [firstX, firstY] = firstPoint;
        const auto& [secondX, secondY] = secondPoint;
        
        ss << firstX << " " << firstY << " " << secondX << " " << secondY;
        if (i == m_drawing.size() - 1)
            break;
        ss << ",";
    }
    return ss.str();
}

void Scribble::SetDrawingFromJson(crow::json::rvalue json)
{
    m_drawing.clear();
    for (const auto& elem : json)
    {
        const auto firstPointX{ json["firstPointX"].i() };
        const auto firstPointY{ json["firstPointY"].i() };
        const auto secondPointX{ json["secondPointX"].i() };
        const auto secondPointY{ json["secondPointY"].i() };

        m_drawing.push_back({ {firstPointX, firstPointY}, {secondPointX, secondPointY} });
    }
}

bool Scribble::IsInDrawingFrame(const QPoint& point)
{
    qDebug() << point << " check " << m_drawingArea;
    return m_drawingArea.contains(point);
}

void Scribble::refresh()
{
    m_refreshTimer.stop();

    cpr::Response response = cpr::Get(
        cpr::Url{ "http://localhost:18080/getcandraw" },
        cpr::Parameters{
        { "id" , std::to_string(m_userId) },
        { "code", m_roomCode }
        }
    );

    if (response.status_code == 203)
    {
        m_canDraw = false;
        cpr::Response response = cpr::Get(
            cpr::Url{ "http://localhost:18080/getdrawing" },
            cpr::Parameters{
            { "id", std::to_string(m_userId) },
            { "code", m_roomCode }
            }
        );

        auto json = crow::json::load(response.text);
        if (json["code"].i() == 200)
        {
            SetDrawingFromJson(json["drawing"]);
            m_refreshTimer.start();
        }
        return;
    }

    if (response.status_code == 200)
    {
        m_canDraw = true;
        cpr::Response response = cpr::Get(
            cpr::Url{ "http://localhost:18080/putdrawing" },
            cpr::Parameters{
            { "id", std::to_string(m_userId) },
            { "code", m_roomCode },
            { "drawing", DrawingToString()}
            }
        );
        m_refreshTimer.start();
        return;
    }

    QMessageBox::critical(this, "Error", "something went wrong");
}


void Scribble::clearWindow()
{
    m_drawing.clear();
    update();
}