#include "QtWidgetsBank.h"
#include <QMessageBox>
#include <QFile>
#include <QDate>
#include "LoginForm.h"

//konstruktor klasy
QtWidgetsBank::QtWidgetsBank(QWidget* parent, const QString& username, double balance, const QMap<QString, UserAccount>& data)
    : QMainWindow(parent), currentUsername(username), currentBalance(balance), userData(data)
{
    ui.setupUi(this);       //inicjalizacja interfejsu
    updateUserInfo();       //wyœwietla aktualnego usera
    updateBalanceDisplay(); //wyœwietla aktualne saldo
    loadTransactionHistory();

    //³¹czenie sygna³ów ze slotami
    connect(ui.depositButton, &QPushButton::clicked, this, &QtWidgetsBank::onDepositButtonClicked);
    connect(ui.withdrawButton, &QPushButton::clicked, this, &QtWidgetsBank::onWithdrawButtonClicked);
    connect(ui.depositButtonATM, &QPushButton::clicked, this, &QtWidgetsBank::onATMDepositButtonClicked);
    connect(ui.withdrawButtonATM, &QPushButton::clicked, this, &QtWidgetsBank::onATMWithdrawButtonClicked);
    connect(ui.transferButton, &QPushButton::clicked, this, &QtWidgetsBank::onTransferButtonClicked);
    connect(ui.logoutButton, &QPushButton::clicked, this, &QtWidgetsBank::onLogoutButtonClicked);

}

QtWidgetsBank::~QtWidgetsBank() = default;

//aktualizacja nazwy na ekranie
void QtWidgetsBank::updateUserInfo() {
    ui.usernameLabel->setText(QString("Witaj, %1!").arg(currentUsername));
}

//aktualizacja salda
void QtWidgetsBank::updateBalanceDisplay() {
    ui.balanceLabel->setText(QString("Saldo: %1 PLN").arg(currentBalance, 0, 'f', 2));
}

void QtWidgetsBank::logTransactions(const QString& fromUser, const QString& type, double amount, const QString& toUser)
{
    QString fileName = "transaction_history.txt";
    QFile file(fileName);

    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << fromUser << " - " << type << " - " << amount << " PLN" << " - " << toUser << " - " << currentDateTime << "\n";

        if (type == "Transfer" && fromUser != toUser) {
            out << toUser << " - Received - " << amount << " PLN" << " - " << fromUser << " - " << currentDateTime << "\n";
        }
        file.close();
    }
}

void QtWidgetsBank::loadTransactionHistory()
{
    QString fileName = "transaction_history.txt";
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui.historyTextEdit->setText("Brak historii");
        return;
    }

    QTextStream in(&file);
    QString historyContent;

    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.startsWith(currentUsername)) {
            historyContent += line + "\n";
        }
    }
    
    ui.historyTextEdit->setText(historyContent);
    file.close();

}



//obs³uga przycisku wp³aty
void QtWidgetsBank::onDepositButtonClicked() {
    
    bool ok;
    double depositAmount = ui.depositlineEdit->text().toDouble(&ok);

    if (!ok || depositAmount <= 0) {
        QMessageBox::warning(this, "Blad", "Nieprawidlowa kwota");
            return;
    }

    currentBalance += depositAmount;

    ui.balanceLabel->setText(QString("Saldo: %1 PLN").arg(currentBalance, 0, 'f', 2));
    
    logTransactions(currentUsername, "Deposit", depositAmount, "self");
    ui.depositlineEdit->clear();
    QMessageBox::information(this, "Sukces", QString("Wplacono %1 PLN").arg(depositAmount, 0, 'f', 2));


    LoginForm loginForm;
    loginForm.updateUserBalance(currentUsername, currentBalance);
    loadTransactionHistory();

}

