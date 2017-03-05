#include "hero.h"
#include <fstream>


Hero::Hero()
{
	which = 0;
	offset = 0;
	delay = 0;
	
	vel = 0;
	jump_vel = 0;
	grav = 0;
	scale = 0;
	
	damage = 0;

	right = false;
	move = false;
	
	glide = false;
	
	slide = false;
	
	climb = 0;
	
	dead = 0;
	
	scope = false;
	
	fallen = false;
	fallenCounter = 0;
	fallenLine = 0;
	fallenY = -1;
}

Hero::~Hero()
{
	free();
}

void Hero::free()
{
	if( !keys.empty() )
	{
		for( auto &i :keys )
		{
			if( i != NULL )
			{
				delete [] i;
				i = NULL;
			}
		}
		
		keys.clear();
	}
	
	if( !sprite.empty() )
	{
		for( auto &i :sprite )
		{
			i->free();
		}
		
		sprite.clear();
	}
	
	which = 0;
	offset = 0;
	delay = 0;
	
	vel = 0;
	jump_vel = 0;
	grav = 0;
	scale = 0;
	
	right = false;
	move = false;
	
	damage = 0;
	
	glide = false;
	
	slide = false;
	
	climb = 0;
	
	dead = 0;
	
	j.free();
	a.free();
	ja.free();
	t.free();
	jt.free();
	
	// box.free();
	// jumpBox.free();
	
	scope = false;
	
	fallen = false;
	fallenCounter = 0;
	fallenLine = 0;
	fallenY = -1;
	
	if( !x.empty() )
	{
		x.clear();
	}
	
	if( !x2.empty() )
	{
		x2.clear();
	}
	
	if( !y.empty() )
	{
		y.clear();
	}
}




void Hero::load( int type, int screen_w, int screen_h, int width )
{
	free();
	
	// 	Set scale.
	scale = 0.75;
	
	int nr = DEAD +1;
	for( int i = 0; i < nr; i++ )
	{
		sprite.push_back( new MySprite() );
		sprite[ i ]->setName( "hero-sprite[" + to_string( i ) + "]" );
		sprite[ i ]->load( "data/04_platform/hero/" + to_string( type ) + "/" + to_string( i ) + ".png", nr -1 );
		sprite[ i ]->setScale( scale, scale );
		
		x.push_back( width /2 );
		x2.push_back( width /2 +sprite[ i ]->getWidth() );
		y.push_back( screen_h -sprite[ i ]->getHeight() -(static_cast <float> (width)*1.5) );
	}
	
	// Start values.
	which = IDLE;
	offset = 0;
	delay = 7;
	
	// Set other values
	vel = 1;
	jump_vel = vel*2 +1;
	grav = 1;
	
	right = true;
	move = false;
	
	// Duration
	j.setLine( (nr-1)*delay + 10*delay );
	a.setLine( (nr-1)*delay + 2*delay );
	ja.setLine( (nr-1)*delay + 2*delay );
	t.setLine( (nr-1)*delay + 2*delay );
	jt.setLine( (nr-1)*delay + 2*delay );
	
	fallenLine = 540;
	
	// corrections
	x[ RUN ] -= sprite[ IDLE ]->getWidth() -20*scale;
	y[ RUN ] += 3;
	if( type == 1 )
		x[ RUN ] += 30 *scale;
	x[ THROW ] -= 21*scale;
	if( type == 1 )
		x[ THROW ] += 8 *scale;
	x2[ THROW ] -= 15*scale;
	if( type == 1 )
		x2[ THROW ] += 5 *scale;
	y[ THROW ] ++;
	x[ ATTACK ] = x[ RUN ];
	x2[ ATTACK ] = x2[ RUN ];
	y[ ATTACK ] += 12*scale;
	x2[ SLIDE ] -= sprite[ IDLE ]->getWidth()/2;
	x[ JUMP ] -= (sprite[ JUMP ]->getWidth() -sprite[ IDLE ]->getWidth() );
	x[ JUMP_ATTACK ] -= (sprite[ JUMP ]->getWidth() -sprite[ IDLE ]->getWidth() );
	y[ JUMP_ATTACK ] += 13*scale;
	x2[ JUMP_ATTACK ] -= (sprite[ JUMP ]->getWidth() -sprite[ IDLE ]->getWidth() );
	x[ JUMP_THROW ] -= (sprite[ JUMP ]->getWidth() -sprite[ IDLE ]->getWidth() );
	y[ JUMP_THROW ] -= 10*scale;
	x2[ DEAD ] -= (sprite[ DEAD ]->getWidth() -sprite[ IDLE ]->getWidth() );
	y[ DEAD ] += 5*scale;
	x[ GLIDE ] -= (sprite[ GLIDE ]->getWidth() -sprite[ IDLE ]->getWidth() );
	
	// damage
	fstream file;
	file.open( "data/txt/hero/sword_current.txt" );
	if( file.bad() )
	{
		printf( "Something went wrong with data/txt/hero/sword_current.txt\n" );
	}
	else
	{
		string line;
		file >> line;
		damage = stof( line );
	}
	file.close();
}

