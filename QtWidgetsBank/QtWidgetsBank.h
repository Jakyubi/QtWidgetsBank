#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsBank.h"

class QtWidgetsBank : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsBank(QWidget* parent = nullptr, const QString& username="" , double balance=0.0);
    ~QtWidgetsBank();

private slots:
    void onDepositButtonClicked();
    void onWithdrawButtonClicked();

private:
    Ui::QtWidgetsBankClass ui;
    QString currentUsername;
    double currentBalance;

    void updateUserInfo();
    void updateBalanceDisplay();
};
