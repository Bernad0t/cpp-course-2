#pragma once
#include <stack>
using namespace std;

#ifdef MATHLIB
#define IMPORT_EXPORT __declspec(dllexport)
#else
#define IMPORT_EXPORT __declspec(dllimport)
#endif

class IMPORT_EXPORT Operator {
public:
	int priority;
	virtual double Calculate(stack<double>& numbers) = 0;
};

class IMPORT_EXPORT BinaryOperator : public Operator {
public:
	virtual double apply(double firstNumber, double secondNumber) = 0;
	double Calculate(stack<double>& numbers) override;
};

class IMPORT_EXPORT UnarOperator : public Operator {
public:
	virtual double apply(double firstNumber) = 0;
	double Calculate(stack<double>& numbers) override;
};
