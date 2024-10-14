#pragma once
#include "./calculator.h"


class Interface {
public:
	void ProcessUser();
private:
	Calculator calculator;
};