#include "winter.h"

Winter::Winter()
{
	state = 0;
	info = "";
	
	screen_w = 0;
	screen_h = 0;
	
	hero = new Hero;
	kunai = new Kunai;
	heart = new Heart;
	scope = new Scope;
	
	brick = new Brick;
	effect = new Effect;
	background = new Background;
	islands = new Islands;
	water = new Water;
	wall = new Wall;
	ladder = new Ladder;
	greenery = new Greenery;
	day = new Day;
	
	mine_factory = new Mine_factory;
}

Winter::~Winter()
{
	free();
}

void Winter::free()
{
	state = 0;
	info = "";
	
	screen_w = 0;
	screen_h = 0;
	
	sound.free();
	
	delete hero;
	delete kunai;
	delete heart;
	delete scope;
	
	
	delete brick;
	delete effect;
	delete background;
	delete islands;
	delete water;
	delete wall;
	delete ladder;
	delete greenery;
	delete day;
	
	delete mine_factory;
}

void Winter::reset()
{
	state = 0;
	
	hero->reset( screen_h );
	hero->setKeys();
	heart->reset();
	scope->reset();
	
	int distance = brick->reset();
	effect->reset();
	background->reset( hero->getX(), hero->getY() );
	islands->reset( distance );
	water->reset( distance );
	wall->reset( distance );
	ladder->reset( distance );
	greenery->reset( distance );
	day->reset();
	
	mine_factory->reset( distance );
	
	
	
	
	// Set color
	hero->setColor( day->getColor() );
		
	brick->setColor( day->getColor() );
	background->setColor( day->getColor() );
	islands->setColor( day->getColor() );
	water->setColor( day->getColor() );
	wall->setColor( day->getColor() );
	ladder->setColor( day->getColor() );
	greenery->setColor( day->getColor() );
	
	mine_factory->setColor( day->getColor() );
}



void Winter::load( int screen_w, int screen_h )
{
	state = 0;
	info = "setting keys";
	
	int type = 2;
	int width = 128;
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	kunai->load();
	heart->load();
	
	brick->load( type, width, screen_w, screen_h );
	effect->load( screen_w, screen_h );
	background->load( type, screen_w, screen_h );
	islands->load( type, width, screen_w, screen_h );
	water->load( type, width, screen_w, screen_h );
	wall->load( type, width, screen_w );
	ladder->load( type, width, screen_w );
	greenery->load( type, width, screen_w );
	day->set();
	
	mine_factory->load( width, screen_w, screen_h );
}

void Winter::handle( sf::Event &event )
{
	//...
}

void Winter::draw( sf::RenderWindow* &window )
{
	mechanics();
	
	if( hero->isDead() )
	{
		sf::Uint8 value = 1;
		hero->fadeout( value );
		kunai->fadeout( value );
		heart->fadeout( value );
		
		brick->fadeout( value );
		effect->fadeout( value );
		background->fadeout( value );
		islands->fadeout( value );
		water->fadeout( value );
		wall->fadeout( value );
		ladder->fadeout( value );
		greenery->fadeout( value );
		
		mine_factory->fadeout( value );
	}
	else
	{
		sf::Uint8 value = 2;
		hero->fadein( value );
		kunai->fadein( value );
		heart->fadein( value );
		
		brick->fadein( value );
		effect->fadein( value );
		background->fadein( value );
		islands->fadein( value );
		water->fadein( value );
		wall->fadein( value );
		ladder->fadein( value );
		greenery->fadein( value );
		
		mine_factory->fadein( value );
	}
	

	// bg
	background->draw( window );
	greenery->draw_bg( window );
	
	// blocks
	ladder->draw( window );
	
	// hero
	hero->draw( window );
	kunai->draw( window );
	
	// enemy
	mine_factory->draw( window );
	
	// rest
	water->draw( window );
	brick->draw( window );
	islands->draw( window );
	wall->draw( window );
	greenery->draw( window );
	heart->draw( window );
	effect->draw( window );
}



bool Winter::positioning( int type, int size, int flatness, int flying_is, int pug, int mine  )
{
	switch( state )
	{
		case 0:	hero->load( type, screen_w, screen_h ); hero->setKeys();
		info = "setting position x, y of background";	break;
		
		case 1:	background->setPosition( hero->getX(), hero->getY() );
		info = "reserving memory (it can take a while)";	break;
		
		case 2:	brick->reserve( size );
		info = "creating top borders of hill";	break;
		
		case 3:	brick->createTopBorders( size, flatness, ladder->getW( 0 ), ladder->getH( 0 ) );
		info = "creating flying islands";	break;
		
		case 4:	islands->createFlyingIslands( brick->getBlocks(), brick->getPlanks(), flying_is );
		info = "creating left borders of hill";	break;
		
		
		
		case 5:	brick->createLeftBorders();
		info = "creating right borders of hill";	break;

		case 6:	brick->createRightBorders();
		info = "setting the smallest x of world";	break;
		
		
		
		case 7:	brick->setLeft();
		info = "setting the biggest x of world";	break;
		
		case 8:	brick->setRight();
		info = "filling hills step 1";	break;
		
		
		
		case 9:		brick->createStuffing( 10, 11 );
		info = "filling hills step 2";	break;
		
		case 10:	brick->createStuffing( 14, 11 );
		info = "filling hills step 3";	break;
		
		case 11:	brick->createStuffing( 8, 15 );
		info = "creating top islands";	break;
		
		
		
		case 12:	islands->createTopIslands( brick->getBlocks(), ladder->getW( 1 ), ladder->getH( 1 ), ladder->getH( 0 ) );
		info = "creating bot islands";	break;
		
		case 13:	islands->createBotIslands( brick->getBlocks(), ladder->getW( 1 ), ladder->getH( 1 ) );
		info = "creating water";	break;
		
		
		
		case 14:	water->createWater( brick->getBlocks(), islands->getBlocks(), brick->getRight() );
		info = "shrink to fit vector of blocks";	break;
		
		
		
		case 15:	brick->shrink();
		info = "setting ladders";	break;
		
		
		
		case 16:	ladder->positioning( brick->getPlanks() );
					ladder->positioning( islands->getPlanks() );
					ladder->shrink();
		info = "setting greenery";	break;
		
		case 17:	greenery->positioning( brick->getBlocks() );
					greenery->positioning( islands->getBlocks() );
		info = "setting wall";	break;
		
		case 18:	wall->positioning( brick->getBlocks(), pug );
					wall->positioning( islands->getBlocks(), pug );
		info = "creating mine factory";	break;
		
		
		case 19: mine_factory->positioning( brick->getBlocks(), mine );
				 mine_factory->positioning( islands->getBlocks(), mine );
		info = "done";	break;
		
		default:
		return true;
		break;
	}
	
	state ++;
	
	return false;
}

string Winter::getInfo()
{
	return info;
}



bool Winter::nextState()
{
	if( hero->isDead() && background->getAlpha() == 0 )
	{
		return true;
	}
	
	return false;
}

bool Winter::backToLevel()
{
	return false;
}