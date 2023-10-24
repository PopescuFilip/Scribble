#pragma once
#include <qpainter.h>
#include <QMouseEvent>

class Node
{
private:
    int m_value;
    int m_radius;
    QPoint m_coordinate;
public:
    Node(int radius = 10);
    Node(const Node& other);
    void setValue(int value);
    void setCoordinate(QPoint);
    void setCoordinate(int x, int y);
    void setX(int x);
    void setY(int y);
    void setRadius(int radius);
    int getValue()const;
    QPoint getCoordinate()const;
    int getX()const;
    int getY()const;
    int getRadius()const;
    bool isInNode(QPoint p)const;
    bool positionIsAvailable(QPoint p)const;
    bool operator ==(const Node& n)const;
};

