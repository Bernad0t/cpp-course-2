#pragma once
#include "operator.h"
#include <Windows.h>
#include <string>

class LoadingDll {
	std::vector<HMODULE> dllHandler;
public:
	std::pair<std::string, Operator*>  loading(std::string nameOp);
	static std::wstring const dllDir;
	~LoadingDll();
};