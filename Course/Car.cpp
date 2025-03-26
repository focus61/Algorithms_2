//
//  Car.cpp
//  Algorithms
//
//  Created by Aleksandr on 3/10/25.
//

#include <string>
using namespace std;

// Примечание: длина строк (кроме «Государственного регистрационного номера») определяется студентом самостоятельно.
struct Car {
	// Государственный регистрационный номер – строка формата
	// «ANNNAA-NN», где N –цифра; A – буква из следующего множества:
	// A, B, E, K, M, H, O, P, C, T, Y, X;
	string registration_number;
	// Марка
	string brand;

	// Цвет
	string color;

	// Год выпуска
	int release_year;
	// Признак наличия авто
	bool is_available;

public:
	Car(string registration_number, string brand, string color, int release_year):
	registration_number(registration_number),
	brand(brand),
	color(color),
	release_year(release_year),
	is_available(true) {}

	Car():
	registration_number("-1"),
	brand(""),
	color(""),
	release_year(0),
	is_available(false) {}
};
