#include "show_scores.h"
#include "file/file.h"

Show_scores::Show_scores()
{
	free();
}

Show_scores::~Show_scores()
{
	free();
}

void Show_scores::free()
{
	screen_w = 0;
	screen_h = 0;
	
	max = 0;
	number = 0;
	vel = 0;
	state = 0;
	
	line.free();
	summary.free();
	
	status.free();
	status_word.free();
	
	coruption.free();
	coruption_word.free();
	coruption_dot.free();
	
	world.free();
	world_word.free();
	world_sprite.free();
	
	money.free();
	money_word.free();
	money_sprite.free();
	
	mine.free();
	mine_word.free();
	mine_sprite.free();
	
	time.free();
	time_word.free();
	
	scores.free();
	scores_word.free();
}



void Show_scores::load( int screen_w, int screen_h, int t )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	line.setName( "show_scores-line" );
	line.create( screen_w -(screen_w/10), 3 );
	line.setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
	line.setPosition( screen_w/20, t -20 );
	
	summary.setName( "show_scores-summary" );
	summary.setFont( "data/02_menu/BADABB__.TTF", 105, 0xFF, 0xFF, 0xFF );
	summary.setText( "Summary" );
	summary.center( screen_w, 60 );
	
	status.setName( "show_scores-status" );
	status.setFont( "data/00_loading/Jaapokki-Regular.otf", 40, 0xFF, 0xFF, 0xFF );
	status.setText( "Result: " );
	status.setPosition( screen_w/20, summary.getBot() +70 );
	status_word.setName( "show_scores-status_word" );
	status_word.setFont( "data/00_loading/Jaapokki-Regular.otf", 35, 0xFF, 0xFF, 0xFF );
	
	
	coruption.setName( "show_scores-coruption" );
	coruption.setFont( "data/00_loading/Jaapokki-Regular.otf", 40, 0xFF, 0xFF, 0xFF );
	coruption.setText( "Coruption: " );
	coruption.setPosition( screen_w/20 -5, status.getBot() +30 );
	coruption_word.setName( "show_scores-coruption_word" );
	coruption_word.setFont( "data/00_loading/Jaapokki-Regular.otf", 35, 0xFF, 0xFF, 0xFF );
	coruption_dot.setName( "show_scores-coruption_dot" );
	
	
	world.setName( "show_scores-world" );
	world.setFont( "data/00_loading/Jaapokki-Regular.otf", 40, 0xFF, 0xFF, 0xFF );
	world.setText( "World: " );
	world.setPosition( screen_w/20 -2, coruption.getBot() +26 );
	world_word.setName( "show_scores-world_word" );
	world_word.setFont( "data/00_loading/Jaapokki-Regular.otf", 35, 0xFF, 0xFF, 0xFF );
	world_sprite.setName( "show_scores-world_sprite" );
	
	
	money.setName( "show_scores-money" );
	money.setFont( "data/00_loading/Jaapokki-Regular.otf", 40, 0xFF, 0xFF, 0xFF );
	money.setText( "Earned money: " );
	money.setPosition( screen_w/20, world.getBot() +32 );
	money_word.setName( "show_scores-money_word" );
	money_word.setFont( "data/00_loading/Jaapokki-Regular.otf", 35, 0xFF, 0xD8, 0x00 );
	money_sprite.setName( "show_scores-money_sprite" );
	
	
	mine.setName( "show_scores-mine" );
	mine.setFont( "data/00_loading/Jaapokki-Regular.otf", 40, 0xFF, 0xFF, 0xFF );
	mine.setText( "Deactivated mines: " );
	mine.setPosition( screen_w/20, money.getBot() +22 );
	mine_word.setName( "show_scores-money_word" );
	mine_word.setFont( "data/00_loading/Jaapokki-Regular.otf", 35, 0xFF, 0xFF, 0xFF );
	mine_sprite.setName( "show_scores-mine_sprite" );
	
	
	time.setName( "show_scores-time" );
	time.setFont( "data/00_loading/Jaapokki-Regular.otf", 40, 0xFF, 0xFF, 0xFF );
	time.setText( "Time played: " );
	time.setPosition( screen_w/20, mine.getBot() +28 );
	time_word.setName( "show_scores-time_word" );
	time_word.setFont( "data/00_loading/Jaapokki-Regular.otf", 35, 0xFF, 0xFF, 0xFF );
	
	scores.setName( "show_scores-scores" );
	scores.setFont( "data/00_loading/Jaapokki-Regular.otf", 70, 0xFF, 0xFF, 0xFF );
	scores.setText( "Scores: " );
	scores.setPosition( screen_w/20, time.getBot() +28 );
	scores_word.setName( "show_scores-scores" );
	scores_word.setFont( "data/00_loading/Jaapokki-Regular.otf", 70, 0xFF, 0xFF, 0xFF );
}

void Show_scores::draw( sf::RenderWindow* &window )
{
	window->draw( line.get() );
	window->draw( summary.get() );
	
	window->draw( status.get() );
	window->draw( status_word.get() );
	
	window->draw( coruption.get() );
	window->draw( coruption_word.get() );
	// window->draw( coruption_dot.get() );
	
	window->draw( world.get() );
	window->draw( world_word.get() );
	// window->draw( world_sprite.get() );
	
	window->draw( money.get() );
	window->draw( money_word.get() );
	// window->draw( money_sprite.get() );
	
	window->draw( mine.get() );
	window->draw( mine_word.get() );
	// window->draw( mine_sprite.get() );
	
	window->draw( time.get() );
	window->draw( time_word.get() );
	
	window->draw( scores.get() );
	window->draw( scores_word.get() );
	
	if( scores_word.getAlpha() == 0xFF )
	{
		if( number < max )
		{
			number += vel;
			
			if( number > max )
			{
				number = max;
			}
			
			scores_word.setText( con::itos( number ) );
			scores_word.setPosition( scores.getRight(), scores.getY() );
		}
	}
}



