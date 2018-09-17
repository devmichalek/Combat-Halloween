#pragma once
#include "content.h"
#include "kind.h"

struct SContent : public cmm::Content
{
	enum TYPE
	{
		NONE = -1,
		FILE = 0,	// World will be loaded from file.
		SERVER,		// World will be downloaded from server.
		EDITOR		// World will be loaded from editor data.
	};

	static cmm::Kind kind;
	static int type;
	static std::string path;	// path to file / url to server (+options)
	static std::vector<std::string> content_sorted;
	static std::vector<std::string> buffer;
public:
	SContent();
	~SContent();
	static const int amount();
	static cmm::Kind category();
	static std::vector<std::string> &get(int category);
};