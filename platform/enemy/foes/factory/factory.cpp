#include "factory.h"
#include "platform/enemy/foes/skeleton/skeleton.h"
#include "platform/enemy/foes/golem/golem.h"
#include "platform/enemy/foes/vampire/vampire.h"
#include "platform/enemy/foes/zombie/zombie.h"
#include "platform/enemy/foes/robot/robot.h"
#include "file/file.h"

template <typename F>
Factory<F>::Factory()
{
	width = 0;
	screen_w = 0;
	screen_h = 0;
	
	deadRect = NULL;
	expletive = NULL;
	lastHP = 0;
}

template <typename F>
Factory<F>::~Factory()
{
	// printf( "called1\n" );
	free();
}




template <typename F>
void Factory<F>::free()
{
	width = 0;
	screen_w = 0;
	screen_h = 0;
	
	if( !lines.empty() )
	{
		lines.clear();
	}
		
	if( !foes.empty() )
	{
		for( auto &i :foes )
		{
			i->free();
		}
		
		foes.clear();
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
	
	hp.free();
	
	if( deadRect != NULL )
	{
		delete deadRect;
		deadRect = NULL;
	}
	
	if( expletive != NULL )
	{
		delete expletive;
		expletive = NULL;
	}
	
	lastHP = 0;
}

template <typename F>
void Factory<F>::reset( int distance )
{
	hp.setAlpha( 0xFF );
	for( auto &it :foes )
	{
		it->reset( distance );
	}
}




template <typename F>
void Factory<F>::load( int width, int screen_w, int screen_h, string name )
{
	free();
	
	// printf( "%lu\n", sprites.size() );
	
	this->width = width;
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	// load lines
	MyFile file;
	
	file.load( "data/txt/enemy/lines/" +name +".txt" );
	if( file.is_good() )
	{
		string line;
		while( getline( file.get(), line ) )
		{
			lines.push_back( con::stoi( line ) );
			// printf( "%d\n", lines[ lines.size() -1 ] );
		}
		
		for( unsigned i = 0; i < lines.size(); i++ )
		{
			sprites.push_back( new MySprite() );
			sprites[ sprites.size() -1 ]->setName( name +"-sprites[ " +con::itos( i ) +" ]" );
			sprites[ sprites.size() -1 ]->load( "data/platform/enemy/" +name +"/" +con::itos( i ) +".png", lines[ i ] );
		}
	}
	file.free();
	
	file.load( "data/txt/enemy/multipliers/" +name +".txt" );
	if( file.is_good() )
	{
		int nr = 0;
		int wide = 0;
		vector< pair<int, int> > temporary;
		
		string line;
		while( getline( file.get(), line ) )
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
						nr = con::stoi( first );
						first = "";
						for( unsigned j = i +1; j < line.size(); j++ )
						{
							if( line[ j ] == ' ' )
							{
								wide = con::stoi( first );
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
				/*
				for( unsigned i = 0; i < temporary.size(); i++ )
				{
					printf( "-- %d %d %f\n", std::get<0>( temporary[ i ] ), std::get<1>( temporary[ i ] ), std::get<2>( temporary[ i ] ) );
				}
				*/
				
				multiplier.push_back( temporary );
				temporary.clear();
			}
		}
	}
	file.free();
	
	file.load( "data/txt/enemy/features/" +name +".txt" );
	if( file.is_good() )
	{
		string line;
		while( getline( file.get(), line ) )
		{
			// printf( "%f\n", con::stof( line ) );
			features.push_back( con::stof( line.c_str() ) );
		}
	}
	file.free();
	
	hp.setName( "factory-hp" );
	hp.setFont( "data/initialization/Jaapokki-Regular.otf", 16, 0xFF, 0x33, 0x33 );
	hp.setText( " " );
	hp.setAlpha( 0xFF );
	
	expletive = new Expletive;
	expletive->load( name );
}

template <typename F>
void Factory<F>::draw( sf::RenderWindow* &window )
{
	for( auto &i :foes )
	{
		if( i->isAlive() )
		{
			if( i->getX() > -width*3 && i->getX() < screen_w + width*4 )
			{
				if( i->getHeartPoints() > 0 )
				{
					hp.setText( "HP: " +con::itos( i->getHeartPoints() ) );
					hp.setPosition( i->getRealX() +i->getRealWidth()/2 -hp.getWidth()/2, i->getRealY() -30 );
					window->draw( hp.get() );
				}
				
				sprites[ i->getState() ]->setOffset( i->getOffset() );
				sprites[ i->getState() ]->setPosition( i->getX(), i->getY() );
				sprites[ i->getState() ]->setScale( i->getHorizontalScale(), i->getVerticalScale() );
				window->draw( sprites[ i->getState() ]->get() );
			}
		}
	}
	
	/*
	// create an empty shape
	sf::ConvexShape convex;
	
	// resize it to 4 points
	convex.setPointCount(4);
	
	// define the points
	foes[ 0 ]->setScale( foes[ 0 ]->getHorizontalScale(), foes[ 0 ]->getVerticalScale() );
	convex.setPoint( 0, sf::Vector2f( foes[ 0 ]->getAttackX(), foes[ 0 ]->getAttackY() ) );
	convex.setPoint( 1, sf::Vector2f( foes[ 0 ]->getAttackX() +foes[ 0 ]->getAttackWidth(), foes[ 0 ]->getAttackY() ) );
	
	convex.setPoint( 2, sf::Vector2f( foes[ 0 ]->getAttackX() +foes[ 0 ]->getAttackWidth(), foes[ 0 ]->getAttackY() +foes[ 0 ]->getAttackHeight() ) );
	convex.setPoint( 3, sf::Vector2f( foes[ 0 ]->getAttackX(), foes[ 0 ]->getAttackY() +foes[ 0 ]->getAttackHeight() ) );
	window->draw( convex );
	*/
}

template <typename F>
void Factory<F>::fadein( int v, int max )
{
	for( auto &i :sprites )
	{
		i->fadein( v, max );
	}
}

template <typename F>
void Factory<F>::fadeout( int v, int min )
{
	hp.fadeout( v, min );
	
	for( auto &i :sprites )
	{
		i->fadeout( v, min );
	}
}






template <typename F>
void Factory<F>::add( int x, int y, int chance )
{
	foes.push_back( new F() );
	
	vector <float> myX;
	vector <float> myX2;
	vector <float> myY;
	vector <int> widths;
	vector <int> heights;
	
	float scale = static_cast <float> (rand()%10 +features[ SCALE ] ) /100;
	foes[ foes.size() -1 ]->setScale( scale, scale );
	
	// printf( "%f\n", scale );
	
	for( unsigned i = 0; i < sprites.size(); i++ )
	{
		sprites[ i ]->setScale( scale, scale );
		myX.push_back( x -sprites[ i ]->getWidth()/2 +width/2 );
		myX2.push_back( x -sprites[ i ]->getWidth()/2 +width/2 );
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
	
	// myX2
	for( unsigned i = 0; i < multiplier[ 2 ].size(); i++ )
	{
		nr = std::get<0>( multiplier[ 2 ][ i ] );
		wide = std::get<1>( multiplier[ 2 ][ i ] ) *scale;
		
		// printf( "%d %d %f\n", nr, wide, scale );
		myX2[ nr ] += wide;
	}
	
	
	foes[ foes.size() -1 ]->setX( myX );
	foes[ foes.size() -1 ]->setX2( myX2 );
	foes[ foes.size() -1 ]->setY( myY );
	foes[ foes.size() -1 ]->setLine( lines );
	foes[ foes.size() -1 ]->setWidth( widths );
	foes[ foes.size() -1 ]->setHeight( heights );
	foes[ foes.size() -1 ]->setVelocity( static_cast <float>(chance) /100 *features[ VEL ] );
	foes[ foes.size() -1 ]->setDelay( features[ DELAY ] );
	foes[ foes.size() -1 ]->setDamage( features[ DAMAGE ] +static_cast <float> (chance) /100 *features[ DAMAGE ] );
	foes[ foes.size() -1 ]->setHeartPoints( features[ HP ] +static_cast <float> (chance) /100 *features[ HP ] );
	foes[ foes.size() -1 ]->setAttackLine( rand()%2 +features[ AL ] );
	
	myX.clear();
	myX2.clear();
	myY.clear();
	widths.clear();
	heights.clear();
}

template <typename F>
void Factory<F>::positioning( vector <Block*> blocks, int chance )
{
	int my_chance = chance;
	if( chance <= 33 )
	{
		my_chance = 50;
	}
	else if( chance <= 66 )
	{
		my_chance = 75;
	}
	
	// printf( "%d\n", my_chance );
	
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
				if( rand()%100 < my_chance )
				{
					int additional_nr = rand()%counter;
					add( startX +width*additional_nr, startY +2, chance );
					foes[ foes.size() -1 ]->setBorders( startX, startX +width*counter );
				}
			}
		}
	}
}

