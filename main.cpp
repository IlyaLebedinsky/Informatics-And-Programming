#include <iostream>
#include <iomanip>
#include <list>
#include <string>
#include <windows.h>
#include <time.h>

using namespace std;

const int emk_bank = 2000;    // ������� ������ ���������
const int max_kup = 40;       // Max ���-�� ����� ������/�����


class ProcCenter
{
protected:
	list<string> nom_kart;
	list<string> fio;
	list<int> sum;
	list<string> pin;

public:
	// ����������� ��� ����������
	ProcCenter()
	{
		// ������ �� ������
	}

	// ����������
	~ProcCenter()
	{
		nom_kart.clear();
		fio.clear();
		sum.clear();
		pin.clear();
	}

	// ���������� ����� ����� �� ��������� �������
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

	// ���������� ��� ��������� �������
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

	// ���������� ����� ��������� �������
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

	// ���������� ����� ��������� �������
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

	// ��������� ����� �� ���� �������
	void add_sum(int ind, int sm)
	{
		int i = 0;
		for (auto iter = sum.begin(); iter != sum.end(); iter++)
		{
			if (ind == i)
			{
				// ����� ������ ����
				int nsum = *iter + sm;
				sum.erase(iter);
				if (sum.empty()) sum.push_front(nsum);             // ���� ������ ������
				else if (iter == sum.end()) sum.push_back(nsum);   // ���� �������� ��������� �� ����� ������
				else sum.insert(iter, nsum);                       // ����� ��������� �� �������� �����
				break;
			}
			else i++;
		}
	}

