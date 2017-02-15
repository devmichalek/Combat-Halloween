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
	
	if( !line.empty() )
	{
		line.clear();
	}
	
	if( !widths.empty() )
	{
		widths.clear();
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
	
	for( unsigned i = 0; i < line.size(); i++ )
	{
		sprites.push_back( new MySprite() );
		sprites[ sprites.size() -1 ]->setName( "skeleton_factory-sprites[ " +to_string( i ) +" ]" );
		sprites[ sprites.size() -1 ]->load( "data/sprites/enemy/skeleton/" +to_string( i ) +".png", line[ i ] );
		sprites[ sprites.size() -1 ]->setScale( 0.5, 0.5 );
		widths.push_back( sprites[ sprites.size() -1 ]->getWidth() );
	}
	
	this->width = width;
	this->screen_w = screen_w;
	this->screen_h = screen_h;
}

void Skeleton_factory::draw( sf::RenderWindow* &window )
{
	for( auto &i :skeletons )
	{
		i->mechanics( width );
		
		if( i->getX() > -width*3 && i->getX() < screen_w + width*3 && i->alive() )
		{
			sprites[ i->getNr() ]->setOffset( i->getOffset() );
			sprites[ i->getNr() ]->setPosition( i->getX(), i->getY() );
			sprites[ i->getNr() ]->setScale( i->get_x_scale() *0.5, 0.5 );
			window->draw( sprites[ i->getNr() ]->get() );
		}
	}
}

void Skeleton_factory::fadein( int v, int max )
{
	for( auto &i :sprites )
	{
		i->fadein( v, max );
	}
}

void Skeleton_factory::fadeout( int v, int min )
{
	for( auto &i :sprites )
	{
		i->fadeout( v, min );
	}
}




void Skeleton_factory::addSkeleton( int x, int y )
{
	skeletons.push_back( new Skeleton() );
	
	vector <float> myX;
	vector <float> myY;
	
	for( unsigned i = 0; i < sprites.size(); i++ )
	{
		myX.push_back( x -sprites[ i ]->getWidth()/2 +width/2 );
		myY.push_back( y -sprites[ i ]->getHeight() );
	}
	
	myY[ 3 ] += 10;
	
	skeletons[ skeletons.size() -1 ]->setPosition( myX, myY );
	skeletons[ skeletons.size() -1 ]->setLine( line, widths );
}

void Skeleton_factory::positioning( vector <Block*> blocks, int chance )
{
	
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		if( blocks[ i ]->nr >= 0 && blocks[ i ]->nr <= 7 )
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
				// printf( "%d %d\n", startX, startX +width*counter );
				addSkeleton( startX +width*(counter-1), startY );
				skeletons[ skeletons.size() -1 ]->setGlobalX( startX, startX +width*counter );
			}
		}
	}
}



void Skeleton_factory::appear( int heroX )
{
	for( auto &it :skeletons )
	{
		it->appear( heroX );
	}
}

void Skeleton_factory::walk( int heroX, int heroY )
{
	for( auto &it :skeletons )
	{
		it->walk( heroX, heroY, width*2 );
	}
}

bool Skeleton_factory::harm( Rect* rect )
{
	if( rect != NULL )
	{
		for( auto &i :skeletons )
		{
			if( i->getX() > -width*3 && i->getX() < screen_w +width*3 && i->harmAvailable() && i->alive() )
			{
				sprites[ i->getNr() ]->setPosition( i->getX(), i->getY() );
				if( sprites[ i->getNr() ]->checkCollision( rect->getX(), rect->getY() -50, rect->getWidth(), rect->getHeight()/2 ) )
				{
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
			if( i->getX() > -width*3 && i->getX() < screen_w +width*3 && i->alive() )
			{
				sprites[ i->getNr() ]->setPosition( i->getX(), i->getY() );
				if( sprites[ i->getNr() ]->checkCollision( rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight() ) )
				{
					i->ableAttack();
				}
			}
		}
	}
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

void Skeleton_factory::setColor( sf::Color color )
{
	for( auto &i :sprites )
	{
		i->setColor( color );
	}
}
