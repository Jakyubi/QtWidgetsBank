#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsBank.h"
#include "LoginForm.h"

class QtWidgetsBank : public QMainWindow //klasa reprezentuje glowne okno aplikacji
{
    Q_OBJECT

public: 
    //konstruktor z wartościami dla uzytkownika
    QtWidgetsBank(QWidget* parent = nullptr, const QString& username = "", double balance = 0.0, const QMap<QString, UserAccount>& data = QMap<QString, UserAccount>());
    ~QtWidgetsBank();

private slots:
    //funkcje obsługujące zdarzenia
    void onDepositButtonClicked();
    void onWithdrawButtonClicked();
    void onTransferButtonClicked();
    void onLogoutButtonClicked();

    void onATMDepositButtonClicked();
    void onATMWithdrawButtonClicked();


private:
    Ui::QtWidgetsBankClass ui;  //generowanie interfejsu
    QString currentUsername;    //nazwa użytkownika
    double currentBalance;      //saldo użytkownika

    QMap<QString, UserAccount> userData;   //dane wszystkich użytkowników

    //funkcje do aktualizacji inter
    void updateUserInfo();
    void updateBalanceDisplay();
    void logTransactions(const QString& fromUser, const QString& type, double amount, const QString& toUser);
    void loadTransactionHistory();

};
