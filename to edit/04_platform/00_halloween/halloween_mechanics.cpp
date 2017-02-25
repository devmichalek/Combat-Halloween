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
		vampire_factory.harm( hero->getAttackBox(), hero->getDamage() );
		zombie_factory.harm( hero->getAttackBox(), hero->getDamage() );
		
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
		vampire_factory.harm( hero->getAttackBox(), hero->getDamage() );
		zombie_factory.harm( hero->getAttackBox(), hero->getDamage() );
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
		islands->checkPixelCollision( kunai->getRect( i ) ) || 
		vampire_factory.harm( kunai->getRect( i ), kunai->getDamage() ) ||
		zombie_factory.harm( kunai->getRect( i ), kunai->getDamage() ) )
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
			vampire_factory.moveX( hero->getDirection(), scope->getVel() );
			zombie_factory.moveX( hero->getDirection(), scope->getVel() );
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
			vampire_factory.moveX( hero->getDirection(), -scope->getVel() );
			zombie_factory.moveX( hero->getDirection(), -scope->getVel() );
		}
	}
	
	// SCOPE MOVE
	scope->move( hero->getX(), this->screen_w );
	
	
// ------------------------------------------------------------------------------------------------
	// BACKGROUND SET XY
	background->setPosition( hero->getX(), hero->getY() );
	
	
	
// ------------------------------------------------------------------------------------------------
	// HERO FALLEN
	if( hero->checkFall( screen_h ) )
	{
		heart->harm( -wall->getFallDamage() );
		hero->setFallenY( brick->getNearGrassY( hero->getX() ) );
	}
	
	if( brick->getGrassDistance() > 0 )
	{
		if( scope->getState() == 0 || scope->getState() == 2 || brick->getLeft() >= -brick->getGrassValue() )
		{
			scope->changeMind();
			hero->undoFallX( brick->getGrassValue() );
		}
		else
		{
			brick->undoFall();
			islands->undoFall( brick->getGrassValue() );
			wall->undoFall( brick->getGrassValue() );
			ladder->undoFall( brick->getGrassValue() );
			greenery->undoFall( brick->getGrassValue() );
			mine_factory->undoFall( brick->getGrassValue() );
			vampire_factory.undoFall( brick->getGrassValue() );
			zombie_factory.undoFall( brick->getGrassValue() );
		}
	}
	else
	{
		hero->runFallenCounter();
	}
	
	hero->undoFallY();
	
// ------------------------------------------------------------------------------------------------
	// HARM BY WALL
	if( wall->harm( hero->getRect() ) )
	{
		heart->harm( -wall->getDamage() );
		effect->runBlood();
	}
	
	// HARM BY MINE
	mine_factory->checkCollision( hero->getRect() );
	if( mine_factory->harm( hero->getRect() ) )
	{
		heart->harm( -mine_factory->getDamage() );
		effect->runBlood();
	}
	
	// HARM BY VAMPIRE
	if( vampire_factory.harmSomebody( hero->getRect() ) )
	{
		heart->harm( -vampire_factory.getDamage() );
		effect->runBlood();
	}
	
	// HARM BY ZOMBIE
	if( zombie_factory.harmSomebody( hero->getRect() ) )
	{
		heart->harm( -zombie_factory.getDamage() );
		effect->runBlood();
	}
	
// ------------------------------------------------------------------------------------------------
	// DEAD
	if( heart->isDead() )
	{
		hero->die();
	}
	else
	{
		wall->mechanics();
		mine_factory->mechanics();
		vampire_factory.mechanics();
		zombie_factory.mechanics();
		
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
	}
	
	// ------------------------------------------------------------------------------------------------
	// CHECK Y AND SHOW EFFECT
	if( hero->getY() > screen_h )
	{
		effect->runFall();
	}
	
// ------------------------------------------------------------------------------------------------
	// SKELETON PART
	
	vampire_factory.appear( hero->getRect() );
	vampire_factory.walk( hero->getRect() );
	vampire_factory.ableAttack( hero->getRect() );
	vampire_factory.upliftMoney( hero->getRect() );
	if( vampire_factory.coinCorner() )
	{
		money_panel->add( vampire_factory.getCash() );
	}
	
	zombie_factory.appear( hero->getRect() );
	zombie_factory.walk( hero->getRect() );
	zombie_factory.ableAttack( hero->getRect() );
	zombie_factory.upliftMoney( hero->getRect() );
	if( zombie_factory.coinCorner() )
	{
		money_panel->add( zombie_factory.getCash() );
	}
}