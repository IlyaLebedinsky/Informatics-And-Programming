#include <iostream>
#include <string>
#include <cassert>
#include <clocale>
#include "money.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	Money dengi, dengi2(17, 37), dengi3;

	cout << "������������:" << endl;
	cout << endl;

	dengi3 = dengi2;
	cout << dengi3 << endl;

	cout << endl;
	cout << "���� � �����:" << endl;
	cout << endl;

	cin >> dengi;
	cout << "�� ����� �����: " << dengi;

	cout << endl;
	cout << "�������� � ���������:" << endl;
	cout << endl;

	cout << dengi << " + " << dengi2 << " = " << dengi + dengi2 << endl;
	cout << dengi2 << " - " << dengi << " = " << dengi2 - dengi << endl;

	cout << endl;
	cout << "��������� � �������:" << endl;
	cout << endl;

	double chislo;
	cout << "������� �����: ";
	cin >> chislo;

	cout << dengi << " * " << chislo << " = " << dengi * chislo << endl;
	cout << dengi << " / " << chislo << " = " << dengi / chislo << endl;

	cout << endl;
	cout << "���������:" << endl;
	cout << endl;

	cout << dengi << " <= " << dengi2 << " = " << (dengi <= dengi2) << endl;
	cout << dengi << " >= " << dengi2 << " = " << (dengi >= dengi2) << endl;
	cout << dengi << " < " << dengi2 << " = " << (dengi < dengi2) << endl;
	cout << dengi << " > " << dengi2 << " = " << (dengi > dengi2) << endl;
	cout << dengi << " != " << dengi2 << " = " << (dengi != dengi2) << endl;
	cout << dengi << " == " << dengi2 << " = " << (dengi == dengi2) << endl;

	cout << endl;
	cout << "�����������:" << endl;
	cout << endl;

	return 0;
}