#pragma once
#include "./operator.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

class ElementPolishEnter {
public:
	ElementPolishEnter(ElementPolishEnter const & const copy);
	ElementPolishEnter(Operator* oper);
	ElementPolishEnter(double number);
	double* number;
	Operator* oper;
	~ElementPolishEnter();
};

class Calculator {
public:
	double ProcessCalculate(string str);
	Calculator();
	~Calculator();
private:
	vector<ElementPolishEnter> elements;
	void ProcessString(string str);
	double GetNumberFromStr(string str, int& cursor);
	Operator* GetOperatorFromStr(string str, int& cursor);
	bool CompareOrderOperator(Operator* oper, Operator* compOper);
	map<string, Operator*> operators;
};
