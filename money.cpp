#include "money.h"
#include <iostream>

const Money operator+(const Money& left, const Money& right) {
	long long r, k, all = 0;
	if (left.rubles < 0) all -= left.pennies;
	else all += left.pennies;
	if (right.rubles < 0) all -= right.pennies;
	else all += right.pennies;
	all += (left.rubles + right.rubles) * 100;
	r = all / 100;
	k = abs(all) % 100;
	return  Money(r, k);
}

const Money operator-(const Money& left, const Money& right) {
	long long r, k, all = 0;
	if (left.rubles < 0) all -= left.pennies;
	else all += left.pennies;
	if (right.rubles < 0) all += right.pennies;
	else all -= right.pennies;
	all += (left.rubles - right.rubles) * 100;
	r = all / 100;
	k = abs(all) % 100;
	return  Money(r, k);
}

const Money operator*(const Money& left, double chislo) {
	long long r, k, all = 0;
	if (left.rubles < 0) all -= left.pennies;
	else all += left.pennies;
	all += (left.rubles * 100);
	all *= chislo;
	r = all / 100;
	k = abs(all) % 100;
	return  Money(r, k);
}

const Money operator/(const Money& left, double chislo) {
	long long r, k, all = 0;
	if (left.rubles < 0) all -= left.pennies;
	else all += left.pennies;
	all += (left.rubles * 100);
	all /= chislo;
	r = all / 100;
	k = abs(all) % 100;
	return  Money(r, k);
}

bool operator== (const Money& left, const Money& right) {
	if (left.rubles == right.rubles && left.pennies == right.pennies) return 1;
	else return 0;
}

bool operator!= (const Money& left, const Money& right) {
	return !(left == right);
}

bool operator>= (const Money& left, const Money& right) {
	if (left == right || left.rubles > right.rubles || left.rubles == right.rubles && left.pennies > right.pennies) return 1;
	else return 0;
}

bool operator<= (const Money& left, const Money& right) {
	return !(left >= right);
}

bool operator> (const Money& left, const Money& right) {
	if (left.rubles > right.rubles || left.rubles == right.rubles && left.pennies > right.pennies) return 1;
	else return 0;
}

bool operator< (const Money& left, const Money& right) {
	return !(left > right);
}

std::ostream& operator<< (std::ostream &out, const Money &money) {

	out << money.rubles << "." << money.pennies << " рублей";

	return out;
}

std::istream& operator>> (std::istream &in, Money &money)
{
	long long prepennies;
	std::cout << "Введите рубли: ";
	in >> money.rubles;
	std::cout << "Введите копейки: ";
	in >> prepennies;
	if (prepennies >= 100) {
		money.pennies = (prepennies % 100);
		money.rubles += (prepennies / 100);
	}
	else if (prepennies < 0) {
		std::cout << "Количество копеек должно быть больше или равно 0." << std::endl;
	}
	else {
		money.pennies = prepennies;
	}
	return in;
}