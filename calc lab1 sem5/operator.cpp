#include "./operator.h"
#include <string>

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

Multiply::Multiply() {
	priority = 2;
}

double Multiply::apply(double firstNumber, double secondNumber) {
	return firstNumber * secondNumber;
}

Sum::Sum() {
	priority = 1;
}

double Sum::apply(double firstNumber, double secondNumber) {
	return firstNumber + secondNumber;
}

Subtract::Subtract() {
	priority = 1;
}

double Subtract::apply(double firstNumber, double secondNumber) {
	return firstNumber - secondNumber;
}

Divide::Divide() {
	priority = 2;
}

double Divide::apply(double firstNumber, double secondNumber) {
	return firstNumber / secondNumber;
}