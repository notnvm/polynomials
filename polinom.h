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
	double getMonomFactor();
	double getVariableFactor(const std::string& str);

	void processMonom();
	void sortSimilar(char key);
	void simplifyMonom();
	void showMonom();

	std::string getResult() { return expression; }

	bool operator<=(monoms& mono) {
		return getMonomFactor() <= mono.getMonomFactor();
	}

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
	polinoms(const std::string& str) : poli(str) {};

	void delete_spaces();
	bool is_empty();
	bool check_symbols();
	void check_correctness();

	void parseToMonoms();

	~polinoms() { polinom.clear(); };
private:
	std::string poli;
	list<monoms> polinom;
};