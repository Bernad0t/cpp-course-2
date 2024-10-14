#include "./interface.h"
#include <iostream>

using namespace std;

void Interface::ProcessUser() {
	string str;
	cout << "input math expression" << endl;
	cin >> str;
	try {
		calculator.ProcessCalculate(str);
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