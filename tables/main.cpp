#include <iostream>

#include "menu.h"

int main() {

	std::setlocale(LC_ALL, "ru-RU");

	try {
		other::c_menu menu;
		menu.init();
	}
	catch (const std::exception& ex) { std::cout << ex.what(); }
	system("pause");
	return 0;

}