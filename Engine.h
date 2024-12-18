#pragma once
#include "./Wrapper.h"

class Engine {
	map<string, Wrapper*> commands;
public:
	void register_command(Wrapper* wrapper, string&& command) {
		if (commands.count(command) > 0) // переназначим
			commands.at(command) = wrapper;
		else
			commands.emplace(command, wrapper);
	}
	string execute_command(string&& command, map<string, string> args) {
		return commands[command]->invoke(args);
	}
};