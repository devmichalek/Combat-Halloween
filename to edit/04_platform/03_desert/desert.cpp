#include "desert.h"

Desert::Desert()
{
	state = 0;
	info = "";
	fade = 0;
	music = new Music;
	
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
	scores = new Scores;
	hp_dots = new Hp_dots;
	
	brick = new Brick;
	effect = new Effect;
	background = new Background;
	islands = new Islands;
	wall = new Wall;
	ladder = new Ladder;
	greenery = new Greenery;
	day = new Day;
	wind = new Wind;
	boulder = new Boulder;
	door = new Door;
	
	mine_factory = new Mine_factory;
	snakes_factory = new Snakes_factory;
	fireball = new Fireball;
	fly_factory = new Fly_factory;
}

Desert::~Desert()
{
	free();
}

void Desert::free()
{
	state = 0;
	info = "";
	fade = 0;
	
	screen_w = 0;
	screen_h = 0;
	
	sound.free();
	delete music;
	
	delete hero;
	delete kunai;
	delete scope;
	
	delete heart;
	delete money;
	delete coins;
	delete skills;
	delete showdamage;
	delete showheal;
	delete scores;
	delete hp_dots;
	
	delete brick;
	delete effect;
	delete background;
	delete islands;
	delete wall;
	delete ladder;
	delete greenery;
	delete day;
	delete wind;
	delete boulder;
	delete door;
	
	delete mine_factory;
	skeleton_factory.free();
	delete snakes_factory;
	delete fireball;
	delete fly_factory;
}

void Desert::reset()
{
	state = 0;
	fade = 0;
	reloadMusic();
	
	hero->reset( screen_h );
	hero->setKeys();
	scope->reset();
	
	heart->reset();
	money->reset();
	coins->reset();
	skills->reset();
	showdamage->reset();
	showheal->reset();
	scores->reset();
	hp_dots->reset();
	
	int distance = brick->reset();
	effect->reset();
	background->reset( hero->getX(), hero->getY() );
	islands->reset( distance );
	wall->reset( distance );
	ladder->reset( distance );
	greenery->reset( distance );
	day->reset();
	wind->reset();
	boulder->reset( distance );
	door->reset( distance );
	
	mine_factory->reset( distance );
	skeleton_factory.reset( distance );
	snakes_factory->reset( distance );
	fireball->reset();
	fly_factory->reset();
	
	// Set color
	hero->setColor( day->getColor() );
	coins->setColor( day->getColor() );
	kunai->setColor( day->getColor() );
		
	brick->setColor( day->getColor() );
	background->setColor( day->getColor() );
	islands->setColor( day->getColor() );
	wall->setColor( day->getColor() );
	ladder->setColor( day->getColor() );
	greenery->setColor( day->getColor() );
	boulder->setColor( day->getColor() );
	door->setColor( day->getColor() );
	hp_dots->setAlpha( day->getAlpha() );
	
	mine_factory->setColor( day->getColor() );
	skeleton_factory.setColor( day->getColor() );
	snakes_factory->setColor( day->getColor() );
	fly_factory->setColor( day->getColor() );
}



void Desert::load( int screen_w, int screen_h, unsigned FPS )
{
	state = 0;
	info = "setting keys";
	
	int type = 3;
	this->width = 128;
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	this->FPS = FPS;
	
	heart->load();
	money->load( screen_w );
	coins->load( width, screen_w, type );
	showdamage->load();
	showheal->load();
	scores->load( screen_w );
	hp_dots->load( type, screen_w );
	
	brick->load( type, width, screen_w, screen_h );
	effect->load( screen_w, screen_h );
	background->load( type, screen_w, screen_h );
	islands->load( type, width, screen_w, screen_h );
	wall->load( type, width, screen_w );
	ladder->load( type, width, screen_w );
	greenery->load( type, width, screen_w );
	day->set( FPS );
	wind->create( screen_w, screen_h );
	boulder->load( type, width, screen_w );
	door->load( type );
	
	mine_factory->load( type, width, screen_w, screen_h );
	skeleton_factory.load( width, screen_h, screen_h, "skeleton" );
	snakes_factory->load( width, screen_w, screen_h );
	fireball->load( FPS, screen_w );
	fly_factory->load( type, screen_w, screen_h );
	
	music->setID( "forest-music" );
	music->load( "data/04_platform/world/3/music.mp3", 50 );
}

void Desert::handle( sf::Event &event )
{
	//...
}

