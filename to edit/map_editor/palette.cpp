#include "map_editor/palette.h"


Palette::Palette()
{
	nr = 0;
	block = NULL;
	
	text_nr = 0;
	text = NULL;
	
	which = x = y = -1;
	
	path = data = "";
	
	width = screen_w = screen_h = 0;
	
	chosen = cut = back = fix =save = false;
	
	disX = disY = 0;
}

Palette::~Palette()
{
	free();
}

void Palette::free()
{
	if( block != NULL )
	{
		for( int i = 0; i < nr; i++ )
		{
			block[ i ].free();
		}
		
		delete [] block;
		block = NULL;
		
		nr = 0;
	}
	
	if( text != NULL )
	{
		for( int i = 0; i < text_nr; i++ )
		{
			text[ i ].free();
		}
		
		delete [] text;
		text = NULL;
		
		text_nr = 0;
	}
	
	which = x = y = -1;
	
	path = data = "";
	
	width = screen_w = screen_h = 0;
	
	chosen = cut = back = fix =save = false;
	
	disX = disY = 0;

	v.clear();
	v_t.clear();
}



void Palette::load( int screen_w, int screen_h, int number )
{
	free();
	
	path = "data/txt/map/" + to_string( number ) + "/";
	width = 128;
	this->screen_w = screen_w;
	this->screen_h = screen_h;


	// load blocks
	if( number == 0 )		nr = 30;
	else if( number == 1 )	nr = 31;
	else if( number == 2 )	nr = 28;
	else					nr = 30;
	block = new MySprite[ nr ];
	for( int i = 0; i < nr; i++ )
	{
		block[ i ].setName( "palette-block[" +to_string( i ) +"]" );
		block[ i ].load( "data/sprites/play/" +to_string( number ) +"/" +to_string( i ) +".png" );
		block[ i ].setAlpha( 0x66 );
		block[ i ].setScale( 0.6, 0.6 );
	}
	// set postion of blocks
	block[ 0 ].setPosition( 0, 0 );
	for( int i = 5; i < nr; i += 5 )
		block[ i ].setPosition( block[ i -5 ].getRight() +20, block[ 0 ].getY() );
	for( int j = 1; j < nr; j += 5 )
	{
		for( int i = j; i < j + 4; i++ )
		{
			if( i == nr  )	break;
			block[ i ].setPosition( block[ j -1 ].getX(), block[ i -1 ].getBot() +5 );
		}
	}
	
	
	
	
	// Text
	text_nr = 6;
	text = new MyText [ text_nr ];
	for( int i = 0; i < text_nr; i++ )
	{
		text[ i ].setID( "palette-text[" + to_string( i ) + "]" );
		text[ i ].setFont( "data/fonts/Jaapokki-Regular.otf", 20, 255, 255, 255 );
	}
	
	text[ 0 ].setText( "save[LShift]" );
	text[ 1 ].setText( "chosen[z]" );
	text[ 2 ].setText( "cut[x]" );
	text[ 3 ].setText( "move[w,s,a,d]" );
	text[ 4 ].setText( "fix[f]" );
	text[ 5 ].setText( "menu[Esc]" );
	
	// set position, set alpha
	text[ 0 ].setPosition( 20, screen_h - 30 );
	text[ 0 ].setAlpha( 0xFF );
	for( int i = 1; i < text_nr; i++ )
	{
		text[ i ].setPosition( text[ i-1 ].getRight() +20, text[ i-1 ].getY() );
		text[ i ].setAlpha( 0xFF );
	}
}



void Palette::draw( sf::RenderWindow* &window )
{
	// Draw blocks
	for( int i = 0; i < nr; i ++ )
	{
		window->draw( block[ i ].get() );
	}
		
	
	// Draw text
	for( int i = 0; i < text_nr; i ++ )
	{
		window->draw( text[ i ].get() );
	}
	
	
	// Draw vector of sprites
	for( unsigned i = 0; i < v.size(); i++ )
	{
		window->draw( v[ i ]->get() );
	}
		
	
	// Draw chosen block
	if( chosen )
	{
		int a = block[ which ].getX();
		int b = block[ which ].getY();
		
		block[ which ].setAlpha( 0xFF );
		block[ which ].setScale( 1, 1 );
		block[ which ].center( x +disX, y +disY, 0, 0 );
		
		window->draw( block[ which ].get() );
		
		block[ which ].setAlpha( 0x66 );
		block[ which ].setScale( 0.6, 0.6 );
		block[ which ].setPosition( a, b );

		// left
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( 0 ) ) )
		{
			disX --;
			text[ 3 ].setColor( 0x33, 0x66, 0x99 );
		}
			
		// right
		else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( 3 ) ) )
		{
			disX ++;
			text[ 3 ].setColor( 0x33, 0x66, 0x99 );
		}
		
		// up
		else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( 22 ) ) )
		{
			disY --;
			text[ 3 ].setColor( 0x33, 0x66, 0x99 );
		}
		
		// down
		else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( 18 ) ) )
		{
			disY ++;
			text[ 3 ].setColor( 0x33, 0x66, 0x99 );
		}
	}
}



