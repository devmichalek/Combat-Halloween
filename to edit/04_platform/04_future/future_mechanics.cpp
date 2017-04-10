#include "future.h"

void Future::mechanics()
{
// HERO ANIMATION
	hero->doOffset();
	
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
	
	// ISLANDS WORLD IS MOVING
	islands->checkStands( hero->getRect() );
	if( islands->isStand() )
	{
		brick->moveX( islands->getDirection(), islands->getVel() );
		islands->moveX( islands->getDirection(), islands->getVel() );
		water->moveX( islands->getDirection(), islands->getVel() );
		wall->moveX( islands->getDirection(), islands->getVel() );
		boulder->moveX( islands->getDirection(), islands->getVel() );
		ladder->moveX( islands->getDirection(), islands->getVel() );
		greenery->moveX( islands->getDirection(), islands->getVel() );
		mine_factory->moveX( islands->getDirection(), islands->getVel() );
		robot_factory.moveX( islands->getDirection(), islands->getVel() );
		cruncher->moveX( islands->getDirection(), islands->getVel() );
		coins->moveX( islands->getDirection(), islands->getVel() );
		hp_dots->moveX( islands->getDirection(), islands->getVel() );
		score_dots->moveX( islands->getDirection(), islands->getVel() );
		exit->moveX( islands->getDirection(), islands->getVel() );
		saws->moveX( islands->getDirection(), islands->getVel() );
		kunai->moveX( islands->getDirection(), islands->getVel() );
	}
	
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
		robot_factory.harm( hero->getAttackBox(), hero->getDamage(), true );
		
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
		robot_factory.harm( hero->getAttackBox(), hero->getDamage(), true );
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
		islands->checkPixelCollision( kunai->getRect( i ) ) )
		{
			kunai->destroy( i );
		}
		
		else if( kunai->isExplosiveKunai( i ) )
		{
			if( robot_factory.harm( kunai->getRect( i ), kunai->getDamage( i ), true ) )
			{
				kunai->destroy( i );
			}
		}
		else if( robot_factory.harm( kunai->getRect( i ), kunai->getDamage( i ) ) )
		{
			if( kunai->isHealKunai( i ) )
			{
				showheal->run( kunai->getDamage( i ) );
				heart->harm( kunai->getDamage( i ) );
			}
			
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
			islands->moveX_stand( hero->getDirection(), scope->getVel() );
			water->moveX( hero->getDirection(), scope->getVel() );
			wall->moveX( hero->getDirection(), scope->getVel() );
			boulder->moveX( hero->getDirection(), scope->getVel() );
			ladder->moveX( hero->getDirection(), scope->getVel() );
			greenery->moveX( hero->getDirection(), scope->getVel() );
			mine_factory->moveX( hero->getDirection(), scope->getVel() );
			robot_factory.moveX( hero->getDirection(), scope->getVel() );
			cruncher->moveX( hero->getDirection(), scope->getVel() );
			coins->moveX( hero->getDirection(), scope->getVel() );
			hp_dots->moveX( hero->getDirection(), scope->getVel() );
			score_dots->moveX( hero->getDirection(), scope->getVel() );
			exit->moveX( hero->getDirection(), scope->getVel() );
			saws->moveX( hero->getDirection(), scope->getVel() );
			kunai->moveX( hero->getDirection(), scope->getVel() );
		}

		if( brick->checkPixelCollision( hero->getRect() ) ||
			wall->checkCollision( hero->getRect() ) ||
			islands->checkPixelCollision( hero->getRect() ) )
		{
			brick->moveX( hero->getDirection(), -scope->getVel() );	// undo
			islands->moveX( hero->getDirection(), -scope->getVel() );
			water->moveX( hero->getDirection(), -scope->getVel() );
			wall->moveX( hero->getDirection(), -scope->getVel() );
			boulder->moveX( hero->getDirection(), -scope->getVel() );
			ladder->moveX( hero->getDirection(), -scope->getVel() );
			greenery->moveX( hero->getDirection(), -scope->getVel() );
			mine_factory->moveX( hero->getDirection(), -scope->getVel() );
			robot_factory.moveX( hero->getDirection(), -scope->getVel() );
			cruncher->moveX( hero->getDirection(), -scope->getVel() );
			coins->moveX( hero->getDirection(), -scope->getVel() );
			hp_dots->moveX( hero->getDirection(), -scope->getVel() );
			score_dots->moveX( hero->getDirection(), -scope->getVel() );
			exit->moveX( hero->getDirection(), -scope->getVel() );
			saws->moveX( hero->getDirection(), -scope->getVel() );
			kunai->moveX( hero->getDirection(), -scope->getVel() );
		}
	}
	
	
	// SCOPE MOVE
	scope->move( hero->getX(), this->screen_w );

