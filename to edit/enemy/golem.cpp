#include "golem.h"

Golem::Golem()
{
	state = 0;
	
	nr = 0;
	sprite = NULL;
	
	which = 0;
	offset = 0;
	delay = 0;
	
	leftX = NULL;
	rightX = NULL;
	centerX = 0;
	
	scale = 0;
	vel = 0;
	hit_counter = 0;
	right = false;
	
	life = 0;
	hit = 0;
	strength = 0;
}

Golem::~Golem()
{
	free();
}

void Golem::free()
{
	state = 0;
	
	if( sprite != NULL )
	{
		for( int i = 0; i < nr; i++ )
		{
			sprite[ i ].free();
		}
		
		delete [] sprite;
		sprite = NULL;
		nr = 0;
	}
	
	which = 0;
	offset = 0;
	delay = 0;
	
	if( leftX != NULL )
	{
		delete [] leftX;
		leftX = NULL;
	}
	
	if( rightX != NULL )
	{
		delete [] rightX;
		rightX = NULL;
	}
	
	centerX = 0;
	
	scale = 0;
	vel = 0;
	
	life_bar.free();
	
	hit_counter = 0;
	right = false;
	
	life = 0;
	hit = 0;
	strength = 0;
}

	
void Golem::load()
{
	free();
	
	nr = 4;
	sprite = new MySprite [ nr ];
	leftX = new float [ nr ];
	rightX = new float [ nr ];
	
	for( int i = 0; i < nr; i++ )
		sprite[ i ].setName( "golem-sprite[" + to_string(i) + "]" );
		
	sprite[ 0 ].load( "data/sprites/enemy/golem/0.png", APPEAR );
	sprite[ 1 ].load( "data/sprites/enemy/golem/1.png", WALK );
	sprite[ 2 ].load( "data/sprites/enemy/golem/2.png", ATTACK );
	sprite[ 3 ].load( "data/sprites/enemy/golem/3.png", DEAD );
	
	scale = 0.4;
	for( int i = 0; i < nr; i++ )
		sprite[ i ].setScale( scale, scale );
	
	delay = 6;
	vel = 0.2;
	
	life_bar.setName( "golem-life_bar" );
	life_bar.create( sprite[ 1 ].getWidth() *3 /4, 15 );
	life_bar.setColor( sf::Color( 0xFF, 0x66, 0x66 ) );
	
	life = 1;
	hit = 0.03;
	strength = 0.05;
}

void Golem::setXY( int x, int y )
{
	for( int i = 0; i < nr; i++ )
	{
		sprite[ i ].setPosition( x, y -sprite[ i ].getHeight() );
		leftX[ i ] = sprite[ i ].getX();
		rightX[ i ] = sprite[ i ].getX() + sprite[ i ].getWidth();
	}
	
	centerX = leftX[ 1 ] + sprite[ 1 ].getWidth()/2;
	life_bar.center( centerX +7, sprite[ 1 ].getY() -20, 0, 0 );
	
	if( state == 0 )
	{
		state = 1;
		which = 0;
	}
}

void Golem::draw( sf::RenderWindow* &window )
{
	if( state == 1 )
	{
		sprite[ which ].setOffset( offset/delay );
		window->draw( sprite[ which ].get() );
		
		offset ++;
		if( offset == APPEAR*delay )
		{
			offset = 0;
			state = 2;
			which = 1;
		}
	}
	else if( state == 2 )
	{
		sprite[ which ].setOffset( offset/delay );
		window->draw( sprite[ which ].get() );
		
		if( life > 0 )
		{
			life_bar.setScale( life, 1 );
			window->draw( life_bar.get() );
		}
		
		offset ++;
		if( offset == WALK*delay )
			offset = 0;
			
		if( hit_counter > 0 && hit_counter < 10 )
		{
			for( int i = 1; i < nr-1; i++ )
			{
				sprite[ i ].setColor( sf::Color( 0xFF, 0x66, 0x66 ) );
			}
			hit_counter ++;
		}
		else
		{
			hit_counter = 0;
			for( int i = 1; i < nr-1; i++ )
			{
				sprite[ i ].setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
			}
		}
	}
	else if( state == 3 )
	{
		sprite[ which ].setOffset( offset/delay );
		window->draw( sprite[ which ].get() );
		
		offset ++;
		if( offset == DEAD*delay )
		{
			offset = 0;
			state = 4;
		}
	}
}

void Golem::fadein( int v, int max )
{
	for( int i = 0; i < nr; i++ )
		sprite[ i ].fadein( v, max );
		
	life_bar.fadein( v, max );
}

void Golem::fadeout( int v, int min )
{
	for( int i = 0; i < nr; i++ )
		sprite[ i ].fadeout( v, min );
		
	life_bar.fadeout( v, min );
}

void Golem::fitX( int x )
{
	if( x > centerX )
	{
		for( int i = 0; i < nr; i++ )
		{
			sprite[ i ].setScale( -scale, scale );
			sprite[ i ].setPosition( rightX[ i ], sprite[ i ].getY() );
		}
	}
	else if( x < centerX )
	{
		for( int i = 0; i < nr; i++ )
		{
			sprite[ i ].setScale( scale, scale );
			sprite[ i ].setPosition( leftX[ i ], sprite[ i ].getY() );
		}
	}
	
	if( leftX[ 1 ] > x )
	{
		centerX -= vel;
		for( int i = 0; i < nr; i++ )
		{
			leftX[ i ] -= vel;
			rightX[ i ] -= vel;
		}
		right = false;
	}
	else if( rightX[ 1 ] < x )
	{
		centerX += vel;
		for( int i = 0; i < nr; i++ )
		{
			leftX[ i ] += vel;
			rightX[ i ] += vel;
		}
		right = true;
	}
	
	life_bar.center( centerX +7, sprite[ 1 ].getY() -20, 0, 0 );
}

bool Golem::checkCollision( int x, int y, int w, int h )
{
	if( state != 1 && state != 3 )
	{
		for( int i = 1; i < nr-1; i++ )	// without appear and dead animation
		{
			if( right ) x += sprite[ i ].getWidth();
			if( sprite[ i ].checkCollision( x, y, w, h ) )
			{
				// printf( "%d %d %d %d\n", x, y, w, h );
				life -= hit;
				hit_counter = 1;
				
				if( life < 0 && state < 3 )
				{
					state = 3;
					offset = 0;
					which = 3;
				}
					
				return true;
			}
		}
	}
	
	return false;
}