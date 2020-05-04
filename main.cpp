#include <iostream>
#include <iomanip>
#include <list>
#include <string>
#include <windows.h>
#include <time.h>

using namespace std;

const int emk_bank = 2000;    // Ёмкость касеты банкомата
const int max_kup = 40;       // Max кол-во купюр выдачи/приёма


class ProcCenter
{
protected:
	list<string> nom_kart;
	list<string> fio;
	list<int> sum;
	list<string> pin;

public:
	// Конструктор без параметров
	ProcCenter()
	{
		// Ничего не делаем
	}

	// Деструктор
	~ProcCenter()
	{
		nom_kart.clear();
		fio.clear();
		sum.clear();
		pin.clear();
	}

	// Возвращает номер карты по заданному индексу
	string get_nom_kart(int ind)
	{
		int i = 0;
		for (auto iter = nom_kart.begin(); iter != nom_kart.end(); iter++)
		{
			if (ind == i)
			{
				return *iter;
			}
			else i++;
		}
		return string("");
	}

	// Возвращает ФИО заданному индексу
	string get_fio(int ind)
	{
		int i = 0;
		for (auto iter = fio.begin(); iter != fio.end(); iter++)
		{
			if (ind == i)
			{
				return *iter;
			}
			else i++;
		}
		return string("");
	}

	// Возвращает сумму заданному индексу
	int get_sum(int ind)
	{
		int i = 0;
		for (auto iter = sum.begin(); iter != sum.end(); iter++)
		{
			if (ind == i)
			{
				return *iter;
			}
			else i++;
		}
		return 0;
	}

	// Возвращает сумму заданному индексу
	string get_pin(int ind)
	{
		int i = 0;
		for (auto iter = pin.begin(); iter != pin.end(); iter++)
		{
			if (ind == i)
			{
				return *iter;
			}
			else i++;
		}
		return string("");
	}

	// Добавляем сумму на счёт клиента
	void add_sum(int ind, int sm)
	{
		int i = 0;
		for (auto iter = sum.begin(); iter != sum.end(); iter++)
		{
			if (ind == i)
			{
				// нашли нужный счёт
				int nsum = *iter + sm;
				sum.erase(iter);
				if (sum.empty()) sum.push_front(nsum);             // Если список пустой
				else if (iter == sum.end()) sum.push_back(nsum);   // Если итератор указывает на конец списка
				else sum.insert(iter, nsum);                       // Иначе вставляем на удалённое место
				break;
			}
			else i++;
		}
	}

	// Списываем сумму со счёта
	void sub_sum(int ind, int sm)
	{
		int i = 0;
		for (auto iter = sum.begin(); iter != sum.end(); iter++)
		{
			if (ind == i)
			{
				// нашли нужный счёт
				int nsum = *iter - sm;
				if (nsum < 0) nsum = 0;
				sum.erase(iter);
				if (sum.empty()) sum.push_front(nsum);           // Если список пустой
				else if (iter == sum.end()) sum.push_back(nsum); // Если итератор указывает на конец списка
				else sum.insert(iter, nsum);                     // Иначе вставляем на удалённое место
				break;
			}
			else i++;
		}
	}
};


class Bankomat : public ProcCenter
{
private:
	list<int> kas100;
	list<int> kas200;
	list<int> kas500;
	list<int> kas1000;
	list<int> kas2000;
	list<int> kas5000;
	string Kart = "";
	int indKart = 0;
	bool prlock_pin = false;

public:
	// Конструктор без параметров
	Bankomat() : ProcCenter()
	{
		// 80% загрузки всех касет
		for (int i = 0; i < 8 * 200; i++)
		{
			kas100.push_back(rand()  % 2000000 + 1000000);
			kas200.push_back(rand()  % 2000000 + 1000000);
			kas500.push_back(rand()  % 2000000 + 1000000);
			kas1000.push_back(rand() % 2000000 + 1000000);
			kas2000.push_back(rand() % 2000000 + 1000000);
			kas5000.push_back(rand() % 2000000 + 1000000);
		}
	}

