//
//  Hashtable.cpp
//  Algorithms
//
//  Created by Aleksandr on 3/10/25.
//

#include <iostream>
#include "Car.cpp"

using namespace std;

// MARK: - Статичный размер таблицы! Вставка, печать, поиск, удаление, линейное опробование.
class Node {
public:
	// «Государственный регистрационный номер»
	string key;
	Car value;
	bool is_deleted = false;
public:
	Node(string key, Car value): key(key), value(value) {}
public:
	Node(bool is_deleted): key(""), value(Car()), is_deleted(is_deleted) {}
public:
	Node(): key(""), value(Car()), is_deleted(false) {}
};

struct Hash_table {
	vector<Node> table;
	size_t max_size = 100;
public:
	Hash_table(): table(100) {}
	/*
	 1. i = 0
	 2. a = h(key) + i*c
	 3. Если Table(a) свободно или Table(a) удалено, то Table(a) = key,
	 записать элемент, «стоп элемент добавлен»
	 4. i = i + 1, переход к шагу 2.
	 */
	public:
	void insert(Car car) {
		string key = car.registration_number;
		int hashIndex = hash(key, max_size);
		for (int i = 0; i < max_size; i++) {
			int index = linear_probe(hashIndex, i);
			if (table[index].key.empty() || table[index].is_deleted) {
				table[index].key = car.registration_number;
				table[index].value = car;
				Car car1 = table[index].value;
				return;
			}
		}
	}

	/*
	 Удаление элемента:
	 1. i = 0
	 2. a = h(key) + i*c
	 3. Если Table(a) = key, то Table(a) = удалено, «стоп элемент уда-
	 лен»
	 4. Если Table(a) свободно, то «стоп элемент не найден»
	 5. i = i + 1, переход к шагу 2.
	 */
	void remove(string registration_number) {
		const string key = registration_number;
		int hashIndex = hash(key, max_size);
		for (int i = 0; i < max_size; i++) {
			int index = linear_probe(hashIndex, i);
			if (table[index].key == key && !table[index].is_deleted) {
				table[index].is_deleted = /*Node(true)*/true;
				cout << "Успешное удаление автомобиля" << endl;
				return;
			}
			if (table[index].key.empty() && !table[index].is_deleted) {
				cout << "Автомобиль не найден!" << endl;
				return;
			}
		}
	}

	void change(string registration_number, bool is_available) {
		string key = registration_number;
		int hashIndex = hash(key, max_size);
		for (int i = 0; i < max_size; i++) {
			int index = linear_probe(hashIndex, i);
			if (table[index].key == key && !table[index].is_deleted) {
				table[index].value.is_available = is_available;
				return;
			}
		}
	}

	/*
	 1. i = 0
	 2. a = h(key) + i*c
	 3. Если Table(a) = key, то «стоп элемент найден»
	 4. Если Table(a) свободно, то «стоп элемент не найден»
	 5. i = i + 1, переход к шагу 2.
	 */
	Car search(string registration_number) {
		string key = registration_number;
		int hashIndex = hash(key, max_size);
		for (int i = 0; i < max_size; i++) {
			int index = linear_probe(hashIndex, i);
			if (table[index].key == key && !table[index].is_deleted) return table[index].value;
			if (table[index].key.empty()) return Car();
		}
		return Car();
	}

	vector<Car> search_by_brand(string search_value) {
		vector<Car> result;
		for (int i = 0; i < max_size; i++) {
			if (!table[i].is_deleted && contains(table[i].value.brand, search_value)) {
				result.push_back(table[i].value);
			}
		}
		return result;
	}

	void print() {
		bool is_empty = true;
		for (int i = 0; i < max_size; i++) {
			Car value = table[i].value;
			if (!table[i].is_deleted && !table[i].key.empty()) {
				if (is_empty) {
					cout << "Автомобили в базе данных:" << endl;
					cout << "------------------------------------------------------------------" << endl;
				}
				is_empty = false;
				cout << "Государственный регистрационный номер: " << value.registration_number << endl;
				cout << "Марка автомобиля: " << value.brand << endl;
				cout << "Цвет автомобиля: " << value.color << endl;
				cout << "Год выпуска: " << value.release_year << endl;
				cout << "В наличии: " << (value.is_available ? "Да" : "Нет") << endl;
				cout << "------------------------------------------------------------------" << endl;
			}
		}
		if (is_empty) cout << "Список пуст" << endl;
		cout << endl;
	}

	private:
	int hash(string key, size_t size) {
		int hash = 0;
		int multiplier = 1;
		for (char c : key) {
			if (isupper(c)) {
				hash += (c - 'A' + 1) * multiplier; // A = 1, B = 2, ..., Z = 26
			} else if (isdigit(c)) {
				hash += (c - '0') * multiplier; // Цифры
			} else if (c == '-') {
				hash += 15;
			}
			multiplier *= 12; // Простое число для уменьшения коллизий
		}

		return abs(hash) % size;
	}

	bool contains(const string& str, const string& substr) {
		if (substr.empty()) return true;
		if (str.length() < substr.length()) return false;

		for (size_t i = 0; i <= str.length() - substr.length(); i++) {
			bool found = true;
			for (size_t j = 0; j < substr.length(); j++) {
				if (str[i + j] != substr[j]) {
					found = false;
					break;
				}
			}
			if (found) return true;
		}
		return false;
	}

	int linear_probe(int hash, int index) {
		return hash + index;
	}
};
