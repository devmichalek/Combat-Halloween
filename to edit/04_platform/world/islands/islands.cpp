#include "islands.h"
#include <cstdlib>
#include <fstream>

Islands::Islands()
{
	width = 0;
	screen_w = 0;
	screen_h = 0;
}

Islands::~Islands()
{
	free();
}

void Islands::free()
{
	width = 0;
	screen_w = 0;
	screen_h = 0;
	
	if( !hovers.empty() )
	{
		for( auto &it :hovers )
		{
			it->free();
		}
		
		hovers.clear();
	}
	
	if( !blocks.empty() )
	{
		for( auto &it :blocks )
		{
			it->free();
		}
		
		blocks.clear();
	}
	
	if( !planks.empty() )
	{
		for( auto &it :planks )
		{
			it->free();
		}
		
		planks.clear();
	}
	
	if( !sprites.empty() )
	{
		for( auto &it :sprites )
		{
			it->free();
		}
		
		sprites.clear();
	}
}

void Islands::reset( int distance )
{
	while( true )
	{
		if( distance > 0 )
		{
			for( auto &it :hovers )
			{
				it->moveX( 1 );
			}
			
			for( auto &it :blocks )
			{
				it->x ++;
			}
			
			distance --;
		}
		else
		{
			break;
		}
	}
}

void Islands::load( int type, int width, int screen_w, int screen_h )
{
	free();
	
	// Load data.
	for( int i = 0; i < 16; i++ )
	{
		sprites.push_back( new MySprite() );
		sprites[ i ]->setName( "islands-sprites[" +to_string( i ) +"]" );
		sprites[ i ]->load( "data/sprites/play/" +to_string( type ) +"/" +to_string( i ) +".png" );
	}
	
	this->width = width;
	this->screen_w = screen_w;
	this->screen_h = screen_h;
}

void Islands::draw( sf::RenderWindow* &window )
{
	for( auto &it :hovers )
	{
		it->moving( width );
		
		for( unsigned i = 0; i < it->getSize(); i++ )
		{
			if( it->getX(i) > -width*2 && it->getX(i) < screen_w +width )
			{
				sprites[ it->getNr(i) ]->setPosition( it->getX(i), it->getY(i) );
				window->draw( sprites[ it->getNr(i) ]->get() );
			}
		}
	}
	
	for( auto &it :blocks )
	{
		if( it->nr != -1 )
		{
			if( it->x > -width && it->x < screen_w )
			{
				sprites[ it->nr ]->setPosition( it->x, it->y );
				window->draw( sprites[ it->nr ]->get() );
			}
		}
	}
}

void Islands::fadein( int v, int max )
{
	for( auto &it :sprites )
	{
		it->fadein( v, max );
	}
}

void Islands::fadeout( int v, int min )
{
	for( auto &it :sprites )
	{
		it->fadeout( v, min );
	}
}



void Islands::addHover( int startX, int endX, int y, int vel )
{
	hovers.push_back( new Hover() ); 	// add block.
	hovers[ hovers.size()-1 ]->positioning( width );
	hovers[ hovers.size()-1 ]->setPosition( startX, endX, y, vel );
}

void Islands::addBlock( int n, int x, int y )
{
	blocks.push_back( new Block() ); 	// add block.
	blocks[ blocks.size()-1 ]->nr = n; 	// set chosen.
	blocks[ blocks.size()-1 ]->x = x; 	// set x.
	blocks[ blocks.size()-1 ]->y = y; 	// set y.
}

void Islands::addPlank( int n, int x, int y )
{
	planks.push_back( new Plank() ); 	// add block.
	planks[ planks.size()-1 ]->nr = n; 	// set chosen.
	planks[ planks.size()-1 ]->x = x; 	// set x.
	planks[ planks.size()-1 ]->y = y; 	// set y.
}



void Islands::createFlyingIslands( vector <Block*> blocks, vector <Plank*> planks, int chance )
{
	for( unsigned i = 0; i < blocks.size()-2; i++ )
	{
		if( blocks[ i ]->nr == 2 || blocks[ i ]->nr == 7 )
		{
			if( blocks[ i ]->y == blocks[ i +2 ]->y && blocks[ i +2 ]->nr != -1 )
			{
				if( rand()%100 < chance )
				{
					int distance = rand()%2 +4;
				
					int startX = blocks[ i ]->x +width;
					int endX = blocks[ i ]->x + (distance +2)*width;
					int y = blocks[ i ]->y;
					
					int vel = 0;
					
					if( rand()%6 < 2 )
					{
						vel = 2;
					}
					else
					{
						vel = 1;
					}
					
					addHover( startX, endX, y, vel );
					
					for( unsigned j = 0; j < planks.size(); j++ )
					{
						if( planks[ j ]->x > blocks[ i +2 ]->x )
						{
							for( unsigned k = j; k < planks.size(); k++ )
							{
								planks[ k ]->x += distance*width;
							}
							
							break;
						}
					}
					
					for( unsigned j = i +1; j < blocks.size(); j++ )
					{
						blocks[ j ]->x += distance*width;
					}
				}
			}
		}
	}
}