	// Деструктор
	~Bankomat()
	{
		// Чистим касеты
		kas100.clear();
		kas200.clear();
		kas500.clear();
		kas1000.clear();
		kas2000.clear();
		kas5000.clear();
	}

	// Выдать наличные клиенту
	list<int> give(int sum)
	{
		list<int> s;
		int ss = 0;

		// Проверяем есть ли деньги у клиента
		if (ProcCenter::get_sum(indKart) < sum)
		{
			s.clear();
			return s;
		}

		while (!kas5000.empty() && (sum - ss) >= 5000)
		{
			ss += 5000;
			s.push_back(5000);              // Номинал купюры
			s.push_back(kas5000.back());    // Добавляем купюру в купюроприёмник
			kas5000.pop_back();             // Удаляем купюру из касеты банкомата
		}

		while (!kas2000.empty() && (sum - ss) >= 2000)
		{
			ss += 2000;
			s.push_back(2000);              // Номинал купюры
			s.push_back(kas2000.back());    // Добавляем купюру в купюроприёмник
			kas2000.pop_back();             // Удаляем купюру из касеты банкомата
		}

		while (!kas1000.empty() && (sum - ss) >= 1000)
		{
			ss += 1000;
			s.push_back(1000);              // Номинал купюры
			s.push_back(kas1000.back());    // Добавляем купюру в купюроприёмник
			kas1000.pop_back();             // Удаляем купюру из касеты банкомата
		}

		while (!kas500.empty() && (sum - ss) >= 500)
		{
			ss += 500;
			s.push_back(500);               // Номинал купюры
			s.push_back(kas500.back());     // Добавляем купюру в купюроприёмник
			kas500.pop_back();              // Удаляем купюру из касеты банкомата
		}

		while (!kas200.empty() && (sum - ss) >= 200)
		{
			ss += 200;
			s.push_back(200);               // Номинал купюры
			s.push_back(kas200.back());     // Добавляем купюру в купюроприёмник
			kas200.pop_back();              // Удаляем купюру из касеты банкомата
		}

		while (!kas100.empty() && (sum - ss) >= 100)
		{
			ss += 100;
			s.push_back(100);               // Номинал купюры
			s.push_back(kas100.back());     // Добавляем купюру в купюроприёмник
			kas100.pop_back();              // Удаляем купюру из касеты банкомата
		}

		if (ss == sum && s.size() <= max_kup * 2)
		{
			// Списываем со счёта клиента
			ProcCenter::sub_sum(indKart, sum);

			// Успешная выдача
			return s;
		}
		else
		{
			// Не смогли собрать нужную сумму, либо купюр больше 40
			// Возвращаем купюры в банкомат
			auto iter = s.begin();
			while (iter != s.end())
			{
				if (*iter == 5000) kas5000.push_back(*(++iter));
				else if (*iter == 2000) kas2000.push_back(*(++iter));
				else if (*iter == 1000) kas1000.push_back(*(++iter));
				else if (*iter == 500) kas500.push_back(*(++iter));
				else if (*iter == 200) kas200.push_back(*(++iter));
				else if (*iter == 100) kas100.push_back(*(++iter));
				else iter++;
				iter++;
			}
			s.clear();
			return s;
		}
	}

