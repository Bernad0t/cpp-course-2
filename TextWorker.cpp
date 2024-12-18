#include "TextWorker.h"
#include <sstream>

string TextWorker::replaceWords(map<string, string> args) {
    string changed = args.at("arg1");
    string changeTo = args.at("arg2");
    string text = args.at("text");
    size_t start_pos = 0;
    while ((start_pos = text.find(changed, start_pos)) != string::npos) {
        text.replace(start_pos, changed.length(), changeTo);
        start_pos += changeTo.length(); 
    }
    return text;
}

string TextWorker::findPhrase(map<string, string> args) {
    string text = args.at("text");
    string phrase = args.at("phrase");
    if (text.find(phrase) != string::npos)
        return phrase;
    return "";
}

string TextWorker::doFirstLettersUp(map<string, string> args) {
    string result = args.at("text");
    bool new_word = true;

    for (char& c : result) {
        if (isspace(c)) {
            new_word = true;
        }
        else if (new_word) {
            c = toupper(c);
            new_word = false;
        }
    }
    return result;
}

string TextWorker::doFristLetterSentencesUp(map<string, string> args) {
    string result = args.at("text");
    bool new_sentence = true;

    for (char& c : result) {
        if (new_sentence && isalpha(c)) {
            c = toupper(c);
            new_sentence = false;
        }
        if (c == '.' || c == '?' || c == '!') {
            new_sentence = true;
        }
    }
    return result;
}

string TextWorker::addSentenceNumbering(map<string, string> args) {
    istringstream iss(args.at("text"));
    ostringstream oss;
    string line;
    int sentence_count = 1;

    while (getline(iss, line, '.')) {
        if (line.empty()) {
            continue;
        }
        oss << sentence_count++ << ". " << line << "." << std::endl;
    }
    return oss.str();
}