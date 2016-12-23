#include "hero/hero.h"

// IDLE
void Hero::idle()
{
	if( !glide && !slide && climb == 0 )
	{
		which = IDLE;
	}
}



//--------------------------------------------------------------------------------------------------------



// MOVE
bool Hero::moving()
{
	// move left
	if( checkKeys( keys[ 0 ][ 0 ], keys[ 0 ][ 1 ] ) )
	{
		if( !glide && !slide && climb == 0 )
		{
			which = RUN;
		}
		
		// move left on the ladder
		else if( climb != 0 )
		{
			climb = 1;
		}
		
		
		mirrorLeft();
		
		if( scope != 1 )
		{
			for( int i = 0; i < nr; i++ )
			{
				sprite[ i ].setPosition( sprite[ i ].getX() -vel, sprite[ i ].getY() );
			}
		}
		
		
		move = true;
		return true;
	}
	
	// move right
	else if( checkKeys( keys[ 1 ][ 0 ], keys[ 1 ][ 1 ] ) ) 
	{
		if( !glide && !slide && climb == 0 )
		{
			which = RUN;
		}
		
		// move right on the ladder
		else if( climb != 0 )
		{
			climb = 1;
		}
		
		
		mirrorRight();
		
		if( scope != 1 )
		{
			for( int i = 0; i < nr; i++ )
			{
				sprite[ i ].setPosition( sprite[ i ].getX() +vel, sprite[ i ].getY() );
			}
		}
		
		move = true;
		return true;
	}
	
	move = false;
	return move;
}

void Hero::mirrorLeft()
{
	for( int i = 0; i < nr; i++ )
	{
		if( i != CLIMB )
		{
			sprite[ i ].setScale( -scale, scale );
		}
	}
	
	if( right )
	{
		for( int i = 0; i < nr; i++ )
		{
			if( i != IDLE && i != CLIMB )
			{
				sprite[ i ].setPosition( sprite[ IDLE ].getX() + sprite[ i ].getWidth(), sprite[ i ].getY() );
			}
		}
		
		sprite[ IDLE ].setPosition( sprite[ IDLE ].getX() + sprite[ IDLE ].getWidth(), sprite[ IDLE ].getY() );
		sprite[ ATTACK ].setPosition( sprite[ IDLE ].getX(), sprite[ IDLE ].getY() );
		sprite[ SLIDE ].setPosition( sprite[ IDLE ].getX(), sprite[ SLIDE ].getY() );
		sprite[ JUMP_ATTACK ].setPosition( sprite[ JUMP ].getX(), sprite[ JUMP ].getY() );
		sprite[ JUMP_THROW ].setPosition( sprite[ JUMP ].getX(), sprite[ JUMP ].getY() );
		sprite[ THROW ].setPosition( sprite[ THROW ].getX() -11, sprite[ IDLE ].getY() -1 );
		
		right = false;
	}
}

void Hero::mirrorRight()
{
	for( int i = 0; i < nr; i++ )
	{
		if( i != CLIMB )
		{
			sprite[ i ].setScale( scale, scale );
		}
	}
	
	if( !right )
	{
		for( int i = 0; i < nr; i++ )
		{
			if( i != CLIMB )
			{
				sprite[ i ].setPosition( sprite[ i ].getX() - ( sprite[ i ].getWidth() ), sprite[ i ].getY() );
				sprite[ i ].setPosition( sprite[ IDLE ].getX() - ( sprite[ i ].getWidth() -sprite[ IDLE ].getWidth() ), sprite[ i ].getY() );
			}
		}
		
		sprite[ ATTACK ].setPosition( sprite[ IDLE ].getX(), sprite[ IDLE ].getY() );
		sprite[ SLIDE ].setPosition( sprite[ IDLE ].getX(), sprite[ SLIDE ].getY() );
		sprite[ JUMP_ATTACK ].setPosition( sprite[ JUMP ].getX(), sprite[ JUMP ].getY() );
		sprite[ JUMP_THROW ].setPosition( sprite[ JUMP ].getX(), sprite[ JUMP ].getY() );
		sprite[ THROW ].setPosition( sprite[ THROW ].getX() +11, sprite[ IDLE ].getY() -1 );
		
		right = true;
	}
}

void Hero::undoMove()
{
	// undo move right
	if( right )
	{
		move = false;
		for( int i = 0; i < nr; i++ )
		{
			sprite[ i ].setPosition( sprite[ i ].getX() -vel, sprite[ i ].getY() );
		}
	}
	
	// undo move left
	else
	{
		move = false;
		for( int i = 0; i < nr; i++ )
		{
			sprite[ i ].setPosition( sprite[ i ].getX() +vel, sprite[ i ].getY() );
		}
	}
}



