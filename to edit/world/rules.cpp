#include "world/rules.h"


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
	
	
	for( unsigned i = 0; i < rules_left.size(); i++ )
	{
		rules_left[ i ].clear();
	}
	rules_left.clear();
	
	
	for( unsigned i = 0; i < rules_bot.size(); i++ )
	{
		rules_bot[ i ].clear();
	}
	rules_bot.clear();
	
	
	/*
	for( unsigned i = 0; i < rules_top.size(); i++ )
	{
		rules_top[ i ].clear();
	}
	rules_top.clear();
	
	*/
}

vector <Law*> Rules::getRightRules( int which )
{
	return rules_right[ which +1 ];
}




void Rules::ruleRightSide()
{
	vector <Law*> temporary;
	
	// -1 - void
	temporary.clear();
	temporary.push_back( new Law( 0 ) );
	temporary.push_back( new Law( 5 ) );
	temporary.push_back( new Law( 8 ) );
	temporary.push_back( new Law( 10 ) );
	rules_right.push_back( temporary );
	
	// 0
	temporary.clear();
	temporary.push_back( new Law( 1 ) );
	temporary.push_back( new Law( 2 ) );
	temporary.push_back( new Law( 3 ) );
	rules_right.push_back( temporary );
	
	// 1
	temporary.clear();
	temporary.push_back( new Law( 1 ) );
	temporary.push_back( new Law( 2 ) );
	temporary.push_back( new Law( 3 ) );
	rules_right.push_back( temporary );
	
	// 2
	temporary.clear();
	temporary.push_back( new Law( -1 ) );	// means that the block can not be put on the right
	rules_right.push_back( temporary );
	
	// 3
	temporary.clear();
	temporary.push_back( new Law( 14 ) );
	rules_right.push_back( temporary );
	
	// 4
	temporary.clear();
	temporary.push_back( new Law( 1 ) );
	temporary.push_back( new Law( 2 ) );
	temporary.push_back( new Law( 3 ) );
	rules_right.push_back( temporary );
	
	// 5
	temporary.clear();
	temporary.push_back( new Law( 6 ) );
	rules_right.push_back( temporary );
	
	// 6
	temporary.clear();
	temporary.push_back( new Law( 6 ) );
	temporary.push_back( new Law( 7 ) );
	rules_right.push_back( temporary );
	
	// 7
	temporary.clear();
	temporary.push_back( new Law( -1 ) );
	rules_right.push_back( temporary );
	
	// 8
	temporary.clear();
	temporary.push_back( new Law( 9 ) );
	temporary.push_back( new Law( 15 ) );
	rules_right.push_back( temporary );
	
	// 9
	temporary.clear();
	temporary.push_back( new Law( -1 ) );
	rules_right.push_back( temporary );
	
	// 10
	temporary.clear();
	temporary.push_back( new Law( 11 ) );
	temporary.push_back( new Law( 12 ) );
	temporary.push_back( new Law( 13 ) );
	rules_right.push_back( temporary );
	
	// 11
	temporary.clear();
	temporary.push_back( new Law( 11 ) );
	temporary.push_back( new Law( 12 ) );
	temporary.push_back( new Law( 13 ) );
	rules_right.push_back( temporary );
	
	// 12
	temporary.clear();
	temporary.push_back( new Law( -1 ) );
	rules_right.push_back( temporary );
	
	// 13
	temporary.clear();
	temporary.push_back( new Law( 14 ) );
	rules_right.push_back( temporary );
	
	// 14
	temporary.clear();
	temporary.push_back( new Law( 11 ) );
	temporary.push_back( new Law( 12 ) );
	temporary.push_back( new Law( 13 ) );
	rules_right.push_back( temporary );
	
	// 15
	temporary.clear();
	temporary.push_back( new Law( 15 ) );
	temporary.push_back( new Law( 9 ) );
	rules_right.push_back( temporary );
}

