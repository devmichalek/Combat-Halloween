#include "halloween.h"

void Halloween::mechanics()
{
	// ------------------------------------------------------------------------------------------------
	// HERO CLIMB
	if( ladder->checkCollision( hero->getRect() ) )
	{
		if( !brick->checkPixelCollision( hero->getRect() ) &&
			!islands->checkPixelCollision( hero->getRect() ) )
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
	
	
	
// ------------------------------------------------------------------------------------------------
	// HERO GRAVITY
	hero->gravitation();
	
	
	
// ------------------------------------------------------------------------------------------------
	// HERO WEIGHTLESSNESS
	if( brick->checkPixelCollision( hero->getRect() ) )
	{
		hero->weightlessness();
		islands->turnOn();
	}
	else if( islands->checkPixelCollision( hero->getRect() ) )
	{
		hero->weightlessness();
	}
	
	
	
	// HERO GLIDE
	else
	{
		hero->gliding();
	}
	
	
	
// ------------------------------------------------------------------------------------------------
	// HERO PIXEL GRAVITY
	if( brick->checkPixelCollision( hero->getRect() ) ||
		islands->checkPixelCollision( hero->getRect() ) )
	{
		hero->pixelGravitation();
	}
	
	
	
// ------------------------------------------------------------------------------------------------
	// HERO SLIDE
	hero->sliding();
	
	
	
// ------------------------------------------------------------------------------------------------
	// HERO JUMP WITH THROW
	if( hero->jumpThrow() )
	{
		scope->setVel( hero->getJump_vel() );
		
		if( hero->throwed() )
		{
			kunai->throwed( hero->getX(), hero->getY(), hero->getSide() );
		}
		
		if( brick->checkPixelCollision( hero->getRect() ) ||
			islands->checkPixelCollision( hero->getRect() ) ||
			hero->getX() + hero->getW() > screen_w ||
			hero->getX() < 0 )
		{
			hero->undoJump();
		}
	}
	
	
	
// ------------------------------------------------------------------------------------------------
	// HERO JUMP WITH ATTACK
	else if( hero->jumpAttack() )
	{
		//golem->checkHit( hero->getAttackBox(), hero->getDamage() );
		
		scope->setVel( hero->getJump_vel() );
		
		if( brick->checkPixelCollision( hero->getRect() ) ||
			islands->checkPixelCollision( hero->getRect() ) ||
			hero->getX() + hero->getW() > screen_w ||
			hero->getX() < 0 )
		{
			hero->undoJump();
		}
	}
	
	
	
// ------------------------------------------------------------------------------------------------
	// HERO THROW
	else if( hero->throwing() )
	{
		if( hero->throwed() )
		{
			kunai->throwed( hero->getX(), hero->getY(), hero->getSide() );
		}
	}
	
	
	
// ------------------------------------------------------------------------------------------------
	// HERO ATTACK
	else if( hero->attack() )
	{
		
	}
	
	
	
// ------------------------------------------------------------------------------------------------
	// HERO JUMP
	else if( hero->jump() )
	{
		scope->setVel( hero->getJump_vel() );
		
		if( brick->checkPixelCollision( hero->getRect() ) ||
			islands->checkPixelCollision( hero->getRect() ) ||
			hero->getX() + hero->getW() > screen_w ||
			hero->getX() < 0 )
		{
			hero->undoJump();
		}
	}
	
	
	
// ------------------------------------------------------------------------------------------------
	// HERO MOVE
	else if( hero->moving() )
	{
		scope->setVel( hero->getVel() );
		
		if( brick->checkPixelCollision( hero->getRect() ) ||
			islands->checkPixelCollision( hero->getRect() ) ||
			hero->getX() + hero->getW() > screen_w ||
			hero->getX() < 0 )
		{
			hero->undoMove();
		}
	}
	
	
	
// ------------------------------------------------------------------------------------------------
	// HERO IDLE
	else
	{
		hero->idle();
	}
	
	
	
// ------------------------------------------------------------------------------------------------
	// KUNAI DESTROY
	for( unsigned i = 0; i < kunai->getNr(); i++ )
	{
		if( brick->checkPixelCollision( kunai->getRect( i ) ) ||
		kunai->getX( i ) + kunai->getW() > screen_w +kunai->getW() ||
		kunai->getX( i ) < -kunai->getW() ||
		wall->checkCollision( kunai->getRect( i ) )	||
		islands->checkPixelCollision( kunai->getRect( i ) ) )
		{
			kunai->destroy( i );
		}
	}
	
	
	
	
// ------------------------------------------------------------------------------------------------
	// HERO SET SCOPE
	hero->setScope( !scope->getScope() );
	
	// SCOPE ALLOW MOVE
	if( scope->allowMoving() )
	{
		// BRICK MOVE
		scope->setFactor( brick->moveX( hero->getDirection(), scope->getVel() ) );
		if( scope->getFactor() == 0 )
		{
			islands->moveX( hero->getDirection(), scope->getVel() );
			ladder->moveX( hero->getDirection(), scope->getVel() );
			greenery->moveX( hero->getDirection(), scope->getVel() );
			mine_factory->moveX( hero->getDirection(), scope->getVel() );
		}

		if( brick->checkPixelCollision( hero->getRect() ) ||
			wall->checkCollision( hero->getRect() ) ||
			islands->checkPixelCollision( hero->getRect() ) )
		{
			brick->moveX( hero->getDirection(), -scope->getVel() );	// undo
			islands->moveX( hero->getDirection(), -scope->getVel() );
			wall->moveX( hero->getDirection(), -scope->getVel() );
			ladder->moveX( hero->getDirection(), -scope->getVel() );
			greenery->moveX( hero->getDirection(), -scope->getVel() );
			mine_factory->moveX( hero->getDirection(), -scope->getVel() );
		}
	}
	
	if( !islands->checkFlyingIslands( hero->getRect() ) )
	{
		islands->moving();
	}
	else
	{
		islands->turnOff( hero->getDirection() );
	}
	
	if( islands->checkOtherIslands( hero->getRect() ) )
	{
		islands->turnOn();
	}
	
	
	
	
	
	// SCOPE MOVE
	scope->move( hero->getX(), screen_w );
	
	
	
// ------------------------------------------------------------------------------------------------
	// BACKGROUND SET XY
	background->setPosition( hero->getX(), hero->getY() );
	
	
	
// ------------------------------------------------------------------------------------------------
	// HERO FALLEN
	if( hero->isFallen( screen_h ) )
	{
		heart->harm( -0xCC );
		hero->setNewY( brick->getLastGrassY() );
		
		if( scope->getState() == 1 || scope->getState() == 3 )
		{
			brick->setNewX( hero->getX() );
		}
		else if( hero->setNewX( brick->getLastGrassX(), screen_w ) )
		{
			scope->transform();
		}
	}
	
	// CHECK Y AND SHOW EFFECT
	if( hero->getY() > screen_h -hero->getH()/2 )
	{
		effect->runFall();
	}
	
	// GET BACK HERO
	if( hero->isSurplus() )
	{
		brick->setNewX( hero->getX() );
	}
	
	// BACK TO LAST GRASS BLOCK
	if( hero->backToGrass() )
	{
		brick->findLastGrass( hero->getRect() );
	}
	if( brick->backToGrass() )
	{
		hero->setFallen();
		islands->backToGrass( brick->getGrassValue() );
		wall->backToGrass( brick->getGrassValue() );
		ladder->backToGrass( brick->getGrassValue() );
		greenery->backToGrass( brick->getGrassValue() );
		mine_factory->backToGrass( brick->getGrassValue() );
	}
	
	
	
// ------------------------------------------------------------------------------------------------
	// HARM BY WALL
	if( wall->harm( hero->getRect() ) )
	{
		heart->harm( -0xAA );
		effect->runBlood();
	}
	
	// HARM BY MINE
	mine_factory->checkCollision( hero->getRect() );
	if( mine_factory->harm( hero->getRect() ) )
	{
		heart->harm( -0xBB );
		effect->runBlood();
	}
	
// ------------------------------------------------------------------------------------------------
	// DEAD
	if( heart->isDead() )
	{
		hero->die();
	}
}