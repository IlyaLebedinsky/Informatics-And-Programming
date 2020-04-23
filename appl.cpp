#include <iostream>
#include <cstdlib>

#include "Pedometer2.h"

//����� ������ ��� ����������� �����
void flush()
{
	while (std::cin.get() != '\n') { continue; }
}

int main()   //������� �������
{
	system("chcp 1251");
	Pedometer a("2000-01-01", "00:00");//������ � ������������ ��������� ���� � �����
	while (true)
	{
		std::system("cls");
		std::cout << "\n                    ���� : \n"
			<< "\n     �������� ��������� ���� � �����-------------1"
			<< "\n     �������� ������-----------------------------2"
			<< "\n     �������� ������� ����� ---------------------3"
			<< "\n     ������� ����� ����� (�����)-----------------4"
			<< "\n     ������� ����� ����� (�����)-----------------5"
			<< "\n     �������� ����� (�����)----------------------6"
			<< "\n     �������� ����� (�����)----------------------7"
			<< "\n     ��������� � ���� ---------------------------8"
			<< "\n     ������� �� ����� ---------------------------9"
			<< "\n     �����-----------------------------------�����";

		std::cout << "\n\n ��� ���������� �������� ������� ������ �����\n";
		auto ch = std::cin.get();
		flush();
		switch (ch)
		{
		case '1':
		{
			std::cout << "��������� ����: " << a.getInitialDate() << '\n';
			std::cout << "��������� �����: " << a.getInitialTime() << '\n';
			break;
		}
		case '2':
		{
			std::string date, time1, time2;
			std::size_t count;
			std::cout << "������� ���� � ������� (yyyy-mm-dd): ";
			std::cin >> date;
			std::cout << "������� ����� ������ ��������� � ������� (hh:mm): ";
			std::cin >> time1;
			std::cout << "������� ����� ����� ��������� � ������� (hh:mm): ";
			std::cin >> time2;
			std::cout << "������� ���������� �����:";
			std::cin >> count;
			if (a.addItem(date, time1, time2, count))
			{
				std::cout << "������ ���������\n";
			}
			else
			{
				std::cout << "�� ������� �������� ������ \n";
			}
			flush();
			break;
		}
		case '3':
		{
			std::cout << "��������� �������� �� ���� � �������\n";
			std::string date, time1, time2;
			std::cout << "������� ���� � ������� (yyyy-mm-dd): ";
			std::cin >> date;
			std::cout << "������� ����� ������ ��������� � ������� (hh:mm): ";
			std::cin >> time1;
			std::cout << "������� ����� ����� ��������� � ������� (hh:mm): ";
			std::cin >> time2;
			auto value = a.getValue("2013-11-21", "10:58", "12:59");
			if (value)
			{
				std::cout << "���������� ����� = " << value << '\n';
			}
			else
			{
				std::cout << "������ �� ����������\n";
			}
			flush();
			break;
		}
		case '4':
		{
			std::cout << "��������� �������� ����� �����\n";
			auto value = a.getAverage();
			if (value != -1)
			{
				std::cout << "������� ���������� ����� = " << value << '\n';
			}
			else
			{
				std::cout << "������ �� ����������\n";
			}

			break;
		}
		case '5':
		{
			std::cout << "��������� �������� ����� ����� � ������\n";
			std::string date, time1, time2;
			std::cout << "������� ���� � ������� (yyyy-mm): ";
			std::cin >> date;
			auto value = a.getAverage(date);
			if (value != -1)
			{
				std::cout << "������� ���������� ����� = " << value << '\n';
			}
			else
			{
				std::cout << "������ �� ����������\n";
			}
			flush();
			break;
		}
		case '6':
		{
			std::cout << "��������� ������������� ����� �����\n";
			auto value = a.getMaximum();
			if (!value.second.empty())
			{
				std::cout << "������������ ���������� ����� = " << value.first << " ������� " << value.second << '\n';
			}
			else
			{
				std::cout << "������ �� ����������\n";
			}

			break;
		}
		case '7':
		{
			std::cout << "��������� ������������� ����� ����� � ������\n";
			std::string date, time1, time2;
			std::cout << "������� ���� � ������� (yyyy-mm): ";
			std::cin >> date;
			auto value = a.getMaximum(date);
			if (!value.second.empty())
			{
				std::cout << "������������ ���������� ����� = " << value.first << " ������� " << value.second << '\n';
			}
			else
			{
				std::cout << "������ �� ����������\n";
			}
			flush();
			break;
		}
		case '8':
		{
			std::string fname;
			std::cout << "������� ��� ����� ��� ���������� :";
			std::cin >> fname;
			if (a.toFile(fname))
			{
				std::cout << "������ ���������\n";
			}
			else
			{
				std::cout << "�� ������� ��������� ������\n";
			}
			flush();
			break;
		}
		case '9':
		{
			std::string fname;
			std::cout << "������� ��� ����� ��� �������� ������ :";
			std::cin >> fname;
			try
			{
				Pedometer b(fname);
				a = b;
				std::cout << "������ ���������\n";
			}
			catch (...)
			{
				std::cout << "�� ������� ��������� ������\n";
			}
			flush();
			break;
		}
		default:
		{
			return 0;
		}
		}

		std::cout << "\n��� ����������� ������� �������\n";
		std::cin.get();
	}
}