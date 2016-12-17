#include "winter/play_winter.h"

void Play_winter::mechanics()
{
	// HERO GRAVITY
	hero->gravitation();
	
	// HERO WEIGHTLESSNESS
	if( brick->checkBlockByPixel( hero->getRect() ) )
	{
		hero->weightlessness();
	}
	
	// HERO GLIDE
	else
	{
		hero->gliding();
	}
	
	
	// HERO PIXEL GRAVITY
	if( brick->checkBlockByPixel( hero->getRect() ) )
	{
		hero->pixelGravitation();
	}
	
	
	
	// HERO SLIDE
	hero->sliding();
	
	// HERO CLIMB
	if( brick->checkLadder( hero->getRect() ) )
	{
		if( !brick->checkBlockByPixel( hero->getRect() ) )
		{
			hero->climbing();
		}
		else
		{
			hero->banClimbing();
		}
	}
	else
	{
		hero->banClimbing();
	}

		
	// HERO JUMP WITH THROW
	if( hero->jumpThrow() )
	{
		if( hero->throwed() )
		{
			kunai->throwed( hero->getX(), hero->getY(), hero->getSide() );
		}
		
		if( brick->checkBlockByPixel( hero->getRect() ) ||
			hero->getX() + hero->getW()> brick->getScreenWidth() ||
			hero->getX() < 0 )
		{
			hero->undoJump();
		}
	}
	
	// HERO JUMP WITH ATTACK
	else if( hero->jumpAttack() )
	{
		golem->checkHit( hero->getAttackBox(), hero->getDamage() );
		
		if( brick->checkBlockByPixel( hero->getRect() ) ||
			hero->getX() + hero->getW()> brick->getScreenWidth() ||
			hero->getX() < 0 )
		{
			hero->undoJump();
		}
	}
	
	// HERO THROW
	else if( hero->throwing() )
	{
		if( hero->throwed() )
		{
			kunai->throwed( hero->getX(), hero->getY(), hero->getSide() );
		}
	}
	
	// HERO ATTACK
	else if( hero->attack() )
	{
		golem->checkHit( hero->getAttackBox(), hero->getDamage() );
	}
	
	// HERO JUMP
	else if( hero->jump() )
	{
		if( brick->checkBlockByPixel( hero->getRect() ) ||
			hero->getX() + hero->getW()> brick->getScreenWidth() ||
			hero->getX() < 0 )
		{
			hero->undoJump();
		}
	}
	
	// HERO MOVE
	else if( hero->moving() )
	{
		if( brick->checkBlockByPixel( hero->getRect() ) ||
			hero->getX() + hero->getW()> brick->getScreenWidth() ||
			hero->getX() < 0 )
		{
			hero->undoMove();
		}
	}
	
	// HERO IDLE
	else
	{
		hero->idle();
	}
	
	// KUNAI DESTROY
	for( unsigned i = 0; i < kunai->getNr(); i++ )
	{
		if( brick->checkBlockByPixel( kunai->getRect( i ) ) ||
		kunai->getX( i ) + kunai->getW() > brick->getScreenWidth() +kunai->getW() ||
		kunai->getX( i ) < -kunai->getW() ||
		golem->checkHit( kunai->getRect( i ), kunai->getDamage() ) )
		{
			kunai->destroy( i );
		}
	}
	
	
	// GOLEM SET X
	golem->matchX( hero->getX(), hero->getW(), hero->getY(), hero->getH() );
	
	if( brick->checkCollision( golem->getRect() ) )
	{
		golem->undoMove();
	}
}