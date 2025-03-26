//
//  Tree.cpp
//  Algorithms
//
//  Created by Aleksandr on 3/10/25.
//

#include <iostream>
#include <string>
#include "_Client.cpp"

class Tree {
public:
	Tree* left;
	Tree* right;
	Client client;
	int height;

	Tree(Client client) : client(client), left(nullptr), right(nullptr), height(1) {
	}

public:
	// MARK: Вставка
	void insert(Tree*& tree, Client client) {
		if (!tree) {
			tree = new Tree(client);
			return;
		}

		if (client.card_number > tree->client.card_number) {
			insert(tree->right, client);
		} else {
			insert(tree->left, client);
		}
		tree = balance(tree);
	}

	// MARK: Удаление
	void remove(Tree*& tree, string card_number) {
		if (!tree) return;
		remove(tree->left, card_number);
		remove(tree->right, card_number);
		if (tree->client.card_number == card_number) {
			/*
			 Если есть ПРАВЫЙ - то перемещаем ПРАВЫЙ на ТЕКУЩИЙ, ТЕКУЩИЙ удаляем
			 Если есть ЛЕВЫЙ - то перемещаем ЛЕВЫЙ на ТЕКУЩИЙ, ТЕКУЩИЙ удаляем
			 Если есть ЛЕВЫЙ И ПРАВЫЙ - то перемещаем ПРАВЫЙ на ТЕКУЩИЙ, ПРАВЫМ ссылаемся на ЛЕВЫЙ, ТЕКУЩИЙ УДАЛЯЕМ
			 Если нет правого и левого, то просто удаляем
			 */

			if (tree->left != NULL && tree->right != NULL) {
				Tree*& left = tree->left;
				tree = tree->right;
				tree->left = left;
			} else if (tree->left != NULL) {
				tree = tree->left;

			} else if (tree->right != NULL) {
				tree = tree->right;
			} else {
				cout << "Клиент удален!" << endl;
				tree = nullptr;
				delete tree;
			}
			return;
		}
		tree = balance(tree);
	}

	void remove_all(Tree*& tree) {
		if (!tree) return;
		remove_all(tree->left);
		remove_all(tree->right);
		tree = nullptr;
		delete tree;
		return;
	}

	// MARK: Поиск
	Client search(Tree* tree, string number) {
		if (!tree) return Client();
		if (tree->client.card_number == number) {
			return tree->client;
		}
		Client left_client = search(tree->left, number);

		if (left_client.card_number != "-1" && !left_client.card_number.empty()) {
			return left_client;
		}

		Client right_client = search(tree->right, number);

		if (right_client.card_number != "-1" && !right_client.card_number.empty()) {
			return right_client;
		}
		return Client();
	}

	vector<Client> search_by_rule(Tree* tree, string search_value, bool is_fio) {
		if (!tree) return {};

		vector<Client> result;

		// Если search_value содержится в fio, добавляем в результат
		Client client = tree->client;
		string rule_value = is_fio ? client.full_name : client.address;
		if (contains(rule_value, search_value)) {
			result.push_back(tree->client);
		}

		// Рекурсивный поиск в левом и правом поддеревьях
		vector<Client> left_results = search_by_rule(tree->left, search_value, is_fio);
		vector<Client> right_results = search_by_rule(tree->right, search_value, is_fio);

		// Добавляем результаты из поддеревьев
		result.insert(result.end(), left_results.begin(), left_results.end());
		result.insert(result.end(), right_results.begin(), right_results.end());

		return result;
	}

	// MARK: Вывод
	void show(Tree* tree) {
		if (!tree) return;
		show(tree->left);
		show(tree->right);

		cout << "Номер водительского удостоверения: " << tree->client.card_number << endl;
		cout << "ФИО: " << tree->client.full_name << endl;
		cout << "Адрес: " << tree->client.address << endl;
		cout << "------------------------------------------------------------------" << endl;
	}

	// MARK: Балансировка
	int get_height(Tree* tree) {
		return tree ? tree->height : 0;
	}

	void update_height(Tree* tree) {
		if (tree) {
			tree->height = 1 + max(get_height(tree->left),
								   get_height(tree->right));
		}
	}


	int balance_factor(Tree* tree) {
		return get_height(tree->left) - get_height(tree->right);
	}

	Tree* rotate_right(Tree* tree) {
		Tree* new_root = tree->left;
		tree->left = new_root->right;
		new_root->right = tree;
		update_height(tree);
		update_height(new_root);
		return new_root;
	}

	Tree* rotate_left(Tree* tree) {
		Tree* new_root = tree->right;
		tree->right = new_root->left;
		new_root->left = tree;
		update_height(tree);
		update_height(new_root);
		return new_root;
	}

	Tree* balance(Tree* tree) {
		update_height(tree);
		int bf = balance_factor(tree);

		if (bf > 1) {
			if (balance_factor(tree->left) < 0)
				tree->left = rotate_left(tree->left);
			return rotate_right(tree);
		}
		if (bf < -1) {
			if (balance_factor(tree->right) > 0)
				tree->right = rotate_right(tree->right);
			return rotate_left(tree);
		}
		return tree;
	}

private:
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
};
