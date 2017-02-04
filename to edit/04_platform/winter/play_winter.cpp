#include "play_winter.h"

Play_winter::Play_winter()
{
	state = 0;
	info = "";
	
	// Create Play_winter objects
	hero = new Hero;
	bg = new Moving_bg;
	brick = new Brick;
	kunai = new Kunai;
	heart = new Heart;
	scope = new Scope;
	greenery = new Greenery;
	ladder = new Ladder;
}

Play_winter::~Play_winter()
{
	free();
}

void Play_winter::free()
{
	state = 0;
	info = "";
	
	sound.free();
	delete hero;
	delete bg;
	delete brick;
	delete kunai;
	delete heart;
	delete scope;
	delete greenery;
	delete ladder;
}

void Play_winter::reset()
{
	hero->reset( screen_h );
	hero->setKeys();
	bg->setXY( hero->getX(), hero->getY() );
	int distance = brick->reset();
	greenery->reset( distance );
	ladder->reset( distance );
	heart->reset();
	scope->reset();
}



void Play_winter::load( int screen_w, int screen_h )
{
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	bg->load( "data/sprites/play/2.png", screen_w, screen_h );
	brick->load( screen_w, screen_h, 2 );
	kunai->load();
	heart->load();
	greenery->load( 2 );
	ladder->load( 2 );
	info = "loading hero";
}

void Play_winter::handle( sf::Event &event )
{
	//...
}

void Play_winter::draw( sf::RenderWindow* &window )
{
	mechanics();
	
	if( hero->isDead() )
	{
		sf::Uint8 v = 1;
		bg->fadeout( v );
		brick->fadeout( v );
		hero->fadeout( v );
		kunai->fadeout( v );
		heart->fadeout( v );
		greenery->fadeout( v );
		ladder->fadeout( v );
	}
	else
	{
		sf::Uint8 v = 2;
		bg->fadein( v );
		brick->fadein( v );
		hero->fadein( v );
		kunai->fadein( v );
		heart->fadein( v );
		greenery->fadein( v );
		ladder->fadein( v );
	}
	

	
	bg->draw( window );
	greenery->drawBG( window, screen_w );
	ladder->draw( window, screen_w );
	hero->draw( window );
	kunai->draw( window );
	brick->draw( window );
	greenery->draw( window, screen_w );
	heart->draw( window );
}



bool Play_winter::positioning( int size, int type )
{
	switch( state )
	{
		case 0: 
		info = "setting keys";
		hero->load( screen_w, screen_h, "data/sprites/hero/" + to_string( type ) + "/" );
		break;
		
		case 1:
		info = "setting position x, y of background";
		hero->setKeys();
		break;
		
		case 2:
		info = "reserving memory (it can take a while)";
		bg->setXY( hero->getX(), hero->getY() );
		break;
		
		case 3:
		info = "creating top border of hills";
		brick->reserve( size );
		break;
		
		case 4:
		info = "creating left border of hills";
		brick->createTopBorders( size, ladder->getW( 0 ), ladder->getH( 0 ) );
		break;
		
		case 5:
		info = "creating right border of hills";
		brick->createLeftBorders();
		break;
		
		case 6:
		info = "setting left x of world";
		brick->createRightBorders();
		break;
		
		case 7:
		info = "setting right x of world";
		brick->setLeft();
		break;
		
		case 8:
		info = "filling hills step 1";
		brick->setRight();
		break;
		
		case 9:
		info = "filling hills step 2";
		brick->createStuffing( 10, 11 );
		break;
		
		case 10:
		info = "filling hills step 3";
		brick->createStuffing( 14, 11 );
		break;
		
		case 11:
		info = "creating top islands";
		brick->createStuffing( 8, 15 );
		break;
	
		case 12:
		info = "creating bottom islands";
		brick->createTopIslands( ladder->getW( 1 ), ladder->getH( 1 ) );
		break;
		
		case 13:
		info = "creating water";
		brick->createBotIslands( ladder->getW( 1 ), ladder->getH( 1 ) );
		break;
		
		case 14:
		info = "shrink to fit vector";
		brick->createWater();
		break;
		
		case 15:
		info = "setting ladders";
		brick->shrink();
		break;
	
		case 16:
		info = "setting greenery";
		ladder->positioning( brick->getPlanks() );
		break;
		
		case 17:
		info = "done";
		greenery->positioning( brick->getBlocks() );
		break;
		
		default:
		return true;
		break;
	}
	
	state ++;
	
	return false;
}

string Play_winter::getInfo()
{
	return info;
}



bool Play_winter::nextState()
{
	if( hero->isDead() && bg->getAlpha() == 0 )
	{
		return true;
	}
	
	return false;
}

bool Play_winter::backToLevel()
{
	return false;
}