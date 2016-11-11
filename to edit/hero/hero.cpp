#include "hero/hero.h"
#include <fstream>

int Hero::strToInt( string s )
{
    bool m=false;
    int tmp=0;
    int i=0;
	
    if(s[0]=='-')
    {
          i++;
          m = true;
    }
	
    while(i<s.size())
    {
      tmp = 10*tmp+s[i]-48;
      i++;
    }
	
    return m ? -tmp : tmp;   
}

Hero::Hero()
{
	which = 0;
	offset = 0;
	delay = 0;
	
	nr = 0;
	sprite = NULL;
	
	int &wr = const_cast <int&> ( off_const ); 
	wr = 10;
	
	vel = 0;
	right = true;
}

Hero::~Hero()
{
	free();
}

void Hero::free()
{
	which = 0;
	offset = 0;
	delay = 0;
	
	if( sprite != NULL )
	{
		for( int i = 0; i < nr; i ++ )
		{
			sprite[ i ].free();
		}
		
		delete [] sprite;
		sprite = NULL;
		nr = 0;
	}

	for( unsigned i = 0; i < keys.size(); i++ )
	{
		if( keys[ i ] != NULL )
		{
			delete [] keys[ i ];
			keys[ i ] = NULL;
		}
	}
	keys.clear();
	
	vel = 0;
	right = true;
}

	
void Hero::load( int& screen_w, int& y, string path )
{
	free();
	//printf( "--%d--\n", off_const );
	delay = 6;
	
	nr = DEAD +1;
	sprite = new MySprite [ nr ];
	
	// set name, load, set scale, set start position
	for( int i = 0; i < nr; i++ )
	{
		sprite[ i ].setName( "hero-sprite nr " + to_string( i ) );
		sprite[ i ].load( path + to_string( i ) + ".png", off_const );
		sprite[ i ].setScale( 0.25, 0.25 );
		sprite[ i ].setPosition( 10, y -sprite[ i ].getHeight() -124 );
	}
	
	fstream file;
	
	file.open( "data/txt/menu/keyboard_temporary.txt" );
	if( file.bad() )
	{
		printf( "Cannot open file! (hero)\n" );
	}
	else
	{
		string line;
		
		for( int i = 0; i < 11; i ++ ) // 11 types of action
		{
			int* arrow;
			keys.push_back( arrow );
			keys[ i ] = new int[ 2 ];
			
			file >> line;
			keys[ i ][ 0 ] = strToInt( line );
			// printf( "%d\n", key[ 0 ] );
			
			file >> line;
			keys[ i ][ 1 ] = strToInt( line );
			// printf( "%d\n", key[ 1 ] );
		}
	}
	
	file.close();
	
	vel = 1;
}

void Hero::draw( sf::RenderWindow* &window )
{
	window->draw( sprite[ which ].get() );
	sprite[ which ].setOffset( offset /delay );
	
	offset ++;
	if( offset == off_const *delay )
		offset = 0;
		
	which = IDLE;
}

void Hero::handle( sf::Event &event )
{
	
}




void Hero::fadein( int v, int max )
{
	for( int i = 0; i < nr; i++ )
	{
		sprite[ i ].fadein( v, max );
	}
}

void Hero::fadeout( int v, int min )
{
	for( int i = 0; i < nr; i++ )
	{
		sprite[ i ].fadeout( v, min );
	}
}

void Hero::moveLeft()
{
	if( keys[ 0 ][ 1 ] == -1 )
	{
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( keys[ 0 ][ 0 ] ) ) )
		{
			which = RUN;
			
			for( int i = 0; i < nr; i++ )
			{
				sprite[ i ].setScale( -0.25, 0.25 );
				sprite[ i ].setPosition( sprite[ i ].getX() -vel, sprite[ i ].getY() );
			}

			if( right )
			{
				//printf( "%d\n", sprite[ 1 ].getX() );
				//printf( "%d\n", sprite[ 1 ].getWidth() );
				for( int i = 0; i < nr; i++ )
				{
					sprite[ i ].setPosition( sprite[ i ].getX() + (sprite[ i ].getWidth()*-1), sprite[ i ].getY() );
				}
				right = false;
				//printf( "%d\n", sprite[ 1 ].getX() );
			}
		}
	}
	else
	{
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( keys[ 0 ][ 0 ] ) ) )
		{
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( keys[ 0 ][ 1 ] ) ) )
			{
				which = RUN;
				
				for( int i = 0; i < nr; i++ )
				{
					sprite[ i ].setScale( -0.25, 0.25 );
					sprite[ i ].setPosition( sprite[ i ].getX() -vel, sprite[ i ].getY() );
				}
				
				if( right )
				{
					for( int i = 0; i < nr; i++ )
					{
						sprite[ i ].setPosition( sprite[ i ].getRight() + (sprite[ i ].getWidth()*-1), sprite[ i ].getY() );
					}
					right = false;
				}
			}
		}
	}
}

void Hero::moveRight()
{
	if( keys[ 1 ][ 1 ] == -1 )
	{
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( keys[ 1 ][ 0 ] ) ) )
		{
			which = RUN;
			
			for( int i = 0; i < nr; i++ )
			{
				sprite[ i ].setScale( 0.25, 0.25 );
				sprite[ i ].setPosition( sprite[ i ].getX() +vel, sprite[ i ].getY() );
			}
			
			if( !right )
			{
				for( int i = 0; i < nr; i++ )
				{
					sprite[ i ].setPosition( sprite[ i ].getX() - sprite[ i ].getWidth(), sprite[ i ].getY() );
				}
				right = true;
			}
		}
	}
	else
	{
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( keys[ 1 ][ 0 ] ) ) )
		{
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( keys[ 1 ][ 1 ] ) ) )
			{
				which = RUN;
				
				for( int i = 0; i < nr; i++ )
				{
					sprite[ i ].setScale( 0.25, 0.25 );
					sprite[ i ].setPosition( sprite[ i ].getX() +vel, sprite[ i ].getY() );
				}
				
				if( !right )
				{
					for( int i = 0; i < nr; i++ )
					{
						sprite[ i ].setPosition( sprite[ i ].getX() - sprite[ i ].getWidth(), sprite[ i ].getY() );
					}
					right = true;
				}
			}
		}
	}
}

void Hero::jump()
{
	
}
