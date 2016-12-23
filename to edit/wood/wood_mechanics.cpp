#include "wood/play_wood.h"

void Play_wood::mechanics()
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
		scope->setVel( hero->getJump_vel() );
		
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
		
		if( scope->checkWall( hero->getX() ) )
		{
			hero->setScope( 1 );
		}
	}
	
	// HERO JUMP WITH ATTACK
	else if( hero->jumpAttack() )
	{
		//golem->checkHit( hero->getAttackBox(), hero->getDamage() );
		
		scope->setVel( hero->getJump_vel() );
		
		if( brick->checkBlockByPixel( hero->getRect() ) ||
			hero->getX() + hero->getW()> brick->getScreenWidth() ||
			hero->getX() < 0 )
		{
			hero->undoJump();
		}
		
		if( scope->checkWall( hero->getX() ) )
		{
			hero->setScope( 1 );
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
		//golem->checkHit( hero->getAttackBox(), hero->getDamage() );
	}
	
	// HERO JUMP
	else if( hero->jump() )
	{
		scope->setVel( hero->getJump_vel() );
		
		if( brick->checkBlockByPixel( hero->getRect() ) ||
			hero->getX() + hero->getW()> brick->getScreenWidth() ||
			hero->getX() < 0 )
		{
			hero->undoJump();
		}
		
		if( scope->checkWall( hero->getX() ) )
		{
			hero->setScope( 1 );
		}
	}
	
	// HERO MOVE
	else if( hero->moving() )
	{
		scope->setVel( hero->getVel() );
		
		if( brick->checkBlockByPixel( hero->getRect() ) ||
			hero->getX() + hero->getW()> brick->getScreenWidth() ||
			hero->getX() < 0 )
		{
			hero->undoMove();
		}
		
		if( scope->checkWall( hero->getX() ) )
		{
			hero->setScope( 1 );
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
		kunai->getX( i ) < -kunai->getW() /*||
		golem->checkHit( kunai->getRect( i ), kunai->getDamage() )*/ )
		{
			kunai->destroy( i );
		}
	}
	
	/*
	// GOLEM SET X
	golem->matchX( hero->getRect() );
	if( brick->checkCollision( golem->getRect() ) )
	{
		golem->undoMove();
	}
	
	// GOLEM ATTACK
	if( golem->checkAttackBox( hero->getRect() ) )
	{
		hero->harm();
		heart->harm( golem->getDamage() );
	}
	*/
	
	
	
	
	
	if( scope->allowMoving() )
	{
		// BG MOVE
		bg->move( hero->getDirection() );
		
		// BRICK MOVE
		brick->moveX( hero->getDirection(), scope->getVel() );
		if( brick->checkBlockByPixel( hero->getRect() ) )
		{
			brick->moveX( hero->getDirection(), -scope->getVel() );	// undo
		}
	}
	
	
	// SCOPE MOVE
	scope->move( hero->getDirection() );
}