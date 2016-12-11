#include "hero/hero.h"

void Hero::idle()
{
	if( !glide  && !slide && !c.isActive() )
	{
		which = IDLE;
	}
}

bool Hero::move()
{
	// move left
	if( checkKeys( keys[ 0 ][ 0 ], keys[ 0 ][ 1 ] ) && !c.isActive() )
	{
		if( !glide && !slide )
		{
			which = RUN;
		}
		
		flag = true;
		
		for( int i = 0; i < nr; i++ )
		{
			sprite[ i ].setScale( -scale, scale );
			sprite[ i ].setPosition( sprite[ i ].getX() -vel, sprite[ i ].getY() );
		}
		
		if( right )
		{
			for( int i = 0; i < nr; i++ )
			{
				if( i != IDLE )
				{
					sprite[ i ].setPosition( sprite[ IDLE ].getX() + ( sprite[ i ].getWidth()*-1 ), sprite[ i ].getY() );
				}
			}
			
			sprite[ IDLE ].setPosition( sprite[ IDLE ].getX() + ( sprite[ IDLE ].getWidth()*-1 ), sprite[ IDLE ].getY() );
			sprite[ ATTACK ].setPosition( sprite[ IDLE ].getX(), sprite[ IDLE ].getY() );
			sprite[ SLIDE ].setPosition( sprite[ IDLE ].getX(), sprite[ SLIDE ].getY() );
			sprite[ JUMP_ATTACK ].setPosition( sprite[ IDLE ].getX() +30, sprite[ JUMP_ATTACK ].getY() );
			sprite[ CLIMB ].setPosition( sprite[ IDLE ].getX() +sprite[ IDLE ].getWidth() +15, sprite[ CLIMB ].getY() );
			
			right = false;
		}
		
		return true;
	}
	
	// move right
	else if( checkKeys( keys[ 1 ][ 0 ], keys[ 1 ][ 1 ] ) && !c.isActive() ) 
	{
		if( !glide && !slide )
		{
			which = RUN;
		}
		
		for( int i = 0; i < nr; i++ )
		{
			sprite[ i ].setScale( scale, scale );
			sprite[ i ].setPosition( sprite[ i ].getX() +vel, sprite[ i ].getY() );
		}
		
		if( !right )
		{
			if( flag )
			{
				for( int i = 0; i < nr; i++ )
				{
					sprite[ i ].setPosition( sprite[ i ].getX() - ( sprite[ i ].getWidth() ), sprite[ i ].getY() );
				}
			}
			
			for( int i = 0; i < nr; i++ )
			{
				if( i != IDLE )
				{
					sprite[ i ].setPosition( sprite[ IDLE ].getX() - ( sprite[ i ].getWidth() -sprite[ IDLE ].getWidth() ), sprite[ i ].getY() );
				}
			}
			
			sprite[ ATTACK ].setPosition( sprite[ IDLE ].getX(), sprite[ IDLE ].getY() );
			sprite[ SLIDE ].setPosition( sprite[ IDLE ].getX(), sprite[ SLIDE ].getY() );
			sprite[ JUMP_ATTACK ].setPosition( sprite[ IDLE ].getX() -30, sprite[ JUMP_ATTACK ].getY() );
			sprite[ CLIMB ].setPosition( sprite[ IDLE ].getRight() -15, sprite[ CLIMB ].getY() );
			
			right = true;
		}
		
		return true;
	}
	
	return false;
}

bool Hero::jump()
{
	if( checkKeys( keys[ 2 ][ 0 ], keys[ 2 ][ 1 ] ) && j.Do() && !glide )
	{
		if( !c.isActive() )
		{
			offset = 0;
			j.start();
			j.setActive( true );
			which = JUMP;
		}
	}
	
	if( j.isActive() )
	{
		which = JUMP;
		
		if( right )
		{
			for( int i = 0; i < nr; i++ )
			{
				sprite[ i ].setPosition( sprite[ i ].getX() +jVel, sprite[ i ].getY() );
			}
		}
		else
		{
			for( int i = 0; i < nr; i++ )
			{
				sprite[ i ].setPosition( sprite[ i ].getX() -jVel, sprite[ i ].getY() );
			}
		}
	}
	
	j.check();
	
	return j.isActive();	
}

bool Hero::attack()
{
	if( checkKeys( keys[ 5 ][ 0 ], keys[ 5 ][ 1 ] ) && a.Do() && !glide && !j.isActive() && !c.isActive() )
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
	}
	
	a.check();
	
	return a.isActive();
}

void Hero::gliding()
{
	if( !c.isActive() )
	{
		which = GLIDE;
	}
}

