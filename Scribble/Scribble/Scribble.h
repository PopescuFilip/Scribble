#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Scribble.h"
#include <QMouseEvent>

class Scribble : public QMainWindow
{
    Q_OBJECT

public:
    Scribble( QWidget * parent = nullptr );
    ~Scribble();

    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void paintEvent(QPaintEvent* event) override;

private:
    Ui::ScribbleClass ui;
    bool m_drawing;
};
