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