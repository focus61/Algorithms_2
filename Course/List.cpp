//
//  List.cpp
//  Algorithms
//
//  Created by Aleksandr on 3/19/25.
//

#include "Rent.cpp"
#include <iostream>

struct ListNode {
	ListNode* next;
	Rent value;
	public: ListNode(Rent value) : next(nullptr), value(value) {};
};

class LinkedList {
	private: ListNode* ref;
	public:
	int size;
	LinkedList(Rent first) : ref(new ListNode(first)), size(1) {};

	void append(Rent rent) {
		size++;
		ListNode* node = new ListNode(rent);
		if (ref == NULL) ref = node;
		ListNode* cur = ref;
		while (cur->next != NULL) {
			cur = cur->next;
		}
		cur->next = node;
		sort();
	}

	void search(string regisration_number) {
		if (ref == NULL) cout << "Список пуст" << endl;
		ListNode* cur = ref;
		while (cur != NULL) {
			if (cur->value.regisration_number == regisration_number) {
				Rent value = cur->value;
				cout << "Найденный элемент:" << endl;
				cout << "Регистрационный номер: " << value.regisration_number << endl;
				cout << "Номер карты: " << value.card_number << endl;
				cout << "Дата выдачи: " << value.date_of_issue << endl;
				cout << "Дата возврата: " << value.date_of_return << endl;
				return;
			}
			cur = cur->next;
		}
		cout << "Элемент не найден!" << endl;
	}

	Rent search_by_card_number(string card_number) {
		return search_by_value(card_number, true);
	}

	Rent search_by_reg_number(string registration_number) {
		return search_by_value(registration_number, false);
	}

	void print() {
		if (ref == NULL) cout << " Список пуст" << endl;
		ListNode* cur = ref;
		while (cur != NULL) {
			cout << " Регистр. номер: " << cur->value.regisration_number << endl;
			cur = cur->next;
		}
	}

	void remove(string regisration_number) {
		if (ref == NULL) {
			cout << "Список пуст" << endl;
			return;
		}

		if (ref->value.regisration_number == regisration_number) {
			ref = nullptr;
			delete ref;
			size--;
			cout << "Успешный возврат автомобиля!" << endl;
			return;
		}

		ListNode* cur = ref;
		ListNode* prev = ref;
		if (cur->value.regisration_number == regisration_number) {
			ref = ref->next;
			cur = nullptr;
			size--;
			delete cur;
			cout << "Успешное удаление!" << endl;
			return;
		}

		while (cur != NULL) {
			if (cur->value.regisration_number == regisration_number) {
				prev->next = cur->next;
				cur = nullptr;
				delete cur;
				size--;
				cout << "Успешное удаление!" << endl;
				return;
			}
			prev = cur;
			cur = cur->next;
		}
		cout << "Элемент не найден!" << endl;
	};

	private: void sort() {
		if (ref == NULL) cout << "Список пуст" << endl;
		ListNode* cur = ref;
		Rent sorted_array[size];

		while (cur != NULL) {
			int more_count = 0;
			ListNode* counter_node = ref;
			while (counter_node != NULL) {
				if (cur->value.regisration_number > counter_node->value.regisration_number) {
					more_count++;
				}
				counter_node = counter_node->next;
			}

			while (sorted_array[more_count].regisration_number == cur->value.regisration_number) {
				more_count++;
			}

			sorted_array[more_count] = cur->value;
			cur = cur->next;
		}
		cur = ref;
		int index = 0;
		while (cur != NULL) {
			cur->value = sorted_array[index];
			cur = cur->next;
			index++;
		}
	}

	Rent search_by_value(string value, bool is_card_number) {
		if (ref == NULL) {
			return Rent();
		}
		ListNode* cur = ref;
		while (cur != NULL) {
			string rent_value = is_card_number ? cur->value.card_number : cur->value.regisration_number;
			if (rent_value == value) {
				return cur->value;
			}
			cur = cur->next;
		}
		return Rent();
	}
};
