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
    QtWidgetsBank w(username, balance);
    w.show();
    return a.exec();
}
 