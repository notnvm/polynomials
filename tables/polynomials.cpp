#include <iostream>
#include <regex>
#include <map>

#include "polynomials.h"

void c_monomial::check_correctness() {
	delete_spaces();
	if (is_empty())
		throw std::exception("string is empty!");
	if (!is_correct())
		throw std::exception("unresolved symbol in string!");
	for (size_t i = 0; i < _expression.size(); ++i)
		if (_expression.at(i) == '^' &&
			(_expression.at(i + 1) == 'x' || _expression.at(i + 1) == 'y' || _expression.at(i + 1) == 'z'))
			throw std::exception("error: variable^variable!");
	for (size_t i = 0; i < _expression.size() - 1; ++i)
		if ((_expression.at(i) == 'x' || _expression.at(i) == 'y' || _expression.at(i) == 'z') &&
			(_expression.at(i + 1) == '+' || _expression.at(i + 1) == '*'))
			throw std::exception("you should type your variable's degree clearly!");
	if(_expression[_expression.length()] == 'x' || _expression[_expression.length()] == 'y' || _expression[_expression.length()] == 'z' 
		|| _expression[_expression.length()] == '+' || _expression[_expression.length()] == '*' || _expression[_expression.length()] == '^' || _expression[_expression.length()] == '.'
		|| _expression[0] == '+' || _expression[0] == '*' || _expression[0] == '^' || _expression[0] == '.')
		throw std::exception("invalid start/end of string!");
}

double c_monomial::get_monomial_coefficient() {
	check_correctness();
	double temp = 1;

	const std::regex regx{ R"((-?\d+(?:\.\d+)?)(?=[xyz]))" };
	std::smatch m;
	std::regex_match(_expression, m, regx);
	std::vector<std::string> res(std::sregex_token_iterator(_expression.begin(), _expression.end(), regx), {});

	for (auto& k : res)
		temp *= std::stod(k);
	res.clear();

	return temp;
}

int c_monomial::get_variable_factor(const std::string& to_find) {
	check_correctness();

	if (_expression.find(to_find) != std::string::npos) {
		std::string res;
		size_t start = _expression.find(to_find);
		for (size_t i = start + to_find.length(); _expression[i] != '*' && i < _expression.length(); ++i) 
			res.push_back(_expression[i]);

		for (const auto& elem : res)
			if (res.find_first_of(".-") != std::string::npos)
				throw std::exception("negative/float variable factor!");

		if (std::stoi(res) < 0 || std::stoi(res) > 9)
			throw std::exception("invalid variable factor! (!=0..9)");

		return std::stoi(res);
	}
	return 0;
}

void c_monomial::sort_similar(const char& key) {
	int result = 0;

	std::map< char, std::vector<size_t> > repeating_variables;
	std::vector<size_t> rep;
	for (size_t i = 0; i < _expression.length(); ++i)
		if (_expression.at(i) == key)
			rep.push_back(i);
	repeating_variables.insert(std::make_pair(key, rep));
	rep.clear();

	for (const auto& a : repeating_variables[key]) {
		result += _expression.at(a + 2) - '0';
	}

	if (result < 0 || result > 9)
		throw std::runtime_error("Invalid Variable factor ");

	_expression.replace(repeating_variables[key].front() + 2, 1, std::to_string(result));
	while (repeating_variables[key].size() != 1) {
		_expression.replace(repeating_variables[key].back(), 3, "");
		repeating_variables[key].pop_back();
	}

	const std::regex reg_repl{ R"([\*]+)" };
	_expression = std::regex_replace(_expression, reg_repl, "*");
	if (_expression.back() == '*')
		_expression.pop_back();
}

void c_monomial::process_monomial() {
	std::map< char, size_t > frequency;
	for (const char& ch : _expression)
		frequency[ch]++;
	std::string chars = "xyz";
	for (auto& pair : frequency)
		if (chars.find(pair.first) != std::string::npos && pair.second > 1)
			sort_similar(pair.first);
}

