#include "04_platform/enemy/skeleton/skeleton_factory.h"

Skeleton_factory::Skeleton_factory()
{
	width = 0;
	screen_w = 0;
	screen_h = 0;
}

Skeleton_factory::~Skeleton_factory()
{
	free();
}

void Skeleton_factory::free()
{
	width = 0;
	screen_w = 0;
	screen_h = 0;
	
	life.free();
	frame.free();
	
	if( !line.empty() )
	{
		line.clear();
	}
	
	if( !sprites.empty() )
	{
		for( auto &i :sprites )
		{
			i->free();
		}
		
		sprites.clear();
	}
	
	if( !skeletons.empty() )
	{
		for( auto &i :skeletons )
		{
			i->free();
		}
		
		skeletons.clear();
	}
}

void Skeleton_factory::reset( int distance )
{
	for( auto &it :skeletons )
	{
		it->reset( distance );
	}
}

void Skeleton_factory::load( int width, int screen_w, int screen_h )
{
	free();
	
	line.push_back( 10 );
	line.push_back( 6 );
	line.push_back( 8 );
	line.push_back( 8 );
	line.push_back( 8 );
	
	life.setName( "skeleton_factory-life" );
	life.load( "data/sprites/hero/heart/fill.png");
	
	frame.setName( "skeleton_factory-frame" );
	frame.load( "data/sprites/hero/heart/frame.png");
	
	for( unsigned i = 0; i < line.size(); i++ )
	{
		sprites.push_back( new MySprite() );
		sprites[ sprites.size() -1 ]->setName( "skeleton_factory-sprites[ " +to_string( i ) +" ]" );
		sprites[ sprites.size() -1 ]->load( "data/sprites/enemy/skeleton/" +to_string( i ) +".png", line[ i ] );
	}
	
	this->width = width;
	this->screen_w = screen_w;
	this->screen_h = screen_h;
}

void Skeleton_factory::draw( sf::RenderWindow* &window )
{
	for( auto &i :skeletons )
	{
		if( i->getX() > -width*3 && i->getX() < screen_w + width*3 && i->isAlive() )
		{
			life.setAlpha( i->getHeartPoints() );
			life.setPosition( i->getRealX() +life.getWidth()/3, i->getRealY() -life.getHeight() );
			window->draw( life.get() );
			
			frame.setPosition( life.getX(), life.getY() );
			window->draw( frame.get() );
			
			sprites[ i->getState() ]->setOffset( i->getOffset() );
			sprites[ i->getState() ]->setPosition( i->getX(), i->getY() );
			sprites[ i->getState() ]->setScale( i->getHorizontalScale(), i->getVerticalScale() );
			window->draw( sprites[ i->getState() ]->get() );
		}
	}
	
	/*
	// create an empty shape
	sf::ConvexShape convex;

	// resize it to 4 points
	convex.setPointCount(4);

	// define the points
	skeletons[ 0 ]->setScale( skeletons[ 0 ]->getHorizontalScale(), skeletons[ 0 ]->getVerticalScale() );
	convex.setPoint( 0, sf::Vector2f( skeletons[ 0 ]->getRealX(), skeletons[ 0 ]->getRealY() ) );
	convex.setPoint( 1, sf::Vector2f( skeletons[ 0 ]->getRealX() +skeletons[ 0 ]->getRealWidth(), skeletons[ 0 ]->getRealY() ) );
	
	convex.setPoint( 2, sf::Vector2f( skeletons[ 0 ]->getRealX() +skeletons[ 0 ]->getRealWidth(), skeletons[ 0 ]->getRealY() +skeletons[ 0 ]->getRealHeight() ) );
	convex.setPoint( 3, sf::Vector2f( skeletons[ 0 ]->getRealX(), skeletons[ 0 ]->getRealY() +skeletons[ 0 ]->getRealHeight() ) );
	window->draw( convex );
	*/
}

void Skeleton_factory::fadein( int v, int max )
{
	frame.fadein( v, max );
	
	for( auto &i :sprites )
	{
		i->fadein( v, max );
	}
}

void Skeleton_factory::fadeout( int v, int min )
{
	life.fadeout( v, min );
	frame.fadeout( v, min );
	
	for( auto &i :sprites )
	{
		i->fadeout( v, min );
	}
}




void Skeleton_factory::addSkeleton( int x, int y, int damage )
{
	skeletons.push_back( new Skeleton() );
	
	vector <float> myX;
	vector <float> myY;
	vector <int> widths;
	vector <int> heights;
	
	int surplus = damage /5;
	
	float scale = static_cast <float>(rand()%10 +(30 +surplus)) /100;
	skeletons[ skeletons.size() -1 ]->setScale( scale, scale );
	
	for( unsigned i = 0; i < sprites.size(); i++ )
	{
		sprites[ i ]->setScale( scale, scale );
		myX.push_back( x -sprites[ i ]->getWidth()/2 +width/2 );
		myY.push_back( y -sprites[ i ]->getHeight() );
		widths.push_back( sprites[ i ]->getWidth() );
		heights.push_back( sprites[ i ]->getHeight() );
	}
	
	myY[ 3 ] += (17*scale);
	
	skeletons[ skeletons.size() -1 ]->setX( myX );
	skeletons[ skeletons.size() -1 ]->setY( myY );
	skeletons[ skeletons.size() -1 ]->setLine( line );
	skeletons[ skeletons.size() -1 ]->setWidth( widths );
	skeletons[ skeletons.size() -1 ]->setHeight( heights );
	skeletons[ skeletons.size() -1 ]->setVelocity( static_cast <float>(damage) /100 );
	skeletons[ skeletons.size() -1 ]->setDelay( rand()%1 +10 );
	skeletons[ skeletons.size() -1 ]->setDamage( damage );
	skeletons[ skeletons.size() -1 ]->setHeartPoints( rand()%100 +60 );
	skeletons[ skeletons.size() -1 ]->setAttackLine( rand()%2 +3 );
}