//obs³uga przycisku wyp³aty
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

    logTransactions(currentUsername, "Withdraw", withdrawAmount, "self");


    ui.withdrawlineEdit->clear();
    QMessageBox::information(this, "Sukces", QString("Wyplacono %1 PLN").arg(withdrawAmount, 0, 'f', 2));
    
    LoginForm loginForm;
    loginForm.updateUserBalance(currentUsername, currentBalance);
    loadTransactionHistory();

}

//obs³uga przycisku przelewu 
void QtWidgetsBank::onTransferButtonClicked()
{

    QString transferUsername = ui.transferUsernameLineEdit->text();
    bool ok;
    double transferAmount = ui.transferCashLineEdit->text().toDouble(&ok);

    if(!ok || transferAmount <= 0.0){
        QMessageBox::warning(this, "Blad", "Wprowadz poprawna kwote");
        return;
    }

    if (currentBalance < transferAmount) {
        QMessageBox::warning(this, "Blad", "Wprowadz poprawna kwote");
        return;
    }

    if (!userData.contains(transferUsername)) {
        QMessageBox::warning(this, "Blad", "User nie istnieje");
        return;
    }

    currentBalance -= transferAmount;
    userData[transferUsername].balance += transferAmount;
    updateBalanceDisplay();

    LoginForm loginForm;
    loginForm.updateUserBalance(currentUsername, currentBalance);
    loginForm.updateUserBalance(transferUsername, userData[transferUsername].balance);
    logTransactions(currentUsername, "Transfer", transferAmount, transferUsername);


    ui.transferUsernameLineEdit->clear();
    ui.transferCashLineEdit->clear();
    QMessageBox::information(this, "Success", QString("Przelew na %1 PLN wykonany").arg(transferAmount));

    loadTransactionHistory();

}

void QtWidgetsBank::onLogoutButtonClicked()
{
    this->close();

    LoginForm loginForm;

    if (loginForm.exec() == QDialog::Accepted) {
        QString username = loginForm.getCurrentUsername();
        double balance = loginForm.getCurrentBalance();
        QtWidgetsBank* newBankWindow = new QtWidgetsBank(nullptr, username, balance);
        newBankWindow->show();
    }

}

void QtWidgetsBank::onATMDepositButtonClicked()
{

    bool ok;
    double depositAmount = ui.depositlineEditATM->text().toDouble(&ok);

    if (!ok || depositAmount <= 0) {
        QMessageBox::warning(this, "Blad", "Nieprawidlowa kwota");
        return;
    }

    currentBalance += depositAmount;

    ui.balanceLabel->setText(QString("Saldo: %1 PLN").arg(currentBalance, 0, 'f', 2));

    logTransactions(currentUsername, "Deposit", depositAmount, "ATM");
    ui.depositlineEditATM->clear();
    QMessageBox::information(this, "Sukces", QString("Wplacono %1 PLN").arg(depositAmount, 0, 'f', 2));


    LoginForm loginForm;
    loginForm.updateUserBalance(currentUsername, currentBalance);
    loadTransactionHistory();
}

void QtWidgetsBank::onATMWithdrawButtonClicked()
{

    bool ok;
    double withdrawAmount = ui.withdrawlineEditATM->text().toDouble(&ok);

    if (!ok || withdrawAmount <= 0 || withdrawAmount > currentBalance) {
        QMessageBox::warning(this, "Blad", "Niepoprawna kwota");
        return;
    }

    currentBalance -= withdrawAmount;

    ui.balanceLabel->setText(QString("Saldo: %1 PLN").arg(currentBalance, 0, 'f', 2));

    logTransactions(currentUsername, "Withdraw", withdrawAmount, "ATM");


    ui.withdrawlineEditATM->clear();
    QMessageBox::information(this, "Sukces", QString("Wyplacono %1 PLN").arg(withdrawAmount, 0, 'f', 2));

    LoginForm loginForm;
    loginForm.updateUserBalance(currentUsername, currentBalance);
    loadTransactionHistory();
}
