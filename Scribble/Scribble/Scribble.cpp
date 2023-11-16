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
    m_points.insert(std::make_pair(event->pos().x(), event->pos().y()));
    m_lastDrawnPoint = event->pos();
    update();
}

void Scribble::mouseMoveEvent(QMouseEvent* event)
{
    if (!m_drawing)
        return;
    QPoint newPoint = event->pos();
    qreal distance = QLineF(m_lastDrawnPoint, newPoint).length();
    if (distance > kInterpolationThreshold) 
        InterpolationLogic(m_lastDrawnPoint, newPoint, distance);
    m_points.insert(std::make_pair(event->pos().x(), event->pos().y()));
    m_lastDrawnPoint = event->pos();
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
    for (const auto& point : m_points)
        painter.drawEllipse(point.first - kBrushSize, point.second - kBrushSize, 2 * kBrushSize, 2 * kBrushSize);
}

void Scribble::InterpolationLogic(const QPoint& point1, const QPoint& point2, float distance)
{
    while (distance > kInterpolationThreshold) 
    {
        float ratio = kInterpolationThreshold / distance;
        int x = (1 - ratio) * point1.x() + ratio * point2.x();
        int y = (1 - ratio) * point1.y() + ratio * point2.y();
        QPoint interpolatedPoint(x, y);
        m_points.insert(std::make_pair(interpolatedPoint.x(), interpolatedPoint.y()));
        distance -= kInterpolationThreshold;
        qDebug() << "intra";
    }
}
