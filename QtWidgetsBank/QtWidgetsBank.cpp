#include "QtWidgetsBank.h"
#include <QMessageBox>
#include "LoginForm.h"

QtWidgetsBank::QtWidgetsBank(QWidget* parent, const QString& username, double balance)
    : QMainWindow(parent), currentUsername(username), currentBalance(balance)
{
    ui.setupUi(this);
    updateUserInfo();
    updateBalanceDisplay();

    connect(ui.depositButton, &QPushButton::clicked, this, &QtWidgetsBank::onDepositButtonClicked);
    connect(ui.withdrawButton, &QPushButton::clicked, this, &QtWidgetsBank::onWithdrawButtonClicked);

}

QtWidgetsBank::~QtWidgetsBank() = default;

void QtWidgetsBank::updateUserInfo() {
    ui.usernameLabel->setText(QString("Witaj, %1!").arg(currentUsername));
}

void QtWidgetsBank::updateBalanceDisplay() {
    ui.balanceLabel->setText(QString("Saldo: %1 PLN").arg(currentBalance, 0, 'f', 2));
}

void QtWidgetsBank::onDepositButtonClicked() {
    
    bool ok;
    double depositAmount = ui.depositlineEdit->text().toDouble(&ok);

    if (!ok || depositAmount <= 0) {
        QMessageBox::warning(this, "Blad", "Nieprawidlowa kwota");
            return;
    }

    currentBalance += depositAmount;

    ui.balanceLabel->setText(QString("Saldo: %1 PLN").arg(currentBalance, 0, 'f', 2));
    
    ui.depositlineEdit->clear();
    QMessageBox::information(this, "Sukces", QString("Wplacono %1 PLN").arg(depositAmount, 0, 'f', 2));


    LoginForm loginForm;
    loginForm.updateUserBalance(currentUsername, currentBalance);
}

void QtWidgetsBank::onWithdrawButtonClicked()
{
    bool ok;
    double withdrawAmount = ui.withdrawlineEdit->text().toDouble(&ok);

    if (!ok || withdrawAmount <= 0 || withdrawAmount > currentBalance) {
        QMessageBox::warning(this, "Blad", "Niepoprawna kwota");
        return;
    }

    currentBalance -= withdrawAmount;

    ui.balanceLabel->setText(QString("Saldo: %1 PLN").arg(currentBalance, 0, 'f', 2));

    ui.withdrawlineEdit->clear();
    QMessageBox::information(this, "Sukces", QString("Wyplacono %1 PLN").arg(withdrawAmount, 0, 'f', 2));
    
    LoginForm loginForm;
    loginForm.updateUserBalance(currentUsername, currentBalance);
}