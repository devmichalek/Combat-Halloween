#pragma once
#include <string>
#include <boost/lexical_cast.hpp>

namespace cmm
{
	std::string floatToStr(float value);
	std::string floatToStr(float value, int precision);
	std::string doubleToStr(double value);
	std::string doubleToStr(double value, int precision);

	bool compareExtension(std::string str, std::string ext);
	bool removeExtension(std::string &str);
	bool removeDoubleQuotes(std::string &str);
}
