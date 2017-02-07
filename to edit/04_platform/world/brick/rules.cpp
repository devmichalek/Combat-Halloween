#include "rules.h"
#include <cstdlib>
#include <stdio.h>
#include <fstream>


Rules::Rules()
{
	// empty
}

Rules::~Rules()
{
	free();
}

void Rules::free()
{
	if( !rules_right.empty() )
	{
		for( unsigned i = 0; i < rules_right.size(); i++ )
		{
			if( !rules_right[ i ].empty() )
			{
				rules_right[ i ].clear();
			}
		}
		
		rules_right.clear();
	}
}



vector <int8_t> Rules::getRightRules( int which )
{
	return rules_right[ which +1 ];
}

int Rules::getTopBlockFor( int nr )
{
	if( nr == 14 )
	{
		return 0;
	}
	else if( nr == -1 )
	{
		return 5;
	}
	
	return 0;
}

int Rules::getBotBlockFor( int nr )
{
	if( nr == 2 )
	{
		return 13;
	}
	
	return -1;
}

int Rules::fillForTop( int nr, int need )
{
	int result = -1;
	
	// printf(" nr %d\n", nr );
	if( need == 14 )
	{
		switch( nr )
		{
			case 0: result = 3; 	break;
			case 1: result = 3; 	break;
			case 2: result = -1; 	break;
			case 3: result = 14; 	break;
			case 4: result = 3; 	break;
			case 5: result = 7; 	break;
			case 6: result = 7; 	break;
			case 7: result = -1; 	break;
			
			case -1:
			
				if( rand()%2 == 1 )
				{
					result = 0;
				}
				else
				{
					result = 5;
				}
					
				break;
		}
	}
	else
	{
		switch( nr )
		{
			case 0: result = 2; 	break;
			case 1: result = 2; 	break;
			case 2: result = -1; 	break;
			case 4: result = 2; 	break;
			case 5: result = 7; 	break;
			case 6: result = 7; 	break;
			case 7: result = -1; 	break;
		}
	}
	
	
	//printf(" result %d\n", result );
	
	return result;
}

int Rules::fillForBot( int nr )
{
	int result = -1;
	
	// printf(" nr %d\n", nr );
	
	switch( nr )
	{
		case 0: result = 2; 	break;
		case 1: result = 2; 	break;
		case 4: result = 2; 	break;
		case 5: result = 7; 	break;
		case 6: result = 7; 	break;
		
		case -1:
		
			if( rand()%2 == 1 )
			{
				result = 0;
			}
			else
			{
				result = 5;
			}
				
			break;
	}
	
	//printf(" result %d\n", result );
	
	return result;
}





void Rules::rule()
{
	vector <int8_t> temporary;
	fstream file;
	
	file.open( "data/txt/rules/right_rules.txt" );
	if( file.bad() )
	{
		printf( "Cannot open %s\n", "data/txt/rules/right_rules.txt" );
	}
	else
	{
		string line;
		while( getline( file, line ) )
		{
			temporary.clear();
			string l = "";
			for( unsigned i = 0; i < line.size(); i++ )
			{
				if( line[ i ] == ' ' )
				{
					temporary.push_back( to_int( l ) );
					l = "";
				}
				else
				{
					l += line[ i ];
				}
			}
			
			rules_right.push_back( temporary );
		}
	}
	
	/*
	for( unsigned i = 0; i < rules_right.size(); i++ )
	{
		for( unsigned j = 0; j < rules_right[ i ].size(); j++ )
		{
			printf( "%d ", rules_right[ i ][ j ] );
		}
		printf( "\n" );
	}
	*/
	
	// printf( "\n\n\n\n" );
	
	file.close();
}

int Rules::to_int( string s )
{
    bool m = false;
    int tmp = 0;
    unsigned i = 0;
    if( s[ 0 ] == '-' )
    {
          i++;
          m = true;
    }
	
    while( i < s.size() )
    {
      tmp = 10*tmp +s[ i ] -48;
      i++;
    }
	
    return m ? -tmp : tmp;   
}

unsigned Rules::getSize( int which )
{
	return rules_right[ which +1 ].size();
}

int8_t Rules::getBlock( int which )
{
	return getRightRules( which )[ rand()%(getSize( which )) ];
}