	// Принять наличные у клиента
	int receive(list<int> sum)
	{
		if (sum.size() > max_kup * 2) return -7;

		int err = 0;

		int sch5000 = 0, sch2000 = 0, sch1000 = 0, sch500 = 0, sch200 = 0, sch100 = 0;

		auto iter = sum.begin();
		while (iter != sum.end())
		{
			// 5000 руб купюра
			if (*iter == 5000)
			{
				if (kas5000.size() >= emk_bank)
				{
					err = -1;   // Переполнение касеты 5000 руб купюр
					break;
				}
				iter++;
				kas5000.push_back(*iter); sch5000++;
				iter++;
			}

			// 2000 руб купюра
			if (iter != sum.end() && *iter == 2000)
			{
				if (kas2000.size() >= emk_bank)
				{
					err = -2;   // Переполнение касеты 2000 руб купюр
					break;
				}
				iter++;
				kas2000.push_back(*iter); sch2000++;
				iter++;
			}

			// 1000 руб купюра
			if (iter != sum.end() && *iter == 1000)
			{
				if (kas1000.size() >= emk_bank)
				{
					err = -3;   // Переполнение касеты 1000 руб купюр
					break;
				}
				iter++;
				kas1000.push_back(*iter); sch1000++;
				iter++;
			}

			// 500 руб купюра
			if (iter != sum.end() && *iter == 500)
			{
				if (kas500.size() >= emk_bank)
				{
					err = -4;   // Переполнение касеты 500 руб купюр
					break;
				}
				iter++;
				kas500.push_back(*iter); sch500++;
				iter++;
			}

			// 200 купюра
			if (iter != sum.end() && *iter == 200)
			{
				if (kas200.size() >= emk_bank)
				{
					err = -5;   // Переполнение касеты 200 руб купюр
					break;
				}
				iter++;
				kas200.push_back(*iter); sch200++;
				iter++;
			}

			// 100 купюра
			if (iter != sum.end() && *iter == 100)
			{
				if (kas100.size() >= emk_bank)
				{
					err = -6;   // Переполнение касеты 100 руб купюр
					break;
				}
				iter++;
				kas100.push_back(*iter); sch100++;
				iter++;
			}
		}

		// Если ошибка вернём деньги клиенту
		if (err != 0)
		{
			for (int i = 0; i < sch5000; i++) kas5000.pop_back();
			for (int i = 0; i < sch2000; i++) kas2000.pop_back();
			for (int i = 0; i < sch1000; i++) kas1000.pop_back();
			for (int i = 0; i < sch500; i++) kas500.pop_back();
			for (int i = 0; i < sch200; i++) kas200.pop_back();
			for (int i = 0; i < sch100; i++) kas100.pop_back();
			return err;
		}
		// Иначе прибавляем деньги на счёт клиента
		else
		{
			int s2 = 5000 * sch5000 + 2000 * sch2000 + 1000 * sch1000 + 500 * sch500 + 200 * sch200 + 100 * sch100;
			ProcCenter::add_sum(indKart, s2);
			return 0;    // Нормальное завершение
		}
	}

	// Узнать инфу о наличии купюр в банкомате
	list<int> sost_bank()
	{
		list<int> s;

		s.push_back(5000);             // 5000 руб
		s.push_back(kas5000.size());
		s.push_back(2000);             // 2000 руб
		s.push_back(kas2000.size());
		s.push_back(1000);             // 1000 руб
		s.push_back(kas1000.size());
		s.push_back(500);              //  500 руб
		s.push_back(kas500.size());
		s.push_back(200);              //  200 руб
		s.push_back(kas200.size());
		s.push_back(100);              //  100 руб
		s.push_back(kas100.size());

		return s;
	}

	// Создание карты и добавление в базу
	string init_kart() 
	{
		// Номер карты
		string aa = to_string(rand() % 10) + to_string(rand() % 10) + to_string(rand() % 10) + to_string(rand() % 10);
		ProcCenter::nom_kart.push_back(aa);

		// ФИО владельца
		cout << "Введите Ф.И.О. владельца карты: ";
		cin.ignore(32767, '\n');
		getline(cin, aa);
		ProcCenter::fio.push_back(aa);

		// Сумма денег на карте
		int sm;
		do
		{
			cout << "Введите сумму денег в рублях на карте (не более 3 млн): ";
			cin >> sm;
		} while (sm < 0 || sm > 3000000);
		ProcCenter::sum.push_back(sm);

		// Пин код
		do
		{
			cout << "Введите PIN-код (4-е цифры от 0 до 9): ";
			cin >> aa;
		} while (aa.length() != 4);
		ProcCenter::pin.push_back(aa);

		return ProcCenter::nom_kart.back();   // Вернём номер созданной карты
	}

