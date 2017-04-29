#include "brick.h"
#include "rules.h"
#include <cstdlib>
#include "file/file.h"

void Brick::reserve( unsigned size )
{
	// Reserve.
	blocks.reserve( size*(2) );
	this->size = blocks.capacity();
	// cout << "size (start): " << this->size << endl;
}

void Brick::shrink()
{
	// Shrink.
	blocks.shrink_to_fit();
	this->size = blocks.capacity();
	// cout << "size (end): " << this->size << endl;
}



Brick::Brick()
{
	width = 0;
	screen_w = 0;
	screen_h = 0;
	
	left = 0;
	right = 0;
	
	grass_distance = 0;
	grass_value = 0;
}

Brick::~Brick()
{
	free();
}

void Brick::free()
{
	width = 0;
	screen_w = 0;
	screen_h = 0;
	
	left = 0;
	right = 0;
	
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
	
	if( !blocks.empty() )
	{
		for( auto &it :blocks )
		{
			it->free();
		}
		
		blocks.clear();
	}
	
	grass_distance = 0;
	grass_value = 0;
}

int Brick::reset()
{
	grass_distance = 0;
	int distance = static_cast <int> (left);
	
	if( distance < 0 )
	{
		distance = -distance;
	}
	
	for( auto &it :blocks )
	{
		it->x += distance;
	}
	
	left += distance;
	right += distance;
	
	// printf( "%d\n", distance );
	
	return distance;
}



void Brick::load( int type, int width, int screen_w, int screen_h )
{
	free();
	
	// Load data.
	for( int i = 0; i < 16; i++ )
	{
		sprites.push_back( new MySprite() );
		sprites[ i ]->setName( "brick-sprites[" +con::itos( i ) +"]" );
		sprites[ i ]->load( "data/platform/world/" +con::itos( type ) +"/" +con::itos( i ) +".png" );
		sprites[ i ]->setScale( 0.9, 0.9 );
	}
	
	this->width = width;
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	grass_value = 2;
}

