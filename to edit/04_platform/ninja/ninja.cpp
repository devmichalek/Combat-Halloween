/**
    hero.h
    Purpose: class Hero contains each hero textures, each mechanics.

    @author Adrian Michalek
    @version 2016.09.15
	@email adrmic98@gmail.com
*/

#include "ninja.h"

// IDLE
void Hero::idle()
{
	if( !glide && !slide && climb == 0 && dead == 0 )
	{
		which = IDLE;
	}
}





// MOVE
void Hero::moveX( float vel )
{
	for( auto &it :x )
	{
		it += vel;
	}
	
	for( auto &it :x2 )
	{
		it += vel;
	}
}

void Hero::moveY( float vel )
{
	for( auto &it :y )
	{
		it += vel;
	}
}

bool Hero::moving()
{
	// move left
	if( checkKeys( keys[ 0 ][ 0 ], keys[ 0 ][ 1 ] ) && !fallen && dead == 0 )
	{
		if( !glide && !slide && climb == 0 )
		{
			which = RUN;
		}
		else if( climb != 0 )	// move left on the ladder
		{
			climb = 1;
		}
		
		if( !scope )
		{
			moveX( -vel );
		}
		
		if( scale > 0 )
		{
			scale = -scale;
		}
		
		right = false;
		move = true;
		return true;
	}
	
	// move right
	else if( checkKeys( keys[ 1 ][ 0 ], keys[ 1 ][ 1 ] ) && !fallen && dead == 0 ) 
	{
		if( !glide && !slide && climb == 0 )
		{
			x[ ATTACK ] = x[ RUN ];
			x2[ ATTACK ] = x2[ RUN ];
			which = RUN;
		}
		else if( climb != 0 )	// move right on the ladder
		{
			climb = 1;
		}
		
		if( !scope )
		{
			moveX( vel );
		}
		
		if( scale < 0 )
		{
			scale = -scale;
		}
		
		right = true;
		move = true;
		return true;
	}
	
	move = false;
	return false;
}

void Hero::undoMove()
{
	move = false;
	
	if( right )
	{
		moveX( -vel );
	}
	else
	{
		moveX( vel );
	}
}





// JUMP
bool Hero::jump()
{
	if( checkKeys( keys[ 2 ][ 0 ], keys[ 2 ][ 1 ] ) && j.run() && !glide && climb == 0 && !fallen && dead == 0 )
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
		
		if( !scope )
		{
			if( right )
			{
				moveX( jump_vel );
			}
			else
			{
				moveX( -jump_vel );
			}
		}
	}
	
	j.check();
	
	return j.isActive();	
}

void Hero::undoJump()
{
	move = false;
	
	if( right )
	{
		moveX( -jump_vel );
	}
	else
	{
		moveX( jump_vel );
	}
}





// ATTACK
bool Hero::attack()
{
	if( checkKeys( keys[ 5 ][ 0 ], keys[ 5 ][ 1 ] ) && a.run() && !glide && !j.isActive() && climb == 0 && !fallen && dead == 0 )
	{
		offset = 0;
		a.start();
		a.setActive( true );
		which = ATTACK;
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
	// temporary stuff
	Rect* rect = NULL;
	int t_x, tw;	
	
	if( which == ATTACK && offset == 6*delay )
	{
		rect = new Rect;
		
		tw = 38;
		if( right )
		{
			t_x = x2[ ATTACK ] -tw;
		}
		else
		{
			t_x = x[ ATTACK ];
		}
		
		rect->set( t_x, sprites[ ATTACK ]->getY(), tw, sprites[ ATTACK ]->getHeight() );
		return rect;
	}
	else if( which == JUMP_ATTACK && offset == 4*delay )
	{
		rect = new Rect;
		
		tw = 48;
		if( right )
		{
			t_x = x2[ JUMP_ATTACK ] -tw;
		}
		else
		{
			t_x = x[ JUMP_ATTACK ];
		}

		rect->set( t_x, sprites[ JUMP_ATTACK ]->getY(), tw, sprites[ JUMP_ATTACK ]->getHeight() );
		return rect;
	}

	return NULL;
}

float Hero::getDamage()
{
	return damage;
}





// GLIDE
void Hero::gliding()
{
	if( climb == 0 && dead == 0 )
	{
		which = GLIDE;
	}
}

bool Hero::isGliding()
{
	return glide;
}





// SLIDE
void Hero::sliding()
{
	if( checkKeys( keys[ 3 ][ 0 ], keys[ 3 ][ 1 ] ) && !fallen && dead == 0 )
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





// JUMP WITH ATTACK
bool Hero::jumpAttack()
{
	if( checkKeys( keys[ 6 ][ 0 ], keys[ 6 ][ 1 ] ) && ja.run() && !glide && j.isActive() && !a.isActive() && !t.isActive() && climb == 0 && !fallen && dead == 0 )
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
		
		if( !scope )
		{
			if( right )
			{
				moveX( jump_vel );
			}
			else
			{
				moveX( -jump_vel );
			}
		}
	}
	
	ja.check();
	return ja.isActive();
}





// JUMP WITH THROW
bool Hero::jumpThrow()
{
	if( checkKeys( keys[ 8 ][ 0 ], keys[ 8 ][ 1 ] ) && jt.run() && !glide && !a.isActive() && !t.isActive() && ( j.isActive() || ja.isActive() ) && climb == 0 && !fallen && dead == 0 )
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
		
		if( !scope )
		{
			if( right )
			{
				moveX( jump_vel );
			}
			else
			{
				moveX( -jump_vel );
			}
		}

	}
	
	jt.check();
	
	return jt.isActive();
}





// CLIMB
void Hero::climbing()
{
	if( checkKeys( keys[ 4 ][ 0 ], keys[ 4 ][ 1 ] ) && !j.isActive() && !ja.isActive() && !jt.isActive() && !glide && !t.isActive() && !a.isActive() && !fallen && dead == 0 )
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
		
		moveY( -vel );
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





// THROW
bool Hero::throwing()
{
	if( checkKeys( keys[ 7 ][ 0 ], keys[ 7 ][ 1 ] ) && !t.isActive() && !glide && !j.isActive() && !a.isActive() && climb == 0 && !fallen && dead == 0 )
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





// GRAVITY STUFF
void Hero::gravitation()
{
	if( j.isActive() && !ja.isActive() && !jt.isActive() )
	{
		if( offset < (sprites.size()-1)*delay/2  )
		{
			moveY( -1 );
		}
		else
		{
			moveY( 1 );
		}
	}
	
	if( !j.isActive() && !ja.isActive() && !jt.isActive() && climb == 0 && !fallen && dead == 0 )
	{
		moveY( grav );
		glide = true;
	}
	else
	{
		glide = false;
	}
}

void Hero::pixelGravitation()
{
	if( climb != 0 && !fallen && dead == 0 )
	{
		moveY( grav );
	}
}

void Hero::weightlessness()
{
	if( climb == 0 && !fallen && dead == 0 )
	{
		glide = false;
		moveY( -grav );
	}
}





// DEAD STUFF
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
	fallenY = y -sprites[ IDLE ]->getHeight() -40;
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