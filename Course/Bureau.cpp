//
//  Bureau.cpp
//  Algorithms
//
//  Created by Aleksandr on 3/8/25.
//

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <set>

#include "Tree.cpp"
#include "Hashtable.cpp"
#include "List.cpp"
#include "Date.cpp"

class Bureau {
/*
 !!! Данные о клиентах должны быть организованны в виде АВЛ-дерева поиска, упорядоченного по «номеру водительского удостоверения».

 !!! Данные об автомобилях должны быть организованны в виде хеш-таблицы, первичным ключом которой является «Государственный регистрационный номер». Метод хеширования определяется вариантом задания.
 */
private:
	Tree* client_tree; // клиентская база изначально пустая
private:
	Hash_table cars_table = Hash_table();
private:
	LinkedList* rent_list;

public:
	// MARK: Операции с клиентами
	// TODO: - 61 BB 123123 == 61 BB 123123 НЕДОПУСТИМО добавлять одинаковые номера. Должны решать коллизии хэш функций, но номера должны быть разные
	void client_registration() {
		string card_number = input_card_number();
		string full_name = input_str("Введите ФИО клиента:");
		string passport = input_string_digits_with_space("Введите паспортные данные клиента:");
		string address = default_str("Введите адрес клиента:");
		Client client = Client(card_number, full_name, passport, address);
		// Ввод данных и регистрация клиента в дереве
		if (client_tree == NULL) {
			client_tree = new Tree(client);
			cout << "Клиент добавлен!" << endl << endl;
			return;
		}
		if (client_tree->search(client_tree, card_number).card_number == "-1") {
			client_tree->insert(client_tree, client);
			cout << "Клиент добавлен!" << endl << endl;
		} else {
			cout << "Клиент уже зарегистрирован!" << endl << endl;
		}
	}

	void remove_client() {
		// Ввод данных и удаление клиента из дерева
		if (client_tree == NULL) {
			cout << "Список пуст" << endl << endl;
			return;
		}
		string card_number = input_card_number();
		client_tree->remove(client_tree, card_number);
		cout << endl;
	}

	void print_clients() {
		// Просмотр всех клиентов из дерева
		if (client_tree == NULL) {
			cout << "Список пуст" << endl << endl;
			return;
		};
		cout << "Клиенты:" << endl;
		cout << "------------------------------------------------------------------" << endl;
		client_tree->show(client_tree);
		cout << endl;
	}

	// TODO: - ЗАМЕЧАНИЕ remove_all_clients
	/*
	 При снятии с обслуживания клиента должны быть уч-
	 тены и обработаны ситуации, когда у клиента имеется выданный
	 автомобиль. Аналогичным образом следует поступать и с удалени-
	 ем сведений об автомобилях.
	 */
	void remove_all_clients() {
		if (client_tree == NULL) {
			cout << "Список пуст" << endl << endl;
			return;
		};
		client_tree->remove_all(client_tree);
		cout << "Успешное удаление!" << endl << endl;
	}

	void search_client() {
		string card_number = input_card_number();
		client_tree->show(client_tree);
		Client client = client_tree->search(client_tree, card_number);
		cout << "Найденный клиент: " << endl;
		cout << "Номер водительского удостоверения: " << client.card_number << endl;
		cout << "ФИО: " << client.full_name << endl;
		cout << "Документы: " << client.passport << endl;
		cout << "Адрес: " << client.address << endl;
		if (rent_list) {
			Rent result_rent = rent_list->search_by_card_number(client.card_number);
			if (!result_rent.regisration_number.empty()) {
				cout << "Государственный регистрационный номер авто: " << result_rent.regisration_number << endl;
			}
		}
		cout << "----------------------------------" << endl << endl;
	}

	void search_clients_fullname() {
		string full_name = input_str("Введите ФИО клиента(или часть ФИО):");
		search_clients(client_tree, full_name, true);
		cout << endl;
	}

	void search_clients_address() {
		string address = default_str("Введите адрес клиента(или часть адреса):");
		search_clients(client_tree, address, false);
		cout << endl;
	}

	// MARK: Операции с авто

//	– добавление нового автомобиля; +
//	– удаление сведений об автомобиле; +
//	– просмотр всех имеющихся автомобилей; +
//	– очистку данных об автомобилях; +

//	– поиск автомобиля по «Государственному регистрационному номеру».
//	Результаты поиска – все сведения о найденном автомобиле, а также ФИО и номер водительского удостоверения клиента,
//	которому выдан этот автомобиль; +

//	– поиск автомобиля по названию марки автомобиля. Результаты поиска – список найденных автомобилей
//	с указанием «Государственный регистрационный номер», марки, цвета, года выпуска; +