template <typename F>
void Factory<F>::positioningIslands( vector <Block*> blocks, int chance )
{
	int my_chance = chance;
	if( chance <= 33 )
	{
		my_chance = 50;
	}
	else if( chance <= 66 )
	{
		my_chance = 75;
	}
	
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		if( blocks[ i ]->nr == 3 || blocks[ i ]->nr == 0 )
		{
			int counter = 1;
			float startX = blocks[ i ]->x;
			float startY = blocks[ i ]->y;
			
			for( unsigned j = i +1; j < blocks.size(); j++ )
			{
				if( blocks[ j ]->nr >= 0 && blocks[ j ]->nr <= 5 &&
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
				if( rand()%100 < my_chance )
				{
					int additional_nr = rand()%counter;
					add( startX +width*additional_nr, startY +2, chance );
					foes[ foes.size() -1 ]->setBorders( startX, startX +width*counter );
				}
			}
		}
	}
}





template <typename F>
void Factory<F>::appear( Rect* rect )
{
	for( auto &it :foes )
	{
		it->appear( rect );
	}
}

template <typename F>
void Factory<F>::walk( Rect* rect )
{
	for( auto &it :foes )
	{
		it->walk( rect );
	}
}

template <typename F>
bool Factory<F>::harm( Rect* rect, int damage, bool group )
{
	bool harmed = false;
	if( rect != NULL )
	{
		for( auto &i :foes )
		{
			if( i->isAlive() && i->getHeartPoints() > 0 )
			{
				if( i->getRealX() > -width*2 && i->getRealX() < screen_w +width*2 )
				{
					Rect r;
					r.set( i->getRealX(), i->getRealY(), i->getRealWidth(), i->getRealHeight() );
					if( r.checkRectCollision( *rect ) )
					{
						expletive->playHits();
						i->harm( -damage );
						if( i->getHeartPoints() <= 0 )
						{
							deadRect = new Rect;
							deadRect->set( i->getRealX() +i->getRealWidth()/2, i->getPlane(), i->getLeft(), i->getRight() );
							i->setDead();
						}
						
						harmed = true;
						if( !group )
						{
							break;
						}
					}
				}
			}
		}
	}
	
	return harmed;
}