void Hero::sliding()
{
	if( checkKeys( keys[ 3 ][ 0 ], keys[ 3 ][ 1 ] ) )
	{
		if( !glide && !c.isActive() )
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

bool Hero::jumpAttack()
{
	if( checkKeys( keys[ 6 ][ 0 ], keys[ 6 ][ 1 ] ) && ja.Do() && !glide && !j.isActive() && !a.isActive() && !t.isActive() && !c.isActive() )
	{
		offset = 0;
		ja.start();
		ja.setActive( true );
		which = JUMP_ATTACK;
	}
	
	if( ja.isActive() )
	{
		which = JUMP_ATTACK;
		
		if( right )
		{
			for( int i = 0; i < nr; i++ )
			{
				sprite[ i ].setPosition( sprite[ i ].getX() +jVel, sprite[ i ].getY() );
			}
		}
		else
		{
			for( int i = 0; i < nr; i++ )
			{
				sprite[ i ].setPosition( sprite[ i ].getX() -jVel, sprite[ i ].getY() );
			}
		}
	}
	
	ja.check();
	
	return ja.isActive();
}

bool Hero::jumpThrow()
{
	if( checkKeys( keys[ 8 ][ 0 ], keys[ 8 ][ 1 ] ) && jt.Do() && !glide && !j.isActive() && !a.isActive() && !t.isActive() && !ja.isActive() && !c.isActive() )
	{
		offset = 0;
		jt.start();
		jt.setActive( true );
		which = JUMP_THROW;
	}
	
	if( jt.isActive() )
	{
		which = JUMP_THROW;
		
		if( right )
		{
			for( int i = 0; i < nr; i++ )
			{
				sprite[ i ].setPosition( sprite[ i ].getX() +jVel, sprite[ i ].getY() );
			}
		}
		else
		{
			for( int i = 0; i < nr; i++ )
			{
				sprite[ i ].setPosition( sprite[ i ].getX() -jVel, sprite[ i ].getY() );
			}
		}
	}
	
	jt.check();
	
	return jt.isActive();
}



bool Hero::climbing()
{
	c.check();
	if( checkKeys( keys[ 4 ][ 0 ], keys[ 4 ][ 1 ] ) && c.Do() )
	{
		c.start();
		return true;
	}
	
	return false;
}

void Hero::allowClimbing()
{
	if( !glide )
	{
		slide = false;
		c.setActive( !c.isActive() );
		which = CLIMB;
	}
}

void Hero::banClimbing()
{
	if( !glide )
	{
		slide = false;
		c.setActive( false );
		j.start();
	}
}

void Hero::newPosition()
{
	if( c.isActive() )
	{
		if( right )
		{
			for( int i = 0; i < nr; i++ )
			{
				sprite[ i ].setPosition( sprite[ i ].getX() +sprite[ IDLE ].getWidth(), sprite[ i ].getY() );
			}
		}
		else
		{
			for( int i = 0; i < nr; i++ )
			{
				sprite[ i ].setPosition( sprite[ i ].getX() -sprite[ IDLE ].getWidth(), sprite[ i ].getY() );
			}
		}
	}
}

void Hero::goUpAndDown()
{
	if( checkKeys( keys[ 3 ][ 0 ], keys[ 3 ][ 1 ] ) )
	{
		if( c.isActive() )
		{
			offset ++;
			for( int i = 0; i < nr; i++ )
			{
				sprite[ i ].setPosition( sprite[ i ].getX(), sprite[ i ].getY() +vel );
			}
		}
	}
	else if( checkKeys( keys[ 2 ][ 0 ], keys[ 2 ][ 1 ] ) && j.Do() && !glide )
	{
		if( c.isActive() )
		{
			offset ++;
			for( int i = 0; i < nr; i++ )
			{
				sprite[ i ].setPosition( sprite[ i ].getX(), sprite[ i ].getY() -vel );
			}
		}
	}
	
	if( offset == (nr-1) *delay )
	{
		offset = 0;
	}
}



bool Hero::throwing()
{
	if( checkKeys( keys[ 7 ][ 0 ], keys[ 7 ][ 1 ] ) && t.Do() && !glide && !j.isActive() && !a.isActive() && !c.isActive() )
	{
		offset = 0;
		t.start();
		t.setActive( true );
		which = THROW;
	}
	
	if( t.isActive() )
	{
		which = THROW;
	}
	
	t.check();
	
	return t.isActive();
}

bool Hero::throwed()
{
	if( offset == 8 )
	{
		return true;
	}
	
	return false;
}

int Hero::getThrowVel()
{
	if( right )
	{
		return vel*4;
	}
	
	return vel*-4;
}

const int Hero::getThrowX()
{
	if( right )
	{
		return sprite[ IDLE ].getX() + 20;
	}
	
	return sprite[ IDLE ].getX() - 20;
}
	
const int Hero::getThrowY()
{
	return sprite[ IDLE ].getY() + 50;
}



void Hero::undoMove()
{
	// undo move right
	if( right )
	{
		for( int i = 0; i < nr; i++ )
		{
			sprite[ i ].setPosition( sprite[ i ].getX() -vel, sprite[ i ].getY() );
		}
	}
	
	// undo move left
	else
	{
		for( int i = 0; i < nr; i++ )
		{
			sprite[ i ].setPosition( sprite[ i ].getX() +vel, sprite[ i ].getY() );
		}
	}
}

void Hero::undoJump()
{
	if( right )
	{
		for( int i = 0; i < nr; i++ )
		{
			sprite[ i ].setPosition( sprite[ i ].getX() -jVel, sprite[ i ].getY() );
		}
	}
	else
	{
		for( int i = 0; i < nr; i++ )
		{
			sprite[ i ].setPosition( sprite[ i ].getX() +jVel, sprite[ i ].getY() );
		}
	}
}



void Hero::gravitation()
{
	if( !j.isActive() && !ja.isActive() && !jt.isActive() && !c.isActive() )
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

void Hero::weightlessness()
{
	glide = false;
	for( int i = 0; i < nr; i++ )
	{
		sprite[ i ].setPosition( sprite[ i ].getX(), sprite[ i ].getY() -grav );
	}
}


int Hero::getDirection()
{
	static int ex = 0;
	
	if( ex < sprite[ RUN ].getX() )
	{
		ex = sprite[ RUN ].getX();
		return 1;
	}
	else if( ex > sprite[ RUN ].getX() )
	{
		ex = sprite[ RUN ].getX();
		return -1;
	}

	return 0;
}
