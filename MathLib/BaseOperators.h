#pragma once
#include "base.h"

#ifdef MATHLIB
#define IMPORT_EXPORT __declspec(dllexport)
#else
#define IMPORT_EXPORT __declspec(dllimport)
#endif

class IMPORT_EXPORT Multiply : public BinaryOperator {
public:
	Multiply();
	double apply(double firstNumber, double secondNumber) override;
};


class IMPORT_EXPORT Sum : public BinaryOperator {
public:
	Sum();
	double apply(double firstNumber, double secondNumber) override;
};

class IMPORT_EXPORT Subtract : public BinaryOperator {
public:
	Subtract();
	double apply(double firstNumber, double secondNumber) override;
};


class IMPORT_EXPORT Divide : public BinaryOperator {
public:
	Divide();
	double apply(double firstNumber, double secondNumber) override;
};