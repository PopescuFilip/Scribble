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
    using Coordinate = std::pair<uint16_t, uint16_t>;
    using Line = std::pair<Coordinate, Coordinate>;
public:
    Scribble();
    Scribble(std::string username, QWidget * parent = nullptr );
    ~Scribble();

    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void paintEvent(QPaintEvent* event) override;

private slots:
    void clearWindow();


private:
    Ui::ScribbleClass ui;
    bool m_drawing;
    Coordinate m_lastDrawnPoint;
    std::vector<Line> m_lines;
    const uint16_t kBrushSize = 5;
    std::string m_user;
    bool m_guessedCorrectly;
};
