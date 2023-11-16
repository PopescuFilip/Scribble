#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Scribble.h"
#include <QMouseEvent>
#include <QPainter>
#include <set>

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
    void InterpolationLogic(const QPoint&, const QPoint&, float);

private:
    Ui::ScribbleClass ui;
    bool m_drawing;
    QPoint m_lastDrawnPoint;
    std::set<std::pair<int, int>> m_points;
    const uint16_t kBrushSize = 5;
    const uint16_t kInterpolationThreshold = 2 * kBrushSize;
};
