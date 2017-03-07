#include "desert.h"

void Desert::mechanics()
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
		islands->turnOn();
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
			kunai->throwed( hero->getX(), hero->getY(), hero->getSide(), skills->getTop() );
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
		if( hero->getOffset() == 0 )	skills->swordUsed();
		skeleton_factory.harm( hero->getAttackBox(), hero->getDamage() );
		
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
			kunai->throwed( hero->getX(), hero->getY(), hero->getSide(), skills->getTop() );
		}
	}
	
	
	
// ------------------------------------------------------------------------------------------------
	// HERO ATTACK
	else if( hero->attack() )
	{
		if( hero->getOffset() == 0 )	skills->swordUsed();
		skeleton_factory.harm( hero->getAttackBox(), hero->getDamage() );
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
	for( unsigned i = 0; i < kunai->getSize(); i++ )
	{
		if( brick->checkPixelCollision( kunai->getRect( i ) ) ||
		kunai->getX( i ) + kunai->getW( i ) > screen_w +kunai->getW( i ) ||
		kunai->getX( i ) < -kunai->getW( i ) ||
		wall->checkCollision( kunai->getRect( i ) )	||
		islands->checkPixelCollision( kunai->getRect( i ) ) ||
		skeleton_factory.harm( kunai->getRect( i ), kunai->getDamage( i ) ) )
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
			wall->moveX( hero->getDirection(), scope->getVel() );
			ladder->moveX( hero->getDirection(), scope->getVel() );
			greenery->moveX( hero->getDirection(), scope->getVel() );
			mine_factory->moveX( hero->getDirection(), scope->getVel() );
			skeleton_factory.moveX( hero->getDirection(), scope->getVel() );
			coins->moveX( hero->getDirection(), scope->getVel() );
			fireball->moveX( hero->getDirection(), scope->getVel() );
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
			skeleton_factory.moveX( hero->getDirection(), -scope->getVel() );
			coins->moveX( hero->getDirection(), -scope->getVel() );
			fireball->moveX( hero->getDirection(), -scope->getVel() );
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
			skeleton_factory.undoFall( brick->getGrassValue() );
			coins->undoFall( brick->getGrassValue() );
			fireball->undoFall( brick->getGrassValue() );
		}
	}
	else
	{
		hero->runFallenCounter();
	}
	
	hero->undoFallY();
	
// ------------------------------------------------------------------------------------------------
	// HARM 
	
	if( !hero->resume() )
	{
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
		
		// HARM BY SKELETON
		if( skeleton_factory.harmSomebody( hero->getRect() ) )
		{
			heart->harm( -skeleton_factory.getDamage() );
			effect->runBlood();
		}
		
		// HARM BY FIREBALL
		if( fireball->harmSomebody( hero->getRect() ) )
		{
			if( fireball->harmed() )
			{
				heart->harm( -fireball->getDamage() );
				effect->runBlood();
			}
		}
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
		skeleton_factory.mechanics();
		coins->mechanics();
		fireball->mechanics( hero->getY(), hero->getDirection() );
		skills->mechanics();
		
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
		effect->runSand();
	}
	
// ------------------------------------------------------------------------------------------------
	// SET COLOR ~ DAY
	day->mechanics();

	
	if( day->isChange() )
	{
		hero->setColor( day->getColor() );
		coins->setColor( day->getColor() );
		
		brick->setColor( day->getColor() );
		background->setColor( day->getColor() );
		islands->setColor( day->getColor() );
		wall->setColor( day->getColor() );
		ladder->setColor( day->getColor() );
		greenery->setColor( day->getColor() );
		
		mine_factory->setColor( day->getColor() );
		skeleton_factory.setColor( day->getColor() );
	}
	
// ------------------------------------------------------------------------------------------------
	// SKELETON PART
	
	skeleton_factory.appear( hero->getRect() );
	skeleton_factory.walk( hero->getRect() );
	skeleton_factory.ableAttack( hero->getRect() );
	
// ------------------------------------------------------------------------------------------------
	// COINS
	coins->setCoin( skeleton_factory.getDeadRect() );
	
	if( coins->upliftMoney( hero->getRect() ) )
	{
		money->add( coins->getMoney() );
	}
}