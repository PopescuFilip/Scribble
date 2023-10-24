#pragma once

#include "Graph.h"
#include <QMouseEvent>
#include <qdatetime.h>
#include <QtWidgets/QMainWindow>
#include "ui_widgetsone.h"

class widgetsone : public QMainWindow
{
    Q_OBJECT

public:
    widgetsone(QWidget *parent = nullptr);
    ~widgetsone();
    virtual void mouseReleaseEvent(QMouseEvent* e);
    virtual void mousePressEvent(QMouseEvent* e);
    virtual void paintEvent(QPaintEvent* e);
    void longPressEvent(QMouseEvent* e);
    void clickRightEvent(QMouseEvent* e);
    void clickLeftEvent(QMouseEvent* e);

protected slots:
    void slot1();

private:
    Ui::widgetsoneClass ui;
    Node firstNode;
    Node longPressNode;
    Graph graph;
    qint64 mLastPressTime;
    static const qint64 LONG_PRESS_THRESHOLD = 1000;
};
