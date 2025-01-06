#include "LoginForm.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

LoginForm::LoginForm(QWidget* parent)  //konstruktor klasy
	: QDialog(parent) //wywolanie konstruktora bazowego
{
	ui.setupUi(this); //inicjalizacja interfejsu
	
	loadUserData("users.txt"); //wczytanie danych

	connect(ui.loginButton, &QPushButton::clicked, this, &LoginForm::onLoginButtonClicked); //polaczenie przycisku z logowaniem
}

LoginForm::~LoginForm() = default; //destruktor klasy, domyslny nic nie robi

void LoginForm::loadUserData(const QString& filePath) { //funkcja wczytuje dane z pliku
	QFile file(filePath); //obiekt QFile reprezentuje plik

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) { //otwarcie pliku read only
		QMessageBox::critical(this, "Blad", "Nie mozna otworzyc pliku z danymi");
			return;
	}

	QTextStream in(&file); //strumien do odczytu z pliku

	while (!in.atEnd()) {
		QString line = in.readLine(); //odczytuje jedna linie
		QStringList parts = line.split(':'); //dzieli na dwie czesci
		if (parts.size() == 2) { //sprawdza czy dobry format
			QString username = parts[0].trimmed(); //usuwa spacje
			QString password = parts[1].trimmed();
			userData[username] = password; //dodaje do mapy
		}
	}
	file.close();
}

void LoginForm::onLoginButtonClicked() { //slot obsluguje klikniecie przycisku
	QString username = ui.usernameLineEdit->text(); //pobiera tekst z pola
	QString password = ui.passwordLineEdit->text();

	if (userData.contains(username) && userData[username] == password) { //sprawdza poprawnosc danych
		QMessageBox::information(this, "Sukces", "Zalogowano pomyslne!");
		accept();
	}
	else {
		QMessageBox::warning(this, "B³¹d", "Niepoprawne cos");	
	}

}
