#include <iostream>
#include <cstdlib>

#include "Pedometer2.h"

//сброс мусора для корректного ввода
void flush()
{
	while (std::cin.get() != '\n') { continue; }
}

int main()   //главная функция
{
	system("chcp 1251");
	Pedometer a("2000-01-01", "00:00");//задаем в конструкторе начальную дату и время
	while (true)
	{
		std::system("cls");
		std::cout << "\n                    МЕНЮ : \n"
			<< "\n     Получить начальную дату и время-------------1"
			<< "\n     Добавить запись-----------------------------2"
			<< "\n     Получить подсчет шагов ---------------------3"
			<< "\n     Среднее число шагов (всего)-----------------4"
			<< "\n     Среднее число шагов (месяц)-----------------5"
			<< "\n     Максимум шагов (всего)----------------------6"
			<< "\n     Максимум шагов (месяц)----------------------7"
			<< "\n     Сохранить в файл ---------------------------8"
			<< "\n     Считать из файла ---------------------------9"
			<< "\n     Выход-----------------------------------иначе";

		std::cout << "\n\n Для выполнения операции введите нужную цифру\n";
		auto ch = std::cin.get();
		flush();
		switch (ch)
		{
		case '1':
		{
			std::cout << "Начальная дата: " << a.getInitialDate() << '\n';
			std::cout << "Начальное время: " << a.getInitialTime() << '\n';
			break;
		}
		case '2':
		{
			std::string date, time1, time2;
			std::size_t count;
			std::cout << "Введите дату в формате (yyyy-mm-dd): ";
			std::cin >> date;
			std::cout << "Введите время начала интервала в формате (hh:mm): ";
			std::cin >> time1;
			std::cout << "Введите время конца интервала в формате (hh:mm): ";
			std::cin >> time2;
			std::cout << "Введите количество шагов:";
			std::cin >> count;
			if (a.addItem(date, time1, time2, count))
			{
				std::cout << "Запись добавлена\n";
			}
			else
			{
				std::cout << "Не удалось добавить запись \n";
			}
			flush();
			break;
		}
		case '3':
		{
			std::cout << "Получение подсчета по дате и времени\n";
			std::string date, time1, time2;
			std::cout << "Введите дату в формате (yyyy-mm-dd): ";
			std::cin >> date;
			std::cout << "Введите время начала интервала в формате (hh:mm): ";
			std::cin >> time1;
			std::cout << "Введите время конца интервала в формате (hh:mm): ";
			std::cin >> time2;
			auto value = a.getValue("2013-11-21", "10:58", "12:59");
			if (value)
			{
				std::cout << "Количество шагов = " << value << '\n';
			}
			else
			{
				std::cout << "Запись не обнаружена\n";
			}
			flush();
			break;
		}
		case '4':
		{
			std::cout << "Получение среднего числа шагов\n";
			auto value = a.getAverage();
			if (value != -1)
			{
				std::cout << "Среднее количество шагов = " << value << '\n';
			}
			else
			{
				std::cout << "Записи не обнаружены\n";
			}

			break;
		}
		case '5':
		{
			std::cout << "Получение среднего числа шагов в месяце\n";
			std::string date, time1, time2;
			std::cout << "Введите дату в формате (yyyy-mm): ";
			std::cin >> date;
			auto value = a.getAverage(date);
			if (value != -1)
			{
				std::cout << "Среднее количество шагов = " << value << '\n';
			}
			else
			{
				std::cout << "Записи не обнаружены\n";
			}
			flush();
			break;
		}
		case '6':
		{
			std::cout << "Получение максимального числа шагов\n";
			auto value = a.getMaximum();
			if (!value.second.empty())
			{
				std::cout << "Максимальное количество шагов = " << value.first << " сделано " << value.second << '\n';
			}
			else
			{
				std::cout << "Записи не обнаружены\n";
			}

			break;
		}
		case '7':
		{
			std::cout << "Получение максимального числа шагов в месяце\n";
			std::string date, time1, time2;
			std::cout << "Введите дату в формате (yyyy-mm): ";
			std::cin >> date;
			auto value = a.getMaximum(date);
			if (!value.second.empty())
			{
				std::cout << "Максимальное количество шагов = " << value.first << " сделано " << value.second << '\n';
			}
			else
			{
				std::cout << "Записи не обнаружены\n";
			}
			flush();
			break;
		}
		case '8':
		{
			std::string fname;
			std::cout << "Введите имя файла для сохранения :";
			std::cin >> fname;
			if (a.toFile(fname))
			{
				std::cout << "Данные сохранены\n";
			}
			else
			{
				std::cout << "Не удалось сохранить данные\n";
			}
			flush();
			break;
		}
		case '9':
		{
			std::string fname;
			std::cout << "Введите имя файла для загрузки данных :";
			std::cin >> fname;
			try
			{
				Pedometer b(fname);
				a = b;
				std::cout << "Данные загружены\n";
			}
			catch (...)
			{
				std::cout << "Не удалось загрузить данные\n";
			}
			flush();
			break;
		}
		default:
		{
			return 0;
		}
		}

		std::cout << "\nДля продолжения нажмите клавишу\n";
		std::cin.get();
	}
}