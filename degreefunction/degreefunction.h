#pragma once
#include "../calc lab1 sem5/operator.h"
#include <string>

class Degree : public BinaryOperator {
public:
	Degree() { priority = 3; }
	double apply(double firstNumber, double secondNumber) { return pow(firstNumber, secondNumber); }
};

extern "C" __declspec(dllexport) Operator * getOper() { Operator* return_value = new Degree; return return_value; }

extern "C" __declspec(dllexport) std::string getName() { return "^"; }