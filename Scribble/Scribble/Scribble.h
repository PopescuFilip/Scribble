#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Scribble.h"

class Scribble : public QMainWindow
{
    Q_OBJECT

public:
    Scribble( QWidget * parent = nullptr );
    ~Scribble();

private:
    Ui::ScribbleClass ui;
};
