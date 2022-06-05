#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <locale>

using namespace std;

int i = 0;  // Глобальная переменная, которая служит для подсчёта кол-ва депозитов.
int number = 0;

ifstream fin;
ofstream fout;

struct mail {
		int ind1;		// индекс получателя
		char* adr1;		//адрес получателя
		char* name1;		// имя получателя
		char* adr2;		// адрес отправителя
		char* name2;		// имя отправителя
		double cost;		// стоимость письма
	};
struct mail* mailBase = new struct mail[i];

int controlInd() {
	cout << "Введите индекс получателя (индекс должен состоять из шести цифр): " << endl;
	while (true) { // цикл продолжается до тех пор, пока пользователь не введет корректное значение
		int checkind;
		cin >> checkind;
		if (cin.fail() or (checkind <= 99999) or (checkind  > 999999)) // если предыдущее извлечение оказалось неудачным,
		{
			cin.clear(); // то возвращаем cin в 'обычный' режим работы
			cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
		}
		else // если всё хорошо, то возвращаем checkind
			return checkind;
	}
}

int controlConsent() {
	cout << "Введите 1 если да, и 0, если нет: " << endl;
	while (true) { 
		int checkconsent;
		cin >> checkconsent;

		if (cin.fail() or ((checkconsent != 0) and (checkconsent != 1))) {
			cin.clear(); 
			cin.ignore(32767, '\n'); 
		}
		else 
			return checkconsent;
	}
}

int controlCount() {
	while (true) { 
		int checkcount;
		cin >> checkcount;
		if (cin.fail() or (checkcount <= 0)) {
			cin.clear(); 
			cin.ignore(32767, '\n'); 
		}
		else 
			return checkcount;
	}
}
double controlCost() {
	cout << "Введите цену письма(если число - десятичная дробь, следует отделить дробную часть запятой: " << endl;
	while (true) {
		double checkcost;
		cin >> checkcost;
		if (cin.fail() or (checkcost <= 0.0)) {
			cin.clear(); 
			cin.ignore(32767, '\n'); 
		}
		else 
			return checkcost;
	}
}

char* controlChar() {
	int i;
	char* str;
	str = new char[15];
	char* Obj = new char[15];
	do {
		cin >> str;
		for (i = 0; str[i]; i++)
			if ((str[i] >= '0' and str[i] <= '9' and str[i]) or (str[i] <= '/' and str[i] >= '!') or (str[i] <= '@' and str[i] >= ':') or (str[i] <= '`' and str[i] >= '[') or (str[i] <= '~' and str[i] >= '{'))
				break;
		if (str[i])
			cout << "Введены не буквы(" << endl << "Повторите ввод" << endl;
	} while (str[i]);

	for (i = 0; str[i]; i++) {
		Obj[i] += str[i];
	}
	return Obj;
}

void menu() {
    cout << "==============================" << endl;
    cout << "Доступные действия:" << endl;
    cout << "\t" << "1) Поиск письма по отправителю" << endl;
    cout << "\t" << "2) Фильтр по индексу" << endl;
    cout << "\t" << "3) Сортировать по увеличению стоимости" << endl;
	cout << "\t" << "4) Печать базы" << endl;
	cout << "\t" << "5) Удалить базу" << endl;
	cout << "\t" << "6) Добавить данные" << endl;
	cout << "\t" << "7) Завершение программы" << endl;
    cout << "==============================" << endl;
    cout << "Введите цифру от 1 до 7: " << endl;
    cout << "==============================" << endl << endl;
}

void readBase() {
	number = 0;
	fin.open("Base.txt");
	char buff[50];
	while (number < i) {
		fin >> buff; //считали первое слово
		mailBase[number].ind1 = atoi(buff);
		fin >> buff;
		mailBase[number].adr1 = new char[strlen(buff) + 1];
		strcpy(mailBase[number].adr1, buff);
		fin >> buff;
		mailBase[number].name1 = new char[strlen(buff) + 1];
		strcpy(mailBase[number].name1, buff);
		fin >> buff;
		mailBase[number].adr2 = new char[strlen(buff) + 1];
		strcpy(mailBase[number].adr2, buff);
		fin >> buff;
		mailBase[number].name2 = new char[strlen(buff) + 1];
		strcpy(mailBase[number].name2, buff);
		fin >> buff;
		mailBase[number].cost = atof(buff);
		number++;
	}
	fin.close();
}

void saveBase() {
	fout.open("Base.txt");
	number = 0;
	while (number < i) {
		fout << mailBase[number].ind1 << " " << mailBase[number].adr1 << " " << mailBase[number].name1 << " " << mailBase[number].adr2 << " " << mailBase[number].name2 << " " << mailBase[number].cost << endl;
		number++;
	}
	fout.close();
	number--;
}

