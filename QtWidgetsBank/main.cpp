#include "QtWidgetsBank.h"
#include <QtWidgets/QApplication>
#include "LoginForm.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginForm loginForm;

    if (loginForm.exec() != QDialog::Accepted) {
        return 0;
    }

    QString username = loginForm.getCurrentUsername();
    double balance = loginForm.getCurrentBalance();
    QMap<QString, UserAccount> userData = loginForm.getUserData();
    QtWidgetsBank w(nullptr, username, balance, userData);
    w.show();
    return a.exec();
}
 


/*
TODO
Wplata / Wyplata //jest
Historia transakcji
Dynamiczna zmiana salda bez relogu //jest
Przelewy miedzy userami

Opcjonalnie:
Dodanie maili do konta i wysylanie potwierdzen

*/