void Palette::handle( sf::Event &event )
{
	for( int i = 0; i < nr; i ++ )
	{
		block[ i ].setAlpha( 0x66 );
	}
	
	for( int i = 0; i < text_nr; i ++ )
	{
		text[ i ].setColor( 0xFF, 0xFF, 0xFF );
	}
	
	for( unsigned i = 0; i < v.size(); i ++ )
	{
		v[ i ]->setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
	}
	
	
	if( event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseButtonReleased )
	{
		if( event.type == sf::Event::MouseMoved )
		{
			x = event.mouseMove.x;
			y = event.mouseMove.y;
		}
		
		
		if( !chosen && !cut && !save )
		{
			for( int i = 0; i < nr; i ++ )
			{
				if( block[ i ].checkCollision( x, y ) )
				{
					block[ i ].setAlpha( 0xFF );
					break;
				}
			}
		}
		
		
		if( cut && !save )
		{
			for( unsigned i = 0; i < v.size(); i ++ )
			{
				if( v[ i ]->checkCollision( x, y ) )
				{
					v[ i ]->setColor( sf::Color( 0xCC, 0x00, 0x00 ) );
					break;
				}
			}
		}
	}
	else if( event.type == sf::Event::MouseButtonPressed )
	{
		x = event.mouseButton.x;
		y = event.mouseButton.y;
		
		bool flag = false;
		
		if( x > screen_w -width*2 && x <= screen_w -width && chosen )
		{
			for( int i = screen_h-width; i > 0; i -= width )
			{
				if( y > i && y < i+width )
				{
					v.push_back( new MySprite() );
					*v[ v.size()-1 ] = block[ which ];
					v[ v.size()-1 ]->setScale( 1, 1 );
					v[ v.size()-1 ]->setAlpha( 0xFF );
					
					if( fix )
						v[ v.size()-1 ]->setPosition( screen_w -width*2, i );
					else
						v[ v.size()-1 ]->setPosition( x +disX -v[ v.size()-1 ]->getWidth()/2, y +disY -v[ v.size()-1 ]->getHeight()/2 );
					
					v_t.push_back( which );
					
					flag = true;
					
					break;
				}
			}
		}
		
		if( !chosen && !cut && !save )
		{
			for( int i = 0; i < nr; i ++ )
			{
				if( block[ i ].checkCollision( x, y ) )
				{
					which = i;
					chosen = true;
					disX = disY = 0;
					block[ i ].setAlpha( 0xFF );
					break;
				}
			}
		}
		
		if( cut && !save )
		{
			for( unsigned i = 0; i < v.size(); i ++ )
			{
				if( v[ i ]->checkCollision( x, y ) )
				{
					v[ i ]->setColor( sf::Color( 0xCC, 0x00, 0x00 ) );
					v.erase( v.begin() + i );
					v_t.erase( v_t.begin() + i );
					flag = true;
					break;
				}
			}
		}
		
		if( flag )
		{
			data = "";
			for( unsigned i = 0; i < v.size(); i ++ )
			{
				data += to_string( v_t[ i ] );
				data += to_string( v[ i ]->getX() ) + " ";
				data += to_string( v[ i ]->getY() ) +"/n";
			}
		}
	}
	
	
	
	
	if( event.type == sf::Event::KeyPressed )
	{
		// Back to menu
		if( event.key.code == sf::Keyboard::Escape )
		{
			back = true;
		}
			
		
		// Turn off - chosen
		if( event.key.code == sf::Keyboard::Z && !cut && !save )
		{
			which = -1;
			fix = false;
			chosen = false;
		}
		
		
		// Turn off/on - cut
		if( event.key.code == sf::Keyboard::X && !save )
		{
			cut = !cut;
			which = -1;
			fix = false;
			chosen = false;
		}
		
		// Turn off/on - save
		if( event.key.code == sf::Keyboard::LShift )
		{
			save = !save;
			cut = false;
			which = -1;
			fix = false;
			chosen = false;
		}
		
		// Turn off/on - fix
		if( event.key.code == sf::Keyboard::F && chosen )
		{
			fix = !fix;
		}
			
	}
	
	if( save )		text[ 0 ].setColor( 0x99, 0x00, 0x66 );
	if( chosen )	text[ 1 ].setColor( 0x41, 0x92, 0x4B );
	if( cut )		text[ 2 ].setColor( 0xCC, 0x00, 0x00 );
	if( fix )		text[ 4 ].setColor( 0x41, 0x92, 0x4B );
}




int Palette::getDisX()
{
	return disX;
}

int Palette::getDisY()
{
	return disY;
}



bool Palette::backToMenu()
{
	return back;
}

bool Palette::saveModeIsOn()
{
	return save;
}

bool Palette::isChosen()
{
	return chosen;
}



string Palette::getPath()
{
	return path;
}

string Palette::getData()
{
	return data;
}