void createBase() {
	while (number < i) {
		cout << endl << "Письмо " << number+1 << endl;
		mailBase[number].ind1 = controlInd();
		cout << "Адрес получателя(ГородУлица; БЕЗ ПРОБЕЛОВ): " << endl;
		mailBase[number].adr1 = controlChar();
		cout << "Имя получателя(ИмяФамилия; БЕЗ ПРОБЕЛОВ): " << endl;
		mailBase[number].name1 = controlChar();
		cout << "Введите адрес отправителя(ГородУлица; БЕЗ ПРОБЕЛОВ): " << endl;
		mailBase[number].adr2 = controlChar();
		cout << "Введите имя отправителя(ИмяФамилия; БЕЗ ПРОБЕЛОВ)" << endl;
		mailBase[number].name2 = controlChar();
		mailBase[number].cost = controlCost();
		number++;
	}
	number--;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	ifstream in("Base.txt");
	string s;
	int command=0;
	int consent;
	int count;

	while (in.peek() != EOF) {
		getline(in,s);
		i++;
	}

	if (i == 0) {
		cout << "Файл пуст" << endl << "Создать новую базу? Если нет, то программа завершится" << endl;
		consent = controlConsent();
		if (consent == 1) {
			cout << "Введите количество писем, данные о которых вы хотите внести: " << endl;
			i = controlCount();
			number = 0;
			while (number < i) {
				cout << endl << "Письмо " << number + 1 << endl;
				mailBase[number].ind1 = controlInd();
				cout << "Адрес получателя(ГородУлица; БЕЗ ПРОБЕЛОВ): " << endl;
				mailBase[number].adr1 = controlChar();
				cout << "Имя получателя(ИмяФамилия; БЕЗ ПРОБЕЛОВ): " << endl;
				mailBase[number].name1 = controlChar();
				cout << "Введите адрес отправителя(ГородУлица; БЕЗ ПРОБЕЛОВ): " << endl;
				mailBase[number].adr2 = controlChar();
				cout << "Введите имя отправителя(ИмяФамилия; БЕЗ ПРОБЕЛОВ)" << endl;
				mailBase[number].name2 = controlChar();
				mailBase[number].cost = controlCost();
				number++;
			}
			number--;
			saveBase();
		}
		else
			exit(0);
	}
	if (i != 0 || consent == 1) {
		while (command != 7) {
			menu();
			cin >> command;
			if (command == 1) {
				char* foundname2;
				count = 0;
				cout << "Введите имя отправителя(ИмяФамилия; БЕЗ ПРОБЕЛОВ): " << endl;
				foundname2 = controlChar();
				number = 0;
				while (number < i) {
					if (mailBase[number].name2 == foundname2) {
						count++;
						cout << mailBase[number].ind1 << " " << mailBase[number].adr1 << " " << mailBase[number].name1 << " " << mailBase[number].adr2 << " " << mailBase[number].name2 << " " << mailBase[number].cost << endl;
					}
					number++;
				}
				number--;
				if (count == 0) {
					cout << "Не найдено писем, отправленных этим человеком" << endl;
				}
			}
			if (command == 2) {
				int foundind;
				count = 0;
				foundind = controlInd();
				number = 0;
				while (number < i) {
					if (mailBase[number].ind1 == foundind) {
						count++;
						cout << mailBase[number].ind1 << " " << mailBase[number].adr1 << " " << mailBase[number].name1 << " " << mailBase[number].adr2 << " " << mailBase[number].name2 << " " << mailBase[number].cost << endl;
					}
					number++;
				}
				number--;
				if (count == 0) {
					cout << "Не найдено писем с данным индексом" << endl;
				}
			}
			if (command == 3) {
				for (int j = 0; j < i - 1; j++) {
					for (int l = j + 1; l < i; l++)
						if (mailBase[j].cost < mailBase[l].cost) {
							swap(mailBase[j], mailBase[l]);
						}
				}
				saveBase();
			}
			if (command == 4) {
				readBase();
				cout << "Вывод:" << endl;
				number = 0;
				while (number < i) {
					cout << number+1 << " " << mailBase[number].ind1 << " " << mailBase[number].adr1 << " " << mailBase[number].name1 << " " << mailBase[number].adr2 << " " << mailBase[number].name2 << " " << mailBase[number].cost << endl;
					number++;
				}
				number--;
			}
			if (command == 5) {
				cout << "Удалить существующую базу? Если да, то в этом случае ее невозможно будет восстановить" << endl;
				consent = controlConsent();
				if (consent == 1) {
					fout.open("Base.txt", ofstream::out | ofstream::trunc);
					fout.close();
					cout << "База успешно удалена" << endl;
				}
				else
					cout << "Удаление отменено" << endl;
			}
			if (command == 6) {
				cout << "Введите количество писем, которые желаете добавить:" << endl;
				int newi;
				newi = controlCount();
				i = i + newi;
				number++;
				while (number < i) {
					cout << endl << "Письмо " << number + 1 << endl;
					mailBase[number].ind1 = controlInd();
					cout << "Адрес получателя(ГородУлица; БЕЗ ПРОБЕЛОВ): " << endl;
					mailBase[number].adr1 = controlChar();
					cout << "Имя получателя(ИмяФамилия; БЕЗ ПРОБЕЛОВ): " << endl;
					mailBase[number].name1 = controlChar();
					cout << "Введите адрес отправителя(ГородУлица; БЕЗ ПРОБЕЛОВ): " << endl;
					mailBase[number].adr2 = controlChar();
					cout << "Введите имя отправителя(ИмяФамилия; БЕЗ ПРОБЕЛОВ)" << endl;
					mailBase[number].name2 = controlChar();
					mailBase[number].cost = controlCost();
					number++;
				}
				number--;
				saveBase();
			}
		}
		if (command == 7) {
			exit(0);
		}
	}
}
