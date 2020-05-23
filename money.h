#pragma once
#include <iostream>
#include <fstream>
#include <cassert>
class Money {

private:
	long long rubles;
	unsigned long long pennies;


public:


	Money(long rub = 0, long long pen = 0) :
		rubles(rub), pennies(pen)
	{
		assert(pen >= 0);
	}

	~Money() {

		std::cout << "Вы закрыли счет: " << rubles << "." << pennies << " рублей" << std::endl;

	}

	Money& operator= (const Money &money)
	{

		rubles = money.rubles;
		pennies = money.pennies;

		// Для цепочки присваиваний
		return *this;
	}

	friend const Money operator*(const Money& left, double chislo);
	friend const Money operator/(const Money& left, double chislo);
	friend const Money operator+(const Money& left, const Money& right);
	friend const Money operator-(const Money& left, const Money& right);
	friend std::ostream& operator<< (std::ostream &out, const Money &money);
	friend std::istream& operator>> (std::istream &in, Money &money);

	friend bool operator== (const Money& left, const Money& right);
	friend bool operator!= (const Money& left, const Money& right);
	friend bool operator>= (const Money& left, const Money& right);
	friend bool operator> (const Money& left, const Money& right);
	friend bool operator<= (const Money& left, const Money& right);
	friend bool operator< (const Money& left, const Money& right);
};