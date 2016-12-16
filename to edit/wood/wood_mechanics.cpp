#include "wood/play_wood.h"

void Play_wood::mechanics()
{
	// HERO GRAVITY
	hero->gravitation();
	
	// HERO WEIGHTLESSNESS
	if( random_block->checkBlockByPixel( hero->getX(), hero->getR(), hero->getY(), hero->getB() ) )
	{
		hero->weightlessness();
	}
	
	// HERO GLIDE
	else
	{
		hero->gliding();
	}
	
	
	// HERO PIXEL GRAVITY
	if( random_block->checkBlockByPixel( hero->getL(), hero->getR(), hero->getT(), hero->getB() ) )
	{
		hero->pixelGravitation();
	}
	
	
	
	// HERO SLIDE
	hero->sliding();
	
	// HERO CLIMB
	if( random_block->checkLadder( hero->getX(), hero->getY(), hero->getW(), hero->getH() ) )
	{
		if( !random_block->checkBlockByPixel( hero->getL(), hero->getR(), hero->getT(), hero->getB() ) )
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
			kunai->throwing( hero->getThrowX(), hero->getThrowY(), hero->getThrowVel() );
		}
		
		if( random_block->checkBlockByPixel( hero->getL(), hero->getR(), hero->getT(), hero->getB() ) ||
			hero->getX() + hero->getW()> random_block->getScreenWidth() ||
			hero->getX() < 0 )
		{
			hero->undoJump();
		}
	}
	
	// HERO JUMP WITH ATTACK
	else if( hero->jumpAttack() )
	{
		if( hero->hit( golem->getX(), golem->getY(), golem->getW(), golem->getH() ) )
		{
			golem->checkHit( hero->getTrueX(), hero->getY(), hero->getTrueW(), hero->getH(), 0.07 );
		}
		
		if( random_block->checkBlockByPixel( hero->getL(), hero->getR(), hero->getT(), hero->getB() ) ||
			hero->getX() + hero->getW()> random_block->getScreenWidth() ||
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
			kunai->throwing( hero->getThrowX(), hero->getThrowY(), hero->getThrowVel() );
		}
	}
	
	// HERO ATTACK
	else if( hero->attack() )
	{
		if( hero->hit( golem->getX(), golem->getY(), golem->getW(), golem->getH() ) )
		{
			golem->checkHit( hero->getTrueX(), hero->getY(), hero->getTrueW(), hero->getH(), 0.07 );
		}
	}
	
	// HERO JUMP
	else if( hero->jump() )
	{
		if( random_block->checkBlockByPixel( hero->getL(), hero->getR(), hero->getT(), hero->getB() ) ||
			hero->getX() + hero->getW()> random_block->getScreenWidth() ||
			hero->getX() < 0 )
		{
			hero->undoJump();
		}
	}
	
	// HERO MOVE
	else if( hero->move() )
	{
		if( random_block->checkBlockByPixel( hero->getX(), hero->getR(), hero->getY(), hero->getB() ) ||
			hero->getX() + hero->getW()> random_block->getScreenWidth() ||
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
		if( random_block->checkBlockByPixel( kunai->getX( i ), kunai->getR( i ), kunai->getY( i ), kunai->getB( i ) ) ||
		kunai->getX( i ) + kunai->getW() > random_block->getScreenWidth() +kunai->getW() ||
		kunai->getX( i ) < -kunai->getW() ||
		golem->checkHit( kunai->getX( i ), kunai->getY( i ), kunai->getW(), kunai->getH(), 0.03 ) )
		{
			kunai->destroy( i );
		}
	}
	
	
	// GOLEM SET X
	golem->matchX( hero->getX(), hero->getW(), hero->getY(), hero->getH() );
	
	// GOLEM ALLOW ATTACK
	if( golem->allowAttack( hero->getX(), hero->getY(), hero->getW(), hero->getH() ) )
	{
		
	}
	
	// BG MOVE
	bg->move( hero->getDirection() );
}