	void add_new_car() {
		string regisration_number = input_registration_number();
		string brand = input_str("Введите марку авто:");
		string color = input_str("Введите цвет авто:");
		int release_year = input_int("Введите год выпуска авто:");
		Car car = Car(regisration_number, brand, color, release_year);
		cars_table.insert(car);
		cout << "Автомобиль добавлен!" << endl << endl;
	}

	void remove_car() {
		string registration_number = input_registration_number();
		cars_table.remove(registration_number);
		cout << endl;
	}

	void print_cars() {
		cars_table.print();
	}

	// TODO: - ЗАМЕЧАНИЕ remove_all_cars
	/*
	 При снятии с обслуживания клиента должны быть уч-
	 тены и обработаны ситуации, когда у клиента имеется выданный
	 автомобиль. Аналогичным образом следует поступать и с удалени-
	 ем сведений об автомобилях.
	 */
	void remove_all_cars() {
		cars_table.remove_all();
		cout << "Успешное удаление" << endl << endl;
	}

	//	– поиск автомобиля по «Государственному регистрационному номеру».
	//	Результаты поиска – все сведения о найденном автомобиле, а также ФИО и номер водительского удостоверения клиента,
	//	которому выдан этот автомобиль;
	void search_car_by_reg_number() {
		string regisration_number = input_registration_number();
		Car search_car = cars_table.search(regisration_number);
		if (search_car.registration_number == "-1") {
			cout << "Автомобиль не найден" << endl;
			return;
		}
		cout << "Найденный автомобиль:" << endl;
		cout << "Государственный регистрационный номер: " << search_car.registration_number << endl;
		cout << "Марка автомобиля: " << search_car.brand << endl;
		cout << "Цвет автомобиля: " << search_car.color << endl;
		cout << "Год выпуска: " << search_car.release_year << endl;
		cout << "В наличии: " << (search_car.is_available ? "Да" : "Нет") << endl;
		if (rent_list) {
			string card_number = rent_list->search_by_reg_number(search_car.registration_number).card_number;
			if (!card_number.empty()) {
				cout << "Номер водительского удостоверения клиента: " << card_number << endl;
				cout << "ФИО клиента: ";
				cout << (client_tree->search(client_tree, card_number).full_name) << endl;
			}
		}
		cout << endl;
	}

	//	– поиск автомобиля по названию марки автомобиля.
	// Результаты поиска – список найденных автомобилей с указанием «Государственный регистрационный номер», марки, цвета, года выпуска;
	void searh_car_by_brand() {
		string brand = input_str("Введите марку авто(или часть марки авто):");
		vector<Car> search_cars = cars_table.search_by_brand(brand);
		if (search_cars.empty()) {
			cout << "Автомобили не найдены" << endl << endl;
			return;
		}
		cout << "Найденные автомобили:" << endl;
		cout << "----------------------------------" << endl;
		for (Car car : search_cars) {
			cout << "Найденный автомобиль:" << endl;
			cout << "Государственный регистрационный номер: " << car.registration_number << endl;
			cout << "Марка автомобиля: " << car.brand << endl;
			cout << "Цвет автомобиля: " << car.color << endl;
			cout << "Год выпуска: " << car.release_year << endl;
			cout << "В наличии: " << (car.is_available ? "Да" : "Нет") << endl;
			cout << "----------------------------------" << endl;
		}
		cout << endl;
	}
	// MARK: Операции с прокатным сервисом (RENT, LIST)
	/*
	 – регистрацию отправки автомобиля в ремонт;
	 – регистрацию прибытия автомобиля из ремонта;
	 – регистрацию выдачи клиенту автомобиля на прокат;
	 – регистрацию возврата автомобиля от клиентов.

	 9.2.12. Регистрация отправки автомобиля на ремонт должна
	 осуществляться только при наличии этого автомобиля (значение
	 поля «Признак наличия» для соответствующего автомобиля име-
	 ет значение «Истина»). При этом значение поля «Признак нали-
	 чия» для соответствующего автомобиля изменяется на значение
	 «Ложь».
	 9.2.13. При регистрации прибытия автомобиля из ремонта зна-
	 чение поля «Признак наличия» для соответствующего автомобиля
	 изменяется на значение «Истина».

	 9.2.14. Регистрация выдачи автомобиля клиенту должна осу-
	 ществляться только при наличии свободного выдаваемого автомо-
	 били (значение поля «Признак наличия» для соответствующего ав-
	 томобиля имеет значение «Истина»).
	 9.2.15. При регистрации выдачи автомобиля клиенту или воз-
	 врата автомобиля от клиента должно корректироваться значение
	 поля «Признак наличия» для соответствующего автомобиля.
	 */

