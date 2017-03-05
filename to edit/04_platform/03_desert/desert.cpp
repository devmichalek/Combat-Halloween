#include "desert.h"

Desert::Desert()
{
	state = 0;
	info = "";
	
	screen_w = 0;
	screen_h = 0;
	
	hero = new Hero;
	kunai = new Kunai;
	scope = new Scope;
	
	heart = new Heart;
	money_panel = new Money_panel;
	coins = new Coins;
	
	brick = new Brick;
	effect = new Effect;
	background = new Background;
	islands = new Islands;
	wall = new Wall;
	ladder = new Ladder;
	greenery = new Greenery;
	day = new Day;
	
	mine_factory = new Mine_factory;
	fireball = new Fireball;
}

Desert::~Desert()
{
	free();
}

void Desert::free()
{
	state = 0;
	info = "";
	
	screen_w = 0;
	screen_h = 0;
	
	sound.free();
	
	delete hero;
	delete kunai;
	delete scope;
	
	delete heart;
	delete money_panel;
	delete coins;
	
	delete brick;
	delete effect;
	delete background;
	delete islands;
	delete wall;
	delete ladder;
	delete greenery;
	delete day;
	
	delete mine_factory;
	skeleton_factory.free();
	delete fireball;
}

void Desert::reset()
{
	state = 0;
	
	hero->reset( screen_h );
	hero->setKeys();
	scope->reset();
	
	heart->reset();
	money_panel->reset();
	coins->reset();
	
	int distance = brick->reset();
	effect->reset();
	background->reset( hero->getX(), hero->getY() );
	islands->reset( distance );
	wall->reset( distance );
	ladder->reset( distance );
	greenery->reset( distance );
	day->reset();
	
	mine_factory->reset( distance );
	skeleton_factory.reset( distance );
	fireball->reset();
	
	// Set color
	hero->setColor( day->getColor() );
	coins->setColor( day->getColor() );
		
	brick->setColor( day->getColor() );
	background->setColor( day->getColor() );
	islands->setColor( day->getColor() );
	wall->setColor( day->getColor() );
	ladder->setColor( day->getColor() );
	greenery->setColor( day->getColor() );
	
	mine_factory->setColor( day->getColor() );
	skeleton_factory.setColor( day->getColor() );
}



void Desert::load( int screen_w, int screen_h, unsigned FPS )
{
	state = 0;
	info = "setting keys";
	
	int type = 3;
	this->width = 128;
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	kunai->load();
	heart->load();
	money_panel->load( screen_w );
	coins->load( width, screen_w, type );
	
	brick->load( type, width, screen_w, screen_h );
	effect->load( screen_w, screen_h );
	background->load( type, screen_w, screen_h );
	islands->load( type, width, screen_w, screen_h );
	wall->load( type, width, screen_w );
	ladder->load( type, width, screen_w );
	greenery->load( type, width, screen_w );
	day->set( FPS );
	
	mine_factory->load( width, screen_w, screen_h );
	skeleton_factory.load( width, screen_h, screen_h, "skeleton" );
	fireball->load( FPS, screen_w );
}

void Desert::handle( sf::Event &event )
{
	//...
}

void Desert::draw( sf::RenderWindow* &window )
{
	mechanics();
	
	if( hero->isDead() )
	{
		sf::Uint8 value = 1;
		hero->fadeout( value );
		kunai->fadeout( value );
		
		heart->fadeout( value );
		money_panel->fadeout( value );
		coins->fadeout( value );
		
		brick->fadeout( value );
		effect->fadeout( value );
		background->fadeout( value );
		islands->fadeout( value );
		wall->fadeout( value );
		ladder->fadeout( value );
		greenery->fadeout( value );
		
		mine_factory->fadeout( value );
		skeleton_factory.fadeout( value );
		fireball->fadeout( value );
	}
	else
	{
		sf::Uint8 value = 2;
		hero->fadein( value );
		kunai->fadein( value );
		
		heart->fadein( value );
		money_panel->fadein( value );
		coins->fadein( value );
		
		brick->fadein( value );
		effect->fadein( value );
		background->fadein( value );
		islands->fadein( value );
		wall->fadein( value );
		ladder->fadein( value );
		greenery->fadein( value );
		
		mine_factory->fadein( value );
		skeleton_factory.fadein( value );
		fireball->fadein( value );
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
	skeleton_factory.draw( window );
	fireball->draw( window );
	
	// rest
	brick->draw( window );
	islands->draw( window );
	wall->draw( window );
	greenery->draw( window );
	heart->draw( window );
	money_panel->draw( window );
	coins->draw( window );
	effect->draw( window );
}



bool Desert::positioning( int type, int size, int flatness, int difficulty )
{
	switch( state )
	{
		case 0:	hero->load( type, screen_w, screen_h, width ); hero->setKeys();
		info = "setting position x, y of background";	break;
		
		case 1:	background->setPosition( hero->getX(), hero->getY() );
		info = "reserving memory (it can take a while)";	break;
		
		case 2:	brick->reserve( size );
		info = "creating top borders of hill";	break;
		
		case 3:	brick->createTopBorders( size, flatness, ladder->getW( 0 ), ladder->getH( 0 ) );
		info = "creating flying islands";	break;
		
		case 4:	islands->createFlyingIslands( brick->getBlocks(), brick->getPlanks(), difficulty );
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
		info = "creating void";	break;
		
		
		
		case 14:
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
		
		case 18:	wall->positioning( brick->getBlocks(), difficulty );
					wall->positioning( islands->getBlocks(), difficulty );
		info = "creating mine factory";	break;
		
		
		case 19: mine_factory->positioning( brick->getBlocks(), difficulty );
				 mine_factory->positioning( islands->getBlocks(), difficulty );
		info = "creating skeleton factory";	break;
		
		case 20: skeleton_factory.positioning( brick->getBlocks(), difficulty );
				 skeleton_factory.positioning( islands->getBlocks(), difficulty );
		info = "setting money multiplier";	break;
		
		case 21: coins->setChance( difficulty );
		info = "done";	break;
		
		default:
		return true;
		break;
	}
	
	state ++;
	
	return false;
}

string Desert::getInfo()
{
	return info;
}



bool Desert::nextState()
{
	if( hero->isDead() && background->getAlpha() == 0 )
	{
		return true;
	}
	
	return false;
}

bool Desert::backToLevel()
{
	return false;
}