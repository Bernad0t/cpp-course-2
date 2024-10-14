#include "./operator.h"
#include <string>

double BinaryOperator::apply(double number) {
	return number;
}

Multiply::Multiply() {
	property = Properties::binary;
	priority = 2;
}

double Multiply::apply(double firstNumber, double secondNumber) {
	return firstNumber * secondNumber;
}

Sum::Sum() {
	property = Properties::binary;
	priority = 1;
}

double Sum::apply(double firstNumber, double secondNumber) {
	return firstNumber + secondNumber;
}

Subtract::Subtract() {
	property = Properties::binary;
	priority = 1;
}

double Subtract::apply(double firstNumber, double secondNumber) {
	return firstNumber - secondNumber;
}

Divide::Divide() {
	property = Properties::binary;
	priority = 2;
}

double Divide::apply(double firstNumber, double secondNumber) {
	return firstNumber / secondNumber;
}