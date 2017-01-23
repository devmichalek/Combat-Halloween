#include "play_wood.h"

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
	if( ladder->checkLadder( hero->getRect(), screen_w ) )
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
			hero->getX() + hero->getW() > screen_w ||
			hero->getX() < 0 )
		{
			hero->undoJump();
		}
	}
	
	// HERO JUMP WITH ATTACK
	else if( hero->jumpAttack() )
	{
		//golem->checkHit( hero->getAttackBox(), hero->getDamage() );
		
		scope->setVel( hero->getJump_vel() );
		
		if( brick->checkBlockByPixel( hero->getRect() ) ||
			hero->getX() + hero->getW() > screen_w ||
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
		//golem->checkHit( hero->getAttackBox(), hero->getDamage() );
	}
	
	// HERO JUMP
	else if( hero->jump() )
	{
		scope->setVel( hero->getJump_vel() );
		
		if( brick->checkBlockByPixel( hero->getRect() ) ||
			hero->getX() + hero->getW() > screen_w ||
			hero->getX() < 0 )
		{
			hero->undoJump();
		}
	}
	
	// HERO MOVE
	else if( hero->moving() )
	{
		scope->setVel( hero->getVel() );
		
		if( brick->checkBlockByPixel( hero->getRect() ) ||
			hero->getX() + hero->getW() > screen_w ||
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
		kunai->getX( i ) + kunai->getW() > screen_w +kunai->getW() ||
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
	
	
	// HERO SET SCOPE
	hero->setScope( !scope->getScope() );
	
	// SCOPE ALLOW MOVE
	if( scope->allowMoving() )
	{
		// BRICK MOVE
		scope->setFactor( brick->moveX( hero->getDirection(), scope->getVel() ) );
		if( scope->getFactor() == 0 )
		{
			greenery->moveX( hero->getDirection(), scope->getVel() );
			ladder->moveX( hero->getDirection(), scope->getVel() );
		}
			
		if( brick->checkBlockByPixel( hero->getRect() ) )
		{
			brick->moveX( hero->getDirection(), -scope->getVel() );	// undo
			greenery->moveX( hero->getDirection(), -scope->getVel() );
			ladder->moveX( hero->getDirection(), -scope->getVel() );
		}
	}
	
	// SCOPE MOVE
	scope->move( hero->getX(), screen_w );
	
	// BACKGROUND SET XY
	bg->setXY( hero->getX(), hero->getY() );
	
	// HERO FALLEN
	if( hero->isFallen( screen_h ) )
	{
		hero->setNewY( brick->getLastGrassY() );
		
		if( scope->getState() == 1 || scope->getState() == 3 )
		{
			brick->setNewX( hero->getX() );
		}
		else
		{
			if( hero->setNewX( brick->getLastGrassX(), screen_w ) )
			{
				scope->transform();
			}
		}
	}
	
	// GET BACK HERO
	if( hero->isSurplus() )
	{
		brick->setNewX( hero->getX() );
	}
	if( hero->backToGrass() )
	{
		brick->findLastGrass( hero->getRect() );
	}
	if( ladder->backToGrass( greenery->backToGrass( brick->backToGrass() ) ) != 0 )
	{
		hero->setFallen();
	}
}