void Show_scores::setScores( int s )
{
	max = s;
	number = 0;
	vel = 1 + (s /500);
	
	scores_word.setText( con::itos( number ) );
	scores_word.setPosition( scores.getRight(), scores.getY() );
}

void Show_scores::setResult( bool r )
{
	if( r )
	{
		status_word.setText( "you win" );
		status_word.setColor( 0x58, 0x70, 0x58 );
		status_word.setPosition( status.getRight() +15, status.getTop() +2 );
	}
	else
	{
		status_word.setText( "you lose" );
		status_word.setColor( 0xE8, 0x68, 0x50 );
		status_word.setPosition( status.getRight() +15, status.getTop() +2 );
	}
}

void Show_scores::setCoruption( sf::Uint8 c )
{
	if( c == 33 )
	{
		coruption_word.setText( "low" );
		coruption_word.setColor( 0x99, 0xff, 0x00 );
		coruption_word.setPosition( coruption.getRight() +15, coruption.getTop() +5 );
		coruption_dot.load( "data/03_level/0.png" );
		coruption_dot.setPosition( coruption_word.getRight() +5, coruption_word.getY() -2 );
	}
	else if( c == 66 )
	{
		coruption_word.setText( "medium" );
		coruption_word.setColor( 0xff, 0xcc, 0x00 );
		coruption_word.setPosition( coruption.getRight() +15, coruption.getTop() +4 );
		coruption_dot.load( "data/03_level/1.png" );
		coruption_dot.setPosition( coruption_word.getRight() +5, coruption_word.getY() -1 );
	}
	else
	{
		coruption_word.setText( "high" );
		coruption_word.setColor( 0xCC, 0x00, 0x00 );
		coruption_word.setPosition( coruption.getRight() +15, coruption.getTop() +5 );
		coruption_dot.load( "data/03_level/2.png" );
		coruption_dot.setPosition( coruption_word.getRight() +5, coruption_word.getY() -1 );
	}
}

void Show_scores::setWorld( sf::Uint8 w )
{
	if( w == 0 )
	{
		world_word.setText( "'The last stand'" );
	}
	else if( w == 1 )
	{
		world_word.setText( "'As nature goes'" );
	}
	else if( w == 2 )
	{
		world_word.setText( "'Winter's Embrace'" );
	}
	else if( w == 3 )
	{
		world_word.setText( "'Zany Gorge Race'" );
	}
	else
	{
		world_word.setText( "'Lost in Cyberspace'" );
	}
	
	world_word.setPosition( world.getRight() +15, world.getTop() +5 );
	world_sprite.load( "data/04_platform/world/" +con::itos( w ) +"/bg.png" );
	world_sprite.setScale( 0.05, 0.05 );
	world_sprite.setPosition( world_word.getRight() +15, world.getTop() );
}

void Show_scores::setMoney( int m )
{
	money_word.setText( con::itos( m ) );
	money_word.setPosition( money.getRight() +15, money.getTop() +5 );
	money_sprite.load( "data/04_platform/panel/coin/0.png", 10 );
	money_sprite.setScale( 0.7, 0.7 );
	money_sprite.setPosition( money_word.getRight() +15, money.getTop() +7 );
}

void Show_scores::setMine( int m, sf::Uint8 w )
{
	mine_word.setText( con::itos( m ) );
	mine_word.setPosition( mine.getRight() +15, mine.getTop() +5 );
	
	mine_sprite.load( "data/04_platform/enemy/mine/" +con::itos(w) +"/0.png", 2 );
	mine_sprite.setScale( 0.5, 0.5 );
	mine_sprite.setPosition( mine_word.getRight() +15, mine.getTop() -125 );
}

void Show_scores::setTimePlayed( string t )
{
	time_word.setText( t );
	time_word.setPosition( time.getRight() +15, time.getTop() +5 );
}

void Show_scores::fadein( int v, int max )
{
	line.fadein( v, max );
	summary.fadein( v, max );
	
	status.fadein( v, max );
	status_word.fadein( v, max );
	
	coruption.fadein( v, max );
	coruption_word.fadein( v, max );
	coruption_dot.fadein( v, max );
	
	world.fadein( v, max );
	world_word.fadein( v, max );
	world_sprite.fadein( v, max );
	
	money.fadein( v, max );
	money_word.fadein( v, max );
	money_sprite.fadein( v, max );
	
	mine.fadein( v, max );
	mine_word.fadein( v, max );
	mine_sprite.fadein( v, max );
	
	time.fadein( v, max );
	time_word.fadein( v, max );
	
	scores.fadein( v, max );
	scores_word.fadein( v, max );
}

void Show_scores::fadeout( int v, int min )
{
	line.fadeout( v, min );
	summary.fadeout( v, min );
	
	status.fadeout( v, min );
	status_word.fadeout( v, min );
	
	coruption.fadeout( v, min );
	coruption_word.fadeout( v, min );
	coruption_dot.fadeout( v, min );
	
	world.fadeout( v, min );
	world_word.fadeout( v, min );
	world_sprite.fadeout( v, min );
	
	money.fadeout( v, min );
	money_word.fadeout( v, min );
	money_sprite.fadeout( v, min );
	
	mine.fadeout( v, min );
	mine_word.fadeout( v, min );
	mine_sprite.fadeout( v, min );
	
	time.fadeout( v, min );
	time_word.fadeout( v, min );
	
	scores.fadeout( v, min );
	scores_word.fadeout( v, min );
}
