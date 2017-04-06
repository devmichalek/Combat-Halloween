#include "halloween.h"
#include "file/file.h"	// itos()

Halloween::Halloween()
{
	// Base.
	state = 0;
	info = "";
	fade = 0;
	
	FPS = 0;
	width = 0;
	screen_w = 0;
	screen_h = 0;
	
	// Sound.
	music = new Music;
	
	// Hero.
	hero = new Hero;
	kunai = new Kunai;
	scope = new Scope;
	
	// Panel.
	skills = new Skills;
	heart = new Heart;
	scores = new Scores;
	money = new Money;
	pause = new Pause;
	
	// Actions.
	hp_dots = new Hp_dots;
	coins = new Coins;
	showdamage = new Showdamage;
	showheal = new Showheal;
	effect = new Effect;
	
	// World,
	background = new Background;
	brick = new Brick;
	islands = new Islands;
	greenery = new Greenery;
	ladder = new Ladder;
	wall = new Wall;
	boulder = new Boulder;
	score_dots = new Score_dots;
	door = new Door;
	// in addition.
	rain = new Rain;
	spikes = new Spikes;
	
	// Enemy.
	lightning = new Lightning;
	mine_factory = new Mine_factory;
	fly_factory = new Fly_factory;
	skulls = new Skulls;
}

Halloween::~Halloween()
{
	free();
}

void Halloween::free()
{
	// Base.
	state = 0;
	info = "";
	fade = 0;
	
	FPS = 0;
	width = 0;
	screen_w = 0;
	screen_h = 0;
	
	// Sound.
	sound.free();
	delete music;
	
	// Hero.
	delete hero;
	delete kunai;
	delete scope;
	
	// Panel.
	delete skills;
	delete heart;
	delete scores;
	delete money;
	delete pause;
	
	// Actions.
	delete hp_dots;
	delete coins;
	delete showdamage;
	delete showheal;
	delete effect;
	
	// World,
	delete background;
	delete brick;
	delete islands;
	delete greenery;
	delete ladder;
	delete wall;
	delete boulder;
	delete score_dots;
	delete door;
	// in addition.
	delete rain;
	delete spikes;
	
	// Enemy.
	delete lightning;
	delete mine_factory;
	vampire_factory.free();
	zombie_factory.free();
	delete fly_factory;
	delete skulls;
}

void Halloween::reset()
{
	// Base.
	state = 0;
	fade = 0;
	
	// Sound.
	reloadMusic();
	
	// Hero.
	hero->reset( screen_h );
	hero->setKeys();
	scope->reset();
	
	// Panel.
	skills->reset();
	heart->reset();
	scores->reset();
	money->reset();
	
	// Actions.
	hp_dots->reset();
	coins->reset();
	showdamage->reset();
	showheal->reset();
	effect->reset();
	
	// World,
	background->reset( hero->getX(), hero->getY() );
	int distance = brick->reset();
	islands->reset( distance );
	greenery->reset( distance );
	ladder->reset( distance );
	wall->reset( distance );
	boulder->reset( distance );
	score_dots->reset( distance );
	door->reset( distance );
	// in addition.
	rain->reset();
	spikes->reset( distance );
	
	// Enemy.
	lightning->reset();
	mine_factory->reset( distance );
	vampire_factory.reset( distance );
	zombie_factory.reset( distance );
	fly_factory->reset();
	skulls->reset();
}



void Halloween::load( int screen_w, int screen_h, unsigned FPS )
{
	state = 0;
	info = "setting keys";
	
	int type = 0;
	this->FPS = FPS;
	this->width = 128;
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	// Sound.
	music->setID( "forest-music" );
	music->load( "data/04_platform/world/" +con::itos(type) +"/music.mp3", 50 );
	
	// Panel.
	heart->load();
	scores->load( type, screen_w );
	money->load( screen_w );
	pause->load( screen_w, screen_h );
	
	// Actions.
	hp_dots->load( type, screen_w );
	coins->load( width, screen_w, type );
	showdamage->load();
	showheal->load();
	effect->load( screen_w, screen_h );
	
	// World, 
	background->load( type, screen_w, screen_h );
	brick->load( type, width, screen_w, screen_h );
	islands->load( type, width, screen_w, screen_h );
	greenery->load( type, width, screen_w );
	ladder->load( type, width, screen_w );
	wall->load( type, width, screen_w );
	boulder->load( type, width, screen_w );
	score_dots->load( screen_w );
	door->load( type );
	// in addition.
	rain->load( screen_w, screen_h );
	spikes->load( type, screen_w, width );
	
	// Enemy.
	lightning->load( FPS );
	mine_factory->load( type, width, screen_w, screen_h );
	vampire_factory.load( width, screen_w, screen_h, "vampire" );
	zombie_factory.load( width, screen_w, screen_h, "zombie" );
	fly_factory->load( type, screen_w, screen_h );
	skulls->load( type, screen_w, screen_h );
}

