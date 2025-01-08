#include "QtWidgetsBank.h"

QtWidgetsBank::QtWidgetsBank(const QString& username, double balance, QWidget *parent)
    : QMainWindow(parent), currentUsername(username), currentBalance(balance)
{
    ui.setupUi(this);
    updateUserInfo();
}

QtWidgetsBank::~QtWidgetsBank() = default;

void QtWidgetsBank::updateUserInfo() {
    ui.usernameLabel->setText(QString("Witaj, %1!").arg(currentUsername));
    ui.balanceLabel->setText(QString("Saldo: %1 PLN").arg(currentBalance, 0, 'f', 2));
}