	// ��������� ����� �� �����
	void sub_sum(int ind, int sm)
	{
		int i = 0;
		for (auto iter = sum.begin(); iter != sum.end(); iter++)
		{
			if (ind == i)
			{
				// ����� ������ ����
				int nsum = *iter - sm;
				if (nsum < 0) nsum = 0;
				sum.erase(iter);
				if (sum.empty()) sum.push_front(nsum);           // ���� ������ ������
				else if (iter == sum.end()) sum.push_back(nsum); // ���� �������� ��������� �� ����� ������
				else sum.insert(iter, nsum);                     // ����� ��������� �� �������� �����
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
	// ����������� ��� ����������
	Bankomat() : ProcCenter()
	{
		// 80% �������� ���� �����
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

	// ����������
	~Bankomat()
	{
		// ������ ������
		kas100.clear();
		kas200.clear();
		kas500.clear();
		kas1000.clear();
		kas2000.clear();
		kas5000.clear();
	}

	// ������ �������� �������
	list<int> give(int sum)
	{
		list<int> s;
		int ss = 0;

		// ��������� ���� �� ������ � �������
		if (ProcCenter::get_sum(indKart) < sum)
		{
			s.clear();
			return s;
		}

		while (!kas5000.empty() && (sum - ss) >= 5000)
		{
			ss += 5000;
			s.push_back(5000);              // ������� ������
			s.push_back(kas5000.back());    // ��������� ������ � �������������
			kas5000.pop_back();             // ������� ������ �� ������ ���������
		}

		while (!kas2000.empty() && (sum - ss) >= 2000)
		{
			ss += 2000;
			s.push_back(2000);              // ������� ������
			s.push_back(kas2000.back());    // ��������� ������ � �������������
			kas2000.pop_back();             // ������� ������ �� ������ ���������
		}

		while (!kas1000.empty() && (sum - ss) >= 1000)
		{
			ss += 1000;
			s.push_back(1000);              // ������� ������
			s.push_back(kas1000.back());    // ��������� ������ � �������������
			kas1000.pop_back();             // ������� ������ �� ������ ���������
		}

		while (!kas500.empty() && (sum - ss) >= 500)
		{
			ss += 500;
			s.push_back(500);               // ������� ������
			s.push_back(kas500.back());     // ��������� ������ � �������������
			kas500.pop_back();              // ������� ������ �� ������ ���������
		}

		while (!kas200.empty() && (sum - ss) >= 200)
		{
			ss += 200;
			s.push_back(200);               // ������� ������
			s.push_back(kas200.back());     // ��������� ������ � �������������
			kas200.pop_back();              // ������� ������ �� ������ ���������
		}

		while (!kas100.empty() && (sum - ss) >= 100)
		{
			ss += 100;
			s.push_back(100);               // ������� ������
			s.push_back(kas100.back());     // ��������� ������ � �������������
			kas100.pop_back();              // ������� ������ �� ������ ���������
		}

		if (ss == sum && s.size() <= max_kup * 2)
		{
			// ��������� �� ����� �������
			ProcCenter::sub_sum(indKart, sum);

			// �������� ������
			return s;
		}
		else
		{
			// �� ������ ������� ������ �����, ���� ����� ������ 40
			// ���������� ������ � ��������
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

	// ������� �������� � �������
	int receive(list<int> sum)
	{
		if (sum.size() > max_kup * 2) return -7;

		int err = 0;

		int sch5000 = 0, sch2000 = 0, sch1000 = 0, sch500 = 0, sch200 = 0, sch100 = 0;

		auto iter = sum.begin();
		while (iter != sum.end())
		{
			// 5000 ��� ������
			if (*iter == 5000)
			{
				if (kas5000.size() >= emk_bank)
				{
					err = -1;   // ������������ ������ 5000 ��� �����
					break;
				}
				iter++;
				kas5000.push_back(*iter); sch5000++;
				iter++;
			}

			// 2000 ��� ������
			if (iter != sum.end() && *iter == 2000)
			{
				if (kas2000.size() >= emk_bank)
				{
					err = -2;   // ������������ ������ 2000 ��� �����
					break;
				}
				iter++;
				kas2000.push_back(*iter); sch2000++;
				iter++;
			}

			// 1000 ��� ������
			if (iter != sum.end() && *iter == 1000)
			{
				if (kas1000.size() >= emk_bank)
				{
					err = -3;   // ������������ ������ 1000 ��� �����
					break;
				}
				iter++;
				kas1000.push_back(*iter); sch1000++;
				iter++;
			}

			// 500 ��� ������
			if (iter != sum.end() && *iter == 500)
			{
				if (kas500.size() >= emk_bank)
				{
					err = -4;   // ������������ ������ 500 ��� �����
					break;
				}
				iter++;
				kas500.push_back(*iter); sch500++;
				iter++;
			}

			// 200 ������
			if (iter != sum.end() && *iter == 200)
			{
				if (kas200.size() >= emk_bank)
				{
					err = -5;   // ������������ ������ 200 ��� �����
					break;
				}
				iter++;
				kas200.push_back(*iter); sch200++;
				iter++;
			}

			// 100 ������
			if (iter != sum.end() && *iter == 100)
			{
				if (kas100.size() >= emk_bank)
				{
					err = -6;   // ������������ ������ 100 ��� �����
					break;
				}
				iter++;
				kas100.push_back(*iter); sch100++;
				iter++;
			}
		}

		// ���� ������ ����� ������ �������
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
		// ����� ���������� ������ �� ���� �������
		else
		{
			int s2 = 5000 * sch5000 + 2000 * sch2000 + 1000 * sch1000 + 500 * sch500 + 200 * sch200 + 100 * sch100;
			ProcCenter::add_sum(indKart, s2);
			return 0;    // ���������� ����������
		}
	}

	// ������ ���� � ������� ����� � ���������
	list<int> sost_bank()
	{
		list<int> s;

		s.push_back(5000);             // 5000 ���
		s.push_back(kas5000.size());
		s.push_back(2000);             // 2000 ���
		s.push_back(kas2000.size());
		s.push_back(1000);             // 1000 ���
		s.push_back(kas1000.size());
		s.push_back(500);              //  500 ���
		s.push_back(kas500.size());
		s.push_back(200);              //  200 ���
		s.push_back(kas200.size());
		s.push_back(100);              //  100 ���
		s.push_back(kas100.size());

		return s;
	}

	// �������� ����� � ���������� � ����
	string init_kart() 
	{
		// ����� �����
		string aa = to_string(rand() % 10) + to_string(rand() % 10) + to_string(rand() % 10) + to_string(rand() % 10);
		ProcCenter::nom_kart.push_back(aa);

		// ��� ���������
		cout << "������� �.�.�. ��������� �����: ";
		cin.ignore(32767, '\n');
		getline(cin, aa);
		ProcCenter::fio.push_back(aa);

		// ����� ����� �� �����
		int sm;
		do
		{
			cout << "������� ����� ����� � ������ �� ����� (�� ����� 3 ���): ";
			cin >> sm;
		} while (sm < 0 || sm > 3000000);
		ProcCenter::sum.push_back(sm);

		// ��� ���
		do
		{
			cout << "������� PIN-��� (4-� ����� �� 0 �� 9): ";
			cin >> aa;
		} while (aa.length() != 4);
		ProcCenter::pin.push_back(aa);

		return ProcCenter::nom_kart.back();   // ����� ����� ��������� �����
	}

	// ������� ����� �� �������
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
			// ����� �����
			if (*iter == nk)
			{
				Kart = nk;
				indKart = sch;

				npar = 0;
				do
				{
					// 3-� ������� �� ���� PIN-����
					if (npar >= 3)
					{
						// ����� �������������
						prlock_pin = true;
						return -2;
					}
					cout << "������� PIN-��� ����� (4-� ����� �� 0 �� 9): ";
					cin >> aa;
					npar++;
				} while (aa != ProcCenter::get_pin(sch));
				break;
			}
			else sch++;
		}

		if (Kart.length() == 0) return -1;   // ����� �� �������
		else return 0;                       // �������� ��������    
	}

	// ������� �����
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

	// ������ ��������� ����� �������
	int print_kart()
	{
		if (Kart.length() > 0)
		{
			cout << "������� ����: " << ProcCenter::get_sum(indKart) << endl;
			return 0;
		}
		else return -1;
	}

	// ����� ���������� �� ����� �� ������� �����
	int info_kart()
	{
		if (Kart.length() > 0)
		{
			cout << "����� �����   : " << ProcCenter::get_nom_kart(indKart) << endl;
			cout << "�.�.�. �������: " << ProcCenter::get_fio(indKart) << endl;
			cout << "����� �� ��� : " << ProcCenter::get_sum(indKart) << endl;
			cout << "PIN-���       : " << ProcCenter::get_pin(indKart) << endl;
			return 0;
		}
		else return -1;
	}

	// ������ ��� Kart
	string get_Kart() { return Kart; }

	// ������ ��� prlock_pin
	bool get_prlock_pin() { return prlock_pin; }
};


// �������� �������
int main()
{
	int sm;                            // ����� ��� ������
	string rej;                        // ����� ������  
	string sum;                        // ����� ��� ������
	list<int> sp;                      // ������ ��� ������
	Bankomat myb;                      // ����� ��������

	system("cls");                     // ������ �������

	SetConsoleCP(1251);                // ������� ����� � �������
	SetConsoleOutputCP(1251);          
	
NACH:
	rej = "n";
	while (rej != "1" && rej != "2" && rej != "3" && rej != "4" && rej != "5" && 
		   rej != "6" && rej != "7" && rej != "8" && rej != "q")
	{
		cout << "������ ������:\n";
		cout << "1 - ������� ����� �������\n";
		cout << "2 - ������� ����� �� �������\n";
		cout << "3 - ������� ����� �������\n";
		cout << "4 - ����������� ��������� ����� �������\n";
		cout << "5 - ����� ������� �� ������ �����\n";
		cout << "6 - ������ ������� ��������\n";
		cout << "7 - ������� �������� �� �������\n";
		cout << "8 - ������� ���������� � ������� ����� � ���������\n";
		cout << "q - ����� �� ���������\n";
		cout << "������� ����� ������: ";
		cin >> rej;                            // ���� ������ ������
	}

	if (rej == "q") goto EXT;                  // ����� �� ���������

	// ������� ����� �������
	if (rej == "1")
	{
		string sum = myb.init_kart();
		cout << "������� ����� �: " << sum << endl;
		goto NACH;
	}

	// ������� ����� �������
	if (rej == "2")
	{
		// �������� ������� ����� � ���������
		if (myb.get_Kart().length() > 0 && !myb.get_prlock_pin())
		{
			cout << "� ��������� ������� ����������� � �� ��������������� �����.\n";
			goto NACH;
		}

		cout << "������� ����� �����: ";
		cin >> sum;
		int res = myb.ins_kart(sum);
		switch (res)
		{
		case -2: cout << "����� �������������.\n"; break;
		case -1: cout << "����� �� �������.\n"; break;
		case 0: cout << "����� ������� ����������.\n"; break;
		}
		goto NACH;
	}

	// ������� ����� �������
	if (rej == "3")
	{
		// �������� ������� ����� � ���������
		if (myb.get_Kart().length() == 0)
		{
			cout << "����� �� ���������.\n";
			goto NACH;
		}
		if (myb.get_prlock_pin())
		{
			cout << "����� �������������.\n";
			goto NACH;
		}

		if (myb.izvl_kart() == 0)
		{
			cout << "����� ������� ���������.\n";
		}
		else cout << "����� ��� � ���������.\n";

		goto NACH;
	}

	// ����������� ��������� ����� �������
	if (rej == "4")
	{
		// �������� ������� ����� � ���������
		if (myb.get_Kart().length() == 0)
		{
			cout << "����� �� ���������.\n";
			goto NACH;
		}
		if (myb.get_prlock_pin())
		{
			cout << "����� �������������.\n";
			goto NACH;
		}

		if (myb.print_kart() != 0)
		{
			cout << "����� ��� � ���������.\n";
		}

		goto NACH;
	}

	// ����� ������� �� ������ �����
	if (rej == "5")
	{ 
		// �������� ������� ����� � ���������
		if (myb.get_Kart().length() == 0)
		{
			cout << "����� �� ���������.\n";
			goto NACH;
		}
		if (myb.get_prlock_pin())
		{
			cout << "����� �������������.\n";
			goto NACH;
		}

		if (myb.info_kart() != 0)
		{
			cout << "����� ��� � ���������.\n";
		}
		
		goto NACH;
	}
		
	// ������ ��������
	if (rej == "6")
	{
		// �������� ������� ����� � ���������
		if (myb.get_Kart().length() == 0)
		{ 
			cout << "����� �� ���������.\n";
			goto NACH;
		}
		if (myb.get_prlock_pin())
		{
			cout << "����� �������������.\n";
			goto NACH;
		}

		do
		{
			cout << "������� ����� ��� ������ (����� ����� ������� 100 ���): ";
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
					cout << "�������� ������:\n";
					cout << setw(7) << *iter << " ��� - ";
					iter++;
					cout << "�" << *iter << endl;
				}
				else
				{
					cout << setw(7) << *iter << " ��� - ";
					iter++;
					cout << "�" << *iter << endl;
				}
				iter++;
			}
		}
		else
		{
			cout << "������ ��������� ����� ����������.\n";
		}
		goto NACH;
	}

	// ���� �������� �� �������
	if (rej == "7")
	{
		// �������� ������� ����� � ���������
		if (myb.get_Kart().length() == 0)
		{
			cout << "����� �� ���������.\n";
			goto NACH;
		}
		if (myb.get_prlock_pin())
		{
			cout << "����� �������������.\n";
			goto NACH;
		}

		sp.clear();
		int sum, k5000 = 0, k2000 = 0, k1000 = 0, k500 = 0, k200 = 0, k100 = 0;
		do
		{
			cout << "������� ���������� 5000 ��� �����: "; cin >> k5000;
		} while (k5000 < 0 || k5000 > max_kup);
		sum = k5000;
		if (sum < max_kup)
		{
			do
			{
				cout << "������� ���������� 2000 ��� �����: "; cin >> k2000;
			} while (k2000 < 0 || (sum + k2000) > max_kup);
			sum += k2000;
		}
		if (sum < max_kup)
		{
			do
			{
				cout << "������� ���������� 1000 ��� �����: "; cin >> k1000;
			} while (k1000 < 0 || (sum + k1000) > max_kup);
			sum += k1000;
		}
		if (sum < max_kup)
		{
			do
			{
				cout << "������� ���������� 500 ��� �����: "; cin >> k500;
			} while (k500 < 0 || sum + (k500) > max_kup);
			sum += k500;
		}
		if (sum < max_kup)
		{
			do
			{
				cout << "������� ���������� 200 ��� �����: "; cin >> k200;
			} while (k200 < 0 || (sum + k200) > max_kup);
			sum += k200;
		}
		if (sum < max_kup)
		{
			do
			{
				cout << "������� ���������� 100 ��� �����: "; cin >> k100;
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
		case -7: cout << "���������� ����� �� ����� ���� ������ " << max_kup << endl; break;
		case -6: cout << "������������ ������ 100 ��� �����\n"; break;
		case -5: cout << "������������ ������ 200 ��� �����\n"; break;
		case -4: cout << "������������ ������ 500 ��� �����\n"; break;
		case -3: cout << "������������ ������ 1000 ��� �����\n"; break;
		case -2: cout << "������������ ������ 2000 ��� �����\n"; break;
		case -1: cout << "������������ ������ 5000 ��� �����\n"; break;
		case  0: cout << "�������� ���������� ��������\n"; break;
		}
		goto NACH;
	}

	// ������ ���������� � ������� ����� � ���������
	if (rej == "8")
	{
		// �������� ������� ����� � ���������
		if (myb.get_Kart().length() == 0)
		{
			cout << "����� �� ���������.\n";
			goto NACH;
		}
		if (myb.get_prlock_pin())
		{
			cout << "����� �������������.\n";
			goto NACH;
		}

		sp = myb.sost_bank();
		auto iter = sp.begin();
		while (iter != sp.end())
		{
			if (iter == sp.begin())
			{
				cout << "������ � �������:\n";
				cout << setw(7) << *iter << " ��� - ";
				iter++;
				cout << *iter << " ��.\n";
			}
			else
			{
				cout << setw(7) << *iter << " ��� - ";
				iter++;
				cout << *iter << " ��.\n";
			}
			iter++;
		}
		goto NACH;
	}

EXT:
	cout << "\n������ ��������� ���������.\n";
	system("pause");
	exit(0);
}
