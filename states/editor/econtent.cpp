#include "econtent.h"

int EContent::loadVersion = 0;
int EContent::saveVersion = 0;

EContent::~EContent()
{
	loadVersion = 0;
	saveVersion = 0;
}

bool EContent::isNewSaveVersion()
{
	return saveVersion != 0;
}

bool EContent::isNewLoadVersion()
{
	return loadVersion != 0;
}

void EContent::resetSaveVersion()
{
	saveVersion = 0;
}

void EContent::resetLoadVersion()
{
	loadVersion = 0;
}