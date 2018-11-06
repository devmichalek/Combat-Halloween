#include "scontent.h"
#include <boost/lexical_cast.hpp>

cmm::Kind SContent::kind;
int SContent::type = SContent::TYPE::NONE;
std::string SContent::path = "";
std::vector<std::string> SContent::content_sorted;
std::vector<std::string> SContent::buffer;

SContent::SContent()
{

}

SContent::~SContent()
{
	type = TYPE::NONE;
	path = "";
	
	if (!content_sorted.empty())
	{
		content_sorted.clear();
	}

	if (!buffer.empty())
	{
		buffer.clear();
	}
}

const int SContent::amount()
{
	return kind.AMOUNT;
}

cmm::Kind SContent::category()
{
	return kind;
}

std::vector<std::string> &SContent::get(int category)
{
	bool was = false;
	buffer.clear();
	for (auto &it : content_sorted)
	{
		if (boost::lexical_cast<int>(it.substr(it.find("t:") + 2, it.find(" c:") - (it.find("t:") + 2))) == category)
		{
			buffer.push_back(it);
			was = true;
		}
		else if (was)
			break;
	}

	buffer.shrink_to_fit();
	return buffer;
}