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