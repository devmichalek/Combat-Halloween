#include "water.h"

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
	while( true )
	{
		if( distance > 0 )
		{
			for( auto &it :waterblocks )
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
		sprites[ i ]->setName( "water-sprites[" +to_string( i ) +"]" );
		sprites[ i ]->load( "data/sprites/play/" +to_string( type ) +"/" +to_string( i +min ) +".png" );
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

void Water::backToGrass( int add )
{
	for( auto &it :waterblocks )
	{
		it->x += add;
	}
}



void Water::createWater( vector <Block*> blocks_1, vector <Block*> blocks_2, int right )
{
	vector <Block*> blocks = blocks_1;
	for( unsigned i = 0; i < blocks_2.size(); i++ )
	{
		blocks.push_back( new Block() );
		blocks[ blocks.size()-1 ]->x = blocks_2[ i ]->x;
		blocks[ blocks.size()-1 ]->y = blocks_2[ i ]->y;
		blocks[ blocks.size()-1 ]->nr = blocks_2[ i ]->nr;
	}
	
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		if( blocks[ i ]->nr == 2 ) // right border
		{
			bool success = false;
			
			// what kind of block is at the bottom
			for( unsigned j = 0; j < blocks.size(); j++ )
			{
				if( blocks[ j ]->x == blocks[ i ]->x )
				{
					if( blocks[ j ]->y == screen_h -width )
					{
						if( blocks[ j ]->nr == 12 )
						{
							// printf( "%d\n", blocks[ i ]->x );
							success = true;
						}
					}
				}
			}
			
			if( success )
			{
				int myX = blocks[ i ]->x +width;
				int good_nr = -1;
				
				// what kind of block is on the right
				for( unsigned j = i+1; j < blocks.size(); j++ )
				{
					if( blocks[ j ]->nr < 8 ) // grass blocks
					{
						if( blocks[ j ]->x == myX )
						{
							if( blocks[ j ]->y == blocks[ i ]->y )
							{
								myX += width;
								
								if( blocks[ j ]->nr == 0 )
								{
									good_nr = j;
									// printf( "%d\n", blocks[ j ]->x );
								}
							}
							else
							{
								break;
							}
						}
					}
				}
				
				if( good_nr != -1 )
				{
					bool ready = false;
					
					// what kind of block is at the bottom again
					for( unsigned j = 0; j < blocks.size(); j++ )
					{
						if( blocks[ j ]->x == blocks[ good_nr ]->x )
						{
							if( blocks[ j ]->y == screen_h -width )
							{
								if( blocks[ j ]->nr == 10 )
								{
									ready = true;
								}
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
		
		if( blocks[ i ]->y == screen_h -width )
		{
			if( blocks[ i ]->nr == 2 || blocks[ i ]->nr == 12 )
			{
				int good_nr = -1;
				
				if( blocks[ i ]->x %width == 0 )
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
