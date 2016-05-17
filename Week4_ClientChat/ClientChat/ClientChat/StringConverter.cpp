#include "stdafx.h"
#include "StringConverter.h"


StringConverter::StringConverter()
{
}


StringConverter::~StringConverter()
{
}

std::string StringConverter::convert(CString inputString)
{
	CT2CA convString(inputString);
	string convStr(convString);
	return convStr;
}