void Hero::setKeys()
{
	if( !keys.empty() )
	{
		for( auto &it :keys )
		{
			delete [] it;
		}
		
		keys.clear();
	}
	
	// Set keys.
	fstream file;
	file.open( "data/txt/keyboard/keyboard_temporary.txt" );
	if( file.bad() )
	{
		printf( "Cannot open file! (hero)\n" );
	}
	else
	{
		string line;
		for( unsigned i = 0; i < sprite.size(); i ++ )
		{
			int* arrow;
			keys.push_back( arrow );
			keys[ i ] = new int[ 2 ];
			
			file >> line;	keys[ i ][ 0 ] = strToInt( line );
			file >> line;	keys[ i ][ 1 ] = strToInt( line );
		}
	}
	file.close();
}

void Hero::draw( sf::RenderWindow* &window )
{
	if( dead == 0 )
	{
		makeFall();
	}
	
	if( dead != 2 )
	{
		sprite[ which ]->setOffset( offset /delay );
	}
	
	
	if( !fallen )
	{
		for( unsigned i = 0; i < sprite.size(); i++ )
		{
			if( !right )	sprite[ i ]->setPosition( x2[ i ], y[ i ] +1 );
			else			sprite[ i ]->setPosition( x[ i ], y[ i ] +1 );
		}
		
		float scaleY = scale;
		if( scaleY < 0 )	scaleY = -scaleY;
		
		sprite[ which ]->setScale( scale, scaleY );
		window->draw( sprite[ which ]->get() );
	}
	
	if( dead != 2 )
	{
		if( climb == 1 || ( climb == 0 && which != CLIMB ) )
		{
			offset ++;
		}
		//printf( "%d\n", offset );
		if( offset == (sprite.size()-1) *delay || ( dead == 1 && offset == (sprite.size()-1) *delay-1 ) )
		{
			offset = 0;
			j.setActive( false );
			a.setActive( false );
			ja.setActive( false );
			t.setActive( false );
			jt.setActive( false );
			
			if( dead == 1 )
			{
				dead = 2;
			}
		}
	}
}



void Hero::fadein( int v, int max )
{
	for( auto &i :sprite )
	{
		i->fadein( v, max );
	}
}

void Hero::fadeout( int v, int min )
{
	for( auto &i :sprite )
	{
		i->fadeout( v, min );
	}
}


int Hero::strToInt( string s )
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
      tmp = 10 *tmp+s[ i ] -48;
      i++;
    }
	
    return m ? -tmp : tmp;   
}

bool Hero::checkKeys( int a, int b )
{
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( a ) ) && b == -1 )
	{
		return true;
	}
	else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( a ) ) )
	{
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( b ) ) )
		{
			return true;
		}
	}

	return false;
}


