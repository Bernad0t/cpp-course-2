#pragma once
#include "./operator.h"

enum class TypePolishEl {
	OPERATOR = 0,
	NUMBER,
};

class ElPolishBase {
public:
	virtual TypePolishEl GetTypePolish() = 0;
	virtual ~ElPolishBase() = default;
};

class ElPolishOp : public ElPolishBase {
public:
	ElPolishOp(Operator* oper) : oper(oper) {}
	TypePolishEl GetTypePolish() { return TypePolishEl::OPERATOR; }
	Operator* oper;
	~ElPolishOp() { delete oper; }
};

class ElPolishNumber : public ElPolishBase {
public:
	ElPolishNumber(double _number) { number = new double(_number); }
	TypePolishEl GetTypePolish() { return TypePolishEl::NUMBER; }
	double* number;
	~ElPolishNumber() { delete number; }
};