	void car_to_rent() {
		string regisration_number = input_registration_number();
		Car car = cars_table.search(regisration_number);
		if (car.registration_number == "-1") {
			cout << "Автомобиль отсутствует в базе!" << endl;
			return;
		}
		if (!car.is_available) {
			cout << "Автомобиль недоступен для аренды" << endl;
			return;
		}
		string card_number = input_card_number();
		Date date_of_issue = input_date(true, "Введите дату дату принятия авто");
		Date date_of_return;
		bool success = false;
		while (!success) {
			date_of_return = input_date(false, "Введите дату дату возврата авто");
			success = correct_date(date_of_issue, date_of_return);
		};

		string date_of_issue_str = to_string(date_of_issue.day) + "." + to_string(date_of_issue.month) + "." + to_string(date_of_issue.year);

		string date_of_return_str = to_string(date_of_return.day) + "." + to_string(date_of_return.month) + "." + to_string(date_of_return.year);

		cout << "Дата передачи: " << date_of_issue_str << endl << "Дата возврата: " << date_of_return_str << endl;
		Rent rent = Rent(card_number, regisration_number, date_of_issue_str, date_of_return_str);
		if (rent_list == NULL) {
			rent_list = new LinkedList(rent);
		} else {
			rent_list->append(rent);
		}
		cars_table.change(regisration_number, false);
	}

	void car_from_rent() {
		string regisration_number = input_registration_number();
		Car car = cars_table.search(regisration_number);
		if (car.registration_number == "-1") {
			cout << "Автомобиль отсутствует в базе!" << endl;
			return;
		}
		if (car.is_available) {
			cout << "Автомобиль уже находится в бюро" << endl;
			return;
		}

		if (rent_list == NULL) {
			cout << "Автомобиль не брали в аренду" << endl;
			return;
		}

		if (rent_list->search_by_reg_number(regisration_number).regisration_number == "-1") {
			cout << "Автомобиль не брали в аренду" << endl;
			return;
		}

		rent_list->remove(regisration_number);
		if (rent_list->size == 0) {
			delete rent_list;
		}
		cars_table.change(regisration_number, true);
		cout << endl;
	}

	void car_to_repair() {
		repair_operations("Сдали авто на ремонт", "Автомобиль недоступен для ремонта", true);
	}

	void car_from_repair() {
		repair_operations("Успешный возврат авто из ремонта", "Автомобиль уже находится в бюро", false);
	}

	void print_rent() {
		rent_list->print();
	}

	// MARK: - Тестовые добавления клиентов и машин
	void testing_add_clients() {
		// RR AA NNNNNN
//		set<string> chars {"A", "B", "E", "K", "M", "H", "O", "P", "C", "T", "Y", "X"};
		if (client_tree != NULL) return;
		Client client1 = Client("11 BB 111111", "Afonin Aleksandr Romanovich", "1234 123456", "Dunaiskii prospekt 121");
		Client client2 = Client("22 AA 222222", "Petrov Petr Petrovich", "1234 123456", "Nevskii 12");
		Client client3 = Client("33 EE 333333", "Ivanov Ivan", "1234 123456", "Nevskii 123");
		Client client4 = Client("44 MM 444444", "Alekseev Aleksei", "1234 123456", "Dunaiskii prospekt 1");
		Client client5 = Client("55 CC 555555", "Afonin Oleg Olegovich", "1234 123456", "Sadovaya 123");
		client_tree = new Tree(client3);
		client_tree->insert(client_tree, client5);
		client_tree->insert(client_tree, client2);
		client_tree->insert(client_tree, client4);
		client_tree->insert(client_tree, client1);
		cout << "Клиенты добавлены!" << endl << endl;
	}
// E333KM-33 	11 BB 111111	26.3.2025 	27.3.2025
	void testing_add_cars() {
		// ANNNAA-NN
		//		set<string> chars {"A", "B", "E", "K", "M", "H", "O", "P", "C", "T", "Y", "X"};
		Car car1 = Car("A111XY-11", "BMW", "red", 1999);
		if (cars_table.search(car1.registration_number).registration_number != "-1") return;
		Car car2 = Car("B222TC-22", "Audi", "blue", 2020);
		Car car3 = Car("E333KM-33", "Lada", "green", 2023);
		Car car4 = Car("O444PC-44", "Nissan", "blue", 2014);
		Car car5 = Car("T555AB-55", "Niva", "gray", 2009);
		cars_table.insert(car1);
		cars_table.insert(car2);
		cars_table.insert(car3);
		cars_table.insert(car4);
		cars_table.insert(car5);
		cout << "Автомобили добавлены!" << endl << endl;

	}
	// MARK: - Приватные функции
private:
	void search_clients(Tree* tree, string search_value, bool is_fio) {
		vector<Client> array = client_tree->search_by_rule(client_tree, search_value, is_fio);
		if (array.size() == 0) {
			cout << "Клиентов не найдено" << endl;
			return;
		}
		cout << "Найденный клиенты:" << endl;
		cout << "----------------------------------" << endl;
		for (Client client: array) {
			cout << "Номер водительского удостоверения: " << client.card_number << endl;
			cout << "ФИО: " << client.full_name << endl;
			cout << "Документы: " << client.passport << endl;
			cout << "Адрес: " << client.address << endl;
			cout << "----------------------------------" << endl;
		}
		cout << endl;
	}

