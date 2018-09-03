#pragma once
#include <vector>
#include <string>

class EContent
{
protected:
	static int saveVersion;
	static int loadVersion;
	static std::vector<std::string> content;
public:
	virtual ~EContent();
	bool isNewSaveVersion();	// tells if content is different than content inside of file
	bool isNewLoadVersion();	// same but with loading
	void resetSaveVersion();
	void resetLoadVersion();
};