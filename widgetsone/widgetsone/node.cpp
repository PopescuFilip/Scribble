#include "node.h"

Node::Node(int radius):
    m_value(-1),
    m_radius(radius)
{

}

Node::Node(const Node& other):
    m_value(other.m_value),
    m_radius(other.m_radius),
    m_coordinate(other.m_coordinate)
{}

void Node::setValue(int value)
{
    this->m_value = value;
}

void Node::setCoordinate(QPoint p)
{
    m_coordinate = p;
}

void Node::setCoordinate(int x, int y)
{
    m_coordinate = QPoint(x,y);
}

void Node::setX(int x)
{
    m_coordinate.setX(x);
}

void Node::setY(int y)
{
    m_coordinate.setY(y);
}

void Node::setRadius(int radius)
{
    m_radius = radius;
}

int Node::getValue() const
{
    return m_value;
}

QPoint Node::getCoordinate()const
{
    return m_coordinate;
}

int Node::getX()const
{
    return m_coordinate.x();
}

int Node::getY()const
{
    return m_coordinate.y();
}

int Node::getRadius() const
{
    return m_radius;
}

bool Node::isInNode(QPoint p) const
{
    return fabs(p.x() - m_coordinate.x()) < m_radius &&
           fabs(p.y() - m_coordinate.y()) < m_radius;
}


bool Node::positionIsAvailable(QPoint p) const
{
    return fabs(p.x() - m_coordinate.x()) >= 2* m_radius or
           fabs(p.y() - m_coordinate.y()) >= 2* m_radius;
}

bool Node::operator ==(const Node &n) const
{
    return this->getX() == n.getX() and this->getY() == n.getY();
}