	string input_str(string description)
	{
		string value;
		while (true)
		{
			cout << description << " ";
			cin >> value;
			if (!is_valid_string_value(value))
			{
				cin.clear(); // Очищаем ошибочное состояние
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очищаем буфер перед getline
				cout << "Ошибка! Введенные данные должны содержать только буквы." << endl;
			} else {
				return value;
			}
		}
	}

	string default_str(string description)
	{
		string value;
		cout << description << " ";
		getline(cin, value);
		return value;
	}

	string input_string_digits_with_space(string description) {
		string value;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		while (true)
		{
			cout << description << " ";
			getline(cin, value);
			bool is_error = false;
			for (char ch : value) {
				if (is_error) continue;
				if (ch != ' ' && !isdigit(ch)) {
					cin.clear(); // Очищаем ошибочное состояние
					cout << "Ошибка!" << endl;
					is_error = true;
				}
			}
			if (!is_error) break;
		}
		return value;
	}

	int input_int(string description) {
		int value;
		while (true)
		{
			cout << description << " ";
			cin >> value;
			if (cin.fail())
			{
				cin.clear(); // Очищаем ошибочное состояние
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очищаем буфер перед getline
				cout << "Ошибка! Введенные данные должны содержать только целое число." << endl;
			} else {
				return value;
			}
		}
	}

	bool is_valid_string_value(string str) {
		for (char element : str) {
			if (isdigit(element)) return false;
		}
		return true;
	}

// MARK: - Приватные функции для работы с клиентом
	string input_card_number() {
		string card_number;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		while (true) {
			cout << "Введите номер водительского удостоверения клиента в формате RR AA NNNNNN: ";
			getline(cin, card_number);
			if (is_correct_card_number(card_number)) {
				return card_number;
			} else {
				cout << "Ошибка ввода!" << endl;
			}
		}
		return card_number;
	}

	bool is_correct_card_number(string card_number) {
		if (card_number.size() != 12) return false;
		string region;
		string serial;
		string number;

		bool is_region = true;
		bool is_serial = false;
		bool is_number = false;

		for (char ch: card_number) {
			bool is_space = ch == ' ';

			if (is_space && is_region) {
				is_serial = true;
				is_region = false;
				continue;
			} else if (is_space && is_serial) {
				is_number = true;
				is_serial = false;
				continue;
			}

			if (is_region) {
				region += ch;
			}
			else if (is_serial) {
				serial += ch;
			}
			else if (is_number) {
				number += ch;
			}
		}
		return correct_serial(serial) && correct_number(number) && correct_region(region);
	}

	bool correct_serial(string serial) {
		set<string> chars {"A", "B", "E", "K", "M", "H", "O", "P", "C", "T", "Y", "X"};
		for (char ch: serial) {
			if (!chars.contains(string(1, ch))) return false;
		}
		return true;
	}
	bool correct_number(string number) {
		return is_only_digit(number);
	}

	bool correct_region(string number) {
		return is_only_digit(number);
	}
	bool is_only_digit(string number) {
		for (char ch: number) {
			if (!isdigit(ch)) {
				return false;
			}
		}
		return true;
	}

	// MARK: - Приватные функции для авто
	// Государственный регистрационный номер – строка формата
	// «ANNNAA-NN», где N –цифра; A – буква из следующего множества:
	// A, B, E, K, M, H, O, P, C, T, Y, X;
	string input_registration_number() {
		string reg_number;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		while (true) {
			cout << "Введите государственный регистрационный номер в формате ANNNAA-NN: ";
			getline(cin, reg_number);
			if (is_correct_registration_number(reg_number)) {
				return reg_number;
			} else {
				cout << "Ошибка ввода!" << endl;
			}
		}
		return reg_number;
	}

