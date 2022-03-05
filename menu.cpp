#include <iostream>

#include "menu.h"

void menu() {
	std::cout << "polinoms\n";
	std::cout << "To enter a polynomial you must apply the following rules:\n";
	std::cout << "Monom rules:\n\n";
	std::cout << "1. If u want to enter variable's coefficient u r to type a number also u can type '-' before u number\n\t For example: 5x, -2.44y etc.\n\n";
	std::cout << "2. If u want to enter variable's factor u r to type '^number'\n\t For example: 5x^3, 4y^0\n\n";
	std::cout << "3. If ur monom has two or three variable u are to type '*' between the variables\n\t For example: 5x^3*6y^2\n\n";
	std::cout << "\t\t!! ATTENTION !!\n\n";
	std::cout << "4. If ur variable has 0 factor u have to type it clearly\n\t For example: 2x^0\n\n";
	std::cout << "5. If ur variable has 1 factor u have to type it clearly\n\t For example: 4z^1, 5y or 5xz are not allowed\n\n";
	std::cout << "6. Variable factor: [0-9], integer\n\n";
	std::cout << "7. There should be no single coefficients\n\t For example: 2x^3*4y^5*3 is forbidden\n\n8. If u want to add single coefficient u must type: 'number'*'variable'^0\n\t For example: 2x^3*4y^5*3z^0\n\n";
	std::cout << "\n Correct monoms using given rules:\n\n";
	std::cout << "\ta. 8x^3*6y^5*2z^4\n";
	std::cout << "\tb. -6.3x*-5y^2*3z^0\n";
	std::cout << "\tc. 5x^1*3z^5*7y^2\n";
	std::cout << "\n Incorrect monoms examples:\n\n";
	std::cout << "\ta. 8xyz\n";
	std::cout << "\tb. 2x^-3*2z^2\n";
	std::cout << "\tc. 4x^2*3z*y\n\n";
	std::cout << "Polinom rules:\n\n";
	std::cout << "\t|A polynomial is an expression containing two or more algebraic terms.\n\t|They are often the sum of several terms having different powers (exponents) of variables.\n\n";
	std::cout << "1. To enter polynom u should use monom rules\n";
	std::cout << "2. There are should be a '+' between each monom\n";
	std::cout << "3. You can put spaces anywhere\n";
	std::cout << "4. If one of ur monoms in polinom has hegative coefficient, you should put ur minus after plus without any brackets\n";
	std::cout << "\t For example: -5.23x^2*y^3*3z^1+-6.8x^0*z^2\n\n";

	/*try {
		std::string entered_expression;
		std::cout << "enter the monom: ";
		std::getline(std::cin >> std::ws, entered_expression);
		monoms mono(entered_expression);
		mono.showMonom();
	}
	catch (const std::runtime_error& rE) {
		std::cout << rE.what() << '\n';
	}
	catch (const std::invalid_argument& iA) {
		std::cerr << "Invalid variable factor, u have to follow given rules!\n";
	}*/

	try {
		std::string entered_expression;
		std::cout << "enter the polinom: ";
		std::getline(std::cin >> std::ws, entered_expression);
		polinoms poli_1(entered_expression);
		poli_1.parseToMonoms();
	}
	catch (const std::exception& eX) {
		std::cout << eX.what() << '\n';
	}
}