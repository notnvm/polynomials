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
		if (strchr("1234567890*^xyz.-+()", elem) == nullptr)
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
	for (size_t i = 0; i < poli.length() - 1; ++i)
		if ((poli[i] == 'x' || poli[i] == 'y' || poli[i] == 'z') && (poli[i + 1] == 'x' || poli[i + 1] == 'y' || poli[i + 1] == 'z'))
			throw std::runtime_error("Incorrect input: There are two variables in a row");
}

double monoms::getMonomCoefficient() {
	check_correctness();
	double monom_coefficient = 1;
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

int monoms::getVariableFactor(const std::string& toFindStart) {
	if (expression.find(toFindStart) != std::string::npos) {
		check_correctness();
		std::string res;
		size_t start = expression.find(toFindStart);
		for (size_t i = start + toFindStart.length(); expression[i] != '*' && i < expression.length(); ++i)
			res.push_back(expression[i]);
		for (const auto& elem : res)
			if (strchr(".-", elem) != nullptr)
				throw std::runtime_error("invalid variable factor");
		if (std::stoi(res) < 0 || std::stoi(res) > 9)
			throw std::runtime_error("invalid variable factor");
		return std::stoi(res);
	}

	return 0;
}

std::string monoms::getMonomFactor() {
	return std::to_string(getVariableFactor("x^")) + std::to_string(getVariableFactor("y^")) + std::to_string(getVariableFactor("z^"));
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
	while (!res.empty()) {
		monoms a(res.back());
		if (a.getMonomCoefficient() != 0) {
			polinom.push_front(a);
			a.simplifyMonom();
		}
		a.~monoms();
		res.pop_back();
	}
	polinom.sort();
}

std::string polinoms::reduction() {
	list<monoms> result;
	std::string temp;
	while (!polinom.empty() && polinom.size() > 1) {
		monoms a(polinom.front().getResult());
		polinom.pop_front();
		if (a.getMonomFactor() == polinom.front().getMonomFactor()) {
			monoms c = a + polinom.front();
			polinom.pop_front();
			polinom.push_front(c);
		}
		else result.push_front(a);
		a.~monoms();
	}
	polinom.merge(result);
	polinom.sort();
	while (!polinom.empty()) {
		if (polinom.front().getMonomCoefficient() != 0)
			temp = temp + polinom.front().getResult() + "+";
		polinom.pop_front();
	}
	temp.pop_back();
	return temp;
}

monoms monoms::operator+(monoms& other) {
	simplifyMonom();
	other.simplifyMonom();
	double resultCoefficient = 0;
	std::string result;
	resultCoefficient = getMonomCoefficient() + other.getMonomCoefficient();
	std::ostringstream str;
	str << std::fixed;
	str << std::setprecision(2);
	str << resultCoefficient;
	std::string temp = other.getResult();
	result = str.str() + temp.substr(temp.find_first_of("xyz"));
	return monoms(result);
}

polinoms polinoms::operator*(const double con) {
	parseToMonoms();
	std::string res;
	list<monoms> result;
	std::ostringstream str;
	str << std::fixed;
	str << std::setprecision(2);
	str << con;
	for (auto& val : polinom) {
		res = val.getResult() + "*" + str.str() + "x^0";
		monoms new_mono(res);
		new_mono.simplifyMonom();
		result.push_front(new_mono);
		new_mono.~monoms();
	}
	result.sort();
	res.clear();
	while (!result.empty()) {
		if (result.front().getMonomCoefficient() != 0)
			res = res + result.front().getResult() + "+";
		result.pop_front();
	}
	if (!res.empty()) {
		res.pop_back();
		return polinoms(res);
	}
	else return polinoms("0");
}

polinoms polinoms::operator+(polinoms& other) {
	parseToMonoms();
	other.parseToMonoms();
	polinom.merge(other.polinom);
	polinom.sort();
	for (auto& val : polinom)
		val.simplifyMonom();
	return polinoms(reduction());
}

polinoms polinoms::operator-(polinoms& other) {
	polinoms current = *this;
	polinoms temp = other * (-1);
	if (!(current == other))
		return current + temp;
	return polinoms("0");
}

polinoms polinoms::operator*(polinoms& other) {
	parseToMonoms();
	other.parseToMonoms();
	for (auto& val : polinom)
		val.simplifyMonom();
	for (auto& val : other.polinom)
		val.simplifyMonom();
	polinom.sort();
	other.polinom.sort();
	list<monoms> result;
	std::string temp;
	for (auto it = polinom.begin(); it != polinom.end(); ++it)
		for (auto it_2 = other.polinom.begin(); it_2 != other.polinom.end(); ++it_2) {
			temp = (*it).getResult() + "*" + (*it_2).getResult();
			monoms multiply(temp);
			multiply.simplifyMonom();
			result.push_front(multiply);
			multiply.~monoms();
			temp.clear();
		}
	result.sort();
	temp.clear();
	while (!result.empty()) {
		temp = temp + result.front().getResult() + "+";
		result.pop_front();
	}
	temp.pop_back();
	polinoms before_reduction(temp);
	before_reduction.parseToMonoms();
	return polinoms(before_reduction.reduction());
}

