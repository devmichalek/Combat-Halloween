#pragma once
#include <vector>
#include <string>

namespace cmm
{
	struct Content
	{
		static std::vector<std::string> content;
		explicit Content();
		virtual ~Content();
	};
}