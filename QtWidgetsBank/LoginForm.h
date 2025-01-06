#pragma once

#include <QDialog>
#include <QMap>
#include <QString>
#include "ui_LoginForm.h"

//LoginForm dziedziczy po QDialog, reprezentujac okno logowania
class LoginForm : public QDialog {
	Q_OBJECT //Makro Qt
public:
	explicit LoginForm(QWidget* parent = nullptr); //konstruktor klasy LoginForm
	~LoginForm(); //destruktor klasy LoginForm
private slots:
	void onLoginButtonClicked(); //slot obsluguje przycisk logowania
private:
	Ui::LoginForm ui; //obiekt generowany automatycznie przez Qt z .ui

	QMap<QString, QString> userData; //mapa, przechowuje dane userow nazwa:haslo
	void loadUserData(const QString& filePath); //funkcja wczytuje dane z pliku .txt
};