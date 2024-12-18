#include "dll_loading.h"
#include <windows.h>
#include <filesystem>
#include <iostream>
#define YA_LOX

using getNameTemplate = std::string (*)();
using getOperTemplate = Operator*(*)();
std::wstring const LoadingDll::dllDir = L"./";

std::pair<std::string, Operator*> LoadingDll::loading(std::string nameOp) {
	for (auto const& entry : std::filesystem::directory_iterator(dllDir)) {
		std::wstring str = entry.path().wstring().c_str();
		HMODULE dllHandler = LoadLibrary(entry.path().wstring().c_str());
		if (!dllHandler)
			continue;
		FARPROC getNameAddr = GetProcAddress(dllHandler, "getName");
		FARPROC getOperAddr = GetProcAddress(dllHandler, "getOper");
		std::string(*getName)() = (getNameTemplate)getNameAddr;
		if (nameOp.compare(getName())) {
			Operator*(*getOper)() = (getOperTemplate)getNameAddr;
			return std::pair<std::string, Operator* >(getName(), getOper());
		}
		this->dllHandler.push_back(dllHandler);
	}
	throw std::runtime_error("don't exist dll");
}

LoadingDll::~LoadingDll() {
	for (auto&& dll : dllHandler) {
		FreeLibrary(dll);
	}
}