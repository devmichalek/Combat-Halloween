#include "forest.h"

Forest::Forest()
{
	state = 0;
	info = "";
	
	screen_w = 0;
	screen_h = 0;
	
	hero = new Hero;
	kunai = new Kunai;
	scope = new Scope;
	
	heart = new Heart;
	money = new Money;
	coins = new Coins;
	skills = new Skills;
	showdamage = new Showdamage;
	showheal = new Showheal;
	
	brick = new Brick;
	effect = new Effect;
	background = new Background;
	sun = new Sun;
	islands = new Islands;
	water = new Water;
	wall = new Wall;
	ladder = new Ladder;
	greenery = new Greenery;
	day = new Day;
	
	mine_factory = new Mine_factory;
	fireball = new Fireball;
}

Forest::~Forest()
{
	free();
}

void Forest::free()
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
	delete money;
	delete coins;
	delete skills;
	delete showdamage;
	delete showheal;
	
	delete brick;
	delete effect;
	delete background;
	delete sun;
	delete islands;
	delete water;
	delete wall;
	delete ladder;
	delete greenery;
	delete day;
	
	delete mine_factory;
	golem_factory.free();
	delete fireball;
}

void Forest::reset()
{
	state = 0;
	
	hero->reset( screen_h );
	hero->setKeys();
	scope->reset();
	
	heart->reset();
	money->reset();
	coins->reset();
	skills->reset();
	showdamage->reset();
	showheal->reset();
	
	int distance = brick->reset();
	effect->reset();
	background->reset( hero->getX(), hero->getY() );
	sun->reset();
	islands->reset( distance );
	water->reset( distance );
	wall->reset( distance );
	ladder->reset( distance );
	greenery->reset( distance );
	day->reset();
	
	mine_factory->reset( distance );
	golem_factory.reset( distance );
	fireball->reset();
	
	// Set color
	hero->setColor( day->getColor() );
	coins->setColor( day->getColor() );
	kunai->setColor( day->getColor() );
		
	brick->setColor( day->getColor() );
	background->setColor( day->getColor() );
	sun->setColor( day->getColor() );
	islands->setColor( day->getColor() );
	water->setColor( day->getColor() );
	wall->setColor( day->getColor() );
	ladder->setColor( day->getColor() );
	greenery->setColor( day->getColor() );
	
	mine_factory->setColor( day->getColor() );
	golem_factory.setColor( day->getColor() );
}



void Forest::load( int screen_w, int screen_h, unsigned FPS )
{
	state = 0;
	info = "setting keys";
	
	int type = 1;
	this->width = 128;
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	this->FPS = FPS;
	
	heart->load();
	money->load( screen_w );
	coins->load( width, screen_w, type );
	showdamage->load();
	showheal->load();
	
	brick->load( type, width, screen_w, screen_h );
	effect->load( screen_w, screen_h );
	background->load( type, screen_w, screen_h );
	sun->load( screen_w, screen_h );
	islands->load( type, width, screen_w, screen_h );
	water->load( type, width, screen_w, screen_h );
	wall->load( type, width, screen_w );
	ladder->load( type, width, screen_w );
	greenery->load( type, width, screen_w );
	day->set( FPS );
	
	mine_factory->load( width, screen_w, screen_h );
	golem_factory.load( width, screen_h, screen_h, "golem_wood" );
	fireball->load( FPS, screen_w );
}

void Forest::handle( sf::Event &event )
{
	//...
}

void Forest::draw( sf::RenderWindow* &window )
{
	mechanics();
	
	if( hero->isDead() )
	{
		sf::Uint8 value = 1;
		hero->fadeout( value );
		kunai->fadeout( value );
		
		heart->fadeout( value );
		money->fadeout( value );
		coins->fadeout( value );
		skills->fadeout( value );
		showdamage->fadeout( value );
		showheal->fadeout( value );
		
		brick->fadeout( value );
		effect->fadeout( value );
		background->fadeout( value );
		sun->fadeout( value );
		islands->fadeout( value );
		water->fadeout( value );
		wall->fadeout( value );
		ladder->fadeout( value );
		greenery->fadeout( value );
		
		mine_factory->fadeout( value );
		golem_factory.fadeout( value );
		fireball->fadeout( value );
	}
	else
	{
		sf::Uint8 value = 2;
		hero->fadein( value );
		kunai->fadein( value );
		
		heart->fadein( value );
		money->fadein( value );
		coins->fadein( value );
		skills->fadein( value );
		
		brick->fadein( value );
		effect->fadein( value );
		background->fadein( value );
		sun->fadein( value );
		islands->fadein( value );
		water->fadein( value );
		wall->fadein( value );
		ladder->fadein( value );
		greenery->fadein( value );
		
		mine_factory->fadein( value );
		golem_factory.fadein( value );
		fireball->fadein( value );
	}
	

	// bg
	background->draw( window );
	sun->draw( window );
	background->drawFront( window );
	greenery->draw_bg( window );
	
	// blocks
	ladder->draw( window );
	
	// hero
	hero->draw( window );
	kunai->draw( window );
	
	// enemy
	mine_factory->draw( window );
	golem_factory.draw( window );
	fireball->draw( window );
	
	// rest
	water->draw( window );
	brick->draw( window );
	islands->draw( window );
	wall->draw( window );
	greenery->draw( window );
	heart->draw( window );
	money->draw( window );
	coins->draw( window );
	skills->draw( window );
	showdamage->draw( *window );
	showheal->draw( *window );
	effect->draw( window );
}



bool Forest::positioning( int type, int size, int flatness, int difficulty )
{
	switch( state )
	{
		case 0:	hero->load( type, screen_w, screen_h, width ); hero->setKeys();
		kunai->load();	skills->load( FPS, screen_w, screen_h );
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
		
		case 18:	wall->positioning( brick->getBlocks(), difficulty );
					wall->positioning( islands->getBlocks(), difficulty );
		info = "creating mine factory";	break;
		
		
		case 19: mine_factory->positioning( brick->getBlocks(), difficulty );
				 mine_factory->positioning( islands->getBlocks(), difficulty );
		info = "creating golem factory";	break;
		
		case 20: golem_factory.positioning( brick->getBlocks(), difficulty );
				 golem_factory.positioning( islands->getBlocks(), difficulty );
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

string Forest::getInfo()
{
	return info;
}



bool Forest::nextState()
{
	if( hero->isDead() && background->getAlpha() == 0 )
	{
		return true;
	}
	
	return false;
}

bool Forest::backToLevel()
{
	return false;
}