void Halloween::handle( sf::Event &event )
{
	pause->handle( event );
}

void Halloween::draw( sf::RenderWindow* &window )
{
	// Sound.
	if( sound.getMusicPlay() )
	{
		music->play();
	}
	
	// Pause
	if( !pause->isPaused() )
	{
		mechanics();
		music->fadein( 1, sound.getMusicVolume() );
	}
	else
	{
		music->fadeout( 1, 15 );
	}
	
	
	// Fade out, fade in.
	if( hero->isDead() && fade == 1 )
	{
		// Value.
		sf::Uint8 value = 1;
		
		// Sound.
		music->fadeout( value );
		
		// Hero.
		hero->fadeout( value );
		kunai->fadeout( value );
		
		// Panel.
		skills->fadeout( value );
		heart->fadeout( value );
		scores->fadeout( value );
		money->fadeout( value );
		
		// Actions.
		hp_dots->fadeout( value );
		coins->fadeout( value );
		showdamage->fadeout( value );
		showheal->fadeout( value );
		effect->fadeout( value );
		
		// World,
		background->fadeout( value );
		brick->fadeout( value );
		islands->fadeout( value );
		greenery->fadeout( value );
		ladder->fadeout( value );
		wall->fadeout( value );
		boulder->fadeout( value );
		score_dots->fadeout( value );
		door->fadeout( value );
		// in addition.
		rain->fadeout( value );
		spikes->fadeout( value );
		
		// Enemy.
		lightning->fadeout( value );
		mine_factory->fadeout( value );
		vampire_factory.fadeout( value );
		zombie_factory.fadeout( value );
		fly_factory->fadeout( value );
		skulls->fadeout( value );
		
		// Set fade.
		if( background->getAlpha() == 0 )
		{
			fade = 0;
		}
	}
	else if( fade == 0 )
	{
		// Value.
		sf::Uint8 value = 2;
		
		// Hero.
		hero->fadein( value );
		kunai->fadein( value );
		
		// Panel.
		skills->fadein( value );
		heart->fadein( value );
		scores->fadein( value );
		money->fadein( value );
		
		// Actions.
		hp_dots->fadein( value );
		coins->fadein( value );
		effect->fadein( value );
		
		// World,
		background->fadein( value );
		brick->fadein( value );
		islands->fadein( value );
		greenery->fadein( value );
		ladder->fadein( value );
		wall->fadein( value );
		boulder->fadein( value );
		score_dots->fadein( value );
		door->fadein( value );
		// in addition.
		rain->fadein( value );
		spikes->fadein( value );
		
		// Enemy.
		lightning->fadein( value );
		mine_factory->fadein( value );
		vampire_factory.fadein( value );
		zombie_factory.fadein( value );
		fly_factory->fadein( value );
		skulls->fadein( value );
		
		// Set fade.
		if( background->getAlpha() == 0xFF )
		{
			fade = 1;
		}
	}
	

	// Background.
	background->draw( window );
	background->drawFront( window );
	greenery->draw_bg( window );
	ladder->draw( window );
	door->draw( window );
	
	// Hero.
	hero->draw( window );
	kunai->draw( window );
	
	// Enemy.
	lightning->draw( window );
	mine_factory->draw( window );
	vampire_factory.draw( window );
	zombie_factory.draw( window );
	fly_factory->draw( window );
	skulls->draw( window );
	
	// Dots.
	score_dots->draw( window );
	hp_dots->draw( window );
	
	// Rest.
	coins->draw( window );
	rain->draw( window );
	spikes->draw( window );
	wall->draw( window );
	boulder->draw( window );
	brick->draw( window );
	islands->draw( window );
	greenery->draw( window );
	
	// Show.
	showdamage->draw( *window );
	showheal->draw( *window );
	
	// Some panel stuff.
	skills->draw( window );
	heart->draw( window );
	scores->draw( window );
	money->draw( window );
	
	// Effect and pause.
	effect->draw( window );
	pause->draw( window );
}



