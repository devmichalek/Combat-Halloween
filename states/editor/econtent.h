#pragma once
#include "content.h"

class EContent : public cmm::Content
{
protected:
	static int saveVersion;
	static int loadVersion;
	
public:
	virtual ~EContent();
	bool isNewSaveVersion();	// tells if content is different than content inside of file
	bool isNewLoadVersion();	// same but with loading
	void resetSaveVersion();
	void resetLoadVersion();
};