void Skeleton_factory::positioning( vector <Block*> blocks, int chance )
{
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		if( blocks[ i ]->nr == 5 || blocks[ i ]->nr == 0 || blocks[ i ]->nr == 4 )
		{
			int counter = 1;
			int startX = blocks[ i ]->x;
			int startY = blocks[ i ]->y;
			
			for( unsigned j = i +1; j < blocks.size(); j++ )
			{
				if( blocks[ j ]->nr >= 0 && blocks[ j ]->nr <= 7 &&
					blocks[ j -1 ]->y == blocks[ j ]->y &&
					blocks[ j -1 ]->x == blocks[ j ]->x -width )
				{
					counter ++;
				}
				else
				{
					i = j;
					break;
				}
			}
			
			if( counter > 2 )
			{
				if( rand()%100 < chance )
				{
					addSkeleton( startX +width*(counter/2), startY, chance );
					skeletons[ skeletons.size() -1 ]->setBorders( startX, startX +width*counter );
				}
			}
		}
	}
}



void Skeleton_factory::appear( Rect* rect )
{
	for( auto &it :skeletons )
	{
		it->appear( rect );
	}
}

void Skeleton_factory::walk( Rect* rect )
{
	for( auto &it :skeletons )
	{
		it->walk( rect );
	}
}

bool Skeleton_factory::harm( Rect* rect, int damage )
{
	if( rect != NULL )
	{
		for( auto &i :skeletons )
		{
			if( i->isAlive() && i->getRealX() > -width*3 && i->getRealX() < screen_w +width*3 && i->getHeartPoints() > 0 )
			{
				Rect r;
				r.set( i->getRealX(), i->getRealY(), i->getRealWidth(), i->getRealHeight() );
				if( r.checkCollision( rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight() ) )
				{
					i->harm( -damage );
					if( i->getHeartPoints() <= 0 )
					{
						i->setDead();
					}
					
					return true;
				}
			}
		}
	}
	
	return false;
}

void Skeleton_factory::ableAttack( Rect* rect )
{
	if( rect != NULL )
	{
		for( auto &i :skeletons )
		{
			if( i->getX() > -width*3 && i->getX() < screen_w +width*3 && i->isAlive() )
			{
				sprites[ i->getState() ]->setPosition( i->getRealX(), i->getRealY() );
				if( sprites[ i->getState() ]->checkCollision( rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight() ) )
				{
					i->ableAttack();
				}
			}
		}
	}
}

bool Skeleton_factory::isSword( Rect* rect )
{
	if( rect != NULL )
	{
		for( vector <Skeleton*> ::iterator i = skeletons.begin(); i != skeletons.end(); i++ )
		{
			if( (*i)->isSword() && (*i)->isAlive() && (*i)->getX() > -width*3 && (*i)->getX() < screen_w +width*3 )
			{
				Rect r;
				r.set( (*i)->getAttackX(), (*i)->getAttackY(), (*i)->getAttackWidth(), (*i)->getAttackHeight() );
				if( r.checkCollision( rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight() ) )
				{
					// printf( "collision!\n" );
					this->sword = i;
					return true;
				}
			}
		}
	}
	
	return false;
}

int Skeleton_factory::getDamage()
{
	return (*sword)->getDamage();
}




void Skeleton_factory::moveX( sf::Uint8 direction, float vel )
{
	if( direction == 1 )
	{
		for( auto &it :skeletons )
		{
			it->moveX( vel );
		}
	}
	else if( direction == 2 )
	{
		for( auto &it :skeletons )
		{
			it->moveX( -vel );
		}
	}
}

void Skeleton_factory::undoFall( sf::Uint8 add )
{
	for( auto &it :skeletons )
	{
		it->moveX( add );
	}
}

void Skeleton_factory::mechanics()
{
	for( auto &i :skeletons )
	{
		i->mechanics();
	}
}

void Skeleton_factory::setColor( sf::Color color )
{
	for( auto &i :sprites )
	{
		i->setColor( color );
	}
}



unsigned Skeleton_factory::getSize()
{
	return skeletons.size();
}

Rect* Skeleton_factory::getRect( int which )
{
	if( skeletons[ which ]->isAlive() )
	{
		Rect* r = new Rect;
		r->set( skeletons[ which ]->getRealX(), 
				skeletons[ which ]->getRealY(), 
				skeletons[ which ]->getRealWidth(), 
				skeletons[ which ]->getRealHeight() );
		return r;
	}
	
	return NULL;
}

void Skeleton_factory::harmDefinite( int which, int damage )
{
	if( skeletons[ which ]->isAlive() )
	{
		skeletons[ which ]->harm( damage );
		if( skeletons[ which ]->getHeartPoints() < 0 )
		{
			skeletons[ which ]->setDead();
		}
	}
}