	// Принять карту от клиента
	int ins_kart(string nk)
	{
		int sch = 0;
		int npar;
		string aa;

		Kart = "";
		indKart = 0;
		prlock_pin = false;

		for (auto iter = ProcCenter::nom_kart.begin(); iter != ProcCenter::nom_kart.end(); iter++)
		{
			// Нашли карту
			if (*iter == nk)
			{
				Kart = nk;
				indKart = sch;

				npar = 0;
				do
				{
					// 3-и попытки на ввод PIN-кода
					if (npar >= 3)
					{
						// Карта заблокирована
						prlock_pin = true;
						return -2;
					}
					cout << "Введите PIN-код карты (4-е цифры от 0 до 9): ";
					cin >> aa;
					npar++;
				} while (aa != ProcCenter::get_pin(sch));
				break;
			}
			else sch++;
		}

		if (Kart.length() == 0) return -1;   // Карта не найдена
		else return 0;                       // Успешная операция    
	}

	// Вернуть карту
	int izvl_kart()
	{
		if (Kart.length() > 0)
		{
			Kart = "";
			indKart = 0;
			prlock_pin = false;
			return 0;
		}
		else return -1;
	}

	// Печать состояния счёта клиента
	int print_kart()
	{
		if (Kart.length() > 0)
		{
			cout << "Текущий счёт: " << ProcCenter::get_sum(indKart) << endl;
			return 0;
		}
		else return -1;
	}

	// Поиск информации по карте по номерку карты
	int info_kart()
	{
		if (Kart.length() > 0)
		{
			cout << "Номер карты   : " << ProcCenter::get_nom_kart(indKart) << endl;
			cout << "Ф.И.О. клиента: " << ProcCenter::get_fio(indKart) << endl;
			cout << "Сумма на сёте : " << ProcCenter::get_sum(indKart) << endl;
			cout << "PIN-код       : " << ProcCenter::get_pin(indKart) << endl;
			return 0;
		}
		else return -1;
	}

	// Геттер для Kart
	string get_Kart() { return Kart; }

	// Геттер для prlock_pin
	bool get_prlock_pin() { return prlock_pin; }
};