void Islands::createBotIslands( vector <Block*> blocks, int w, int h )
{
	vector <int> posX;
	vector <int> posY;
	vector <int> counters;
	
	// Searcher
	for( auto i = blocks.begin(); i != blocks.end(); i++ )
	{
		// blocks with grass, apriopriate y
		if( (*i)->y < screen_h -width*2 )
		{
			if( (*i)->nr >= 5 && (*i)->nr <= 7 )
			{
				posX.push_back( (*i)->x );
				posY.push_back( (*i)->y );
				counters.push_back( 1 );
				
				for( auto j = i +1; j != blocks.end(); j++ )
				{
					if( (*j)->y == (*i)->y ) // check y
					{
						if( ((*j)->nr >= 5 && (*j)->nr <= 7) || (*j)->nr == -1 )
						{
							counters[ counters.size()-1 ] ++;
						}
						else
						{
							i = j +1;
							break;
						}
					}
					else
					{
						i = j +1;
						break;
					}
				}
			}
			
		}
	}

	
	// Creator
	for( unsigned i = 0; i < posX.size(); i++ )
	{
		// x and y for ladder
		int myX, myY;
		
		// searching for free space
		sf::Uint8 success = 0;
		
		// check left
		for( unsigned j = 0; j < blocks.size(); j++ )
		{
			if( blocks[ j ]->y == posY[ i ] && blocks[ j ]->nr == -1 )
			{
				if( blocks[ j ]->x == posX[ i ] -width )
				{
					success = 1;
					myX = blocks[ j ]->x +width -w +10;
					break;
				}
			}
		}
		
		int surplus = 0;
		// check right
		if( success == 0 )
		{
			for( unsigned j = 0; j < blocks.size()-1; j++ )
			{
				if( blocks[ j ]->y == posY[ i ] && blocks[ j ]->nr == -1 && blocks[j -1]->nr != -1 )
				{
					if( blocks[ j ]->x == posX[ i ] + width *(counters[ i ]-1)
					&& blocks[ j ]->x != blocks[ j +1 ]->x )	// check if we can climb (change of floor)
					{
						success = 2;
						myX = blocks[ j ]->x -10;
						surplus = 0 *width;
						// printf( "2 %d\n", myX );
						break;
					}
				}
			}
		}
		
		if( success != 0 )
		{
			// add ladder
			addPlank( 1, myX, posY[ i ] -h +width*2 );
			
			if( success == 2 )
			{
				myX -= width*(counters[ i ] -1) -w -surplus;
				counters[ i ] -= 1;
			}
			
			if( posY[ i ] == screen_h -width*4 ) // 0, 1, 2.
			{
				myY = screen_h -width;
				int saveX = myX;
				
				addBlock( 10, myX, myY );
				myX += width;
				
				for( int j = 0; j < counters[ i ]-2; j++ )
				{
					addBlock( 11, myX, myY );
					myX += width;
				}
				
				addBlock( 12, myX, myY );
				
				myY = screen_h -width*2;
				myX = saveX;
			}
			else
			{
				myY = screen_h -width;
			}
			
			addBlock( 0, myX, myY );
			myX += width;
			
			for( int j = 0; j < counters[ i ]-2; j++ )
			{
				addBlock( 1, myX, myY );
				myX += width;
			}
			
			addBlock( 2, myX, myY );
		}
	}
}

void Islands::createTopIslands( vector <Block*> blocks, int w, int h )
{
	vector <int> posX;
	vector <int> posY;
	vector <int> counters;
	
	// Searcher
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		// blocks with grass, apriopriate y
		if( blocks[ i ]->y >= screen_h -width*2 &&
		  ( blocks[ i ]->nr == 0 ||
			blocks[ i ]->nr == 4 ||
			blocks[ i ]->nr == 5 ) )
		{
			posX.push_back( blocks[ i ]->x );
			posY.push_back( blocks[ i ]->y );
			counters.push_back( 1 );
			
			for( unsigned j = i+1; j < blocks.size(); j++ )
			{
				if( blocks[ j ]->y == blocks[ i ]->y )
				{
					if( blocks[ j ]->nr == 2 || blocks[ j ]->nr == 3 || blocks[ j ]->nr == 7 )
					{
						counters[ counters.size()-1 ] ++;
						i = j +1;
						break;
					}
					
					if( blocks[ j ]->nr == 1 || blocks[ j ]->nr == 6 )
					{
						counters[ counters.size()-1 ] ++;
					}
				}
			}
		}
	}
	
	// Merger
	bool merger = true;
	while( merger )
	{
		merger = false;
		for( unsigned i = 0; i < posX.size() -1; i++ )
		{
			if( posY[ i ] == posY[ i +1 ] )
			{
				if( posX[ i ] +(width *(counters[ i ] +1) ) == posX[ i +1 ] )
				{
					merger = true;
					counters[ i ] += counters[ i +1 ] +1;
					posX.erase( posX.begin() +i +1 );
					posY.erase( posY.begin() +i +1 );
					counters.erase( counters.begin() +i +1 );
				}
			}
		}
	}
	
	// Creator
	for( unsigned i = 0; i < posX.size(); i++ )
	{
		if( counters[ i ] >= 4 )
		{
			int myX = posX[ i ] +width;
			int myY = posY[ i ] -(width*2);
			
			// add ladder
			addPlank( 1, myX -w +10, posY[ i ] -h );
			
			while( counters[ i ] >= 4 )
			{
				int result = 0;
				while( result < 2 )
				{
					result = rand()%(counters[ i ]/2) +1;
				}
				
				//---------------------------
				addBlock( 5, myX, myY );
				result -= 1;
				myX += width;
				
				// 6
				for( int j = 0; j < result-1; j++ )
				{
					addBlock( 6, myX, myY );
					myX += width;
				}
				
				// 7
				addBlock( 7, myX, myY );
				myX += width*2;
				//---------------------------
				
				counters[ i ] -= ( result +3 );
			}
		}
	}
	
}



