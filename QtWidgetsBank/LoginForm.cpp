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
	connect(ui.registerButton, &QPushButton::clicked, this, &LoginForm::onRegisterButtonClicked); //polaczenie przycisku z rejestracja
}

LoginForm::~LoginForm() = default; //destruktor klasy, domyslny nic nie robi



void LoginForm::loadUserData(const QString& filePath) { //funkcja wczytuje dane z pliku
	QFile file(filePath); //obiekt QFile reprezentuje plik

	if (!file.exists()) { //jesli plik nie istnieje, tworzy go
		file.open(QIODevice::WriteOnly | QIODevice::Text);
		file.close();
		QMessageBox::information(this, "Couldn't find users.txt", "Created new file");
		return;	//plik jest pusty wiec nie ma potrzeby odczytu
	}

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) { //otwarcie pliku read only
		QMessageBox::critical(this, "Error", "Cannon open data file");
			return;
	}

	QTextStream in(&file); //strumien do odczytu z pliku

	while (!in.atEnd()) {
		QString line = in.readLine(); //odczytuje jedna linie
		QStringList parts = line.split(':'); //dzieli na dwie czesci
		if (parts.size() == 3) { //sprawdza czy dobry format
			QString username = parts[0].trimmed(); //usuwa spacje
			QString password = parts[1].trimmed();
			double balance = parts[2].toDouble();
			userData[username] = {password, balance}; //dodaje do mapy
		}
	}
	file.close();
}

void LoginForm::saveUserData(const QString& filePath)
{
	QFile file(filePath);

	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QMessageBox::critical(this, "Error", "Can not save");
		return;
	}

	QTextStream out(&file); //tworzy strumien tekstowy

	for (auto it = userData.begin(); it != userData.end(); ++it) { //zapisuje kazda pare user:haslo
		out << it.key() << ":" << it.value().password << ":" << it.value().balance << "\n";
	}

	file.close();

}

void LoginForm::onLoginButtonClicked()  { //slot obsluguje klikniecie przycisku
	QString username = ui.usernameLineEdit->text(); //pobiera tekst z pola
	QString password = ui.passwordLineEdit->text();

	if (userData.contains(username) && userData[username].password == password) { //sprawdza poprawnosc danych
		loggedInUsername = username;
		loggedInBalance = userData[username].balance;
		QMessageBox::information(this, "Success", "Successfully logged in");
		accept();
	}
	else {
		QMessageBox::warning(this, "Error", "Wrong login or password");	
	}

	ui.usernameLineEdit->clear();
	ui.passwordLineEdit->clear();
}


void LoginForm::onRegisterButtonClicked()
{
	QString newUsername = ui.registerUsernameLineEdit->text(); //pobiera nazwe usera
	QString newPassword = ui.registerPasswordLineEdit->text(); //pobiera haslo

	if (newUsername.isEmpty() || newPassword.isEmpty()) {
		QMessageBox::warning(this, "Error", "Cannot be empty");
		return;
	}

	if (userData.contains(newUsername)) {
		QMessageBox::warning(this, "Error", "User already exists");
		return;
		ui.registerUsernameLineEdit->clear();
		ui.registerPasswordLineEdit->clear();
	}

	userData[newUsername] = { newPassword, 0.0 }; //dodaje nowego usera
	saveUserData("users.txt"); //zapisuje do pliku
	QMessageBox::information(this, "Success", "Successfully registered");

	ui.registerUsernameLineEdit->clear();
	ui.registerPasswordLineEdit->clear();
}

void LoginForm::updateUserBalance(const QString& username, double newBalance)
{
	if (userData.contains(username)) {
		userData[username].balance = newBalance;
		saveUserData("users.txt");
	}
}