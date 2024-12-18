#include "./interface.h"
#include <iostream>

using namespace std;

void Interface::ProcessUser() {
	string str;
	while (str != "/0") {
		cout << "input math expression. For exite input /0" << endl;
		getline(cin, str);
		if (str == "/0")
			break;
		try {
			cout << calculator.ProcessCalculate(str) << endl;
		}
		catch (runtime_error& message) {
			cout << message.what();
		}
		str.clear();
	}
}

int main() {
	Interface interf;
	interf.ProcessUser();
	return 0;
}