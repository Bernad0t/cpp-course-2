#include "TextWorker.h"
#include "Wrapper.h"
#include "./Engine.h"
#include <iostream>

void test() {
    TextWorker subj;
    Engine engine;

    Wrapper replaceWrapper(subj, &TextWorker::replaceWords);
    engine.register_command(&replaceWrapper, "replace_word");

    Wrapper doUpWordsWrapper(subj, &TextWorker::doFirstLettersUp);
    engine.register_command(&doUpWordsWrapper, "up_words");

    Wrapper doUpSentencesWrapper(subj, &TextWorker::doFristLetterSentencesUp);
    engine.register_command(&doUpSentencesWrapper, "up_sentences");

    Wrapper addNumberWrapper(subj, &TextWorker::addSentenceNumbering);
    engine.register_command(&addNumberWrapper, "add_sentence_numbering");

    Wrapper findWrapper(subj, &TextWorker::findPhrase);
    engine.register_command(&findWrapper, "find");

    string text = "hello world. this is a test. another sentence.";

    cout << engine.execute_command("replace_word", { {"text", text}, {"arg1", "world"}, {"arg2", "universe"} }) << endl;
    cout << engine.execute_command("up_words", { {"text", text} }) << endl;
    cout << engine.execute_command("up_sentences", { {"text", text} }) << endl;
    cout << engine.execute_command("add_sentence_numbering", { {"text", text} }) << endl;
    cout << engine.execute_command("find", { {"text", text}, {"phrase", "world"} }) << endl;
}

int main() {
    test();
	return 0;
}