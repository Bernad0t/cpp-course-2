#include "pch.h"
#include "./BaseOperators.h"

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