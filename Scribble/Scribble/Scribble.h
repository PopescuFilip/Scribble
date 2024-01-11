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
    Scribble(int username, QWidget * parent = nullptr );
    ~Scribble();

    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void paintEvent(QPaintEvent* event) override;
    void clickedOnButton(int username);

private slots:
    void clearWindow();


private:
    Ui::ScribbleClass ui;
    bool m_drawing;
    bool m_guessedCorrectly;
    Coordinate m_lastDrawnPoint;
    std::vector<Line> m_lines;
    int m_userId;
    std::string m_roomCode;
    const uint16_t kBrushSize = 5;
};