//--------------------------------------------------------------------------------------------------------



// JUMP
bool Hero::jump()
{
	if( checkKeys( keys[ 2 ][ 0 ], keys[ 2 ][ 1 ] ) && j.Do() && !glide && climb == 0 )
	{
		offset = 0;
		j.start();
		j.setActive( true );
		which = JUMP;
	}
	
	if( j.isActive() )
	{
		which = JUMP;
		move = true;
		
		if( scope != 1 )
		{
			if( right )
			{
				for( int i = 0; i < nr; i++ )
				{
					sprite[ i ].setPosition( sprite[ i ].getX() +jump_vel, sprite[ i ].getY() );
				}
			}
			else
			{
				for( int i = 0; i < nr; i++ )
				{
					sprite[ i ].setPosition( sprite[ i ].getX() -jump_vel, sprite[ i ].getY() );
				}
			}
		}
	}
	
	j.check();
	
	return j.isActive();	
}

void Hero::undoJump()
{
	if( right )
	{
		move = false;
		for( int i = 0; i < nr; i++ )
		{
			sprite[ i ].setPosition( sprite[ i ].getX() -jump_vel, sprite[ i ].getY() );
		}
	}
	else
	{
		move = false;
		for( int i = 0; i < nr; i++ )
		{
			sprite[ i ].setPosition( sprite[ i ].getX() +jump_vel, sprite[ i ].getY() );
		}
	}
}



//--------------------------------------------------------------------------------------------------------



// ATTACK
bool Hero::attack()
{
	if( checkKeys( keys[ 5 ][ 0 ], keys[ 5 ][ 1 ] ) && a.Do() && !glide && !j.isActive() && climb == 0 )
	{
		offset = 0;
		a.start();
		a.setActive( true );
		which = ATTACK;
		sprite[ ATTACK ].setPosition( sprite[ RUN ].getX(), sprite[ RUN ].getY() -3 );
	}
	
	if( a.isActive() )
	{
		which = ATTACK;
		move = false;
	}
	
	a.check();
	
	return a.isActive();
}

Rect* Hero::getAttackBox()
{
	Rect* rect = NULL;
	int t_x, t_y;	// temporary stuff
	int t_w, t_h;
	
	if( which == ATTACK && offset == 6*delay )
	{
		rect = new Rect;
		t_y = sprite[ ATTACK ].getY();
		t_w = 30;
		t_h = sprite[ ATTACK ].getHeight();

		if( right )		t_x = ( sprite[ ATTACK ].getWidth() -t_w ) + sprite[ ATTACK ].getX();
		else			t_x = sprite[ ATTACK ].getX() -sprite[ ATTACK ].getWidth();
		
		rect->set( t_x, t_y, t_w, t_h );
		return rect;
	}
	else if( which == JUMP_ATTACK && offset == 4*delay )
	{
		rect = new Rect;
		t_y = sprite[ JUMP_ATTACK ].getY();
		t_w = 35;
		t_h = sprite[ JUMP_ATTACK ].getHeight();
							
		if( right )		t_x = ( sprite[ JUMP_ATTACK ].getWidth() -t_w ) + sprite[ JUMP_ATTACK ].getX();
		else			t_x = sprite[ JUMP_ATTACK ].getX() -sprite[ JUMP_ATTACK ].getWidth();
		
		rect->set( t_x, t_y, t_w, t_h );
		return rect;
	}

	return NULL;
}

float Hero::getDamage()
{
	return damage;
}

void Hero::harm()
{
	hit_counter = 1;
}

void Hero::makeColor()
{
	if( hit_counter > 0 )
	{
		hit_counter ++;
		
		if( hit_counter < hit_line )
		{
			for( int i = 0; i < nr; i++ )
			{
				sprite[ i ].setColor( sf::Color( 0xFF, 0x66, 0x66 ) );
			}
		}
		else
		{
			hit_counter = 0;
			
			for( int i = 0; i < nr; i++ )
			{
				sprite[ i ].setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
			}
		}
	}
}



//--------------------------------------------------------------------------------------------------------



// GLIDE
void Hero::gliding()
{
	if( climb == 0 )
	{
		which = GLIDE;
	}
}

bool Hero::isGliding()
{
	return glide;
}



//--------------------------------------------------------------------------------------------------------



// SLIDE
void Hero::sliding()
{
	if( checkKeys( keys[ 3 ][ 0 ], keys[ 3 ][ 1 ] ) )
	{
		if( !glide && climb == 0 )
		{
			slide = true;
			which = SLIDE;
		}
	}
	else
	{
		slide = false;
	}
}



