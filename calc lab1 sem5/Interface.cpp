#include "./interface.h"
#include <iostream>

using namespace std;

void Interface::ProcessUser() {
	string str;
	cout << "input math expression" << endl;
	cin >> str;
	try {
		cout << calculator.ProcessCalculate(str) << endl;
	}
	catch (string message) {
		cout << message;
	}
}

int main() {
	Interface interface;
	interface.ProcessUser();
	return 0;
}