#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsBank.h"

class QtWidgetsBank : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsBank(QWidget *parent = nullptr);
    ~QtWidgetsBank();

private:
    Ui::QtWidgetsBankClass ui;
};
