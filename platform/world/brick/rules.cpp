#include "rules.h"
#include <cstdlib>
#include <stdio.h>
#include "file/file.h"


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
			case 0: if( rand()%3 == 1 )
						result = 3;
					else
						result = 1;
						break;
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
	MyFile file;
	
	file.load( "data/txt/rules/right_rules.txt" );
	if( file.is_good() )
	{
		string line;
		while( getline( file.get(), line ) )
		{
			temporary.clear();
			string l = "";
			for( unsigned i = 0; i < line.size(); i++ )
			{
				if( line[ i ] == ' ' )
				{
					temporary.push_back( con::stoi( l ) );
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
	
	file.free();
}

unsigned Rules::getSize( int which )
{
	return rules_right[ which +1 ].size();
}

int8_t Rules::getBlock( int which )
{
	return getRightRules( which )[ rand()%(getSize( which )) ];
}