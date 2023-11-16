#include "Scribble.h"

Scribble::Scribble(QWidget *parent)
    : QMainWindow(parent),
      m_drawing(false)
{
    ui.setupUi(this);
}

Scribble::~Scribble()
{}

void Scribble::mousePressEvent(QMouseEvent * event)
{
    m_drawing = true;
}

void Scribble::mouseMoveEvent(QMouseEvent* event)
{
    if (!m_drawing)
        return;
    m_points.push_back(event->pos());
    update();
}

void Scribble::mouseReleaseEvent(QMouseEvent* event)
{
    m_drawing = false;
}

void Scribble::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setBrush(Qt::black);
    if(m_drawing)
        for(const auto& point: m_points)
            painter.drawEllipse(point.x() - 5, point.y() - 5, 10, 10);
}
