#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Scribble.h"
#include <QMouseEvent>
#include <QPainter>

#include <cpr/cpr.h>
#include <crow.h>
#include <sstream>
#include <qmessagebox.h>
#include <qtimer.h>
#include "GameState.h"

class Scribble : public QMainWindow
{
    Q_OBJECT

public:
    using Coordinate = std::pair<uint16_t, uint16_t>;
    using Line = std::pair<Coordinate, Coordinate>;
public:
    Scribble(int userId, std::string roomCode, QWidget * parent = nullptr );
    ~Scribble();

    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void paintEvent(QPaintEvent* event) override;

public:
    std::string DrawingToString();
    void SetDrawingFromJson(crow::json::rvalue json);
    bool IsInDrawingFrame(const QPoint& point);

private slots:
    void clearWindow();
    void refresh();


private:
    Ui::ScribbleClass ui;
    
    int m_userId;
    std::string m_roomCode;

    bool m_canDraw;
    bool m_guessedCorrectly;

    bool m_isDrawing;
    Coordinate m_lastDrawnPoint;
    std::vector<Line> m_drawing;

    QTimer m_refreshTimer;

    const QRect m_drawingArea;
    const uint16_t kBrushSize = 5;
};
