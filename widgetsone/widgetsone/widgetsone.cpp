#include "widgetsone.h"

widgetsone::widgetsone(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    mLastPressTime = 0;
}

widgetsone::~widgetsone()
{}

void widgetsone::slot1()
{
    graph.toggleOriented();
    update();
}

void widgetsone::longPressEvent(QMouseEvent* e)
{
    if (longPressNode.getValue() != -1 and graph.positionIsAvailable(e->pos()))
    {
        graph.setNode(longPressNode.getValue(), e->pos());
        update();
    }
    longPressNode.setValue(-1);
    update();
}

void widgetsone::clickRightEvent(QMouseEvent* e)
{
    if (!graph.positionIsAvailable(e->pos()))
        return;
    Node n;
    graph.addNode(e->pos());
    QFile file("file.txt");
    graph.updateFile(file);
    file.close();
    update();
}

void widgetsone::clickLeftEvent(QMouseEvent* e)
{
    std::vector<Node> nodes = graph.getNodes();
    for (Node& n : nodes)
    {
        if (n.isInNode(e->pos()))
        {
            if (firstNode.getValue() == -1)
                firstNode = n;

            else if (firstNode.getValue() == n.getValue())
                firstNode.setValue(-1);
            else
            {
                Arch archToAdd = Arch(graph.getAdressOfNode(firstNode.getValue()), graph.getAdressOfNode(n.getValue()));
                if (!graph.isInGraph(archToAdd))
                {
                    graph.addArch(archToAdd);
                    QFile file("file.txt");
                    graph.updateFile(file);
                    file.close();
                }
                firstNode.setValue(-1);
            }
            update();
            break;
        }
    }
}


void widgetsone::mouseReleaseEvent(QMouseEvent* e)
{
    const quint64 pressTime = QDateTime::currentMSecsSinceEpoch() - mLastPressTime;
    if (pressTime > widgetsone::LONG_PRESS_THRESHOLD)
        longPressEvent(e);
    else if (e->button() == Qt::RightButton)
        clickRightEvent(e);
    else if (e->button() == Qt::LeftButton)
        clickLeftEvent(e);

}

void widgetsone::mousePressEvent(QMouseEvent* e)
{
    mLastPressTime = QDateTime::currentMSecsSinceEpoch();
    for (Node& n : graph.getNodes())
    {
        if (n.isInNode(e->pos()))
        {
            longPressNode = n;
        }
    }
}

void widgetsone::paintEvent(QPaintEvent* e)
{
    QPainter painter(this);
    std::vector<Node> noduri = graph.getNodes();
    for (const Node& n : noduri)
    {
        int x = n.getX();
        int y = n.getY();
        int radius = graph.getRadius();
        QRect r(x - radius, y - radius, 2 * radius, 2 * radius);
        if (firstNode.getValue() != -1 && n == firstNode)
        {
            painter.save();
            QPen pen;
            pen.setColor(Qt::red);
            pen.setWidth(5);
            painter.setPen(pen);
            painter.drawEllipse(r);
            painter.restore();
        }
        else
            painter.drawEllipse(r);
        QString s;
        s.setNum(n.getValue());
        painter.drawText(r, Qt::AlignCenter, s);
    }
    std::vector<Arch> arches = graph.getArches();
    for (Arch& a : arches)
    {
        painter.drawLine(a.getFirstNode()->getCoordinate(), a.getSecondNode()->getCoordinate());
        if (graph.isOriented())
        {
            QPolygon arrowHead = graph.createArrowHead(a.getFirstNode()->getCoordinate(), 
                                                       a.getSecondNode()->getCoordinate(), 
                                                       2 * graph.getRadius());
            painter.drawPolygon(arrowHead);
        }
    }
}

