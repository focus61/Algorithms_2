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
private:
	Tree* client_tree;
	Hash_table cars_table = Hash_table();
	LinkedList* rent_list;

public:
	// MARK: Операции с клиентами
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
		if (rent_list) {
			Rent result_rent = rent_list->search_by_card_number(card_number);
			if (!result_rent.regisration_number.empty() && result_rent.regisration_number != "-1") {
				cout << "НЕВОЗМОЖНО УДАЛИТЬ: " << card_number << endl;
			} else {
				client_tree->remove(client_tree, card_number);
			}
			cout << endl;
			return;
		}
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

	void remove_all_clients() {

		if (client_tree == NULL) {
			cout << "Список пуст" << endl << endl;
			return;
		};
		Tree* new_tree = nullptr;
		remove_clients(client_tree, new_tree);
		if (new_tree) {
			client_tree = new_tree;
			cout << "Остальные клиенты сняты с обслуживания!" << endl << endl;
		} else {
			delete new_tree;
			cout << "Клиенты сняты с обслуживания!" << endl << endl;
		}
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
			if (!result_rent.regisration_number.empty() && result_rent.regisration_number != "-1") {
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
		if (!cars_table.search(registration_number).is_available) {
			cout << "Невозможно снять с обслуживания авто!" << endl;
		} else {
			cars_table.remove(registration_number);
		}
		cout << endl;
	}

	void print_cars() {
		cars_table.print();
	}

	void remove_all_cars() {
		bool all_deleted = true;
		for (int i = 0; i < cars_table.max_size; i++) {
			Node element = cars_table.table[i];
			if (!element.key.empty() && !element.value.is_available) {
				all_deleted = false;
				cout << "Не удалось снять с обслуживания авто: " << element.value.registration_number << endl;
			} else {
				cars_table.table[i] = Node();
			}
		};
		if (all_deleted) cout << "Успешное удаление всех авто" << endl;
		cout << endl;
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
			rent_list = nullptr;
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
	// E333KM-33 	11 BB 111111
	// A111XY-11 	33 EE 333333
	void testing_add_cars() {
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
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

	void remove_clients(Tree*& tree, Tree*& not_deleted_tree) {
		if (!tree) return;
		remove_clients(tree->left, not_deleted_tree);
		remove_clients(tree->right, not_deleted_tree);
		if (rent_list) {
			Rent result_rent = rent_list->search_by_card_number(tree->client.card_number);
			if (!result_rent.regisration_number.empty() && result_rent.regisration_number != "-1") {
				Car car = cars_table.search(result_rent.regisration_number);
				if (!car.is_available) {
					not_deleted_tree->insert(not_deleted_tree, tree->client);
					cout << "НЕВОЗМОЖНО УДАЛИТЬ: " << tree->client.card_number << endl;
				}
			}
		}
		tree = nullptr;
		delete tree;
		return;
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
};