	// Формат: ANNNAA-NN
	bool is_correct_registration_number(string value) {
		if (value.size() != 9) return false;
		set<string> chars {"A", "B", "E", "K", "M", "H", "O", "P", "C", "T", "Y", "X"};
		int index = 0;
		for (char element : value) {
			if (index == 0 || index == 4 || index == 5) {
				// Если недопустимые буквы выходим
				if (!chars.contains(string(1, element))) return false;
			} else if (index == 6) {
				// Если не дефис выходим
				if (element !=  '-') return false;
			} else {
				// Если не цифра выходим
				if (!isdigit(element)) return false;
			}
			index++;
		}
		return true;
	}

	// MARK: - Приватные для работы с арендой/возвратом
	Date input_date(bool is_issue, string description) {
		int day;
		int month;
		int year;
		while (true) {
			cout << description << " в формате DD MM YYYY: ";
			cin >> day >> month >> year;
			if (cin.fail())
			{
				cin.clear(); // Очищаем ошибочное состояние
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очищаем буфер перед getline
				cout << "Ошибка! Введенные данные должны содержать только целое число." << endl;
			} else {
				if (is_issue && year != 2025) {
					cin.clear(); // Очищаем ошибочное состояние
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очищаем буфер перед getline
					cout << "Ошибка! Нужно ввести текущий год - 2025" << endl;
					continue;
				}

				if (month > 12 || month < 1) {
					cin.clear(); // Очищаем ошибочное состояние
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очищаем буфер перед getline
					cout << "Ошибка! Нужно ввести месяц в диапазоне [1,12]" << endl;
					continue;
				}

				if (day > 31 || day < 1) {
					cin.clear(); // Очищаем ошибочное состояние
					cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очищаем буфер перед getline
					cout << "Ошибка! Нужно ввести день в диапазоне [1, 31]" << endl;
					continue;
				}
				break;
			}
		}
		return Date(day, month, year);
	}

	bool correct_date(Date issue_date, Date return_date) {
		if (issue_date.day == return_date.day && issue_date.month == return_date.month && issue_date.year == return_date.year) {
			cout << "Даты не должны быть равны!" << endl;
			return false; // 11.11.1995 - 11.11.1995 - Fail
		}

		if (issue_date.year > return_date.year) {
			cout << "Год принятия не должен превышать год возврата!" << endl;
			return false; // 11.10.1997 - 11.10.1995 - Fail
		}

		if ((issue_date.month > return_date.month) &&
			(issue_date.year == return_date.year)) {
			cout << "Некорректная дата возврата!" << endl;
			return false; // 11.11.1995 - 11.10.1995 - Fail
		}

		if ((issue_date.day > return_date.day) &&
			(issue_date.month == return_date.month) &&
			(issue_date.year == return_date.year)) {
			cout << "Некорректная дата возврата!" << endl;
			return false; // 12.11.1995 - 11.11.1995 - Fail
		}

		// 11.11.1993 - 12.11.1993 - OK
		return true;
	}

	void repair_operations(string success_desc, string fail_disc, bool to_repair) {
		string regisration_number = input_registration_number();
		Car car = cars_table.search(regisration_number);
		if (car.registration_number == "-1") {
			cout << "Автомобиль отсутствует в базе!" << endl;
			return;
		}

		if ((to_repair && !car.is_available) || (!to_repair && car.is_available)) {
			cout << fail_disc << endl;
			return;
		}

		cars_table.change(regisration_number, !to_repair);
		cout << success_desc << endl << endl;
	}
/*
 – регистрацию нового клиента; +
 – снятие с обслуживания клиента; +
 – просмотр всех зарегистрированных клиентов; +
 – очистку данных о клиентах; +
 – поиск клиента по «номер водительского удостоверения». Результаты поиска – все сведения о найденном клиенте и государственный регистрационный номер автомобиля, который ему выдан; +
 – поиск клиента по фрагментам ФИО или адреса. Результаты поиска – список найденных клиентов с указанием номера водительского удостоверения, ФИО и адреса; +

 57


 – регистрацию отправки автомобиля в ремонт;
 – регистрацию прибытия автомобиля из ремонта;
 – регистрацию выдачи клиенту автомобиля на прокат;
 – регистрацию возврата автомобиля от клиентов
 */
};
//
//int main() {
//	Bureau* bureau = new Bureau();
//	bureau->car_to_rent();
//
//	return 0;
//}
//	Bureau b = Bureau();
//	b.addNewCar("A321BD-42");
//	b.addNewCar("A321BD-42");

