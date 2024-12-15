#pragma once
#include "./TextWorker.h"
#include <string>
#include <map>
using namespace std;

class Wrapper
{
public:
	using subjectMethod = string(TextWorker::*)(map<string, string>); // метод класса
	Wrapper(TextWorker& subject, subjectMethod func) : subject(subject), func(func) {}
	string invoke(map<string, string> args) {
		return (subject.*func)(args);
	}
private:
	TextWorker& subject;
	subjectMethod func;
};