void Islands::moveX( sf::Uint8 direction, float vel )
{
	if( direction == 1 )
	{
		for( auto &it :hovers )
		{
			it->moveX( vel );
		}
		
		for( auto &it :blocks )
		{
			it->x += vel;
		}
	}
	else if( direction == 2 )
	{
		for( auto &it :hovers )
		{
			it->moveX( -vel );
		}
		
		for( auto &it :blocks )
		{
			it->x -= vel;
		}
	}
}

void Islands::backToGrass( int add )
{
	for( auto &it :hovers )
	{
		it->moveX( add );
	}
	
	for( auto &it :blocks )
	{
		it->x += add;
	}
}



vector <Block*> Islands::getBlocks()
{
	return blocks;
}

vector <Plank*> Islands::getPlanks()
{
	return planks;
}


bool Islands::checkCollision( Rect* rect )
{
	if( rect != NULL )
	{
		for( auto &it :hovers )
		{
			for( unsigned i = 0; i < it->getSize(); i++ )
			{
				if( it->getX(i) > -width*2 && it->getX(i) < screen_w +width )
				{
					sprites[ it->getNr(i) ]->setPosition( it->getX(i), it->getY(i) );
					if( sprites[ it->getNr(i) ]->checkCollision( rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight() ) )
					{
						return true;
					}
				}
			}
		}
		
		for( auto &i :blocks )
		{
			if( i->nr != -1 )
			{
				if( i->x > -width && i->x < screen_w )
				{
					sprites[ i->nr ]->setPosition( i->x, i->y );
					if( sprites[ i->nr ]->checkCollision( rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight() ) )
					{
						return true;
					}
				}
			}
		}
	}
	
	return false;
}

bool Islands::checkPixelCollision( Rect* rect )
{
	if( rect != NULL )
	{
		int l = rect->getX();		// left
		int r = rect->getRight();	// right
		int t = rect->getY();		// top
		int b = rect->getBot(); 	// bot
		
		for( auto &it :hovers )
		{
			for( unsigned i = 0; i < it->getSize(); i++ )
			{
				if( it->getX(i) > -width*2 && it->getX(i) < screen_w +width )
				{
					sprites[ it->getNr(i) ]->setPosition( it->getX(i), it->getY(i) );
					
					for( int j = l; j <= r; j++ )
					{
						if( sprites[ it->getNr(i) ]->checkPixelCollision( j, t ) )		return true;
						else if( sprites[ it->getNr(i) ]->checkPixelCollision( j, b ) )	return true;
					}
					
					for( int j = t; j <= b; j++ )
					{
						if( sprites[ it->getNr(i) ]->checkPixelCollision( l, j ) )		return true;
						else if( sprites[ it->getNr(i) ]->checkPixelCollision( r, j ) )	return true;
					}
				}
			}
		}
		
		for( unsigned i = 0; i < blocks.size(); i++ )
		{
			if( blocks[ i ]->nr != -1 )
			{
				if( blocks[ i ]->x > -width && blocks[ i ]->x < screen_w )
				{
					sprites[ blocks[ i ]->nr ]->setPosition( blocks[ i ]->x, blocks[ i ]->y );
				
					for( int j = l; j <= r; j++ )
					{
						if( sprites[ blocks[ i ]->nr ]->checkPixelCollision( j, t ) )		return true;
						else if( sprites[ blocks[ i ]->nr ]->checkPixelCollision( j, b ) )	return true;
					}
					
					for( int j = t; j <= b; j++ )
					{
						if( sprites[ blocks[ i ]->nr ]->checkPixelCollision( l, j ) )		return true;
						else if( sprites[ blocks[ i ]->nr ]->checkPixelCollision( r, j ) )	return true;
					}
				}
			}
		}
	}
	
	return false;
}