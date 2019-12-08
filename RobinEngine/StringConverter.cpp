/*------------------------------------------------------------------------
Name: yoonsoo.kwon
Assignment name : Class project
Course name : CS200
Term : Fall Year(2019)
------------------------------------------------------------------------*/
#include  "StringConvertor.h"

std::wstring StringConverter::StringToWide(std::string str)
{
	std::wstring wide_string(str.begin(), str.end());
	return  wide_string;
}
