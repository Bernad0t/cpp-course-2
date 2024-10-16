#include "./calculator.h"
#include <queue>
#include <stack>

Calculator::Calculator() {
	operators["*"] = new Multiply();
	operators["/"] = new Divide();
	operators["+"] = new Sum();
	operators["-"] = new Subtract();
	operators["cos"] = new Cos();
}

Calculator::~Calculator() {
	for (auto&& element : operators) {
		delete element.second;
	}
	for (auto&& element : elements) {
		if (element->GetTypePolish() != TypePolishEl::OPERATOR)
			delete element;
	}
}

double Calculator::GetNumberFromStr(string str, int& cursor) {
	string res;
	while (str[cursor] >= '0' && str[cursor] <= '9' || str[cursor] == '.') {
		res += str[cursor];
		cursor++;
	}
	return stod(res);
}

Operator* Calculator::GetOperatorFromStr(string str, int& cursor) {
	string strOper;
	while ((str[cursor] < '0' || str[cursor] > '9') && str[cursor] != ')' && str[cursor] != '(' && operators.count(strOper) == 0) {
		strOper += str[cursor];
		cursor++;
	}
	if (operators.count(strOper) != 0)
		return operators[strOper];
	else
		throw string("operator dont't exist");
}

bool Calculator::CompareOrderOperator(Operator* oper, Operator* compOper) {
	return oper->priority > compOper->priority;
}

void Calculator::ProcessString(string str) {
	stack<Operator**> operStack;
	int i = 0;
	while (i < str.length()) {  // polish entry
		if (str[i] == '(') {
			operStack.push(nullptr);
			i++;
		}
		else if (str[i] >= '0' && str[i] <= '9') {
			ElPolishBase* el = new ElPolishNumber(GetNumberFromStr(str, i));
			elements.push_back(el);
		}
		else if (str[i] == ')') {
			bool bracketVisited = false;
			while (operStack.size() > 0 && operStack.top() != nullptr) {
				ElPolishBase* el = new ElPolishOp(*operStack.top());
				elements.push_back(el);
				operStack.pop();
				if (operStack.top() == nullptr)
					bracketVisited = true;
			}
			if (!bracketVisited)
				throw string("one bracket don't exist");
			operStack.pop();
			i++;
		}
		else{
			Operator** oper = new Operator*;
			try {
				*oper = GetOperatorFromStr(str, i);
			}
			catch(string message) {
				throw message;
			}
			if (oper == nullptr)
				throw string("operator don't exist");
			while (operStack.size() > 0 && operStack.top() != nullptr && !CompareOrderOperator(*oper, *operStack.top())) {
				ElPolishBase* el = new ElPolishOp(*operStack.top());
				elements.push_back(el);
				operStack.pop();
			}
			operStack.push(oper);
		}
	}
	while (!operStack.empty()) {
		if (operStack.top() == nullptr)
			throw string("close bracket don't exist");
		ElPolishBase* el = new ElPolishOp(*operStack.top());
		operStack.pop();
		elements.push_back(el);
	}
}

double Calculator::ProcessCalculate(string str) {
	try {
		ProcessString(str);
	}
	catch (string message) {
		throw message;
	}
	double solution = 0;
	stack<double> numberStack;
	for (auto&& element : elements) {
		if (element->GetTypePolish() == TypePolishEl::OPERATOR) {
			ElPolishOp* oper = dynamic_cast<ElPolishOp*>(element);
			solution = oper->oper->Calculate(numberStack);
			numberStack.push(solution);
		}
		else {
			ElPolishNumber* number = dynamic_cast<ElPolishNumber*>(element);
			numberStack.push(*number->number);
		}
	} 
	return solution;
}
