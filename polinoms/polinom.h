#pragma once

#include "new_list.h"

class monoms {
public:
	monoms() {};
	monoms(std::string str) : expression(str) {};

	void delete_spaces();
	bool is_empty();
	bool check_symbols();
	void check_correctness();

	double getMonomCoefficient();
	std::string getMonomFactor();
	int getVariableFactor(const std::string& str);

	void processMonom();
	void sortSimilar(char key);
	void simplifyMonom();
	void showMonom();

	std::string getResult() { return expression; }

	bool operator<=(monoms& mono) {
		return getMonomFactor() <= mono.getMonomFactor();
	}

	monoms operator+(monoms& other);

	friend std::ostream& operator<<(std::ostream& out, const monoms& mono) {
		out << mono.expression;
		return out;
	}
	
	~monoms() { expression.clear(); finalStr.clear(); };

private:
	std::string expression;
	std::string finalStr;
};

class polinoms {
public:
	polinoms() {};
	polinoms(const std::string& str) : poli(str) { check_correctness(); };

	void delete_spaces();
	bool is_empty();
	bool check_symbols();
	void check_correctness();

	void parseToMonoms();
	std::string reduction();

	void merge(polinoms other) {
		parseToMonoms();
		other.parseToMonoms();
		polinom.merge(other.polinom);
	}

	polinoms operator*(const double con);
	polinoms operator+(polinoms& other);
	polinoms operator-(polinoms& other);
	polinoms operator*(polinoms& other);

	bool operator==(polinoms& other) {
		return poli == other.poli;
	}

	friend std::ostream& operator<<(std::ostream& out, const polinoms& poli) {
		out << poli.poli;
		return out;
	}

	~polinoms() { polinom.clear(); poli.clear(); };
private:
	std::string poli;
	list<monoms> polinom;
};