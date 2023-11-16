#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Scribble.h"
#include <QMouseEvent>
#include <QPainter>
#include <vector>

class Scribble : public QMainWindow
{
    Q_OBJECT

public:
    Scribble( QWidget * parent = nullptr );
    ~Scribble();

    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void paintEvent(QPaintEvent* event) override;

private:
    Ui::ScribbleClass ui;
    bool m_drawing;
    std::vector<QPoint> m_points;
};
