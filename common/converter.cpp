#include "converter.h"

std::string cmm::floatToStr(float value)
{
	std::string str = std::to_string(value);
	for (size_t i = str.size() - 1; i >= 0; --i)
	{
		if (str[i] == '0')
			str.erase(i);
		else
			break;
	}

	if (!str.empty() && str[str.size() - 1] == '.')
		str += "0";
	return str;
}

std::string cmm::floatToStr(float value, int precision)
{
	std::string str = std::to_string(value);

	size_t pos = str.find('.');
	if (pos != std::string::npos)
		str = str.substr(0, pos + 1 + precision);

	return str;
}

std::string cmm::doubleToStr(double value)
{
	std::string str = std::to_string(value);
	for (size_t i = str.size() - 1; i >= 0; --i)
	{
		if (str[i] == '0')
			str.erase(i);
		else
			break;
	}

	if (!str.empty() && str[str.size() - 1] == '.')
		str += "0";
	return str;
}

std::string cmm::doubleToStr(double value, int precision)
{
	std::string str = std::to_string(value);

	size_t pos = str.find('.');
	if (pos != std::string::npos)
		str = str.substr(0, pos + 1 + precision);

	return str;
}



bool cmm::compareExtension(std::string str, std::string ext)
{
	if (str.size() > ext.size())
	{
		int i = ext.size() - 1;
		for (; i >= 0; --i)
		{
			if (ext[i] != str[(str.size() - 1) - ((ext.size() - 1) - i)])
				break;
		}

		if (i < 0)
			return true;
	}

	return false;
}

bool cmm::removeExtension(std::string &str)
{
	size_t pos = str.rfind('.');
	if (pos != std::string::npos && pos > 0)
	{
		str = str.substr(0, str.size() - (str.size() - pos));
		return true;
	}

	return false;
}

bool cmm::removeDoubleQuotes(std::string & str)
{
	if (str.size() > 2 && str.front() == '"' && str.back() == '"')
	{
		str = str.substr(1, str.size() - 2);
		return true;
	}

	return false;
}