void Brick::draw( sf::RenderWindow* &window )
{
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



void Brick::fadein( int v, int max )
{
	for( auto &it :sprites )
	{
		it->fadein( v, max );
	}
}

void Brick::fadeout( int v, int min )
{
	for( auto &it :sprites )
	{
		it->fadeout( v, min );
	}
}



void Brick::addPlank( int n, int x, int y )
{
	planks.push_back( new Block() ); 	// add block.
	planks[ planks.size()-1 ]->nr = n; 	// set chosen.
	planks[ planks.size()-1 ]->x = x; 	// set x.
	planks[ planks.size()-1 ]->y = y; 	// set y.
}

void Brick::addBlock( int n, int x, int y )
{
	blocks.push_back( new Block() ); 	// add block.
	blocks[ blocks.size()-1 ]->nr = n; 	// set chosen.
	blocks[ blocks.size()-1 ]->x = x; 	// set x.
	blocks[ blocks.size()-1 ]->y = y; 	// set y.
}

sf::Uint8 Brick::getNewFloor( sf::Uint8 floor, int chance )
{
	sf::Uint8 min = 1;
	sf::Uint8 max = 4;
	
	// Draw lots for true / false to change floor.
	if( rand()%100 > chance )	// 50% is base
	{
		if( floor == min )
		{
			return min +1;
		}
		if( floor == min +1 )
		{
			if( rand()%2 == 1 )	return min;
			else				return min +2;
		}
		if( floor == max -1 )
		{
			if( rand()%2 == 1 )	return max;
			else				return max -2;
		}
		else if( floor == max )
		{
			return max -1;
		}
	}
	
	return floor;
}




void Brick::createTopBorders( int size, int chance, int w, int h )
{
	// printf( "%d\n", blocks.size() );
	// Set first and second block.
	blocks.push_back( new Block() );
	blocks[ blocks.size()-1 ]->nr = 4;
	blocks[ blocks.size()-1 ]->x = 0;
	blocks[ blocks.size()-1 ]->y = screen_h -width;
	
	blocks.push_back( new Block() );
	blocks[ blocks.size()-1 ]->nr = 1;
	blocks[ blocks.size()-1 ]->x = width;
	blocks[ blocks.size()-1 ]->y = screen_h -width;
	
	// Create rules.
	Rules* rules = new Rules;
	rules->rule();
	
	sf::Uint8 floor = 1;
	size -= 2;
	while( size-- )
	{
		// add block to the right
		int8_t lastNr = blocks[ blocks.size()-1 ]->nr;
		if( lastNr == -1 )
		{
			if( rand()%2 == 1 )
			{
				addBlock( -1, blocks[ blocks.size()-1 ]->x + width, screen_h -width*floor );
			}
			else
			{
				addBlock( -1, blocks[ blocks.size()-1 ]->x + width, screen_h -width*floor );
				addBlock( -1, blocks[ blocks.size()-1 ]->x + width, screen_h -width*floor );
			}
		}
		addBlock( rules->getBlock( lastNr ) , blocks[ blocks.size()-1 ]->x + width, screen_h -width*floor );
		
		sf::Uint8 new_floor = getNewFloor( floor, chance );
		if( new_floor > floor )
		{
			int need;
			if( rand()%2 == 1 )	need = -1;
			else				need = 14;
				
			while( true )
			{
				lastNr = blocks[ blocks.size()-1 ]->nr;
				if( lastNr == need )
				{
					break;
				}
				
				lastNr = blocks[ blocks.size()-1 ]->nr;
				addBlock( rules->fillForTop( lastNr, need ), blocks[ blocks.size()-1 ]->x + width, screen_h -width*floor );
				if( size > 0 )	size --;
			}
			
			
			floor = new_floor;
			lastNr = blocks[ blocks.size()-1 ]->nr;
			addBlock( rules->getTopBlockFor( lastNr ), blocks[ blocks.size()-1 ]->x, screen_h -width*floor );
				
			
			// add ladder
			addPlank( 0, blocks[ blocks.size()-1 ]->x -w +10, blocks[ blocks.size()-1 ]->y +width -h );
		}
		else if( new_floor < floor )
		{
			int need;
			if( rand()%2 == 1 )	need = 2;
			else				need = 7;
			
			while( true )
			{
				lastNr = blocks[ blocks.size()-1 ]->nr;
				addBlock( rules->fillForBot( lastNr ), blocks[ blocks.size()-1 ]->x + width, screen_h -width*floor );
				if( size > 0 )	size --;
				
				lastNr = blocks[ blocks.size()-1 ]->nr;
				if( lastNr == need )
				{
					break;
				}
			}
			
			floor = new_floor;
			lastNr = blocks[ blocks.size()-1 ]->nr;
			addBlock( rules->getBotBlockFor( lastNr ), blocks[ blocks.size()-1 ]->x, screen_h -width*floor );
			
			// add block to the right
			int8_t lastNr = blocks[ blocks.size()-1 ]->nr;
			addBlock( rules->getBlock( lastNr ) , blocks[ blocks.size()-1 ]->x +width, screen_h -width*floor );
			if( size > 0 )	size --;
			
			// add ladder
			addPlank( 0, blocks[ blocks.size()-1 ]->x -10, blocks[ blocks.size()-1 ]->y -h );
		}
	}

	
	delete rules;
}

void Brick::createLeftBorders()
{
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		if( blocks[ i ]->y < screen_h -width && ( blocks[ i ]->nr == 10 || blocks[ i ]->nr == 0 ) )
		{
			// we check if we have free place
			bool free_place = true;
			for( auto &j :blocks )
			{
				if( blocks[ i ]->y +width == j->y && blocks[ i ]->x == j->x )
				{
					free_place = false;
				}
			}
			
			if( free_place )
			{
				if( blocks[ i ]->nr == 0 )
				{
					// we are looking for block nr 13
					
					bool put = false;
					int x = blocks[ i ]->x +width;
					
					for( unsigned j = i +1; j < blocks.size(); j++ )
					{
						bool success = false;
						
						while( !success )
						{
							for( auto &k :blocks )
							{
								if( x == k->x && blocks[ i ]->y +width == k->y )
								{
									success = true;
								}
							}
							
							if( !success )
							{
								// new x
								x += width;
							}
							
							int further = 0;
							for( auto &k :blocks)
							{
								if( k->x > further )
								{
									further = k->x;
								}
							}
							
							if( x > further )
							{
								break;
							}
						}
						
						if( x == blocks[ j ]->x && blocks[ i ]->y +width == blocks[ j ]->y )
						{
							if( blocks[ j ]->nr == 13 )
							{
								put = true;
								// printf( "%d %d\n", x, blocks[ i ]->y +width );
							}
							
							break;
						}
					}
					
					if( rand()%2 == 1 || put )
					{
						addBlock( 10, blocks[ i ]->x, blocks[ i ]->y +width );
					}
					else
					{
						addBlock( 8, blocks[ i ]->x, blocks[ i ]->y +width );
					}
				}
				else if( blocks[ i ]->nr == 10 )
				{
					addBlock( 10, blocks[ i ]->x, blocks[ i ]->y +width );
				}
			}
		}
	}
}

