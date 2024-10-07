#pragma once
#include <iostream>
#include <string>
#include <sqlite3.h>

class Account
{
private:
	std::string login;
	std::string password;
	int points;

public:
	Account(const std::string& accountLogin, const std::string& accountPassword, int accountPoints = 0);
	Account();

	std::string getLogin() const;
	std::string getPassword() const;
	int getPoints() const;

	void operator+=(int addedPoints);
	void operator-=(int usedPoints);
};