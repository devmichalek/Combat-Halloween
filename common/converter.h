#pragma once
#include <string>
#include <boost/lexical_cast.hpp>

namespace cmm
{
	const char CNEWLINE = '\n';
	const char CSPACE = ' ';
	const std::string SNEWLINE = "\n";
	const std::string SSPACE = " ";
	const std::string SEMPTY = "";
	const char* const CSNEWLINE = "\n";
	const char* const CSSPACE = " ";

	std::string floatToStr(float value);
	std::string floatToStr(float value, int precision);
	std::string doubleToStr(double value);
	std::string doubleToStr(double value, int precision);

	bool compareExtension(std::string str, std::string ext);
	bool removeExtension(std::string &str);
	bool removeDoubleQuotes(std::string &str);
	std::string extractFromString(std::string &line, std::string seek, char until);
	void erase_all(std::string &str, char seek);
}
