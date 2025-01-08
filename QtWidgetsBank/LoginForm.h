#pragma once

#include <QDialog>
#include <QMap>
#include <QString>
#include "ui_LoginForm.h"


struct UserAccount { //struktura reprezentuj¹ca has³o i saldo
	QString password;
	double balance;
};

//LoginForm dziedziczy po QDialog, reprezentujac okno logowania
class LoginForm : public QDialog {
	Q_OBJECT //Makro Qt
public:
	explicit LoginForm(QWidget* parent = nullptr); //konstruktor klasy LoginForm
	~LoginForm(); //destruktor klasy LoginForm
private slots:
	void onLoginButtonClicked(); //slot obsluguje przycisk logowania
	void onRegisterButtonClicked(); //obsluga rejestracji

private:
	Ui::LoginForm ui; //obiekt generowany automatycznie przez Qt z .ui

	QMap<QString, UserAccount> userData; //mapa, przechowuje dane userow nazwa:haslo:saldo
	void loadUserData(const QString& filePath); //funkcja wczytuje dane z pliku .txt
	void saveUserData(const QString& filePath); //zapisuje do pliku
};