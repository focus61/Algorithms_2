//
//  Rent.cpp
//  Algorithms
//
//  Created by Aleksandr on 3/19/25.
//

#include <string>

using namespace std;

struct Rent {
	// Номер водительского удостоверения – строка формата «RR AA NNNNNN», где
	// RR – код региона (цифры);
	// AA – серия (буквы из следующего множества: А, В, Е, К, М, Н, О, Р, С, Т, У, Х);
	// NNNNNN – порядковый номер удостоверения (цифры). Код, серия и номер отделяются друг от друга пробелами;
	string card_number;

	// Государственный регистрационный номер – строка формата
	// «ANNNAA-NN», где N –цифра; A – буква из следующего множества:
	// А, В, Е, К, М, Н, О, Р, С, Т, У, Х;
	string regisration_number;

	// Дата выдачи
	string date_of_issue;

	// Дата возврата
	string date_of_return;
public:
	Rent(): card_number("-1"), regisration_number("-1"),  date_of_issue("-1"), date_of_return("-1") {}

	Rent(string card_number,
		 string regisration_number,
		 string date_of_issue,
		 string date_of_return):
	card_number(card_number), regisration_number(regisration_number),  date_of_issue(date_of_issue), date_of_return(date_of_return) {}
};
