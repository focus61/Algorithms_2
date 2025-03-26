//
//  Client.cpp
//  Algorithms
//
//  Created by Aleksandr on 3/9/25.
//

#include <string>
using namespace std;

/* Примечание: длина строк (кроме номер водительского удостоверения) определяется студентом самостоятельно. */
struct Client {
	// Номер водительского удостоверения – строка формата «RR AA NNNNNN», где
	// RR – код региона (цифры);
	// AA – серия (буквы из следующего множества: А, В, Е, К, М, Н, О, Р, С, Т, У, Х);
	// NNNNNN – порядковый номер удостоверения (цифры). Код, серия и номер отделяются друг от друга пробелами;
	string card_number;
	// ФИО
	string full_name;
	// Паспортные данные
	string passport;
	// Адрес клиента
	string address;
//public:
//	Client(): card_number("-1"), full_name(""), passport(""), address("") {}

};
