#include "snakes_factory.h"
#include <cstdlib>
#include <fstream>

Snakes_factory::Snakes_factory()
{
	deadRect = NULL;
	free();
}

Snakes_factory::~Snakes_factory()
{
	free();
}

void Snakes_factory::free()
{
	width = 0;
	screen_w = 0;
	screen_h = 0;
	damage = 0;
	
	hp.free();
	
	if( !snakes.empty() )
	{
		for( auto &i :snakes )
		{
			i->free();
		}
		
		snakes.clear();
	}
	
	if( !sprites.empty() )
	{
		for( auto &i :sprites )
		{
			i->free();
		}
		
		sprites.clear();
	}
	
	if( !multiplier.empty() )
	{
		for( auto &it :multiplier )
		{
			if( !it.empty() )
			{
				it.clear();
			}
		}
		
		multiplier.clear();
	}
	
	if( !features.empty() )
	{
		features.clear();
	}
	
	if( !lines.empty() )
	{
		lines.clear();
	}
	
	if( deadRect != NULL )
	{
		delete deadRect;
		deadRect = NULL;
	}
	
	hit.free();
	stand.free();
}

void Snakes_factory::reset( int distance )
{
	hp.setAlpha( 0xFF );
	for( auto &it :snakes )
	{
		it->reset( distance );
	}
}



void Snakes_factory::load( int width, int screen_w, int screen_h )
{
	free();
	
	this->width = width;
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	string txt_lines = "data/txt/enemy/lines/snakes.txt";
	string txt_multiplier = "data/txt/enemy/multipliers/snakes.txt";
	string txt_features = "data/txt/enemy/features/snakes.txt";
	
	// Set lines.
	fstream file;
	file.open( txt_lines );
	if( file.bad() )
	{
		printf( "Something went wrong... %s [file]\n", txt_lines.c_str() );
	}
	else
	{
		string line;
		while( getline( file, line ) )
		{
			lines.push_back( stoi( line ) );
		}
		
		for( unsigned i = 0; i < 3; i++ )
		{
			sprites.push_back( new MySprite() );
			sprites[ sprites.size() -1 ]->setName( "snakes_factory-sprites nr" +to_string( i ) );
			sprites[ sprites.size() -1 ]->load( "data/04_platform/enemy/snakes/" +to_string( i ) +".png", lines[ i ] );
			sprites[ sprites.size() -1 ]->setScale( 0.5, 0.5 );
		}
	}
	file.close();
	

	
	
	
	// Set sounds.
	hit.setName( "snakes_factory-hit" );
	hit.load( "data/04_platform/enemy/snakes/sounds/hit/0.wav" );
	
	stand.setName( "snakes_factory-stand" );
	//stand.load( "data/04_platform/enemy/mine/sounds/explosion.wav" );
	
	// Set HP.
	hp.setName( "snakes_factory-hp" );
	hp.setFont( "data/00_loading/Jaapokki-Regular.otf", 18, 0xFF, 0x33, 0x33 );
	hp.setText( " " );
	hp.setAlpha( 0xFF );
	
	
	file.open( txt_multiplier );
	if( file.bad() )
	{
		printf( "Something went wrong... %s [file]\n", txt_multiplier.c_str() );
	}
	else
	{
		int nr = 0;
		int wide = 0;
		vector< pair<int, int> > temporary;
		
		string line;
		while( getline( file, line ) )
		{
			nr = 0;
			wide = 0;
			
			if( line != "a" )
			{
				// printf( "%s\n", line.c_str() );
				string first = "";
				for( unsigned i = 0; i < line.size(); i++ )
				{
					if( line[ i ] == ' ' )
					{
						nr = stoi( first );
						first = "";
						for( unsigned j = i +1; j < line.size(); j++ )
						{
							if( line[ j ] == ' ' )
							{
								wide = stoi( first );
								break;
							}
							first += line[ j ];
						}
						break;
					}
					first += line[ i ];
				}
				
				temporary.push_back( std::make_pair( nr, wide ) );
				// printf( "%d %d %f\n", nr, wide, mult );
			}
			
			
			if( line == "a" )
			{
				multiplier.push_back( temporary );
				temporary.clear();
			}
		}
	}
	file.close();
	
	file.open( txt_features );
	if( file.bad() )
	{
		printf( "Something went wrong... %s [file]\n", txt_features.c_str() );
	}
	else
	{
		string line;
		while( getline( file, line ) )
		{
			// printf( "%f\n", stof( line ) );
			features.push_back( stof( line ) );
		}
	}
	file.close();
}

