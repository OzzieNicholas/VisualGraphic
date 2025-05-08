#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BasicAxis.h"

class BasicAxis : public QMainWindow
{
    Q_OBJECT

public:
    BasicAxis(QWidget *parent = nullptr);
    ~BasicAxis();

private:
    Ui::BasicAxisClass ui;
};
