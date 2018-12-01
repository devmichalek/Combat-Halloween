#pragma once
#include <string>
#include <boost/lexical_cast.hpp>

namespace cmm
{
	std::string floatToStr(float value);
	std::string floatToStr(float value, int precision);
	std::string doubleToStr(double value);
	std::string doubleToStr(double value, int precision);
}
