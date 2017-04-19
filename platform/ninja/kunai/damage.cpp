/**
    damage.h
    Purpose: struct Damage counts damage for particular variable.

    @author Adrian Michalek
    @version 2017.03.03
	@email adrmic98@gmail.com
*/

#include "damage.h"

string Damage::multiply( int which, float value, int number )
{
	if( number == 0 )
	{
		value = 0;
	}
	
	for( int i = 0; i < number -1; i++ )
	{
		switch( which )
		{
			case 0:	value = value *2;	break;
			case 1:	value = value *2;	break;
			case 2:	value += 9;	break;
			case 3:	value += 9;	break;
			case 4:	value = value *2.15;	break;
			case 5:	value = value *2.07;	break;
		}
	}
	
	// precision 3
	string base = to_string( value );
	string newstr = "";
	int counter = -1;
	for( unsigned i = 0; i < base.size(); i++ )
	{
		if( counter == 0 )
		{
			break;
		}
		
		newstr += base[ i ];
		if( base[ i ] == '.' )
		{
			counter = 3;
		}
		
		if( counter > 0 )
		{
			counter --;
		}
	}
	
	if( newstr[ newstr.size() -1 ] == '0' )
	{
		newstr.erase( newstr.size() -1 );
	}
	
	if( newstr[ newstr.size() -1 ] == '0' )
	{
		newstr.erase( newstr.size() -1 );
	}
	
	if( newstr[ newstr.size() -1 ] == '.' )
	{
		newstr.erase( newstr.size() -1 );
		
	}
	
	return newstr;
}