template <typename F>
bool Factory<F>::stunt( Rect* rect, float s )
{
	bool harmed = false;
	if( rect != NULL )
	{
		for( auto &i :foes )
		{
			if( i->isAlive() && i->getHeartPoints() > 0 )
			{
				if( i->getRealX() > -width*2 && i->getRealX() < screen_w +width*2 )
				{
					Rect r;
					r.set( i->getRealX(), i->getRealY(), i->getRealWidth(), i->getRealHeight() );
					if( r.checkRectCollision( *rect ) )
					{
						expletive->playHits();
						i->stunt( s );
						harmed = true;
					}
				}
			}
		}
	}
	
	return harmed;
}

template <typename F>
void Factory<F>::ableAttack( Rect* rect )
{
	if( rect != NULL )
	{
		for( typename vector <F*> ::iterator i = foes.begin(); i != foes.end(); i++ )
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

template <typename F>
bool Factory<F>::harmSomebody( Rect* rect )
{
	if( rect != NULL )
	{
		
		for( typename vector <F*> ::iterator i = foes.begin(); i != foes.end(); i++ )
		{
			if( (*i)->isAlive() )
			{
				if( (*i)->harmSomebody() && (*i)->getX() > -width*2 && (*i)->getX() < screen_w +width*2 )
				{
					expletive->playAttacks();
					Rect r;
					r.set( (*i)->getAttackX(), (*i)->getAttackY(), (*i)->getAttackWidth(), (*i)->getAttackHeight() );
					if( r.checkRectCollision( *rect ) )
					{
						// printf( "collision!\n" );
						this->sword = i;
						return true;
					}
				}
			}
		}
	}
	
	return false;
}




template <typename F>
int Factory<F>::getDamage()
{
	return (*sword)->getDamage();
}

template <typename F>
Rect* Factory<F>::getDeadRect()
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




template <typename F>
void Factory<F>::moveX( sf::Uint8 direction, float vel )
{
	if( direction == 1 )
	{
		for( auto &it :foes )
		{
			it->moveX( vel );
		}
	}
	else if( direction == 2 )
	{
		for( auto &it :foes )
		{
			it->moveX( -vel );
		}
	}
}

template <typename F>
void Factory<F>::undoFall( sf::Uint8 add )
{
	for( auto &it :foes )
	{
		it->moveX( add );
	}
}

template <typename F>
void Factory<F>::mechanics()
{
	for( auto &i :foes )
	{
		i->mechanics();
	}
}

template <typename F>
void Factory<F>::setColor( sf::Color color )
{
	hp.setAlpha( color.a );
	
	for( auto &i :sprites )
	{
		i->setColor( color );
	}
}



template <typename F>
void Factory<F>::turn()
{
	expletive->turn();
}

template <typename F>
void Factory<F>::turnOn()
{
	expletive->turnOn();
}

template <typename F>
void Factory<F>::turnOff()
{
	expletive->turnOff();
}

template <typename F>
void Factory<F>::setVolume( int v )
{
	expletive->setVolume( v );
}


template class Factory <Skeleton>;
template class Factory <Golem>;
template class Factory <Vampire>;
template class Factory <Zombie>;
template class Factory <Robot>;