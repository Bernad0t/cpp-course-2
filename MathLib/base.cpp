#include "./base.h"
#include "pch.h"

#include <vector>
#include <stack>
#include "base.h"

using namespace std;

double BinaryOperator::Calculate(stack<double>& numbers) {
	auto getNextNumStack{ [](stack<double>& numberStack) {numberStack.pop(); return numberStack.top();} };
	double solution = apply(getNextNumStack(numbers), numbers.top());
	numbers.pop();
	return solution;
}

double UnarOperator::Calculate(stack<double>& numbers) {
	double solution = apply(numbers.top());
	numbers.pop();
	return solution;
}