bool Halloween::positioning( int type, int size, int flatness, int difficulty  )
{
	switch( state )
	{
		case 0:	hero->load( type, screen_w, screen_h, width ); hero->setKeys();
		kunai->load();	skills->load( FPS, screen_w, screen_h );
		info = "setting position x, y of background";	break;
		
		case 1:	background->mechanics( hero->getX(), hero->getY() );
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
		info = "creating vampire and zombie factory";	break;
		
		case 20: vampire_factory.positioning( brick->getBlocks(), difficulty );
				 vampire_factory.positioning( islands->getBlocks(), difficulty );
				 zombie_factory.positioning( brick->getBlocks(), difficulty );
				 zombie_factory.positioning( islands->getBlocks(), difficulty );
				 vampire_factory.positioning( islands->getBlocks(), difficulty );
				 zombie_factory.positioning( brick->getBlocks(), difficulty );
		info = "setting money multiplier";	break;
		
		case 21: coins->setChance( difficulty );
		info = "positioning boulders";	break;
		
		case 22: boulder->positioning( brick->getBlocks(), wall->getXs(), difficulty );
				 boulder->positioning( islands->getBlocks(), wall->getXs(), difficulty );
		info = "setting doors";	break;
		
		case 23: door->positioning( brick->getLastBlock() );
		info = "loading music";	break;
		
		case 24: setSound();	reloadMusic();
		info = "loading money";	break;
		
		case 25: money->loadMoney();	money->setText();
		info = "settings scores";	break;
		
		case 26: scores->positioning( difficulty );
		info = "positioning score dots";	break;
		
		case 27: score_dots->positioning( difficulty, brick->getBlocks(), brick->getWidth() );
				 score_dots->positioning( difficulty, islands->getBlocks(), brick->getWidth() );
		info = "positioning spikes";	break;
		
		case 28: spikes->positioning( brick->getBlocks(), islands->getBlocks(), difficulty );
		info = "done"; break;
		
		default:
		return true;
		break;
	}
	
	state ++;
	
	return false;
}

string Halloween::getInfo()
{
	return info;
}



bool Halloween::defeatState()
{
	if( hero->isDead() && background->getAlpha() == 0 )
	{
		money->saveMoney();
		return true;
	}
	
	return false;
}

bool Halloween::winState()
{
	if( door->nextState() )
	{
		money->saveMoney();
		return true;
	}
	
	return false;
}

bool Halloween::backToLevel()
{
	return false;
}

void Halloween::setSound()
{
	// Set chunks.
	if( !sound.getChunkPlay() )
	{
		coins->turnOff();
		wall->turnOff();
		boulder->turnOff();
		spikes->turnOff();
		mine_factory->turnOff();
		vampire_factory.turnOff();
		zombie_factory.turnOff();
	}
	else
	{
		coins->turnOn();
		wall->turnOn();
		boulder->turnOn();
		spikes->turnOn();
		mine_factory->turnOn();
		vampire_factory.turnOn();
		zombie_factory.turnOn();
		
		// Set chunks volume.
		coins->setVolume( sound.getChunkVolume() );
		wall->setVolume( sound.getChunkVolume() );
		boulder->setVolume( sound.getChunkVolume() );
		spikes->setVolume( sound.getChunkVolume() );
		mine_factory->setVolume( sound.getChunkVolume() );
		vampire_factory.setVolume( sound.getChunkVolume() );
		zombie_factory.setVolume( sound.getChunkVolume() );
	}
	
	// Set music volume.
	music->setVolume( sound.getMusicVolume() );
}

void Halloween::reloadMusic()
{
	music->reload();
	Mix_HaltMusic();
}