void Snakes_factory::draw( sf::RenderWindow* &window )
{
	for( auto &i :snakes )
	{
		if( i->isAlive() )
		{
			if( i->getX() > -width && i->getX() < screen_w + width )
			{
				if( i->getHeartPoints() > 0 )
				{
					hp.setText( "HP: " +to_string( i->getHeartPoints() ) );
					hp.setPosition( i->getRealX() +i->getRealWidth()/2 -18, i->getRealY() -60 );
					window->draw( hp.get() );
				}
				
				if( i->alphaAble() )
					sprites[ i->getState() ]->setAlpha( i->getAlpha() );
					
				sprites[ i->getState() ]->setOffset( i->getOffset() );
				sprites[ i->getState() ]->setPosition( i->getX(), i->getY() );
				window->draw( sprites[ i->getState() ]->get() );
			}
		}
	}
}



void Snakes_factory::fadein( int v, int max )
{
	for( auto &i :sprites )
	{
		i->fadein( v, max );
	}
}

void Snakes_factory::fadeout( int v, int min )
{
	for( auto &i :snakes )
	{
		i->setAlphaState( 1 );
	}
	
	hp.fadeout( v, min );
	for( auto &i :sprites )
	{
		i->fadeout( v, min );
	}
}



void Snakes_factory::addSnake( int x, int y, int chance )
{
	snakes.push_back( new Snakes() );
	
	vector <float> myX;
	vector <float> myY;
	vector <int> widths;
	vector <int> heights;
	
	float scale = static_cast <float> (rand()%10 +features[ SCALE ] ) /100;
	snakes[ snakes.size() -1 ]->setScale( scale, scale );
	
	// printf( "%f\n", scale );
	
	for( unsigned i = 0; i < sprites.size(); i++ )
	{
		sprites[ i ]->setScale( scale, scale );
		myX.push_back( x -sprites[ i ]->getWidth()/2 +width/2 );
		myY.push_back( y -sprites[ i ]->getHeight() );
		widths.push_back( sprites[ i ]->getWidth() );
		heights.push_back( sprites[ i ]->getHeight() );
	}
	
	int nr;
	int wide;
	
	// myX
	for( unsigned i = 0; i < multiplier[ 0 ].size(); i++ )
	{
		nr = std::get<0>( multiplier[ 0 ][ i ] );
		wide = std::get<1>( multiplier[ 0 ][ i ] ) *scale;
		
		// printf( "%d %d %f\n", nr, wide, scale );
		myX[ nr ] += wide;
	}
	
	// myY
	for( unsigned i = 0; i < multiplier[ 1 ].size(); i++ )
	{
		nr = std::get<0>( multiplier[ 1 ][ i ] );
		wide = std::get<1>( multiplier[ 1 ][ i ] ) *scale;
		
		// printf( "%d %d %f\n", nr, wide, scale );
		myY[ nr ] += wide;
	}
	
	
	snakes[ snakes.size() -1 ]->setX( myX );
	snakes[ snakes.size() -1 ]->setY( myY );
	snakes[ snakes.size() -1 ]->setLine( lines );
	snakes[ snakes.size() -1 ]->setWidth( widths );
	snakes[ snakes.size() -1 ]->setHeight( heights );
	snakes[ snakes.size() -1 ]->setDelay( features[ DELAY ] );
	damage = features[ DAMAGE ] +static_cast <float> (chance) /100 *features[ DAMAGE ];
	snakes[ snakes.size() -1 ]->setHeartPoints( features[ HP ] +static_cast <float> (chance) /100 *features[ HP ] );
	snakes[ snakes.size() -1 ]->setAttackLine( rand()%2 +features[ AL ] );
	
	myX.clear();
	myY.clear();
	widths.clear();
	heights.clear();
}