int Hero::getX()
{
	return static_cast <int> (x[ IDLE ]);
}

int Hero::getY()
{
	if( which == SLIDE )
	{
		return y[ SLIDE ];
	}
	
	return y[ IDLE ];
}

int Hero::getW()
{
	return sprite[ IDLE ]->getWidth();
}

int Hero::getH()
{
	if( which == SLIDE )
	{
		return sprite[ SLIDE ]->getHeight();
	}
	
	return sprite[ IDLE ]->getHeight();
}


float Hero::getVel()
{
	return vel;
}

float Hero::getJump_vel()
{
	return jump_vel;
}

void Hero::setScope( bool scope )
{
	this->scope = scope;
}

bool Hero::checkFall( int screen_h )
{
	if( getY() > screen_h +getH() /2 && !fallen )
	{
		fallen = true;
		return true;
	}
	
	return false;
}

void Hero::setFallenY( int y )
{
	fallenY = y -sprite[ IDLE ]->getHeight() -40;
}

bool Hero::isFallen()
{
	return fallen;
}

void Hero::undoFallX( sf::Uint8 add )
{
	moveX( -add );
}

void Hero::undoFallY()
{
	if( fallenY < y[ IDLE ] && fallenY != -1 )
	{
		for( auto &i :y )
		{
			i -= 10;
		}
	}
	else
	{
		fallenY = -1;
	}
}

void Hero::runFallenCounter()
{
	if( fallen )
	{
		fallen = !fallen;
		fallenCounter = 1;
	}
}



void Hero::makeFall()
{
	if( fallenCounter > 0 && !fallen )
	{
		fallenCounter ++;
		
		if( fallenCounter%60 == 0 )	// 1 sec
		{
			if( sprite[ IDLE ]->getAlpha() == 100 )
			{
				for( auto &i :sprite )
				{
					i->setAlpha( 0xFF );
				}
			}
			else
			{
				for( auto &i :sprite )
				{
					i->setAlpha( 100 );
				}
			}
		}
	}
	
	if( fallenCounter == fallenLine )
	{
		fallenCounter = 0;
		for( auto &i :sprite )
		{
			i->setAlpha( 0xFF );
		}
	}
}

void Hero::die()
{
	if( dead == 0 )
	{
		dead = 1;
		
		if( which <= SLIDE )
		{
			offset = 0;
			j.setActive( false );
			a.setActive( false );
			ja.setActive( false );
			t.setActive( false );
			jt.setActive( false );
			which = DEAD;
		}
		else
		{
			offset = (sprite.size()-1)*delay -1;
		}
	}
}

bool Hero::isDead()
{
	if( dead == 2 )
	{
		return true;
	}
	
	return false;
}



sf::Uint8 Hero::getDirection()
{
	if( move )
	{
		if( right )
		{
			return 2;
		}
		else
		{
			return 1;
		}
	}

	return 0;
}

bool Hero::getSide()
{
	return right;
}

Rect* Hero::getRect()
{
	Rect* rect = new Rect;
	rect->set( x[ IDLE ], y[ IDLE ], sprite[ IDLE ]->getWidth(), sprite[ IDLE ]->getHeight() );
	return rect;
}

void Hero::reset( int posY )
{
	int startX = 100;
	int startY = posY -sprite[ IDLE ]->getHeight() -500;
	
	while( true )
	{
		if( x[ IDLE ] > startX )
		{
			for( auto &i :x )
			{
				i -= 2;
			}
			
			for( auto &i :x2 )
			{
				i -= 2;
			}
		}
		else
		{
			break;
		}
	}
	
	while( true )
	{
		if( y[ IDLE ] > startY )
		{
			for( auto &i :y )
			{
				i -= 2;
			}
		}
		else
		{
			break;
		}
	}
	
	dead = 0;
	which = IDLE;
}

void Hero::setColor( sf::Color color )
{
	for( auto &i :sprite )
	{
		i->setColor( color );
	}
}