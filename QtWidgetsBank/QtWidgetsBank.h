#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsBank.h"

class QtWidgetsBank : public QMainWindow
{
    Q_OBJECT

public:
    explicit QtWidgetsBank(const QString& username, double balance, QWidget *parent = nullptr);
    ~QtWidgetsBank();

private:
    Ui::QtWidgetsBankClass ui;
    QString currentUsername;
    double currentBalance;

    void updateUserInfo();
};
