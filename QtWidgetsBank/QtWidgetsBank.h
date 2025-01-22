#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsBank.h"
#include <QString>
#include <QMap>
#include <QDialog>
#include "LoginForm.h"

class QtWidgetsBank : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsBank(QWidget* parent = nullptr, const QString& username = "", double balance = 0.0, const QMap<QString, UserAccount>& data = QMap<QString, UserAccount>());
    ~QtWidgetsBank();

private slots:
    void onDepositButtonClicked();
    void onWithdrawButtonClicked();

    void onTransferButtonClicked();


private:
    Ui::QtWidgetsBankClass ui;
    QString currentUsername;
    double currentBalance;

    QMap<QString, UserAccount> userData;



    void updateUserInfo();
    void updateBalanceDisplay();

};
