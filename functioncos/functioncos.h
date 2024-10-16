#pragma once
#include "../calc lab1 sem5/operator.h"
#include <string>

class Cos : public UnarOperator {
public:
	Cos() { priority = 5; }
	double apply(double firstNumber) { return cos(firstNumber); }
};

extern "C" __declspec(dllexport) Operator * getOper() { Operator* return_value = new Cos; return return_value; }

extern "C" __declspec(dllexport) std::string getName() { return "cos"; }