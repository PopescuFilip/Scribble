#include "Scribble.h"

Scribble::Scribble(QWidget *parent)
    : QMainWindow(parent),
      m_drawing(false)
{
    ui.setupUi(this);
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
