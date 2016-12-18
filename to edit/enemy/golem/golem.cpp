#include "golem.h"



void Golem::setXY( int x, int y )
{
	for( int i = 0; i < nr; i++ )
	{
		sprite[ i ].setPosition( x, y -sprite[ i ].getHeight() );
	}
	
	centerX = x + sprite[ 1 ].getWidth()/2;
	leftX = x;
	life_bar.setPosition( x, sprite[ 1 ].getY() -20 );
	
	if( state == 0 )
	{
		state = 1;
	}
}

void Golem::matchX( Rect* rect )
{
	if( state == 2 && rect != NULL )
	{
		int x = rect->getX();
		int y = rect->getY();
		int w = rect->getWidth();
		int h = rect->getHeight();
		
		if( ( y >= sprite[ 1 ].getY() && y+h < sprite[ 1 ].getY() + sprite[ 1 ].getHeight() ) ||
			( y +h >= sprite[ 1 ].getY() && y < sprite[ 1 ].getY() + sprite[ 1 ].getHeight() ) )
		{
			if( x > centerX )
			{
				for( int i = 0; i < nr; i++ )
				{
					sprite[ i ].setScale( -scale, scale );
				}
				
				if( right )
				{
					for( int i = 0; i < nr; i++ )
					{
						sprite[ i ].setPosition( leftX + sprite[ i ].getWidth(), sprite[ i ].getY() );
					}
					
					right = false;
				}
			}
			else if( x < centerX )
			{
				for( int i = 0; i < nr; i++ )
				{
					sprite[ i ].setScale( scale, scale );
				}
				
				if( !right )
				{
					for( int i = 0; i < nr; i++ )
					{
						sprite[ i ].setPosition( leftX, sprite[ i ].getY() );
					}
					
					sprite[ 2 ].setPosition( leftX -(sprite[ 2 ].getWidth() -sprite[ 1 ].getWidth() ), sprite[ 2 ].getY() );
					
					right = true;
				}
			}
			
			if( attack_counter == 0 || attack_counter > 120 )
			{
				if( leftX +25 > x + w )
				{
					centerX -= vel;
					leftX -= vel;
					
					for( int i = 0; i < nr; i++ )
					{
						sprite[ i ].setPosition( leftX, sprite[ i ].getY() );
					}
				}
				else if( leftX + sprite[ 1 ].getWidth() -25 < x )
				{
					centerX += vel;
					leftX += vel;
					
					for( int i = 0; i < nr; i++ )
					{
						sprite[ i ].setPosition( leftX + sprite[ i ].getWidth(), sprite[ i ].getY() );
					}
				}
			}
			
			
			// life bar
			life_bar.setPosition( leftX, sprite[ 1 ].getY() -20 );
		}
	}
}

void Golem::undoMove()
{
	if( !right )
	{
		centerX -= vel;
		leftX -= vel;
	}
	else
	{
		centerX += vel;
		leftX += vel;
	}
}



bool Golem::checkHit( Rect* rect, float damage )
{
	if( state == 2 && rect != NULL )
	{
		if( right )
			attackBox.setPosition( leftX, sprite[ 1 ].getY() +10 );
		else
			attackBox.setPosition( leftX +sprite[ 1 ].getWidth() -attackBox.getWidth(), sprite[ 1 ].getY() +10 );
		
		if( attackBox.checkRectCollision( *rect ) )
		{
			life -= damage;
			hit_counter = 1;
			return true;
		}
	}
	
	return false;
}

bool Golem::checkAttackBox( Rect* rect )
{
	if( state == 2 && rect != NULL )
	{
		if( attackBox.checkCollision( rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight() ) )
		{
			if( attack_counter == 0 )
			{
				offset = 0;
				attack_counter = 1;
			}
			
			if( offset == 4*delay && attack_counter == 1 )
				return true;
		}
	}
	
	return false;
}

