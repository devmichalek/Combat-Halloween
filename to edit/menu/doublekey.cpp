#include "menu/doublekey.h"


bool DoubleKey::isEmpty()
{
	if( a == -1 && b == -1 )
	{
		return true;
	}
	
	return false;
}

bool DoubleKey::oneIsFree()
{
	if( a == -1 || b == -1 )
	{
		return true;
	}
	
	return false;
}