void Snakes_factory::positioning( vector <Block*> blocks, int chance )
{
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		if( blocks[ i ]->nr == 5 || blocks[ i ]->nr == 0 || blocks[ i ]->nr == 4 )
		{
			int counter = 1;
			float startX = blocks[ i ]->x;
			float startY = blocks[ i ]->y;
			
			for( unsigned j = i +1; j < blocks.size(); j++ )
			{
				if( blocks[ j ]->nr >= 0 && blocks[ j ]->nr <= 7 &&
					blocks[ j -1 ]->y == blocks[ j ]->y &&
					blocks[ j -1 ]->x == blocks[ j ]->x -width )
				{
					counter ++;
				}
				else
				{
					i = j;
					break;
				}
			}
			
			if( counter > 2 )
			{
				if( rand()%100 < 90 )
				{
					int additional_nr = rand()%counter;
					addSnake( startX +width*additional_nr, startY +10, chance );
					snakes[ snakes.size() -1 ]->setLeft( startX );
				}
			}
		}
	}
}




void Snakes_factory::appear( float x )
{
	for( auto &it :snakes )
	{
		it->appear( x );
	}
}

bool Snakes_factory::harm( Rect* rect, int damage )
{
	if( rect != NULL )
	{
		for( auto &i :snakes )
		{
			if( i->isAlive() && i->getHeartPoints() > 0 )
			{
				if( i->getRealX() > -width && i->getRealX() < screen_w +width )
				{
					Rect r;
					r.set( i->getRealX(), i->getRealY(), i->getRealWidth(), i->getRealHeight() );
					if( r.checkRectCollision( *rect ) )
					{
						if( hit.isPlayable() )
						{
							hit.play();
						}
						
						i->harm( -damage );
						if( i->getHeartPoints() <= 0 )
						{
							deadRect = new Rect;
							deadRect->set( i->getX(), i->getPlane(), i->getX(), i->getX() +i->getRealWidth() );
							i->setDead();
						}
						
						return true;
					}
				}
			}
		}
	}
	
	return false;
}

void Snakes_factory::ableAttack( Rect* rect )
{
	if( rect != NULL )
	{
		for( vector <Snakes*>::iterator i = snakes.begin(); i != snakes.end(); i++ )
		{
			if( (*i)->isAlive() )
			{
				if( (*i)->getX() > -width*2 && (*i)->getX() < screen_w +width*2 )
				{
					Rect r;
					r.set( (*i)->getAttackX(), (*i)->getAttackY(), (*i)->getAttackWidth(), (*i)->getAttackHeight() );
					if( r.checkRectCollision( *rect ) )
					{
						(*i)->ableAttack();
					}
				}
			}
		}
	}
}

bool Snakes_factory::harmSomebody( Rect* rect )
{
	if( rect != NULL )
	{
		for( vector <Snakes*>::iterator i = snakes.begin(); i != snakes.end(); i++ )
		{
			if( (*i)->isAlive() )
			{
				if( (*i)->harmSomebody() && (*i)->getX() > -width*2 && (*i)->getX() < screen_w +width*2 )
				{
					Rect r;
					r.set( (*i)->getAttackX(), (*i)->getAttackY(), (*i)->getAttackWidth(), (*i)->getAttackHeight() );
					if( r.checkRectCollision( *rect ) )
					{
						return true;
					}
				}
			}
		}
	}
	
	return false;
}



Rect* Snakes_factory::getDeadRect()
{
	if( deadRect != NULL )
	{
		Rect* rect = new Rect;
		rect->set( deadRect->getX(), deadRect->getY(), deadRect->getWidth(), deadRect->getHeight() );
		delete deadRect;
		deadRect = NULL;
		
		return rect;
	}
	
	return NULL;
}

void Snakes_factory::moveX( sf::Uint8 direction, float vel )
{
	if( direction == 1 )
	{
		for( auto &it :snakes )
		{
			it->moveX( vel );
		}
	}
	else if( direction == 2 )
	{
		for( auto &it :snakes )
		{
			it->moveX( -vel );
		}
	}
}

void Snakes_factory::undoFall( sf::Uint8 add )
{
	for( auto &it :snakes )
	{
		it->moveX( add );
	}
}

void Snakes_factory::mechanics()
{
	for( auto &i :snakes )
	{
		i->mechanics();
	}
}

void Snakes_factory::setColor( sf::Color color )
{
	hp.setAlpha( color.a );
	for( auto &i :sprites )
	{
		i->setColor( color );
	}
}



int Snakes_factory::getDamage()
{
	return damage;
}



void Snakes_factory::turnOn()
{
	hit.turnOn();
	// stand.turnOn();
}

void Snakes_factory::turnOff()
{
	hit.turnOff();
	// stand.turnOff();
}

void Snakes_factory::setVolume( int v )
{
	hit.setVolume( v );
	// stand.setVolume( v );
}
