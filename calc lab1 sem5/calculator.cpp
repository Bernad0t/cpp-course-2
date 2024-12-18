#include "./calculator.h"
#include <queue>
#include <stack>
#include "dll_loading.h"
#include <iostream>

Calculator::Calculator() {
	operators["*"] = new Multiply();
	operators["/"] = new Divide();
	operators["+"] = new Sum();
	operators["-"] = new Subtract();
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
	while ((str[cursor] < '0' || str[cursor] > '9') && str[cursor] != ')' && str[cursor] != '(' && str[cursor] != ' ' && operators.count(strOper) == 0) {
		strOper += str[cursor];
		cursor++;
	}
	if (operators.count(strOper) != 0)
		return operators[strOper];
	else {
		operators.insert(dll.loading(strOper));
		return operators[strOper];
	}
}

bool Calculator::CompareOrderOperator(Operator* oper, Operator* compOper) {
	return oper->priority > compOper->priority;
}

void Calculator::ProcessString(string str) {
	stack<Operator**> operStack; // two pointer because we need one pointer after function to store at elements where elements is polish string like vector 
	int i = 0;
	while (i < str.length()) {  // polish entry
		if (str[i] == ' ') {
			i++;
			continue;
		}
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
				throw runtime_error("one bracket don't exist");
			operStack.pop();
			i++;
		}
		else{
			Operator* oper;
			oper = GetOperatorFromStr(str, i);
			if (oper == nullptr)
				throw runtime_error("operator don't exist");
			while (operStack.size() > 0 && operStack.top() != nullptr && !CompareOrderOperator(oper, *operStack.top())) {
				ElPolishBase* el = new ElPolishOp(*operStack.top());
				elements.push_back(el);
				operStack.pop();
			}
			operStack.push(&oper);
		}
	}
	while (!operStack.empty()) {
		if (operStack.top() == nullptr)
			throw runtime_error("close bracket don't exist");
		ElPolishBase* el = new ElPolishOp(*operStack.top());
		operStack.pop();
		elements.push_back(el);
	}
}

double Calculator::ProcessCalculate(string str) {
	ProcessString(str);
	double solution = 0;
	stack<double> numberStack;
	for (auto&& element : elements) {
		if (element->GetTypePolish() == TypePolishEl::OPERATOR) {
			solution = dynamic_cast<ElPolishOp*>(element)->oper->Calculate(numberStack); //  cast in order to calculate 
			numberStack.push(solution);
		}
		else {
			ElPolishNumber* number = dynamic_cast<ElPolishNumber*>(element);
			numberStack.push(*number->number);
		}
	} 
	return solution;
}
