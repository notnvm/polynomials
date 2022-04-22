#pragma once

#include <string>
#include <list>

#include <sstream>
#include <iomanip>

#include "list.h"

#include "../g_tests/gtest/gtest_prod.h"

class c_monomial {
public:
	c_monomial() = default;
	c_monomial(std::string str) : _expression(str) {};
	c_monomial(double coefficient, int monomial_factor) {
		std::ostringstream str;
		str << std::fixed;
		str << std::setprecision(2);
		str << coefficient;

		_expression = str.str() + "x^" + std::to_string(monomial_factor / 100) + "*y^" + std::to_string((monomial_factor % 100) / 10) + "*z^" + std::to_string(monomial_factor % 10);
	};
	~c_monomial() { _expression.clear(); }

public:
	inline std::string get_expression() { return _expression; }
	inline std::string get_monomial_factor() { return std::to_string(get_variable_factor("x^")) + std::to_string(get_variable_factor("y^")) + std::to_string(get_variable_factor("z^")); }
	void   check_correctness();
	double get_monomial_coefficient();
	void   simplify_monomial();
public:
	friend std::ostream& operator<<(std::ostream& out, const c_monomial& mono) { out << mono._expression; return out; }
	bool operator<=(c_monomial& mono) { return get_monomial_factor() <= mono.get_monomial_factor(); }
	bool operator==(c_monomial& mono) { return get_monomial_factor() == mono.get_monomial_factor(); }
	c_monomial operator+(c_monomial& other);
	c_monomial operator*(const double cons);
	c_monomial operator*(c_monomial& other);
private:
	FRIEND_TEST(polynomials, delete_spaces_);
	FRIEND_TEST(polynomials, check_empty);
	FRIEND_TEST(polynomials, check_empty_failed);

	inline void delete_spaces() { _expression.erase(std::remove_if(_expression.begin(), _expression.end(), ::isspace), _expression.end()); }
	inline bool is_empty() { return _expression.empty(); }
	inline bool is_correct() { return (_expression.find_first_not_of("1234567890*^xyz.-+ ") != std::string::npos) ? false : true; }

	void   sort_similar(const char& key);
	int    get_variable_factor(const std::string& to_find);
	void   process_monomial();

protected:
	std::string _expression;
};

class c_polynomial : public c_monomial {
public:
	c_polynomial(std::string str) : c_monomial(str) { parse_to_monomials(); }
	c_polynomial(list< c_monomial > lst) { _polynomial.clear(); _polynomial.merge(lst); _polynomial.sort(); }
	inline void get_polynomial() { std::cout << _polynomial; }
public:
	c_polynomial operator*(const double cons);
	c_polynomial operator+(c_polynomial& other);
	c_polynomial operator-(c_polynomial& other);
	c_polynomial operator*(c_polynomial& other);

	inline bool operator==(c_polynomial& other) { return _expression == other._expression; }
private:
	list<c_monomial> _polynomial;
private:
	void parse_to_monomials();
	std::string reduction();
};