//	Client client1;
//	client1.address = "client1.address";
//	client1.card_number = "1";
//	client1.full_name = "client1.full_name";
//	client1.passport = "client1.passport";
//
//	Client client3;
//	client3.address = "client2.address";
//	client3.card_number = "3";
//	client3.full_name = "client2.full_name";
//	client3.passport = "client2.passport";
//
//	Client client4;
//	client4.address = "client3.address";
//	client4.card_number = "4";
//	client4.full_name = "client3.full_name";
//	client4.passport = "client3.passport";
//
//	Client client5;
//	client5.address = "client4.address";
//	client5.card_number = "5";
//	client5.full_name = "client4.full_name";
//	client5.passport = "client4.passport";
//
//	Client client6;
//	client6.address = "client5.address";
//	client6.card_number = "6";
//	client6.full_name = "client5.full_name";
//	client6.passport = "client5.passport";
//
//
//	Client client7;
//	client7.address = "client5.address";
//	client7.card_number = "7";
//	client7.full_name = "client5.full_name";
//	client7.passport = "client5.passport";
//
//	Client client8;
//	client8.address = "client5.address";
//	client8.card_number = "8";
//	client8.full_name = "client5.full_name";
//	client8.passport = "client5.passport";

//	Client client8;
//	client8.address = "client5.address";
//	client8.card_number = "8";
//	client8.full_name = "client5.full_name";
//	client8.passport = "client5.passport";

//	Tree* tree = nullptr;
//	tree->insert(tree, client6);
//	tree->insert(tree, client3);
//	tree->insert(tree, client7);
//	tree->insert(tree, client1);
//	tree->insert(tree, client4);
//	tree->insert(tree, client5);
//	tree->insert(tree, client8);
//	tree->show(tree);
//	tree->remove(tree, "3");
//	tree->show(tree);
//	Client search_client = tree->search(tree, "4");

// MARK: - ХЭЩ ТАБЛИЦА
//	Hash_table hash = Hash_table();
//	Car car = Car("1111", "BMW", "RED", 2022, true);
//	hash.insert(car);
//
//	Car car2 = Car("2222", "MERS", "BLUE", 2022, true);
//	hash.insert(car2);
//
//	Car car3 = Car("3333", "MERS", "BLUE", 2022, true);
//	hash.insert(car3);
//
//
//	Car car4 = Car("4444", "MERS", "BLUE", 2022, true);
//	hash.insert(car4);
//
//
//
//	Car car5 = Car("5555", "MERS", "BLUE", 2022, true);
//	hash.insert(car5);
//
//
//	Car car6 = Car("6666", "MERS", "BLUE", 2022, true);
//	Car car7 = Car("6666", "MERS2", "BLUE2", 2022, true);
//	hash.insert(car6);
//	hash.insert(car7);
//	hash.print();
//	hash.search(car6);
//	hash.remove(car6);
//	hash.search(car6);
//	hash.print();
//	hash.remove(car6);
//	hash.search(car6);
//	hash.print();
//	cout << "=====" << endl;
//	hash.remove(car);
//	hash.remove(car3);
//	hash.remove(car4);
//	hash.remove(car5);
//	hash.remove(car6);
//	hash.remove(car5);
//	hash.print();
//
//	hash.insert(car);
//	hash.insert(car);
//	hash.insert(car);
//	hash.insert(car);
//	hash.insert(car);
//	hash.print();
//	hash.insert(car2);
//	hash.insert(car2);
//	hash.insert(car2);
//	hash.print();
//	hash.remove(car2);
//	hash.remove(car2);
//	hash.print();

	// Номер водительского удостоверения – строка формата «RR AA NNNNNN», где
	// RR – код региона (цифры);
	// AA – серия (буквы из следующего множества: А, В, Е, К, М, Н, О, Р, С, Т, У, Х);
	// NNNNNN – порядковый номер удостоверения (цифры). Код, серия и номер отделяются друг от друга пробелами;

	// MARK: - is_correct_card_number
//	cout << "Корректный ли номер?: "<< client8.is_correct_card_number("22 A4 123456") << endl;
//	cout << "=========" << endl;
//	cout << (tree->search(tree, "7") ? "YES" : "NO   7") << endl;
//	cout << "=========" << endl;
//	cout << (tree->search(tree, "6") ? "YES" : "NO   6") << endl;
//	cout << "=========" << endl;
//	cout << (tree->search(tree, "5") ? "YES   5" : "NO   5") << endl;
//	cout << "=========" << endl;
//	cout << (tree->search(tree, "4") ? "YES" : "NO   4") << endl;
//	cout << "=========" << endl;
//	cout << (tree->search(tree, "3") ? "YES" : "NO   3") << endl;
//	cout << "=========" << endl;
//	cout << (tree->search(tree, "2") ? "YES" : "NO   2") << endl;
//	cout << "=========" << endl;
//	cout << (tree->search(tree, "9") ? "YES" : "NO   9") << endl;
//	cout << "=========" << endl;
//	cout << (tree->search(tree, "1") ? "YES 1" : "NO   9") << endl;

