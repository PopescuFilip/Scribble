#include "Scribble.h"
#include "JoinRoom.h"

Scribble::Scribble()
{
};

Scribble::Scribble(std::string username, QWidget *parent)
    : QMainWindow(parent),
      m_drawing(false),
      m_guessedCorrectly(false),
      m_user(username)
{
    ui.setupUi(this);

    setFixedSize(1280, 720);
    setGeometry(140, 70, 2560, 1440);

    connect(ui.ClearWindowButton, SIGNAL(clicked()), this, SLOT(clearWindow()));
}

Scribble::~Scribble()
{}

void Scribble::mousePressEvent(QMouseEvent* event)
{
    m_drawing = true;
    m_lastDrawnPoint = { event->pos().x(), event->pos().y() };
    update();
}

void Scribble::mouseMoveEvent(QMouseEvent* event)
{
    if (!m_drawing)
        return;
    Coordinate newPoint { event->pos().x(), event->pos().y() };
    m_lines.push_back({ m_lastDrawnPoint,newPoint });
    m_lastDrawnPoint = { event->pos().x(), event->pos().y() };
    update();
}

void Scribble::mouseReleaseEvent(QMouseEvent* event)
{
    m_drawing = false;
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


void Scribble::clearWindow()
{
    m_lines.clear();
    update();
}

void Scribble::clickedOnButton(std::string username)
{
    JoinRoom* newWindow = new JoinRoom(username);
    newWindow->show();
}