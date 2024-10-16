#pragma once
#include "./operator.h"
#include "./elpolish.h"
#include <string>
#include <vector>
#include <map>
#include "dll_loading.h"

using namespace std;

class Calculator {
public:
	LoadingDll dll;
	double ProcessCalculate(string str);
	Calculator();
	~Calculator();
private:
	vector<ElPolishBase*> elements;
	void ProcessString(string str);
	double GetNumberFromStr(string str, int& cursor);
	Operator* GetOperatorFromStr(string str, int& cursor);
	bool CompareOrderOperator(Operator* oper, Operator* compOper);
	map<string, Operator*> operators;
};
