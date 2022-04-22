#include <iostream>

#include "menu.h"

void other::c_menu::rules() {
	system("cls");
	printf("                                                                          \n"
		"To enter a polynomial you must apply the following rules : \n"
		"Monomial rules : \n\n"
		"1. If u want to enter variable's coefficient u r to type a number. Also u can type ' - ' before ur number\n\t For example: 5x, -2.44y etc.\n\n"
		"2. If u want to enter variable's factor u r to type ' ^ number'\n\t For example: 5x^3, 4y^0\n\n"
		"3. If ur monomial has two or three variable u are to type '*' between the variables\n\t For example : 5x ^ 3 * 6y ^ 2\n\n"
		"\t\t!!ATTENTION !!\n\n"
		"4. If ur variable has 0 factor u have to type it clearly\n\t For example : 2x ^ 0\n\n"
		"5. If ur variable has 1 factor u have to type it clearly\n\t For example : 4z ^ 1, 5y or 5xz are not allowed\n\n"
		"6. Variable factor : [0 - 9] , integer\n\n"
		"7. There should be no single coefficients\n\t For example : 2x ^ 3 * 4y ^ 5 * 3 is forbidden\n\n8.If u want to add single coefficient u must type : 'number' * 'variable' ^ 0\n\t For example : 2x ^ 3 * 4y ^ 5 * 3z ^ 0\n\n"
		"\n Correct monomials using given rules : \n\n"
		"\ta. 8x ^ 3 * 6y ^ 5 * 2z ^ 4\n"
		"\tb. - 6.3x * -5y ^ 2 * 3z ^ 0\n"
		"\tc. 5x ^ 1 * 3z ^ 5 * 7y ^ 2\n"
		"\n Incorrect monomials examples : \n\n"
		"\ta. 8xyz\n"
		"\tb. 2x ^ -3 * 2z ^ 2\n"
		"\tc. 4x ^ 2 * 3z * y\n\n"
		"Polynomial rules : \n\n"
		"\t | A polynomial is an expression containing two or more algebraic terms.\n\t | They are often the sum of several terms having different powers(exponents) of variables.\n\n"
		"1. To enter polynomial u should use monomial rules\n"
		"2. There are should be a '+' between each monomial\n"
		"3. You can put spaces anywhere\n"
		"4. If one of ur monomials in polynomial has hegative coefficient, you should put ur minus after plus without any brackets\n"
		"\t For example : -5.23x ^ 2 * y ^ 3 * 3z ^ 1 + -6.8x ^ 0 * z ^ 2\n\n"
		"\n Correct polynomials example : \n\n"
		"\ta. 5x ^ 2 * y ^ 3 * z ^ 4 * x ^ 2 + 2x ^ 1 * y ^ 2 * z ^ 4\n"
		"\tb. 7x ^ 4 * y ^ 3 * z ^ 4 + 15x ^ 1 * y ^ 2 * z ^ 4\n"
		"\tc. 7x ^ 4 * y ^ 3 * z ^ 4 + 15x ^ 1 * y ^ 2 * z ^ 4 + 3x ^ 1 * z ^ 3 * y ^ 5\n\n"
		"\n"
		"                                                                             \n");
}

void other::c_menu::init() {

	size_t choice;
	printf("                                                                             \n"
		"=============================================================================\n"
		"																			  \n"
		"                        Menu Options                                         \n"
		"=============================================================================\n"
		"                                                                             \n"
		"  1. Check rules                                                             \n"
		"  2. Add polynomials                                                         \n"
		"  3. Clear console                                                           \n"
		"                                                                             \n"
		"=============================================================================\n"
		"  !! You must type all the variables x,y,z even if x,y,z factor is 0 !!      \n"
		"  !!     x^2 + 2x + 1 ==> x^2*y^0*z^0 + 2x^1*y^0*z^0 + x^0*y^0*z^0   !!      \n"
		"=============================================================================\n"
		"                                                                             \n"
		"==> ");
		std::cin >> choice;

		switch (choice) {
		case 1:
			rules();
			init();
			break;
		case 2:
			get_polynomials();
			break;
		case 3:
			system("cls");
			init();
			break;
		default:
			std::cout << "bad choice!";
			system("cls");
			init();
			break;
		}
}

void other::c_menu::get_polynomials() {
	size_t choice;
	printf("                                                                          \n"
		"=============================================================================\n"
		"																			  \n"
		"                         Options											  \n"
		"=============================================================================\n"
		"                                                                             \n"
		"  1. A * const                                                               \n\n"
		"  2. A + B																	  \n"
		"  3. A - B																	  \n"
		"  4. A * B																	  \n"
		"                                                                             \n"
		"=============================================================================\n"
		"                                                                             \n"
		"==> ");
	std::cin >> choice;

	switch (choice) {
	case 1:
		multiply_by_const();
		break;
	case 2:
		sum();
		break;
	case 3:
		difference();
		break;
	case 4:
		multiply();
		break;
	default:
		std::cout << "bad choice!";
		system("cls");
		init();
		break;
	}
}

void other::c_menu::sum() {
	std::string polynomial_1, polynomial_2;
	std::cout << "\nA = ";
	std::getline(std::cin >> std::ws, polynomial_1);
	std::cout << "B = ";
	std::getline(std::cin >> std::ws, polynomial_2);

	c_polynomial A(polynomial_1);
	c_polynomial B(polynomial_2);
	A.check_correctness();
	B.check_correctness();

	std::cout << "=============================================================================\n";
	std::cout << "A + B = " << A + B << "\n";
	std::cout << "=============================================================================\n";
}

void other::c_menu::difference() {
	std::string polynomial_1, polynomial_2;
	std::cout << "\nA = ";
	std::getline(std::cin >> std::ws, polynomial_1);
	std::cout << "B = ";
	std::getline(std::cin >> std::ws, polynomial_2);

	c_polynomial A(polynomial_1);
	c_polynomial B(polynomial_2);
	A.check_correctness();
	B.check_correctness();

	std::cout << "=============================================================================\n";
	std::cout << "A - B = " << A - B << "\n";
	std::cout << "=============================================================================\n";
}

void other::c_menu::multiply_by_const() {
	std::string polynomial_1;
	double cons;
	std::cout << "\nA = ";
	std::getline(std::cin >> std::ws, polynomial_1);
	std::cout << "\nConst = ";
	std::cin >> cons;

	c_polynomial A(polynomial_1);
	A.check_correctness();

	std::cout << "=============================================================================\n";
	std::cout << "A * const = " << A * cons << "\n";
	std::cout << "=============================================================================\n";
}

void other::c_menu::multiply() {
	std::string polynomial_1, polynomial_2;
	std::cout << "\nA = ";
	std::getline(std::cin >> std::ws, polynomial_1);
	std::cout << "B = ";
	std::getline(std::cin >> std::ws, polynomial_2);

	c_polynomial A(polynomial_1);
	c_polynomial B(polynomial_2);
	A.check_correctness();
	B.check_correctness();

	std::cout << "=============================================================================\n";
	std::cout << "A * B = " << A * B << "\n";
	std::cout << "=============================================================================\n";
}