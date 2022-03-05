#include <regex>
#include <map>
#include <iostream>

#include <iomanip>
#include <sstream>

#include "polinom.h"

void monoms::delete_spaces() {
	expression.erase(std::remove_if(expression.begin(), expression.end(), ::isspace), expression.end());
}

bool monoms::is_empty() {
	return expression.empty();
}

bool monoms::check_symbols() {
	for (const auto& elem : expression)
		if (strchr("1234567890*^xyz.-", elem) == nullptr) 
			return false;
	return true;
}

void monoms::check_correctness() {
	delete_spaces();
	if (is_empty())
		throw std::runtime_error("entered string is empty");
	if (!check_symbols())
		throw std::runtime_error("incorrect symbols in monom");
	for (std::string::iterator it = expression.begin(); it < expression.end(); ++it)
		if (*it == '^' && *(it + 1) == '-')
			throw std::runtime_error("Variable factor cant be negative");
}

void polinoms::delete_spaces() {
	poli.erase(std::remove_if(poli.begin(), poli.end(), ::isspace), poli.end());
}

bool polinoms::is_empty() {
	return poli.empty();
}

bool polinoms::check_symbols() {
	for (const auto& elem : poli)
		if (strchr("1234567890*^xyz.-+", elem) == nullptr)
			return false;
	return true;
}

void polinoms::check_correctness() {
	delete_spaces();
	if (is_empty())
		throw std::runtime_error("entered string is empty");
	if (!check_symbols())
		throw std::runtime_error("incorrect symbols in polinom");
	for (std::string::iterator it = poli.begin(); it < poli.end(); ++it)
		if (*it == '^' && *(it + 1) == '-')
			throw std::runtime_error("Variable factor cant be negative");
}

double monoms::getMonomCoefficient() {
	check_correctness();
	double monom_coefficient = 1;
	// check for last character or print *2z^0
	// (-?\d+(?:\.\d+)?)(?![^xyz]) ==> before xyz and last
	//const std::regex regx{ R"((\d+(?:\.\d+)?)(?=[xyz]))" }; 
	//const std::regex regx{ R"((-?\d+(?:\.\d+)?)[xyz])" };
	const std::regex regx{ R"((-?\d+(?:\.\d+)?)(?=[xyz]))" }; 
	std::smatch m;
	std::regex_match(expression, m, regx);
	std::vector<std::string> res(std::sregex_token_iterator(expression.begin(), expression.end(), regx), {});
	while (!res.empty()) {
		monom_coefficient *= std::stod(res.back());
		res.pop_back();
	}
	return monom_coefficient;
}

double monoms::getVariableFactor(const std::string& toFindStart) {
	if (expression.find(toFindStart) != std::string::npos) {
		check_correctness();
		std::string res;
		size_t start = expression.find(toFindStart);
		for (size_t i = start + toFindStart.length(); expression[i] != '*' && i < expression.length(); ++i)
			res.push_back(expression[i]);
		if (std::stod(res) < 0 || std::stod(res) > 9)
			throw std::runtime_error("invalid variable factor");
		return std::stod(res);
	}

	return 0;
}

double monoms::getMonomFactor() {
	return getVariableFactor("x^") + getVariableFactor("y^") + getVariableFactor("z^");
}

void monoms::sortSimilar(char key) {
		int result = 0;
		std::map< char, std::vector<size_t> > repeatingVariables;
		std::vector<size_t> rep;
		for (size_t i = 0; i < expression.length(); ++i)
			if (expression.at(i) == key)
				rep.push_back(i);
		repeatingVariables.insert(std::make_pair(key, rep));
		rep.clear();
		for (const auto& a : repeatingVariables[key]) {
			result += expression.at(a + 2) - '0';
		}
		if (result < 0 || result > 9)
			throw std::runtime_error("Invalid Variable factor ");
		expression.replace(repeatingVariables[key].front() + 2, 1, std::to_string(result));
		while (repeatingVariables[key].size() != 1) {
			expression.replace(repeatingVariables[key].back(), 3, "");
			repeatingVariables[key].pop_back();
		}
		const std::regex reg_repl{ R"([\*]+)" };
		expression = std::regex_replace(expression, reg_repl, "*");
		if (expression.back() == '*')
			expression.pop_back();
}

void monoms::processMonom() {
	size_t x_count = 0, y_count = 0, z_count = 0;
	for (size_t i = 0; i < expression.length(); ++i) {
		if (expression.at(i) == 'x')
			x_count++;
		if (expression.at(i) == 'y')
			y_count++;
		if (expression.at(i) == 'z')
			z_count++;
	}
	if (x_count > 1)
		sortSimilar('x');
	if (y_count > 1)
		sortSimilar('y');
	if (z_count > 1)
		sortSimilar('z');
}

void monoms::simplifyMonom() {
	std::ostringstream str;
	str << std::fixed;
	str << std::setprecision(2);
	str << getMonomCoefficient();
	const std::regex regx{ R"((-?\d+(?:\.\d+)?)(?=[xyz]))" };
	expression = std::regex_replace(expression, regx, "");
	processMonom();
	finalStr = str.str() + expression;
	expression = finalStr;
	if (getVariableFactor("x^") < 0 || getVariableFactor("x^") > 9)
		throw std::runtime_error("Invalid x power");
	if (getVariableFactor("y^") < 0 || getVariableFactor("y^") > 9)
		throw std::runtime_error("Invalid y power");
	if (getVariableFactor("z^") < 0 || getVariableFactor("z^") > 9)
		throw std::runtime_error("Invalid z power");
}

void monoms::showMonom() {
	simplifyMonom();
	std::cout << "Monom: " << expression << '\n';
	std::cout << "X power: " << getVariableFactor("x^") << '\n';
	std::cout << "Y power: " << getVariableFactor("y^") << '\n';
	std::cout << "Z power: " << getVariableFactor("z^") << '\n';
	std::cout << "mono coefficient: " << getMonomCoefficient() << '\n';
	std::cout << "mono factor: " << getMonomFactor() << '\n';
}

void polinoms::parseToMonoms() {
	check_correctness();
	const std::regex regx{ R"([xyz\d\*\^\-\.]+)" };
	std::smatch m;
	std::regex_match(poli, m, regx);
	std::vector<std::string> res(std::sregex_token_iterator(poli.begin(), poli.end(), regx), {});
	/*while (!res.empty()) {
		monoms a(res.back());
		a.simplifyMonom();
		if (a.getMonomCoefficient() != 0)
			polinom.push_front(a.getResult());
		a.~monoms();
		res.pop_back();
	}
	for (auto& val : polinom)
		std::cout << val << '\n';*/

	while (!res.empty()) {
		monoms a(res.back());
		//a.simplifyMonom();
		if (a.getMonomCoefficient() != 0)
			polinom.push_front(a);
		a.~monoms();
		res.pop_back();
	}
	//polinom.sort();
	for (auto& val : polinom)
		std::cout << val << '\n';
}