void c_monomial::simplify_monomial() {
	std::ostringstream str;
	str << std::fixed;
	str << std::setprecision(2);
	str << get_monomial_coefficient();

	const std::regex regx{ R"((-?\d+(?:\.\d+)?)(?=[xyz]))" };
	_expression = std::regex_replace(_expression, regx, "");

	process_monomial();
	_expression = str.str() + _expression;
}

c_monomial c_monomial::operator+(c_monomial& other) {

	simplify_monomial();
	other.simplify_monomial();
	double result_coefficient = get_monomial_coefficient() + other.get_monomial_coefficient();

	return c_monomial(result_coefficient, std::stoi(get_monomial_factor()));
}

c_monomial c_monomial::operator*(const double cons) {
	simplify_monomial();
	double new_coefficient = 1;
	new_coefficient = cons * (*this).get_monomial_coefficient();
	return c_monomial(new_coefficient, std::stoi((*this).get_monomial_factor()));
}

c_monomial c_monomial::operator*(c_monomial& other) {
	double new_coefficient = 1;
	int new_factor = 0;
	new_coefficient = get_monomial_coefficient() * other.get_monomial_coefficient();
	new_factor = std::stoi(get_monomial_factor()) + std::stoi(other.get_monomial_factor());
	return c_monomial(new_coefficient, new_factor);
}

void c_polynomial::parse_to_monomials() {
	const std::regex regx{ R"([xyz\d\*\^\-\.]+)" };
	std::smatch m;
	std::regex_match(_expression, m, regx);
	std::vector<std::string> res(std::sregex_token_iterator(_expression.begin(), _expression.end(), regx), {});

	while (!res.empty()) {
		c_monomial temp(res.back());
		if (temp.get_monomial_coefficient() != 0) {
			_polynomial.push_front(temp);
			temp.simplify_monomial();
		}
		temp.~c_monomial();
		res.pop_back();
	}
	_polynomial.sort();


	//
	for (const auto& val : _polynomial)
		check_correctness();

}

std::string c_polynomial::reduction() {
	list<c_monomial> result;
	std::string temp;

	while (!_polynomial.empty() && _polynomial.size() > 1) {
		c_monomial a(_polynomial.front().get_expression());
		_polynomial.pop_front();
		if (a.get_monomial_factor() == _polynomial.front().get_monomial_factor()) {
			c_monomial c = a + _polynomial.front();
			_polynomial.pop_front();
			_polynomial.push_front(c);
		}
		else result.push_front(a);
		a.~c_monomial();
	}
	_polynomial.merge(result);
	_polynomial.sort();

	while (!_polynomial.empty()) {
		if (_polynomial.front().get_monomial_coefficient() != 0)
			temp = temp + _polynomial.front().get_expression() + "+";
		_polynomial.pop_front();
	}
	temp.pop_back();

	return temp;
}

c_polynomial c_polynomial::operator*(const double cons) {
	list< c_monomial > result;

	for (auto& val : _polynomial)
		if ((val * cons).get_monomial_coefficient() != 0)
			result.push_front(val * cons);
	if (result.empty())
		return c_polynomial("0");

	return c_polynomial(result).reduction();
}

c_polynomial c_polynomial::operator+(c_polynomial& other) {
	_polynomial.merge(other._polynomial);
	_polynomial.sort();
	for (auto& val : _polynomial)
		val.simplify_monomial();

	return c_polynomial(reduction());
}

c_polynomial c_polynomial::operator-(c_polynomial& other) {
	c_polynomial current = *this;
	c_polynomial temp = other * (-1);
	if (!(current == other))
		return current + temp;

	return c_polynomial("0");
}

c_polynomial c_polynomial::operator*(c_polynomial& other) {
	list< c_monomial > result;
	for (auto& val : _polynomial)
		val.simplify_monomial();
	for (auto& val : other._polynomial)
		val.simplify_monomial();
	for (auto it = _polynomial.begin(); it != _polynomial.end(); ++it)
		for (auto it_2 = other._polynomial.begin(); it_2 != other._polynomial.end(); ++it_2)
			result.push_front((*it) * (*it_2));
	return c_polynomial(result).reduction();
}


