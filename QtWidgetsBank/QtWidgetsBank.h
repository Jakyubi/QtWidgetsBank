#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsBank.h"
#include "LoginForm.h"

class QtWidgetsBank : public QMainWindow //klasa reprezentuje glowne okno aplikacji
{
    Q_OBJECT

public: 
    //konstruktor z wartoœciami dla uzytkownika
    QtWidgetsBank(QWidget* parent = nullptr, const QString& username = "", double balance = 0.0, const QMap<QString, UserAccount>& data = QMap<QString, UserAccount>());
    ~QtWidgetsBank();

private slots:
    //funkcje obs³uguj¹ce zdarzenia
    void onDepositButtonClicked();
    void onWithdrawButtonClicked();
    void onTransferButtonClicked();


private:
    Ui::QtWidgetsBankClass ui;  //generowanie interfejsu
    QString currentUsername;    //nazwa u¿ytkownika
    double currentBalance;      //saldo u¿ytkownika

    QMap<QString, UserAccount> userData;   //dane wszystkich u¿ytkowników

    //funkcje do aktualizacji interfejsu
    void updateUserInfo();
    void updateBalanceDisplay();

};