// MARK: - LINKED LIST
//	Rent rent1 = Rent("1111", "1111", "1111", "1111");
//	Rent rent2 = Rent("2222", "2222", "2222", "2222");
//	Rent rent6 = Rent("2222", "2222", "2222", "2222");
//	Rent rent7 = Rent("3333", "3333", "3333", "3333");
//	Rent rent8 = Rent("3333", "3333", "3333", "3333");
//
//	Rent rent3 = Rent("3333", "3333", "3333", "3333");
//	Rent rent4 = Rent("4444", "4444", "4444", "4444");
//
//	LinkedList list = LinkedList(rent4);
////	list.append(rent2);
////	list.append(rent7);
////	list.append(rent1);
////	list.append(rent3);
////	list.append(rent8);
////	list.append(rent6);
//	list.remove(rent4.regisration_number);
//	list.print();
//	list.search(rent2.regisration_number);
//	list.remove(rent1.regisration_number);
//	list.remove(rent4.regisration_number);
//	list.remove(rent3.regisration_number);
//	list.remove(rent2.regisration_number);

//	cout << "Высота: " << tree->get_height(tree) << endl;
//	tree = tree->big_rotate_right(tree);
//	cout << "====" << endl;
//	tree->show(tree);

	//


//	Bureau bureau = Bureau();
//	bureau.client_registration("1", "Afonin");
//	bureau.client_registration("2", "Ivanov");
//	bureau.client_registration("3", "Petukhov");
//	bureau.client_registration("4", "Ologev");
//	bureau.client_registration("5", "Ivanova");
//	bureau.print_clients();
////	bureau.remove_all();
//	bureau.print_clients();
////	bureau.add_new_car("5555");
//	bureau.print_cars();
//	bureau.add_new_rent("3", "5555");
//	bureau.print_rent();
//	bureau.search_client("4");
//	bureau.search_clients_fullname("Ivanov");
//	bureau.search_clients_address("1");
//	bureau.search_clients_address("10");


//	bureau.add_new_car();

//	По данному числу N определите количество последовательностей из нулей и единиц длины N, в которых никакие три единицы не стоят рядом.
//	235
//
//
//	return 0;
//}

/*
 1 Предметная область: Обслуживание клиентов в бюро проката автомобилей (см. п. 9.2)
 1 Метод хеширования: Закрытое хеширование с линейным опробованием
 0 Метод сортировки: Подсчетом
 0 Вид списка: Линейный однонаправленный
 1 Метод обхода дерева: Обратный
 1 Алгоритм поиска слова в тексте: Прямой
 */

