#include "./calculator.h"
#include <queue>
#include <stack>

ElementPolishEnter::ElementPolishEnter(ElementPolishEnter const & const copy) : oper(copy.oper) {
	if (copy.number != nullptr) {
		number = new double;
		*number = *copy.number;
	}
	else if (copy.oper != nullptr) {
		number = nullptr;
	}
	
}

ElementPolishEnter::ElementPolishEnter(Operator* oper){
	this->oper = oper;
	number = nullptr;
}

ElementPolishEnter::ElementPolishEnter(double number) {
	this->number = new double;
	*(this->number) = number;
	oper = nullptr;
}

ElementPolishEnter::~ElementPolishEnter() {
	if (oper != nullptr)
		delete oper;
	if (number != nullptr)
		delete number;
}

Calculator::Calculator() {
	operators["*"] = new Multiply();
	operators["/"] = new Divide();
	operators["+"] = new Sum();
	operators["-"] = new Subtract();
}

Calculator::~Calculator() {
	for (const auto& element : operators) {
		delete element.second;
		operators.erase(element.first);
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
	while ((str[cursor] < '0' || str[cursor] > '9') && str[cursor] != ')' && str[cursor] != '(') {
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
		if (str[i] == '(')
			operStack.push(nullptr);
		else if (str[i] >= '0' && str[i] <= '9') {
			ElementPolishEnter el(GetNumberFromStr(str, i));
			elements.push_back(el);
		}
		else if (str[i] == ')') {
			bool bracketVisited = false;
			while (operStack.top() != nullptr || operStack.size() > 0) {
				elements.push_back(ElementPolishEnter(*operStack.top()));
				operStack.pop();
				if (operStack.top() == nullptr)
					bracketVisited = true;
			}
			if (!bracketVisited)
				throw string("open bracket don't exist");
			operStack.pop();
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
				elements.push_back(ElementPolishEnter(*operStack.top()));
				operStack.pop();
			}
			operStack.push(oper);
		}
	}
	while (!operStack.empty()) {
		if (operStack.top() == nullptr)
			throw string("close bracket don't exist");
		ElementPolishEnter* el = new ElementPolishEnter(*operStack.top());
		operStack.pop();
		elements.push_back(*el);
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
	double expressResult = 0;
	queue<Operator*> operQueue;
	queue<double> numberQueue;
	for (auto&& element : elements) {
		if (element.oper != nullptr) {
			operQueue.push(element.oper);
		}
		else {
			numberQueue.push(*element.number);
			if (operQueue.front()->property == Properties::unar) {
				solution += operQueue.front()->apply(numberQueue.front());
				operQueue.pop();
				numberQueue.pop();
				numberQueue.push(solution);
			}
			else if (numberQueue.size() == 2) {
				solution += operQueue.front()->apply(numberQueue.front(), numberQueue.back());
				operQueue.pop();
				numberQueue.pop();
				numberQueue.pop();
				numberQueue.push(solution);
			}
		}
	}
}
