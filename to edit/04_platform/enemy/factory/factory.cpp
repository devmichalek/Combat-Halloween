#include "04_platform/enemy/factory/factory.h"
#include "04_platform/enemy/skeleton/skeleton.h"
#include "04_platform/enemy/golem/golem.h"
#include <fstream>

template <typename F>
Factory<F>::Factory()
{
	// printf( "called0\n" );
	width = 0;
	screen_w = 0;
	screen_h = 0;
	
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
	
	if( !m.empty() )
	{
		for( auto &it :m )
		{
			if( !it.empty() )
			{
				it.clear();
			}
		}
		
		m.clear();
	}
	
	if( !features.empty() )
	{
		features.clear();
	}
}

template <typename F>
void Factory<F>::reset( int distance )
{
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
	
	string txt_lines = "data/txt/enemy/lines/" +name +".txt";
	string png_sprites = "data/sprites/enemy/" +name +"/";
	string txt_multiplier = "data/txt/enemy/multiplier/" +name +".txt";
	string txt_features = "data/txt/enemy/features/" +name +".txt";
	
	// load lines
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
			lines.push_back( strToInt( line ) );
			// printf( "%d\n", lines[ lines.size() -1 ] );
		}
		
		for( unsigned i = 0; i < lines.size(); i++ )
		{
			sprites.push_back( new MySprite() );
			sprites[ sprites.size() -1 ]->setName( name +"-sprites[ " +to_string( i ) +" ]" );
			sprites[ sprites.size() -1 ]->load( png_sprites +to_string( i ) +".png", lines[ i ] );
		}
	}
	file.close();
	
	file.open( txt_multiplier );
	if( file.bad() )
	{
		printf( "Something went wrong... %s [file]\n", txt_multiplier.c_str() );
	}
	else
	{
		int nr = 0;
		int wide = 0;
		float mult = 0;
		vector < tuple <int, int, float> > temporary;
		
		string line;
		while( getline( file, line ) )
		{
			nr = 0;
			wide = 0;
			mult = 0;
			
			if( line != "a" )
			{
				// printf( "%s\n", line.c_str() );
				string first = "";
				for( unsigned i = 0; i < line.size(); i++ )
				{
					if( line[ i ] == ' ' )
					{
						nr = strToInt( first );
						first = "";
						for( unsigned j = i +1; j < line.size(); j++ )
						{
							if( line[ j ] == ' ' )
							{
								wide = strToInt( first );
								first = "";
								for( unsigned k = j +1; k < line.size(); k++ )
								{
									if( line[ k ] == ' ' )
									{
										mult = strToInt( first );
										mult /= 100;
										break;
									}
									
									first += line[ k ];
								}
								
								break;
							}
							
							first += line[ j ];
						}
						
						break;
					}
					
					first += line[ i ];
				}
				
				temporary.push_back( std::make_tuple(nr, wide, mult) );
				// printf( "%d %d %f\n", nr, wide, mult );
			}
			
			
			if( line == "a" )
			{
				for( unsigned i = 0; i < temporary.size(); i++ )
				{
					// printf( "-- %d %d %f\n", std::get<0>( temporary[ i ] ), std::get<1>( temporary[ i ] ), std::get<2>( temporary[ i ] ) );
				}
				
				m.push_back( temporary );
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
		
		int t = AMOUNT;
		while( t-- )
		{
			getline( file, line );
			features.push_back( atof( line.c_str() ) );
		}
	}
	file.close();
}

template <typename F>
void Factory<F>::draw( sf::RenderWindow* &window )
{
	for( auto &i :foes )
	{
		if( i->isAlive() )
		{
			if( i->getX() > -width*3 && i->getX() < screen_w + width*3 )
			{
				sprites[ i->getState() ]->setOffset( i->getOffset() );
				sprites[ i->getState() ]->setPosition( i->getX(), i->getY() );
				sprites[ i->getState() ]->setScale( i->getHorizontalScale(), i->getVerticalScale() );
				window->draw( sprites[ i->getState() ]->get() );
			}
		}
	}
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
	for( auto &i :sprites )
	{
		i->fadeout( v, min );
	}
}





template <typename F>
int Factory<F>::strToInt( string s )
{
    bool m = false;
    int tmp = 0;
    unsigned i = 0;
	
    if( s[ 0 ] == '-' )
    {
          i++;
          m = true;
    }
	
    while( i < s.size() )
    {
      tmp = 10*tmp +s[ i ] -48;
      i++;
    }
	
    return m ? -tmp : tmp;   
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
	for( unsigned i = 0; i < m[ 0 ].size(); i++ )
	{
		nr = std::get<0>( m[ 0 ][ i ] );
		wide = std::get<1>( m[ 0 ][ i ] ) *std::get<2>( m[ 0 ][ i ] )*scale;
		
		// printf( "%d %d %f\n", nr, wide, scale );
		myX[ nr ] += wide;
	}
	
	// myY
	for( unsigned i = 0; i < m[ 1 ].size(); i++ )
	{
		nr = std::get<0>( m[ 1 ][ i ] );
		wide = std::get<1>( m[ 1 ][ i ] ) *std::get<2>( m[ 1 ][ i ] )*scale;
		
		// printf( "%d %d %f\n", nr, wide, scale );
		myY[ nr ] += wide;
	}
	
	// myX2
	for( unsigned i = 0; i < m[ 2 ].size(); i++ )
	{
		nr = std::get<0>( m[ 2 ][ i ] );
		wide = std::get<1>( m[ 2 ][ i ] ) *std::get<2>( m[ 2 ][ i ] )*scale;
		
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
	foes[ foes.size() -1 ]->setDamage( static_cast <float> (chance) /100 *features[ DAMAGE ] );
	foes[ foes.size() -1 ]->setHeartPoints( rand()%100 +features[ HP ] );
	foes[ foes.size() -1 ]->setAttackLine( rand()%2 +features[ AL ] );
}

template <typename F>
void Factory<F>::positioning( vector <Block*> blocks, int chance )
{
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		if( blocks[ i ]->nr == 5 || blocks[ i ]->nr == 0 || blocks[ i ]->nr == 4 )
		{
			int counter = 1;
			int startX = blocks[ i ]->x;
			int startY = blocks[ i ]->y;
			
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
				if( rand()%100 < chance )
				{
					add( startX +width*(counter/2), startY, chance );
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
bool Factory<F>::harm( Rect* rect, int damage )
{
	if( rect != NULL )
	{
		for( auto &i :foes )
		{
			if( i->isAlive() && i->getHeartPoints() > 0 )
			{
				if( i->getRealX() > -width*3 && i->getRealX() < screen_w +width*3 )
				{
					Rect r;
					r.set( i->getRealX(), i->getRealY(), i->getRealWidth(), i->getRealHeight() );
					if( r.checkCollision( rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight() ) )
					{
						i->harm( -damage );
						if( i->getHeartPoints() <= 0 )
						{
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

template <typename F>
void Factory<F>::ableAttack( Rect* rect )
{
	if( rect != NULL )
	{
		for( auto &i :foes )
		{
			if( i->isAlive() )
			{
				if( i->getX() > -width*3 && i->getX() < screen_w +width*3 )
				{
					sprites[ i->getState() ]->setPosition( i->getRealX(), i->getRealY() );
					if( sprites[ i->getState() ]->checkCollision( rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight() ) )
					{
						i->ableAttack();
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
				if( (*i)->harmSomebody() && (*i)->getX() > -width*3 && (*i)->getX() < screen_w +width*3 )
				{
					Rect r;
					r.set( (*i)->getAttackX(), (*i)->getAttackY(), (*i)->getAttackWidth(), (*i)->getAttackHeight() );
					if( r.checkCollision( rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight() ) )
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
	for( auto &i :sprites )
	{
		i->setColor( color );
	}
}

template class Factory <Skeleton>;
template class Factory <Golem>;