#pragma once
#include  "StringConvertor.h"
#include  <Windows.h>

class ErrorLogger
{
public:
	static  void Log(std::string message);
	static void Log(HRESULT hr, std::string message);
    static void Log(HRESULT hr, std::wstring message);
};