void Golem::makeColor()
{
	if( hit_counter > 0 )
	{
		hit_counter ++;
		
		if( hit_counter < hit_line )
		{
			for( int i = 1; i < nr-1; i++ )
			{
				sprite[ i ].setColor( sf::Color( 0xFF, 0x66, 0x66 ) );
			}
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
}




Golem::Golem()
{
	nr = 0;
	sprite = NULL;
	
	which = 0;
	offset = 0;
	delay = 0;
	
	vel = 0;
	scale = 0;
	right = false;
	
	offset_nr = NULL;
	state = 0;
	
	life = 0;
	
	centerX = 0;
	leftX = 0;
	hit_line = 0;
	hit_counter = 0;
	
	attack_line = 0;
	attack_counter = 0;
	
	damage = 0;
}

Golem::~Golem()
{
	free();
}

void Golem::free()
{
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
	
	vel = 0;
	scale = 0;
	right = false;
	
	if( offset_nr != NULL )
	{
		delete [] offset_nr;
		offset_nr = NULL;
	}
	
	state = 0;
	
	life = 0;
	life_bar.free();
	
	centerX = 0;
	leftX = 0;
	hit_line = 0;
	hit_counter = 0;
	
	attack_line = 0;
	attack_counter = 0;
	
	attackBox.free();
	
	damage = 0;
}


void Golem::load()
{
	free();
	
	nr = 4;
	sprite = new MySprite [ nr ];
	offset_nr = new int[ nr ];
	
	offset_nr[ 0 ] = 15;
	offset_nr[ 1 ] = offset_nr[ 2 ] = 6;
	offset_nr[ 3 ] = 7;
	
	scale = 0.8;
	for( int i = 0; i < nr; i++ )
	{
		sprite[ i ].setName( "golem-sprite[" + to_string(i) + "]" );
		sprite[ i ].load( "data/sprites/enemy/golem/" +to_string( i ) +".png", offset_nr[ i ] );
		sprite[ i ].setScale( scale, scale );
	}
	
	which = 0;
	offset = 0;
	delay = 6;
	vel = 0.2;
	
	life = 1;
	life_bar.setName( "golem-life_bar" );
	life_bar.create( sprite[ 1 ].getWidth(), 15 );
	life_bar.setColor( sf::Color( 0xFF, 0x66, 0x66 ) );
	
	hit_line = 10;
	hit_counter = 0;
	
	attack_line = 0xFF;
	attack_counter = 0;
	
	right = true;
	
	attackBox.setName( "golem-attackBox" );
	attackBox.create( 60, sprite[ 1 ].getHeight() -25 );
	attackBox.setColor( sf::Color( 0x44, 0xFF, 0x00 ) );
	attackBox.setAlpha( 100 );
	
	damage = 7;
}

void Golem::draw( sf::RenderWindow* &window )
{
	// APPEAR
	if( state == 1 )
	{
		if( offset == offset_nr[ which ]*delay -1 )
		{
			state = 2;
			offset = 0;
			which = 1;
		}
	}
	
	// WALK AND ATTACK
	else if( state == 2 )
	{
		if( life > 0 )
		{
			life_bar.setScale( life, 1 );
			window->draw( life_bar.get() );
		}
		else
		{
			state = 3;
			offset = 0;
			which = 3;
		}
		
		if(  attack_counter > 1 && attack_counter < attack_line )
		{
			attack_counter ++;
		}
		else if( attack_counter > 1 )
		{
			attack_counter = 0;
		}
		
		if( attack_counter == 1 )
		{
			which = 2;
			if( offset == offset_nr[ which ]*delay -1 )
			{
				offset = 0;
				which = 1;
				attack_counter = 2;
			}
		}
		
		makeColor();
	}
	
	// DEAD
	else if( state == 3 )
	{
		if( offset == offset_nr[ which ]*delay -1 )
		{
			state = 4;
		}
	}
	
	// DRAW
	if( state != 0 && state != 4 )
	{
		offset ++;
		if( offset == offset_nr[ which ]*delay )
		{
			offset = 0;
		}
		
		sprite[ which ].setOffset( offset/delay );
		window->draw( sprite[ which ].get() );
		
		if( right )
			attackBox.setPosition( leftX, sprite[ 1 ].getY() +10 );
		else	
			attackBox.setPosition( leftX +sprite[ 1 ].getWidth() -attackBox.getWidth(), sprite[ 1 ].getY() +10 );
			
		window->draw( attackBox.get() );
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



Rect* Golem::getRect()
{
	int t_x = leftX;
	int t_y = sprite[ 1 ].getY();
	int t_w = sprite[ 1 ].getWidth();
	int t_h = sprite[ 1 ].getHeight();
	
	Rect* rect = new Rect;
	rect->set( t_x, t_y, t_w, t_h );
	return rect;
}

float Golem::getDamage()
{
	return damage;
}