//--------------------------------------------------------------------------------------------------------



// JUMP WITH ATTACK
bool Hero::jumpAttack()
{
	if( checkKeys( keys[ 6 ][ 0 ], keys[ 6 ][ 1 ] ) && ja.Do() && !glide && j.isActive() && !a.isActive() && !t.isActive() && climb == 0 )
	{
		offset = 0;
		ja.start();
		ja.setActive( true );
		which = JUMP_ATTACK;
	}
	
	if( ja.isActive() )
	{
		which = JUMP_ATTACK;
		move = true;
	
		if( scope != 1 )
		{
			if( right )
			{
				for( int i = 0; i < nr; i++ )
				{
					sprite[ i ].setPosition( sprite[ i ].getX() +jump_vel, sprite[ i ].getY() );
				}
			}
			else
			{
				for( int i = 0; i < nr; i++ )
				{
					sprite[ i ].setPosition( sprite[ i ].getX() -jump_vel, sprite[ i ].getY() );
				}
			}
		}
	}
	
	ja.check();
	
	return ja.isActive();
}



//--------------------------------------------------------------------------------------------------------



// JUMP WITH THROW
bool Hero::jumpThrow()
{
	if( checkKeys( keys[ 8 ][ 0 ], keys[ 8 ][ 1 ] ) && jt.Do() && !glide && !a.isActive() && !t.isActive() && ( j.isActive() || ja.isActive() ) && climb == 0 )
	{
		offset = 0;
		jt.start();
		jt.setActive( true );
		which = JUMP_THROW;
	}
	
	if( jt.isActive() )
	{
		which = JUMP_THROW;
		move = true;
		
		if( scope != 1 )
		{
			if( right )
			{
				for( int i = 0; i < nr; i++ )
				{
					sprite[ i ].setPosition( sprite[ i ].getX() +jump_vel, sprite[ i ].getY() );
				}
			}
			else
			{
				for( int i = 0; i < nr; i++ )
				{
					sprite[ i ].setPosition( sprite[ i ].getX() -jump_vel, sprite[ i ].getY() );
				}
			}
		}

	}
	
	jt.check();
	
	return jt.isActive();
}



//--------------------------------------------------------------------------------------------------------



// CLIMB
void Hero::climbing()
{
	if( checkKeys( keys[ 4 ][ 0 ], keys[ 4 ][ 1 ] ) && !j.isActive() && !ja.isActive() && !jt.isActive() && !glide && !t.isActive() && !a.isActive() )
	{
		which = CLIMB;
		slide = false;
		
		if( climb == 0 )
		{
			climb = 2;
		}
		else
		{
			climb = 1;
		}
		
		for( int i = 0; i < nr; i++ )
		{
			sprite[ i ].setPosition( sprite[ i ].getX(), sprite[ i ].getY() -vel );
		}
	}
	else if( climb == 1 )
	{
		climb = 2;
	}
}

void Hero::banClimbing()
{
	climb = 0;
}



//--------------------------------------------------------------------------------------------------------



// THROW
bool Hero::throwing()
{
	if( checkKeys( keys[ 7 ][ 0 ], keys[ 7 ][ 1 ] ) && !t.isActive() && !glide && !j.isActive() && !a.isActive() && climb == 0 )
	{
		offset = 0;
		t.start();
		t.setActive( true );
		which = THROW;
	}
	
	if( t.isActive() )
	{
		which = THROW;
		move = false;
	}
	
	t.check();
	
	return t.isActive();
}

bool Hero::throwed()
{
	if( offset == 3*delay )
	{
		return true;
	}
	
	return false;
}



//--------------------------------------------------------------------------------------------------------



// GRAVITY STUFF
void Hero::gravitation()
{
	if( !j.isActive() && !ja.isActive() && !jt.isActive() && climb == 0 )
	{
		for( int i = 0; i < nr; i++ )
		{
			sprite[ i ].setPosition( sprite[ i ].getX(), sprite[ i ].getY() +grav );
		}
		
		glide = true;
	}
	else
	{
		glide = false;
	}
}

void Hero::pixelGravitation()
{
	if( climb != 0 )
	{
		for( int i = 0; i < nr; i++ )
		{
			sprite[ i ].setPosition( sprite[ i ].getX(), sprite[ i ].getY() +grav );
		}
	}
}

void Hero::weightlessness()
{
	if( climb == 0 )
	{
		glide = false;
		for( int i = 0; i < nr; i++ )
		{
			sprite[ i ].setPosition( sprite[ i ].getX(), sprite[ i ].getY() -grav );
		}
	}
}