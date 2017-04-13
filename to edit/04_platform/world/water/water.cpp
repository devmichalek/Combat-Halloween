#include "water.h"
#include "file/file.h"

Water::Water()
{
	min = 0;
	width = 0;
	screen_w = 0;
	screen_h = 0;
}

Water::~Water()
{
	free();
}

void Water::free()
{
	min = 0;
	width = 0;
	screen_w = 0;
	screen_h = 0;
	
	if( !waterblocks.empty() )
	{
		for( auto &it :waterblocks )
		{
			it->free();
		}
		
		waterblocks.clear();
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

void Water::reset( int distance )
{
	for( auto &it :waterblocks )
	{
		it->x += distance;
	}
}



void Water::load( int type, int width, int screen_w, int screen_h )
{
	free();
	
	min = 16;
	this->width = width;
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	for( unsigned i = 0; i < 2; i++ )
	{
		sprites.push_back( new MySprite() );
		sprites[ i ]->setName( "water-sprites[" +con::itos( i ) +"]" );
		sprites[ i ]->load( "data/04_platform/world/" +con::itos( type ) +"/" +con::itos( i +min ) +".png" );
	}
}

void Water::draw( sf::RenderWindow* &window )
{
	for( auto &it :waterblocks )
	{
		if( it->x > -width && it->x < screen_w +width )
		{
			sprites[ it->nr ]->setPosition( it->x, it->y );
			window->draw( sprites[ it->nr ]->get() );
		}
	}
}

void Water::fadein( int v, int max )
{
	for( auto &it :sprites )
	{
		it->fadein( v, max );
	}
}

void Water::fadeout( int v, int min )
{
	for( auto &it :sprites )
	{
		it->fadeout( v, min );
	}
}



void Water::addBlock( int n, int x, int y )
{
	waterblocks.push_back( new Block() ); 	// add block.
	waterblocks[ waterblocks.size()-1 ]->nr = n; 	// set chosen.
	waterblocks[ waterblocks.size()-1 ]->x = x; 	// set x.
	waterblocks[ waterblocks.size()-1 ]->y = y; 	// set y.
}



void Water::moveX( sf::Uint8 direction, float vel )
{
	if( direction == 1 )
	{
		for( auto &it :waterblocks )
		{
			it->x += vel;
		}
	}
	else if( direction == 2 )
	{
		for( auto &it :waterblocks )
		{
			it->x -= vel;
		}
	}
}

void Water::undoFall( sf::Uint8 add )
{
	for( auto &it :waterblocks )
	{
		it->x += add;
	}
}

void Water::setColor( sf::Color color )
{
	for( auto &i :sprites )
	{
		i->setColor( color );
	}
}



void Water::createWater( vector <Block*> b1, vector <Block*> b2, float right )
{
	vector <Block*> blocks = b1;
	for( unsigned i = 0; i < b2.size(); i++ )
	{
		blocks.push_back( new Block() );
		blocks[ blocks.size()-1 ]->x = b2[ i ]->x;
		blocks[ blocks.size()-1 ]->y = b2[ i ]->y;
		blocks[ blocks.size()-1 ]->nr = b2[ i ]->nr;
	}
	
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		if( blocks[ i ]->y == screen_h -width )
		{
			if( blocks[ i ]->nr == 2 || blocks[ i ]->nr == 12 )
			{
				int good_nr = -1;
				
				if( static_cast <int> (blocks[ i ]->x) %width == 0 )
				{
					for( int k = blocks[ i ]->x +width; k < right; k += width )
					{
						// check block on the right
						for( unsigned j = 0; j < blocks.size(); j++ )
						{
							if( blocks[ j ]->x == k && blocks[ j ]->y == blocks[ i ]->y )
							{
								if( blocks[ j ]->nr == 10 || blocks[ j ]->nr == 0 )
								{
									good_nr = j;
									k = right;
									break;
								}
							}
						}
					}
				}
				

				if( good_nr != -1 )
				{
					// 16
					for( int j = blocks[ i ]->x; j <= blocks[ good_nr ]->x; j += width )
					{
						addBlock( 0, j, blocks[ i ]->y );
					}
				}
			}
		}
		
	}
	
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		if( (blocks[ i ]->nr == 2 || blocks[ i ]->nr == 12) && static_cast <int> (blocks[ i ]->x) %width == 0 ) // right border
		{
			bool success = false;
			
			// what kind of block is at the bottom
			for( unsigned j = 0; j < blocks.size(); j++ )
			{
				if( blocks[ j ]->x == blocks[ i ]->x )
				{
					if( blocks[ j ]->y == screen_h -width )
					{
						// printf( "1. %d\n", blocks[ i ]->x );
						success = true;
						break;
					}
				}
			}
			
			if( success )
			{
				int good_nr = -1;
				
				// what kind of block is on the right
				int right = blocks.size()*width;
				
				for( int k = blocks[ i ]->x +width; k <= right; k += width )
				{
					for( unsigned j = i+1; j < blocks.size(); j++ )
					{
						if( blocks[ j ]->nr < 8 ) // grass blocks
						{
							if( blocks[ j ]->x == k )
							{
								if( blocks[ j ]->y == blocks[ i ]->y )
								{
									if( blocks[ j ]->nr == 0 || blocks[ j ]->nr == 10 )
									{
										good_nr = j;
										// printf( "2. %d\n", blocks[ j ]->x );
										k = right +width;
										break;
									}
								}
							}
						}
					}
				}
				
				// printf( "%d\n", good_nr );
				if( good_nr != -1 )
				{
					bool ready = false;
					// what kind of block is at the bottom again
					for( unsigned j = 0; j < blocks.size(); j++ )
					{
						if( blocks[ j ]->x == blocks[ good_nr ]->x )
						{
							// printf( "--0. pass\n" );
							if( blocks[ j ]->y == screen_h -width )
							{
								// printf( "--1. pass\n" );
								ready = true;
							}
						}
					}
					
					if( ready )
					{
						// check that there is no bottom islands
						for( unsigned j = 0; j < blocks.size(); j++ )
						{
							if( blocks[ j ]->y > blocks[ i ]->y )
							{
								if( blocks[ j ]->x > blocks[ i ]->x && blocks[ j ]->x < blocks[ good_nr ]->x )
								{
									if( blocks[ j ]->nr >= 0 && blocks[ j ]->nr <= 7 )
									{
										// printf( "WARNING %d\n", blocks[ j ]->x );
										ready = false;
										break;
									}
								}
							}
						}
							
					}
					
					if( ready )
					{
						// printf( "im ready  %d %d\n",  blocks[ i ]->x, blocks[ good_nr ]->x );
						
						// 16
						for( int j = blocks[ i ]->x; j <= blocks[ good_nr ]->x; j += width )
						{
							addBlock( 0, j, blocks[ i ]->y );
						}
						
						// 17
						for( int k = blocks[ i ]->y +width; k <= screen_h -width; k += width )
						{
							for( int j = blocks[ i ]->x; j <= blocks[ good_nr ]->x; j += width )
							{
								addBlock( 1, j, k );
							}
						}
					}
				}
			}
		}
		
	}

	
	// delete if we have surplus
	
	bool end = false;
	while( !end )
	{
		end = true;
		
		for( unsigned i = 0; i < waterblocks.size(); i++ )
		{
			for( unsigned j = 0; j < waterblocks.size(); j++ )
			{
				if( waterblocks[ i ]->x == waterblocks[ j ]->x &&
					waterblocks[ i ]->y == waterblocks[ j ]->y && j != i  )
				{
					if( waterblocks[ i ]->nr == 0 )
					{
						waterblocks.erase( waterblocks.begin() +i );
					}
					else if( waterblocks[ j ]->nr == 0 )
					{
						waterblocks.erase( waterblocks.begin() +j );
					}
					else
					{
						waterblocks.erase( waterblocks.begin() +j );
					}
					
					//printf( "happen\n" );
					
					end = false;
				}
			}
		}
	}
	
	// set right.
	float r = 0;
	for( auto &i :waterblocks )
	{
		if( i->x > r )
		{
			r = i->x;
		}
	}
	
	r += width;
	
	// printf( "%f %f\n", r, right );
	
	for( int i = static_cast <int> (r); i <= static_cast <int> (right); i += width )
	{
		addBlock( 0, i, screen_h -width );
	}
}



bool Water::checkCollision( Rect* rect )
{
	if( rect != NULL )
	{
		for( unsigned i = 0; i < waterblocks.size(); i++ )
		{
			if( waterblocks[ i ]->x > -width && waterblocks[ i ]->x < screen_w +width )
			{
				sprites[ waterblocks[ i ]->nr ]->setPosition( waterblocks[ i ]->x, waterblocks[ i ]->y );
				if( sprites[ waterblocks[ i ]->nr ]->checkCollision( rect->getX(), rect->getY() -50, rect->getWidth(), rect->getHeight() ) )
				{
					return true;
				}
			}
		}
	}
	
	return false;
}
