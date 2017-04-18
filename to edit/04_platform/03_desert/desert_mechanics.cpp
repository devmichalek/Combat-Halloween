#include "desert.h"

void Desert::mechanics()
{
// TIME
	time_box->mechanics();
	
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
		wall->moveX( islands->getDirection(), islands->getVel() );
		boulder->moveX( islands->getDirection(), islands->getVel() );
		ladder->moveX( islands->getDirection(), islands->getVel() );
		greenery->moveX( islands->getDirection(), islands->getVel() );
		mine_factory->moveX( islands->getDirection(), islands->getVel() );
		skeleton_factory.moveX( islands->getDirection(), islands->getVel() );
		snakes_factory->moveX( islands->getDirection(), islands->getVel() );
		coins->moveX( islands->getDirection(), islands->getVel() );
		hp_dots->moveX( islands->getDirection(), islands->getVel() );
		score_dots->moveX( islands->getDirection(), islands->getVel() );
		fireball->moveX( islands->getDirection(), islands->getVel() );
		wind->moveX( islands->getDirection(), islands->getVel() );
		fly_factory->moveX( islands->getDirection(), islands->getVel() );
		exit->moveX( islands->getDirection(), islands->getVel() );
		kunai->moveX( islands->getDirection(), islands->getVel() );
	}
	
