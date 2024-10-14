#pragma once
#include <vector>

using namespace std;

enum class Properties {
	binary = 0,
	unar = 1
};

class Operator {
public:
	Properties property;
	int priority;
	virtual double apply(double firstNumber, double secondNumber) = 0;
	virtual double apply(double number) = 0;
};

class BinaryOperator : public Operator {
public:
	virtual double apply(double firstNumber, double secondNumber) = 0;
	double apply(double number) override;
};


class Multiply : public BinaryOperator {
public:
	Multiply();
	double apply(double firstNumber, double secondNumber) override;
};


class Sum : public BinaryOperator {
public:
	Sum();
	double apply(double firstNumber, double secondNumber) override;
};

class Subtract : public BinaryOperator {
public:
	Subtract();
	double apply(double firstNumber, double secondNumber) override;
};


class Divide : public BinaryOperator {
public:
	Divide();
	double apply(double firstNumber, double secondNumber) override;
};