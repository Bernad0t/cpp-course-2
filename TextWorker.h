#pragma once
#include <string>
#include <map>

using namespace std;

class TextWorker
{
public:
	string replaceWords(map<string, string> args);
	string doFirstLettersUp(map<string, string> args);
	string findPhrase(map<string, string> args);
	string doFristLetterSentencesUp(map<string, string> args);
	string addSentenceNumbering(map<string, string> args);
};