// ------------------------------------------------------------------------------------------------
	// HERO WEIGHTLESSNESS
	if( brick->checkPixelCollision( hero->getRect() ) )
	{
		hero->weightlessness();
		islands->start();
	}
	else if( islands->checkPixelCollision( hero->getRect() ) )
	{
		hero->weightlessness();
		islands->start();
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
		skeleton_factory.harm( hero->getAttackBox(), hero->getDamage(), true );
		
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
		skeleton_factory.harm( hero->getAttackBox(), hero->getDamage(), true );
		snakes_factory->harm( hero->getAttackBox(), hero->getDamage(), true );
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
		if( kunai->isActive( i ) )
		{
			if( brick->checkPixelCollision( kunai->getRect( i ) ) ||
			kunai->getX( i ) + kunai->getW( i ) > screen_w +kunai->getW( i ) ||
			kunai->getX( i ) < -kunai->getW( i ) ||
			wall->checkCollision( kunai->getRect( i ) )	||
			islands->checkPixelCollision( kunai->getRect( i ) ) )
			{
				kunai->destroy( i );
			}
			
			else if( kunai->isStuntKunai( i ) )
			{
				if( skeleton_factory.stunt( kunai->getRect( i ), kunai->getDamage( i ) ) || 
					snakes_factory->harm( kunai->getRect( i ), 0 ) )
				{
					kunai->destroy( i );
				}
			}
			else if( kunai->isExplosiveKunai( i ) )
			{
				if( skeleton_factory.harm( kunai->getRect( i ), kunai->getDamage( i ), true ) || 
					snakes_factory->harm( kunai->getRect( i ), kunai->getDamage( i ), true ) )
				{
					kunai->destroy( i );
				}
			}
			else if( skeleton_factory.harm( kunai->getRect( i ), kunai->getDamage( i ) ) )
			{
				if( kunai->isHealKunai( i ) )
				{
					showheal->run( kunai->getDamage( i ) );
					heart->harm( kunai->getDamage( i ) );
				}
				
				kunai->destroy( i );
			}
			else if( snakes_factory->harm( kunai->getRect( i ), kunai->getDamage( i ) ) )
			{
				if( kunai->isHealKunai( i ) )
				{
					showheal->run( kunai->getDamage( i ) );
					heart->harm( kunai->getDamage( i ) );
				}
				
				kunai->destroy( i );
			}
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
			wall->moveX( hero->getDirection(), scope->getVel() );
			boulder->moveX( hero->getDirection(), scope->getVel() );
			ladder->moveX( hero->getDirection(), scope->getVel() );
			greenery->moveX( hero->getDirection(), scope->getVel() );
			mine_factory->moveX( hero->getDirection(), scope->getVel() );
			skeleton_factory.moveX( hero->getDirection(), scope->getVel() );
			snakes_factory->moveX( hero->getDirection(), scope->getVel() );
			coins->moveX( hero->getDirection(), scope->getVel() );
			hp_dots->moveX( hero->getDirection(), scope->getVel() );
			score_dots->moveX( hero->getDirection(), scope->getVel() );
			fireball->moveX( hero->getDirection(), scope->getVel() );
			wind->moveX( hero->getDirection(), scope->getVel() );
			fly_factory->moveX( hero->getDirection(), scope->getVel() );
			exit->moveX( hero->getDirection(), scope->getVel() );
			kunai->moveX( hero->getDirection(), scope->getVel() );
		}

		if( brick->checkPixelCollision( hero->getRect() ) ||
			wall->checkCollision( hero->getRect() ) ||
			islands->checkPixelCollision( hero->getRect() ) )
		{
			brick->moveX( hero->getDirection(), -scope->getVel() );	// undo
			islands->moveX( hero->getDirection(), -scope->getVel() );
			wall->moveX( hero->getDirection(), -scope->getVel() );
			boulder->moveX( hero->getDirection(), -scope->getVel() );
			ladder->moveX( hero->getDirection(), -scope->getVel() );
			greenery->moveX( hero->getDirection(), -scope->getVel() );
			mine_factory->moveX( hero->getDirection(), -scope->getVel() );
			skeleton_factory.moveX( hero->getDirection(), -scope->getVel() );
			snakes_factory->moveX( hero->getDirection(), -scope->getVel() );
			coins->moveX( hero->getDirection(), -scope->getVel() );
			hp_dots->moveX( hero->getDirection(), -scope->getVel() );
			score_dots->moveX( hero->getDirection(), -scope->getVel() );
			fireball->moveX( hero->getDirection(), -scope->getVel() );
			wind->moveX( hero->getDirection(), -scope->getVel() );
			fly_factory->moveX( hero->getDirection(), -scope->getVel() );
			exit->moveX( hero->getDirection(), -scope->getVel() );
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
			wall->undoFall( brick->getGrassValue() );
			boulder->undoFall( brick->getGrassValue() );
			ladder->undoFall( brick->getGrassValue() );
			greenery->undoFall( brick->getGrassValue() );
			mine_factory->undoFall( brick->getGrassValue() );
			skeleton_factory.undoFall( brick->getGrassValue() );
			snakes_factory->undoFall( brick->getGrassValue() );
			coins->undoFall( brick->getGrassValue() );
			hp_dots->undoFall( brick->getGrassValue() );
			score_dots->undoFall( brick->getGrassValue() );
			fireball->undoFall( brick->getGrassValue() );
			wind->undoFall( brick->getGrassValue() );
			fly_factory->undoFall( brick->getGrassValue() );
			exit->undoFall( brick->getGrassValue() );
			kunai->undoFall( brick->getGrassValue() );
		}
	}
	else
	{
		hero->runFallenCounter();
	}
	
	hero->undoFallY();
	
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
		day->mechanics();
		wind->mechanics();
		
		fireball->mechanics( hero->getY(), hero->getDirection() );
		mine_factory->mechanics();
		skeleton_factory.mechanics();
		snakes_factory->mechanics();
		fly_factory->mechanics();
		
		
		
		if( !islands->checkFlyingIslands( hero->getRect() ) )
		{
			islands->mechanics();
		}
		else
		{
			islands->stop( hero->getDirection() );
		}
		
		if( islands->checkOtherIslands( hero->getRect() ) )
		{
			islands->start();
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
			
			// HARM BY SKELETON
			if( skeleton_factory.harmSomebody( hero->getRect() ) )
			{
				heart->harm( -skeleton_factory.getDamage() );
				showdamage->run( to_string( -skeleton_factory.getDamage() ) );
				effect->runBlood();
			}
			
			// HARM BY SNAKES
			if( snakes_factory->harmSomebody( hero->getRect() ) )
			{
				heart->harm( -snakes_factory->getDamage() );
				showdamage->run( to_string( -snakes_factory->getDamage() ) );
				effect->runBlood();
			}
			
			// HARM BY FIREBALL
			if( fireball->harmSomebody( hero->getRect() ) )
			{
				if( fireball->harmed() )
				{
					heart->harm( -fireball->getDamage() );
					showdamage->run( to_string( -fireball->getDamage() ) );
					effect->runBlood();
				}
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
		if( day->isChange() )
		{
			hero->setColor( day->getColor() );
			coins->setColor( day->getColor() );
			hp_dots->setAlpha( day->getAlpha() );
			score_dots->setAlpha( day->getAlpha() );
			kunai->setColor( day->getColor() );
			
			brick->setColor( day->getColor() );
			background->setColor( day->getColor() );
			islands->setColor( day->getColor() );
			wall->setColor( day->getColor() );
			boulder->setColor( day->getColor() );
			ladder->setColor( day->getColor() );
			greenery->setColor( day->getColor() );
			
			fireball->setColor( day->getColor() );
			mine_factory->setColor( day->getColor() );
			skeleton_factory.setColor( day->getColor() );
			snakes_factory->setColor( day->getColor() );
			fly_factory->setColor( day->getColor() );
		}
		
// ------------------------------------------------------------------------------------------------
		// SKELETON PART
		
		skeleton_factory.appear( hero->getRect() );
		skeleton_factory.walk( hero->getRect() );
		skeleton_factory.ableAttack( hero->getRect() );
		
// ------------------------------------------------------------------------------------------------
		// SNAKES PART
		
		snakes_factory->appear( hero->getX() );
		snakes_factory->ableAttack( hero->getRect() );
		
// ------------------------------------------------------------------------------------------------
		// COINS AND HP DOTS
		if( hp_dots->drop( coins->drop( skeleton_factory.getDeadRect() ) ) )
		{
			scores->addFoePoint();
		}
		
		if( hp_dots->drop( coins->drop( snakes_factory->getDeadRect() ) ) )
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