void Desert::draw( sf::RenderWindow* &window )
{
	if( sound.getMusicPlay() )
	{
		music->play();
	}
	
	mechanics();
	
	if( hero->isDead() && fade == 1 )
	{
		music->fadeout( 1, 0 );
		
		sf::Uint8 value = 1;
		hero->fadeout( value );
		kunai->fadeout( value );
		
		heart->fadeout( value );
		money->fadeout( value );
		coins->fadeout( value );
		skills->fadeout( value );
		showdamage->fadeout( value );
		showheal->fadeout( value );
		scores->fadeout( value );
		hp_dots->fadeout( value );
		
		brick->fadeout( value );
		effect->fadeout( value );
		background->fadeout( value );
		islands->fadeout( value );
		wall->fadeout( value );
		boulder->fadeout( value );
		ladder->fadeout( value );
		greenery->fadeout( value );
		wind->fadeout( value );
		door->fadeout( value );
		
		mine_factory->fadeout( value );
		skeleton_factory.fadeout( value );
		snakes_factory->fadeout( value );
		fireball->fadeout( value );
		fly_factory->fadeout( value );
		
		// set fade
		if( background->getAlpha() == 0 )	fade = 0;
	}
	else if( fade == 0 )
	{
		music->fadein( 1, sound.getMusicVolume() );
		
		sf::Uint8 value = 2;
		hero->fadein( value );
		kunai->fadein( value );
		
		heart->fadein( value );
		money->fadein( value );
		coins->fadein( value );
		skills->fadein( value );
		scores->fadein( value );
		hp_dots->fadein( value );
		
		brick->fadein( value );
		effect->fadein( value );
		background->fadein( value );
		islands->fadein( value );
		wall->fadein( value );
		boulder->fadein( value );
		ladder->fadein( value );
		greenery->fadein( value );
		door->fadein( value );
		
		mine_factory->fadein( value );
		skeleton_factory.fadein( value );
		snakes_factory->fadein( value );
		fireball->fadein( value );
		fly_factory->fadein( value );
		
		// set fade
		if( background->getAlpha() == 0xFF )	fade = 1;
	}
	

	// bg
	background->draw( window );
	greenery->draw_bg( window );
	
	// blocks
	ladder->draw( window );
	
	// hero
	door->draw( window );
	hero->draw( window );
	kunai->draw( window );
	
	// enemy
	mine_factory->draw( window );
	skeleton_factory.draw( window );
	snakes_factory->draw( window );
	fireball->draw( window );
	fly_factory->draw( window );
	
	// rest
	hp_dots->draw( window );
	wind->draw( window );
	brick->draw( window );
	islands->draw( window );
	wall->draw( window );
	boulder->draw( window );
	greenery->draw( window );
	heart->draw( window );
	money->draw( window );
	coins->draw( window );
	skills->draw( window );
	showdamage->draw( *window );
	showheal->draw( *window );
	scores->draw( window );
	effect->draw( window );
}



bool Desert::positioning( int type, int size, int flatness, int difficulty )
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
		info = "creating snakes factory";	break;
		
		case 21: snakes_factory->positioning( brick->getBlocks(), difficulty );
				 snakes_factory->positioning( islands->getBlocks(), difficulty );
		info = "setting money multiplier";	break;
		
		case 22: coins->setChance( difficulty );
		info = "positioning boulders";	break;
		
		case 23: boulder->positioning( brick->getBlocks(), wall->getXs(), difficulty );
				 boulder->positioning( islands->getBlocks(), wall->getXs(), difficulty );
		info = "setting doors";	break;
		
		case 24: door->positioning( brick->getLastBlock() );
		info = "loading music";	break;
		
		case 25: setSound();	reloadMusic();	break;
		info = "done";
		
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



bool Desert::defeatState()
{
	if( hero->isDead() && background->getAlpha() == 0 )
	{
		return true;
	}
	
	return false;
}

bool Desert::winState()
{
	if( door->nextState() )
	{
		return true;
	}
	
	return false;
}

bool Desert::backToLevel()
{
	return false;
}

void Desert::setSound()
{
	// Set chunks
	if( !sound.getChunkPlay() )
	{
		wall->turnOff();
		coins->turnOff();
		mine_factory->turnOff();
		skeleton_factory.turnOff();
		snakes_factory->turnOff();
		boulder->turnOff();
	}
	else
	{
		wall->turnOn();
		coins->turnOn();
		mine_factory->turnOn();
		skeleton_factory.turnOn();
		snakes_factory->turnOn();
		boulder->turnOn();
		
		// Set chunk volume
		wall->setVolume( sound.getChunkVolume() );
		coins->setVolume( sound.getChunkVolume() );
		mine_factory->setVolume( sound.getChunkVolume() );
		skeleton_factory.setVolume( sound.getChunkVolume() );
		snakes_factory->setVolume( sound.getChunkVolume() );
		boulder->setVolume( sound.getChunkVolume() );
	}
	
	// Set music volume
	music->setVolume( sound.getMusicVolume() );
}

void Desert::reloadMusic()
{
	music->reload();
	Mix_HaltMusic();
}