// ------------------------------------------------------------------------------------------------
	// HERO FALLEN
	if( hero->checkFall( screen_h ) )
	{
		heart->harm( -wall->getFallDamage() );
		hero->setFallenY( brick->getNearGrassY( hero->getX() ) );
	}
	
	if( brick->getGrassDistance() > 0 )
	{
		if( scope->getState() == 0 || scope->getState() == 2 || static_cast <int> (brick->getLeft()) >= -brick->getGrassValue() )
		{
			scope->changeMind();
			hero->undoFallX( brick->getGrassValue() );
		}
		else
		{
			brick->undoFall();
			islands->undoFall( brick->getGrassValue() );
			water->undoFall( brick->getGrassValue() );
			wall->undoFall( brick->getGrassValue() );
			boulder->undoFall( brick->getGrassValue() );
			ladder->undoFall( brick->getGrassValue() );
			greenery->undoFall( brick->getGrassValue() );
			mine_factory->undoFall( brick->getGrassValue() );
			robot_factory.undoFall( brick->getGrassValue() );
			cruncher->undoFall( brick->getGrassValue() );
			coins->undoFall( brick->getGrassValue() );
			hp_dots->undoFall( brick->getGrassValue() );
			score_dots->undoFall( brick->getGrassValue() );
			exit->undoFall( brick->getGrassValue() );
			saws->undoFall( brick->getGrassValue() );
			kunai->undoFall( brick->getGrassValue() );
		}
	}
	else
	{
		hero->runFallenCounter();
	}
	
	hero->undoFallY();
	
// ------------------------------------------------------------------------------------------------
	
	
// ------------------------------------------------------------------------------------------------
	// DEAD
	if( heart->isDead() )
	{
		hero->die();
	}
	else
	{
		kunai->mechanics();
		
		skills->mechanics();
		scores->mechanics();
		money->mechanics();
		pause->allow();
		
		hp_dots->mechanics();
		coins->mechanics();
		showdamage->focus( hero->getX(), hero->getY() );
		showdamage->mechanics();
		showheal->focus( hero->getX(), hero->getY() );
		showheal->mechanics();
		effect->mechanics();
		
		background->mechanics( hero->getX(), hero->getY() );
		wall->mechanics();
		boulder->mechanics( hero->getRect() );
		score_dots->mechanics();
		exit->checkHero( hero->getX() );
		saws->mechanics();
		
		cruncher->mechanics( hero->getY(), hero->getDirection() );
		mine_factory->mechanics();
		robot_factory.mechanics();
		
		if( !islands->checkFlyingIslands( hero->getRect() ) )
		{
			islands->mechanics();
		}
		else
		{
			islands->turnOff( hero->getDirection() );
		}
		
		if( islands->checkOtherIslands( hero->getRect() ) )
		{
			islands->turnOn();
		}
		
		// HARM 
	
		if( !hero->resume() )
		{
			// HARM BY WALL
			if( wall->harm( hero->getRect() ) )
			{
				heart->harm( -wall->getDamage() );
				showdamage->run( to_string( -wall->getDamage() ) );
				effect->runBlood();
			}
			
			// HARM BY BOULDER
			if( boulder->harm( hero->getRect() ) )
			{
				heart->harm( -boulder->getDamage() );
				showdamage->run( to_string( -boulder->getDamage() ) );
				effect->runBlood();
			}
			
			// HARM BY MINE
			mine_factory->checkCollision( hero->getRect() );
			if( mine_factory->harm( hero->getRect() ) )
			{
				heart->harm( -mine_factory->getDamage() );
				showdamage->run( to_string( -mine_factory->getDamage() ) );
				effect->runBlood();
			}
			
			// HARM BY ROBOT
			if( robot_factory.harmSomebody( hero->getRect() ) )
			{
				heart->harm( -robot_factory.getDamage() );
				showdamage->run( to_string( -robot_factory.getDamage() ) );
				effect->runBlood();
			}
			
			// HARM BY cruncher
			if( cruncher->harmSomebody( hero->getRect() ) )
			{
				heart->harm( -cruncher->getDamage() );
				showdamage->run( to_string( -cruncher->getDamage() ) );
				effect->runCruncher();
			}
			
			// HARM BY SPIKES
			saws->check( hero->getRect() );
			if( saws->harm( hero->getRect() ) )
			{
				heart->harm( -saws->getDamage() );
				showdamage->run( to_string( -saws->getDamage() ) );
				effect->runBlood();
			}
		}
		
// ------------------------------------------------------------------------------------------------
		// CHECK Y AND SHOW EFFECT
		if( hero->getY() > screen_h ||
			water->checkCollision( hero->getRect() ))
		{
			effect->runAcid();
		}
		
		
// ------------------------------------------------------------------------------------------------
		// ROBOT PART
		
		robot_factory.appear( hero->getRect() );
		robot_factory.walk( hero->getRect() );
		robot_factory.ableAttack( hero->getRect() );
		
// ------------------------------------------------------------------------------------------------
		// COINS, HP DOTS AND SCORES
		if( hp_dots->drop( coins->drop( robot_factory.getDeadRect() ) ) )
		{
			scores->addFoePoint();
		}
		
		if( coins->uplift( hero->getRect() ) )
		{
			money->add( coins->getMoney() );
		}
		
		if( hp_dots->uplift( hero->getRect() ) )
		{
			showheal->run( hp_dots->getHP() );
			heart->harm( hp_dots->getHP() );
		}
		
			
		if( score_dots->uplift( hero->getRect() ) )
		{
			scores->addPoint();
		}
	}
}