// Основная функция
int main()
{
	int sm;                            // Сумма для выдачи
	string rej;                        // Режим работы  
	string sum;                        // Сумма для выдачи
	list<int> sp;                      // Список для работы
	Bankomat myb;                      // Класс банкомат

	system("cls");                     // Чистим консоль

	SetConsoleCP(1251);                // Русский текст в консоли
	SetConsoleOutputCP(1251);          
	
NACH:
	rej = "n";
	while (rej != "1" && rej != "2" && rej != "3" && rej != "4" && rej != "5" && 
		   rej != "6" && rej != "7" && rej != "8" && rej != "q")
	{
		cout << "Режимы работы:\n";
		cout << "1 - Создать карту клиента\n";
		cout << "2 - Принять карту от клиента\n";
		cout << "3 - Вернуть карту клиенту\n";
		cout << "4 - Распечатать состояние счёта клиента\n";
		cout << "5 - Найти клиента по номеру карты\n";
		cout << "6 - Выдать клиенту наличные\n";
		cout << "7 - Принять наличные от клиента\n";
		cout << "8 - Вывести информацию о наличии купюр в банкомате\n";
		cout << "q - Выйти из программы\n";
		cout << "Введите режим работы: ";
		cin >> rej;                            // Ввод режима работы
	}

	if (rej == "q") goto EXT;                  // Выход из программы

	// Создать карту клиента
	if (rej == "1")
	{
		string sum = myb.init_kart();
		cout << "Создана карта №: " << sum << endl;
		goto NACH;
	}

	// Принять карту клиента
	if (rej == "2")
	{
		// Проверка наличия карты в банкомате
		if (myb.get_Kart().length() > 0 && !myb.get_prlock_pin())
		{
			cout << "В банкомате имеется вставленная и не заблокированная карта.\n";
			goto NACH;
		}

		cout << "Введите номер карты: ";
		cin >> sum;
		int res = myb.ins_kart(sum);
		switch (res)
		{
		case -2: cout << "Карта заблокирована.\n"; break;
		case -1: cout << "Карта не найдена.\n"; break;
		case 0: cout << "Карта принята банкоматом.\n"; break;
		}
		goto NACH;
	}

	// Вернуть карту клиенту
	if (rej == "3")
	{
		// Проверка наличия карты в банкомате
		if (myb.get_Kart().length() == 0)
		{
			cout << "Карта не вставлена.\n";
			goto NACH;
		}
		if (myb.get_prlock_pin())
		{
			cout << "Карта заблокирована.\n";
			goto NACH;
		}

		if (myb.izvl_kart() == 0)
		{
			cout << "Карта успешно извлечена.\n";
		}
		else cout << "Карты нет в банкомате.\n";

		goto NACH;
	}

	// Распечатать состояние счёта клиента
	if (rej == "4")
	{
		// Проверка наличия карты в банкомате
		if (myb.get_Kart().length() == 0)
		{
			cout << "Карта не вставлена.\n";
			goto NACH;
		}
		if (myb.get_prlock_pin())
		{
			cout << "Карта заблокирована.\n";
			goto NACH;
		}

		if (myb.print_kart() != 0)
		{
			cout << "Карты нет в банкомате.\n";
		}

		goto NACH;
	}

	// Найти клиента по номеру карты
	if (rej == "5")
	{ 
		// Проверка наличия карты в банкомате
		if (myb.get_Kart().length() == 0)
		{
			cout << "Карта не вставлена.\n";
			goto NACH;
		}
		if (myb.get_prlock_pin())
		{
			cout << "Карта заблокирована.\n";
			goto NACH;
		}

		if (myb.info_kart() != 0)
		{
			cout << "Карты нет в банкомате.\n";
		}
		
		goto NACH;
	}
		
	// Выдача наличных
	if (rej == "6")
	{
		// Проверка наличия карты в банкомате
		if (myb.get_Kart().length() == 0)
		{ 
			cout << "Карта не вставлена.\n";
			goto NACH;
		}
		if (myb.get_prlock_pin())
		{
			cout << "Карта заблокирована.\n";
			goto NACH;
		}

		do
		{
			cout << "Введите сумму для выдачи (целое число кратное 100 руб): ";
			cin >> sum;
			sm = atoi(sum.c_str());
		} while (sm < 0 || (sm % 100) != 0);
		
		sp.clear();
		sp = myb.give(sm);
		if (sp.size() != 0)
		{
			auto iter = sp.begin();
			while (iter != sp.end())
			{
				if (iter == sp.begin())
				{
					cout << "Выданные купюры:\n";
					cout << setw(7) << *iter << " руб - ";
					iter++;
					cout << "№" << *iter << endl;
				}
				else
				{
					cout << setw(7) << *iter << " руб - ";
					iter++;
					cout << "№" << *iter << endl;
				}
				iter++;
			}
		}
		else
		{
			cout << "Выдача указанной суммы невозможна.\n";
		}
		goto NACH;
	}

	// Приём наличных от клиента
	if (rej == "7")
	{
		// Проверка наличия карты в банкомате
		if (myb.get_Kart().length() == 0)
		{
			cout << "Карта не вставлена.\n";
			goto NACH;
		}
		if (myb.get_prlock_pin())
		{
			cout << "Карта заблокирована.\n";
			goto NACH;
		}

		sp.clear();
		int sum, k5000 = 0, k2000 = 0, k1000 = 0, k500 = 0, k200 = 0, k100 = 0;
		do
		{
			cout << "Введите количество 5000 руб купюр: "; cin >> k5000;
		} while (k5000 < 0 || k5000 > max_kup);
		sum = k5000;
		if (sum < max_kup)
		{
			do
			{
				cout << "Введите количество 2000 руб купюр: "; cin >> k2000;
			} while (k2000 < 0 || (sum + k2000) > max_kup);
			sum += k2000;
		}
		if (sum < max_kup)
		{
			do
			{
				cout << "Введите количество 1000 руб купюр: "; cin >> k1000;
			} while (k1000 < 0 || (sum + k1000) > max_kup);
			sum += k1000;
		}
		if (sum < max_kup)
		{
			do
			{
				cout << "Введите количество 500 руб купюр: "; cin >> k500;
			} while (k500 < 0 || sum + (k500) > max_kup);
			sum += k500;
		}
		if (sum < max_kup)
		{
			do
			{
				cout << "Введите количество 200 руб купюр: "; cin >> k200;
			} while (k200 < 0 || (sum + k200) > max_kup);
			sum += k200;
		}
		if (sum < max_kup)
		{
			do
			{
				cout << "Введите количество 100 руб купюр: "; cin >> k100;
			} while (k100 < 0 || (sum + k100) > max_kup);
			sum += k100;
		}

		for (int i = 0; i < k5000; i++)
		{
			sp.push_back(5000);
			sp.push_back(rand() % 2000000 + 1000000);
		}
		for (int i = 0; i < k2000; i++)
		{
			sp.push_back(2000);
			sp.push_back(rand() % 2000000 + 1000000);
		}
		for (int i = 0; i < k1000; i++)
		{
			sp.push_back(1000);
			sp.push_back(rand() % 2000000 + 1000000);
		}
		for (int i = 0; i < k500; i++)
		{
			sp.push_back(500);
			sp.push_back(rand() % 2000000 + 1000000);
		}
		for (int i = 0; i < k200; i++)
		{
			sp.push_back(200);
			sp.push_back(rand() % 2000000 + 1000000);
		}
		for (int i = 0; i < k100; i++)
		{
			sp.push_back(100);
			sp.push_back(rand() % 2000000 + 1000000);
		}
		
		int res = myb.receive(sp);
		switch (res)
		{
		case -7: cout << "Количество купюр не может быть больше " << max_kup << endl; break;
		case -6: cout << "Переполнение касеты 100 руб купюр\n"; break;
		case -5: cout << "Переполнение касеты 200 руб купюр\n"; break;
		case -4: cout << "Переполнение касеты 500 руб купюр\n"; break;
		case -3: cout << "Переполнение касеты 1000 руб купюр\n"; break;
		case -2: cout << "Переполнение касеты 2000 руб купюр\n"; break;
		case -1: cout << "Переполнение касеты 5000 руб купюр\n"; break;
		case  0: cout << "Успешное завершение операции\n"; break;
		}
		goto NACH;
	}

	// Узнать информацию о наличии купюр в банкомате
	if (rej == "8")
	{
		// Проверка наличия карты в банкомате
		if (myb.get_Kart().length() == 0)
		{
			cout << "Карта не вставлена.\n";
			goto NACH;
		}
		if (myb.get_prlock_pin())
		{
			cout << "Карта заблокирована.\n";
			goto NACH;
		}

		sp = myb.sost_bank();
		auto iter = sp.begin();
		while (iter != sp.end())
		{
			if (iter == sp.begin())
			{
				cout << "Купюры в наличии:\n";
				cout << setw(7) << *iter << " руб - ";
				iter++;
				cout << *iter << " шт.\n";
			}
			else
			{
				cout << setw(7) << *iter << " руб - ";
				iter++;
				cout << *iter << " шт.\n";
			}
			iter++;
		}
		goto NACH;
	}

EXT:
	cout << "\nРабота программы завершена.\n";
	system("pause");
	exit(0);
}