void Rules::ruleLeftSide()
{
	vector <Law*> temporary;
	
	// 0
	temporary.clear();
	temporary.push_back( new Law( -1 ) );
	rules_left.push_back( temporary );
	
	// 1
	temporary.clear();
	temporary.push_back( new Law( 0 ) );
	temporary.push_back( new Law( 1 ) );
	temporary.push_back( new Law( 4 ) );
	rules_left.push_back( temporary );
	
	// 2
	temporary.clear();
	temporary.push_back( new Law( 0 ) );
	temporary.push_back( new Law( 1 ) );
	temporary.push_back( new Law( 4 ) );
	rules_left.push_back( temporary );
	
	// 3
	temporary.clear();
	temporary.push_back( new Law( 0 ) );
	temporary.push_back( new Law( 1 ) );
	temporary.push_back( new Law( 4 ) );
	rules_left.push_back( temporary );
	
	// 4
	temporary.clear();
	temporary.push_back( new Law( 13 ) );
	rules_left.push_back( temporary );
	
	// 5
	temporary.clear();
	temporary.push_back( new Law( -1 ) );
	rules_left.push_back( temporary );
	
	// 6
	temporary.clear();
	temporary.push_back( new Law( 6 ) );
	temporary.push_back( new Law( 5 ) );
	rules_left.push_back( temporary );
	
	// 7
	temporary.clear();
	temporary.push_back( new Law( 5 ) );
	temporary.push_back( new Law( 7 ) );
	rules_left.push_back( temporary );
	
	// 8
	temporary.clear();
	temporary.push_back( new Law( -1 ) );
	rules_left.push_back( temporary );
	
	// 9
	temporary.clear();
	temporary.push_back( new Law( 8 ) );
	temporary.push_back( new Law( 15 ) );
	rules_left.push_back( temporary );
	
	// 10
	temporary.clear();
	temporary.push_back( new Law( -1 ) );
	rules_left.push_back( temporary );
	
	// 11
	temporary.clear();
	temporary.push_back( new Law( 10 ) );
	temporary.push_back( new Law( 11 ) );
	temporary.push_back( new Law( 14 ) );
	rules_left.push_back( temporary );
	
	// 12
	temporary.clear();
	temporary.push_back( new Law( 10 ) );
	temporary.push_back( new Law( 11 ) );
	temporary.push_back( new Law( 14 ) );
	rules_left.push_back( temporary );
	
	// 13
	temporary.clear();
	temporary.push_back( new Law( 10 ) );
	temporary.push_back( new Law( 11 ) );
	temporary.push_back( new Law( 14 ) );
	rules_left.push_back( temporary );
	
	// 14
	temporary.clear();
	temporary.push_back( new Law( 13 ) );
	rules_left.push_back( temporary );
	
	// 15
	temporary.clear();
	temporary.push_back( new Law( 8 ) );
	temporary.push_back( new Law( 15 ) );
	rules_left.push_back( temporary );
}

void Rules::ruleBotSide()
{
	vector <Law*> temporary;
	
	// 0
	temporary.clear();
	temporary.push_back( new Law( 8 ) );
	temporary.push_back( new Law( 10 ) );
	temporary.push_back( new Law( 14 ) );
	rules_bot.push_back( temporary );
	
	// 1
	temporary.clear();
	temporary.push_back( new Law( 11 ) );
	temporary.push_back( new Law( 15 ) );
	rules_bot.push_back( temporary );
	
	// 2
	temporary.clear();
	temporary.push_back( new Law( 9 ) );
	temporary.push_back( new Law( 12 ) );
	temporary.push_back( new Law( 13 ) );
	rules_bot.push_back( temporary );
	
	// 3
	temporary.clear();
	temporary.push_back( new Law( 11 ) );
	temporary.push_back( new Law( 15 ) );
	rules_bot.push_back( temporary );
	
	// 4
	temporary.clear();
	temporary.push_back( new Law( 11 ) );
	temporary.push_back( new Law( 15 ) );
	rules_bot.push_back( temporary );
	
	// 5-9
	for( int i = 0; i < 5; i++ )
	{
		temporary.clear();
		temporary.push_back( new Law( -1 ) );
		rules_bot.push_back( temporary );
	}
	
	
	// 10
	temporary.clear();
	temporary.push_back( new Law( 10 ) );
	temporary.push_back( new Law( 14 ) );
	rules_bot.push_back( temporary );
	
	// 11
	temporary.clear();
	temporary.push_back( new Law( 11 ) );
	temporary.push_back( new Law( 15 ) );
	rules_bot.push_back( temporary );
	
	// 12
	temporary.clear();
	temporary.push_back( new Law( 12 ) );
	temporary.push_back( new Law( 13 ) );
	rules_bot.push_back( temporary );
	
	// 13
	temporary.clear();
	temporary.push_back( new Law( 11 ) );
	temporary.push_back( new Law( 15 ) );
	rules_bot.push_back( temporary );
	
	// 14
	temporary.clear();
	temporary.push_back( new Law( 11 ) );
	temporary.push_back( new Law( 15 ) );
	rules_bot.push_back( temporary );
	
	// 15
	temporary.clear();
	temporary.push_back( new Law( -1 ) );
	rules_bot.push_back( temporary );
}

/*
void Rules::ruleTopSide( int number )
{
	vector <Law*> temporary;
	
	if( number == 1 )
	{
		// 0
		temporary.clear();
		temporary.push_back( new Law( -1 ) );
		rules_top.push_back( temporary );
		
	}
}
*/