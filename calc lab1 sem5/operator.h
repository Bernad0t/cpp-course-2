#pragma once
#include <vector>
#include <stack>

class Operator {
public:
	int priority;
	virtual double Calculate(std::stack<double>& numbers) = 0;
};

class BinaryOperator : public Operator {
public:
	virtual double apply(double firstNumber, double secondNumber) = 0;
	double Calculate(std::stack<double>& numbers) override;
};

class UnarOperator : public Operator {
public:
	virtual double apply(double firstNumber) = 0;
	double Calculate(std::stack<double>& numbers) override;
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