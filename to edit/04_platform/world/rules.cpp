#include "rules.h"
#include <cstdlib>
#include <stdio.h>


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
	for( unsigned i = 0; i < rules_right.size(); i++ )
	{
		rules_right[ i ].clear();
	}
	
	rules_right.clear();
}



vector <int8_t> Rules::getRightRules( int which )
{
	return rules_right[ which +1 ];	// +1 because of void block ( -1 )
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





void Rules::ruleRightSide()
{
	vector <int8_t> temporary;
	
	// -1 - void
	temporary.clear();
	temporary.push_back( 0 );
	temporary.push_back( 5 );
	rules_right.push_back( temporary );
	
	// 0
	temporary.clear();
	temporary.push_back( 1 );
	temporary.push_back( 2 );
	rules_right.push_back( temporary );
	
	// 1
	temporary.clear();
	temporary.push_back( 2 );
	temporary.push_back( 1 );
	rules_right.push_back( temporary );
	
	// 2
	temporary.clear();
	temporary.push_back( -1 );	// means that the block can not be put on the right
	rules_right.push_back( temporary );
	
	// 3
	temporary.clear();
	temporary.push_back( -1 );
	rules_right.push_back( temporary );
	
	// 4
	temporary.clear();
	temporary.push_back( 1 );
	temporary.push_back( 2 );
	rules_right.push_back( temporary );
	
	// 5
	temporary.clear();
	temporary.push_back( 6 );
	rules_right.push_back( temporary );
	
	// 6
	temporary.clear();
	temporary.push_back( 6 );
	temporary.push_back( 7 );
	rules_right.push_back( temporary );
	
	// 7
	temporary.clear();
	temporary.push_back( -1 );
	rules_right.push_back( temporary );
	
	// 8
	temporary.clear();
	temporary.push_back( 9 );
	temporary.push_back( 15 );
	rules_right.push_back( temporary );
	
	// 9
	temporary.clear();
	temporary.push_back( -1 );
	rules_right.push_back( temporary );
	
	// 10
	temporary.clear();
	temporary.push_back( 11 );
	temporary.push_back( 12 );
	rules_right.push_back( temporary );
	
	// 11
	temporary.clear();
	temporary.push_back( 11 );
	temporary.push_back( 12 );
	rules_right.push_back( temporary );
	
	// 12
	temporary.clear();
	temporary.push_back( -1 );
	rules_right.push_back( temporary );
	
	// 13
	temporary.clear();
	temporary.push_back( 4 );
	rules_right.push_back( temporary );
}
