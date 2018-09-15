#pragma once
#include "content.h"

struct WContent : public cmm::Content	// World Data
{
	enum TYPE
	{
		NONE = -1,
		FILE = 0,	// World will be loaded from file.
		SERVER,		// World will be downloaded from server.
		EDITOR		// World will be loaded from editor data.
	};

	static int type;
	static std::string path;	// path to file / url to server (+options)
	static std::vector<std::string> content_sorted;
};