/*
 9.2.1. Информационная система для предметной области «Обслу-
 живание клиентов в бюро проката автомобилей» должна осущест-
 влять ввод, хранение, обработку и вывод данных о:
 – клиентах;
 – автомобилях, принадлежащих бюро проката;
 – выдаче на прокат и возврате автомобилей от клиентов.
 9.2.2. Данные о каждом клиенте должны содержать:
 – Номер водительского удостоверения – строка формата «RR AA
 NNNNNN», где RR – код региона (цифры); AA – серия (буквы из сле-
 дующего множества: А, В, Е, К, М, Н, О, Р, С, Т, У, Х); NNNNNN –
 порядковый номер удостоверения (цифры). Код, серия и номер отде-
 ляются друг от друга пробелами;
 – ФИО – строка;
 – Паспортные данные – строка;
 – Адрес – строка.
 Примечание: длина строк (кроме номер водительского удостове-
 рения) определяется студентом самостоятельно.
 9.2.3. Данные о клиентах должны быть организованны в виде
 АВЛ-дерева поиска, упорядоченного по «номеру водительского удо-
 стоверения».
 9.2.4. Данные о каждом автомобиле должны содержать:
 – Государственный регистрационный номер – строка формата
 «ANNNAA-NN», где N –цифра; A – буква из следующего множества:
 А, В, Е, К, М, Н, О, Р, С, Т, У, Х;
 – Марку – строка;
 – Цвет – строка;
 – Год выпуска – целое;
 – Признак наличия – логическое.
 Примечание: длина строк (кроме «Государственного регистраци-
 онного номера») определяется студентом самостоятельно.
 9.2.5. Данные об автомобилях должны быть организованны в ви-
 де хеш-таблицы, первичным ключом которой является «Государ-
 ственный регистрационный номер». Метод хеширования определя-
 ется вариантом задания.
 9.2.6. Данные о выдаче на прокат или возврате автомобилей от
 клиентов должны содержать:
 – строку, формат которой соответствует аналогичной строке
 в данных о клиентах;
 56
 – Государственный регистрационный номер – строка, формат ко-
 торой соответствует аналогичной строке в данных об автомобилях;
 – Дату выдачи – строка;
 – Дату возврата – строка.
 Примечание: наличие в этих данных записи, содержащей в поле
 «Номер водительского удостоверения» значение X и в поле «Госу-
 дарственный регистрационный номер» значение Y, означает выда-
 чу клиенту с номером водительского удостоверения X автомобиля
 с государственным регистрационным номером Y . Отсутствие такой
 записи означает, что клиенту с номером водительского удостовере-
 ния X не выдавался автомобиль с номером Y .
 9.2.7. Данные о выдаче на прокат или возврате автомобилей от
 клиентов должны быть организованны в виде списка, который упо-
 рядочен по первичному ключу – «Государственный регистрацион-
 ный номер». Вид списка и метод сортировки определяются вариан-
 том задания.
 9.2.8. Информационная система «Обслуживание клиентов в бю-
 ро проката автомобилей» должна осуществлять следующие опе-
 рации:
 – регистрацию нового клиента;
 – снятие с обслуживания клиента;
 – просмотр всех зарегистрированных клиентов;
 – очистку данных о клиентах;
 – поиск клиента по «номер водительского удостоверения». Ре-
 зультаты поиска – все сведения о найденном клиенте и государ-
 ственный регистрационный номер автомобиля, который ему
 выдан;
 – поиск клиента по фрагментам ФИО или адреса. Результаты по-
 иска – список найденных клиентов с указанием номера водитель-
 ского удостоверения, ФИО и адреса;
 – добавление нового автомобиля;
 – удаление сведений об автомобиле;
 – просмотр всех имеющихся автомобилей;
 – очистку данных об автомобилях;
 – поиск автомобиля по «Государственному регистрационному
 номеру». Результаты поиска – все сведения о найденном автомоби-
 ле, а также ФИО и номер водительского удостоверения клиента, ко-
 торому выдан этот автомобиль;
 – поиск автомобиля по названию марки автомобиля. Результа-
 ты поиска – список найденных автомобилей с указанием «Государ-
 ственный регистрационный номер», марки, цвета, года выпуска;
 57
 – регистрацию отправки автомобиля в ремонт;
 – регистрацию прибытия автомобиля из ремонта;
 – регистрацию выдачи клиенту автомобиля на прокат;
 – регистрацию возврата автомобиля от клиентов.
 9.2.9. Состав данных о клиенте или автомобиле, выдаваемых при
 просмотре всех зарегистрированных клиентов или просмотре всех
 автомобилей, принадлежащих бюро проката, определяется студен-
 том самостоятельно, но должен содержать не менее двух полей.
 9.2.10. Метод поиска автомобиля по марке определяется студен-
 том самостоятельно. Выбранный метод необходимо сравнить с аль-
 тернативными методами.
 9.2.11. Поиск клиента по фрагментам ФИО или адреса должен
 осуществляться путем систематического обхода АВЛ-дерева поис-
 ка. Метод обхода определяется вариантом задания. При поиске кли-
 ента по фрагментам ФИО или адреса могут быть заданы как полное
 ФИО или адрес, так и их части (например, только фамилия клиен-
 та без имени и отчества, только название улицы из адреса). Для об-
 наружения заданного фрагмента в полном ФИО или адресе должен
 применяться алгоритм поиска слова в тексте, указанный в вариан-
 те задания.
 9.2.12. Регистрация отправки автомобиля на ремонт должна
 осуществляться только при наличии этого автомобиля (значение
 поля «Признак наличия» для соответствующего автомобиля име-
 ет значение «Истина»). При этом значение поля «Признак нали-
 чия» для соответствующего автомобиля изменяется на значение
 «Ложь».
 9.2.13. При регистрации прибытия автомобиля из ремонта зна-
 чение поля «Признак наличия» для соответствующего автомобиля
 изменяется на значение «Истина».
 9.2.14. Регистрация выдачи автомобиля клиенту должна осу-
 ществляться только при наличии свободного выдаваемого автомо-
 били (значение поля «Признак наличия» для соответствующего ав-
 томобиля имеет значение «Истина»).
 9.2.15. При регистрации выдачи автомобиля клиенту или воз-
 врата автомобиля от клиента должно корректироваться значение
 поля «Признак наличия» для соответствующего автомобиля.
 9.2.16. При снятии с обслуживания клиента должны быть уч-
 тены и обработаны ситуации, когда у клиента имеется выданный
 автомобиль. Аналогичным образом следует поступать и с удалени-
 ем сведений об автомобилях.
 */

