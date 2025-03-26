//
//  Programm.cpp
//  Algorithms
//
//  Created by Aleksandr on 3/23/25.
//

#include <iostream>
#include "Bureau.cpp"
/*
 – добавление нового автомобиля; +
 – удаление сведений об автомобиле;
 – просмотр всех имеющихся автомобилей;
 – очистку данных об автомобилях;
 – поиск автомобиля по «Государственному регистрационному
 номеру». Результаты поиска – все сведения о найденном автомоби-
 ле, а также ФИО и номер водительского удостоверения клиента, ко-
 торому выдан этот автомобиль; +

 – поиск автомобиля по названию марки автомобиля. Результа-
 ты поиска – список найденных автомобилей с указанием «Государ-
 ственный регистрационный номер», марки, цвета, года выпуска;
 57


 – регистрацию отправки автомобиля в ремонт;
 – регистрацию прибытия автомобиля из ремонта;
 – регистрацию выдачи клиенту автомобиля на прокат;
 – регистрацию возврата автомобиля от клиентов
 */
void client_operations(Bureau* bureau);
void car_operations(Bureau* bureau);
void rent_operations(Bureau* bureau);
void main_menu(bool is_test);

int main() {
	main_menu(false);
	return 0;
}

// MARK: - Клиент ГОТОВ ПОЛНОСТЬЮ
void client_operations(Bureau* bureau, bool is_test) {
	while (true) {
		int selected;
		cout << "1. Зарегистрировать нового клиента" << endl;
		cout << "2. Снять клиента с обслуживания" << endl;
		cout << "3. Просмотр всех зарегестрированных клиентов" << endl;
		cout << "4. Очистить данные о клиентах" << endl;
		cout << "5. Поиск клиента по номеру водительского удостоверения" << endl;
		cout << "6. Поиск клиента по фрагменту ФИО" << endl;
		cout << "7. Поиск клиента по фрагменту адреса" << endl;
		cout << "0. Назад" << endl;
		cout << "Выберите пункт: ";
		cin >> selected;
		cout << endl;
		switch (selected) {
			case 1:
				if (is_test) {
					bureau->testing_add_clients();
				} else {
					bureau->client_registration();
				}
				break;
			case 2: bureau->remove_client(); break;
			case 3: bureau->print_clients(); break;
			case 4: bureau->remove_all_clients(); break;
			case 5: bureau->search_client(); break;
			case 6: bureau->search_clients_fullname(); break;
			case 7: bureau->search_clients_address(); break;
			case 0: return;
			default: cout << "Ошибка!" << endl; break;
		}
	}
}
// MARK: - Машины ГОТОВ ПОЛНОСТЬЮ
void car_operations(Bureau* bureau, bool is_test) {
	while (true) {
		int selected;
		cout << "1. Добавить новый автомобиль" << endl;
		cout << "2. Удалить сведения об автомобиле" << endl;
		cout << "3. Просмотр всех имеющихся автомобилей" << endl;
		cout << "4. Очистить данные об автомобилях" << endl;
		cout << "5. Поиск клиента по государственному регистрационному номеру" << endl;
		cout << "6. Поиск клиента по названию марки автомобиля" << endl;
		cout << "0. Назад" << endl;
		cout << "Выберите пункт: ";
		cin >> selected;
		cout << endl;
		switch (selected) {
			case 1:
				if (is_test) {
					bureau->testing_add_cars();
				} else {
					bureau->add_new_car();
				}
				break;
			case 2: bureau->remove_car(); break;
			case 3: bureau->print_cars(); break;
			case 4: bureau->remove_all_cars(); break;
			case 5: bureau->search_car_by_reg_number(); break;
			case 6: bureau->searh_car_by_brand(); break;
			case 0: return;
			default: cout << "Ошибка!" << endl; break;
		}
	}
}
// MARK: - АРЕНДА НЕ ГОТОВ
void rent_operations(Bureau* bureau) {
	while (true) {
		int selected;
		cout << "1. Регистрация отправки автомобиля в ремонт" << endl;
		cout << "2. Регистрация прибытия автомобиля из ремонта" << endl;
		cout << "3. Регистрация выдачи клиенту автомобиля на прокат" << endl;
		cout << "4. Регистрация возврата автомобиля от клиентов" << endl;
		cout << "0. Назад" << endl;
		cout << "Выберите пункт: ";
		cin >> selected;
		cout << endl;
		switch (selected) {
			case 1: bureau->car_to_repair(); break;
			case 2: bureau->car_from_repair(); break;
			case 3: bureau->car_to_rent(); break;
			case 4: bureau->car_from_rent(); break;
			case 0: return;
			default:
				cout << "Ошибка!" << endl;
		}
	}
}

void main_menu(bool is_test) {
	Bureau* bureau = new Bureau();
	while (true) {
		int selected;
		cout << "1. Операции с клиентами" << endl;
		cout << "2. Операции с автомобилями" << endl;
		cout << "3. Операции с арендой и ремонтом" << endl;
		if (!is_test) cout << "4. Тестовая среда с автоматическим добавлением авто и клиентов" << endl;
		cout << "0. Выход" << endl;
		cout << "Выберите пункт: ";
		cin >> selected;
		cout << endl;
		switch (selected) {
			case 1: client_operations(bureau, is_test); break;
			case 2: car_operations(bureau, is_test); break;
			case 3: rent_operations(bureau); break;
			case 4:
				if (!is_test) {
					main_menu(true);
					break;
				} else return;
			case 0:
				bureau = nullptr;
				delete bureau;
				return;
			default:
				cout << "Ошибка!" << endl;
				break;
		}
	}
}