void Brick::createRightBorders()
{
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		if( blocks[ i ]->y < screen_h -width && ( blocks[ i ]->nr == 12 || blocks[ i ]->nr == 2 ) )
		{
			// we check if we have free place
			bool free_place = true;
			for( auto &j :blocks )
			{
				if( blocks[ i ]->y +width == j->y && blocks[ i ]->x == j->x )
				{
					free_place = false;
				}
			}
			
			if( free_place )
			{
				// we have to check what kind of block is on the left 'further'
				int type = -1;
				int distance = -1;
				
				for( auto &j :blocks )
				{
					if( j->y == blocks[ i ]->y +width && blocks[ i ]->x -j->x > 0 )
					{
						if( j->nr == 8 || j->nr == 10 ||
							j->nr == 0 || j->nr == 14 )
						{
							if( distance >= blocks[ i ]->x - j->x || distance == -1 )
							{
								distance = blocks[ i ]->x - j->x;

								// we found block
								type = j->nr;
							}
						}
					}
				}
				
				// printf( "type = %d\n", type );
				
				if( type == 8 )			type = 9;
				else 					type = 12;
				
				addBlock( type, blocks[ i ]->x, blocks[ i ]->y +width );
			}
		}
	}
}

void Brick::createStuffing( int a, int n )
{
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		if( blocks[ i ]->nr == a || blocks[ i ]->nr == n )
		{
			// we check if we have free place
			bool free_place = true;
			for( auto &j :blocks )
			{
				if( static_cast <int> (blocks[ i ]->y) == static_cast <int> (j->y) &&
					static_cast <int> (blocks[ i ]->x) +width == static_cast <int> (j->x)  )
				{
					free_place = false;
					break;
				}
			}
			
			if( free_place && static_cast <int> (blocks[ i ]->x) + width <= right )
			{
				addBlock( n, static_cast <int> (blocks[ i ]->x) + width, static_cast <int> (blocks[ i ]->y) );
			}
		}
	}
	
	// printf( "happen\n" );
}

void Brick::setLeft()
{
	// Searching for left
	for( auto &i :blocks )
	{
		if( i->x < left )
		{
			left = i->x;
		}
	}
}

void Brick::setRight()
{
	// Searching right
	for( auto &i :blocks )
	{
		if( i->x > right )
		{
			right = i->x;
		}
	}
}




sf::Uint8 Brick::moveX( sf::Uint8 direction, float vel )
{
	// printf( "%f\n", vel );
	if( direction == 1 )
	{
		if( left > -10 )
		{
			return 1;
		}
		
		for( auto &i :blocks )
		{
			i->x += vel;
		}
		
		left += vel;
		right += vel;
	}
	else if( direction == 2 )
	{
		if( right < screen_w -width +10 )
		{
			return 2;
		}
		
		for( auto &i :blocks )
		{
			i->x -= vel;
		}
		
		left -= vel;
		right -= vel;
	}
	
	return 0;
}


int Brick::getNearGrassY( int hero_x )
{
	bool flag = false;
	for( unsigned i = blocks.size()-1; i >= 0; i-- )
	{
		if( blocks[ i ]->nr >= 0 && blocks[ i ]->nr <= 7 )
		{
			if( blocks[ i ]->x < hero_x )
			{
				if( flag )
				{
					grass_distance = hero_x -blocks[ i ]->x;
					// printf( "%d\n", grass_distance );
					return blocks[ i ]->y;
				}
				flag = true;
			}
		}
	}
	
	return 0;
}

int Brick::getGrassDistance()
{
	if( grass_distance > 0 )
	{
		grass_distance -= grass_value;
		if( grass_distance < 0 )
			grass_distance = 0;
	}
	
	return grass_distance;
}

sf::Uint8 Brick::getGrassValue()
{
	return grass_value;
}

void Brick::undoFall()
{
	for( auto &i :blocks )
	{
		i->x += grass_value;
	}
	
	left += grass_value;
	right += grass_value;
}

void Brick::setColor( sf::Color color )
{
	for( auto &i :sprites )
	{
		i->setColor( color );
	}
}


sf::Uint8 Brick::getWidth()
{
	return width;
}

vector <Block*> Brick::getBlocks()
{
	return blocks;
}

vector <Block*> Brick::getPlanks()
{
	return planks;
}

float Brick::getLeft()
{
	return left;
}

float Brick::getRight()
{
	return right;
}

Rect* Brick::getLastBlock()
{
	float x = 0;
	float y = 0;
	int min = 0;
	int max = 7;
	
	Rect* r = new Rect;
	
	for( auto &it :blocks )
	{
		if( it->nr >= min && it->nr <= max )
		{
			if( x < it->x )
			{
				// printf( "%f\n", it->x );
				x = it->x;
				y = it->y;
			}
		}
	}
	
	// printf( "right %f, last %f\n", getRight(), x );
	
	r->set( static_cast <int> (x), static_cast <int> (y), width, width );
	return r;
}




bool Brick::checkCollision( Rect* rect )
{
	if( rect != NULL )
	{
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

bool Brick::checkPixelCollision( Rect* rect )
{
	if( rect != NULL )
	{
		int l = rect->getX();		// left
		int r = rect->getRight();	// right
		int t = rect->getY();		// top
		int b = rect->getBot(); 	// bot
		
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