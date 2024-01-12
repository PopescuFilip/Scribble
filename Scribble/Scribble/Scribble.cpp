#include "Scribble.h"
#include "JoinRoom.h"


Scribble::Scribble(int username, QWidget *parent)
    : QMainWindow(parent),
      m_isDrawing(false),
      m_guessedCorrectly(false),
      m_userId(username),
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
}

Scribble::~Scribble()
{}

void Scribble::mousePressEvent(QMouseEvent* event)
{
    qDebug() << "mouse press";
    m_isDrawing = true;
    m_lastDrawnPoint = { event->pos().x(), event->pos().y() };
    update();
}

void Scribble::mouseMoveEvent(QMouseEvent* event)
{
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
    m_lines.push_back({ m_lastDrawnPoint,newPoint });
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
    for (const auto& line : m_lines)
        painter.drawLine(line.first.first, line.first.second, line.second.first, line.second.second);
}

std::string Scribble::DrawingToString()
{
    std::stringstream ss;
    for (size_t i = 0; i < m_lines.size(); ++i)
    {
        const auto& [firstPoint, secondPoint] = m_lines[i];
        const auto& [firstX, firstY] = firstPoint;
        const auto& [secondX, secondY] = secondPoint;
        
        ss << firstX << " " << firstY << " " << secondX << " " << secondY;
        if (i == m_lines.size() - 1)
            break;
        ss << ",";
    }
    return ss.str();
}

bool Scribble::IsInDrawingFrame(const QPoint& point)
{
    qDebug() << point << " check " << m_drawingArea;
    return m_drawingArea.contains(point);
}


void Scribble::clearWindow()
{
    m_lines.clear();
    update();
}