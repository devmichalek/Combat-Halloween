#include "map_editor/palette.h"

Palette::Palette()
{
	folder_name = "";
	width = 0;
	
	nr = 0;
	block = NULL;
	
	which = -1;
	x = -1;
	y = -1;
	
	text_nr = 0;
	text = NULL;
	
	deleteOn = false;
	chosenOn = false;
	saveOn = false;
	back = false;
	
	disX = disY = 0;
}

Palette::~Palette()
{
	free();
}

void Palette::free()
{
	folder_name = "";
	width = 0;
	
	if( block != NULL )
	{
		delete [] block;
		block = NULL;
		nr = 0;
	}
	
	which = -1;
	x = -1;
	y = -1;
	
	if( text != NULL )
	{
		delete [] text;
		text = NULL;
		text_nr = 0;
	}
	
	deleteOn = false;
	chosenOn = false;
	saveOn = false;
	back = false;
	
	disX = disY = 0;
}


void Palette::load( int screen_w, int screen_h, int num )
{
	free();
	
	folder_name = "data/txt/map/" + to_string( num ) + "/";
	width = 128;
	



	// load blocks
	if( num == 0 )		nr = 30;
	else if( num == 1 )	nr = 31;
	else if( num == 2 )	nr = 28;
	else				nr = 30;
	block = new MySprite[ nr ];
	for( int i = 0; i < nr; i++ )
	{
		block[ i ].setName( "palette-block[" +to_string( i ) +"]" );
		block[ i ].load( "data/sprites/play/" +to_string( num ) +"/" +to_string( i ) +".png" );
		block[ i ].setAlpha( 100 );
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
	text_nr = 3;
	text = new MyText [ text_nr ];
	for( int i = 0; i < text_nr; i++ )
	{
		text[ i ].setID( "palette-text[" + to_string( i ) + "]" );
		text[ i ].setFont( "data/fonts/Jaapokki-Regular.otf", 30, 255, 255, 255 );
	}
	text[ 0 ].setText( "chosen [z]" );
	text[ 1 ].setText( "delete [x]" );
	text[ 2 ].setText( "save [LShift]" );
	// set position, set alpha
	text[ 0 ].setPosition( 30, screen_h - 50 );
	text[ 0 ].setAlpha( 0xFF );
	for( int i = 1; i < text_nr; i++ )
	{
		text[ i ].setPosition( text[ i-1 ].getRight() +30, text[ i-1 ].getY() );
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
		
	
	// Draw one special block
	if( which != -1 )
	{
		int tx = block[ which ].getX();
		int ty = block[ which ].getY();
		
		block[ which ].setScale( 1, 1 );
		block[ which ].center( x +disX, y +disY, 0, 0 );
		block[ which ].setAlpha( 0xFF );
		
		window->draw( block[ which ].get() );
		
		block[ which ].setScale( 0.6, 0.6 );
		block[ which ].setPosition( tx, ty );
		block[ which ].setAlpha( 100 );
	}
	
	// left
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( 71 ) ) )
		disX --;
	// right
	else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( 72 ) ) )
		disX ++;
	
	// up
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( 73 ) ) )
		disY --;
		
	// down
	else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( 74 ) ) )
		disY ++;
}

void Palette::handle( sf::Event &event )
{
	for( int i = 0; i < nr; i ++ )
	{
		block[ i ].setAlpha( 100 );
	}
		
	
	if( !deleteOn && !saveOn )
	{
		if( event.type == sf::Event::MouseMoved )
		{
			x = event.mouseMove.x;
			y = event.mouseMove.y;
			
			if( !chosenOn )
			{
				for( int i = 0; i < nr; i ++ )
				{
					if( block[ i ].checkCollision( x, y ) )
						block[ i ].setAlpha( 0xFF );
				}
			}
		}
		
		else if( event.type == sf::Event::MouseButtonPressed )
		{
			x = event.mouseButton.x;
			y = event.mouseButton.y;
			
			if( !chosenOn )
			{
				for( int i = 0; i < nr; i ++ )
				{
					if( block[ i ].checkCollision( x, y ) )
					{
						which = i;
						chosenOn = true;
						text[ 0 ].setColor( 0xCC, 0xCC, 88 );
						block[ i ].setAlpha( 0xFF );
						
						disX = disY = 0;
						break;
					}
				}
			}
		}
		
		else if( event.type == sf::Event::MouseButtonReleased )
		{
			for( int i = 0; i < nr; i ++ )
			{
				if( block[ i ].checkCollision( x, y ) )
				{
					block[ i ].setAlpha( 0xFF );
				}
			}
		}
	}
	
	
	
	if( event.type == sf::Event::KeyPressed )
	{
		// Back to menu
		if( event.key.code == sf::Keyboard::Escape )	back = true;
		
		
		// Turn off - chosen
		if( event.key.code == sf::Keyboard::Z && !saveOn )
		{
			chosenOn = false;
			deleteOn = false;
			which = -1;
			text[ 0 ].setColor( 0xFF, 0xFF, 0xFF );
		}
		
		
		// Turn off/on - delete
		if( event.key.code == sf::Keyboard::X && !saveOn )
		{
			deleteOn = !deleteOn;
			chosenOn = false;
			
			which = -1;
			text[ 0 ].setColor( 0xFF, 0xFF, 0xFF );
			
			if( deleteOn )	text[ 1 ].setColor( 0xCC, 0xCC, 88 );
			else			text[ 1 ].setColor( 0xFF, 0xFF, 0xFF );
		}
		
		// Turn off/on - save
		if( event.key.code == sf::Keyboard::LShift )
		{
			saveOn = !saveOn;
			deleteOn = false;
			chosenOn = false;
			
			which = -1;
			text[ 0 ].setColor( 0xFF, 0xFF, 0xFF );
			text[ 1 ].setColor( 0xFF, 0xFF, 0xFF );
			
			if( saveOn )	text[ 2 ].setColor( 0xCC, 0xCC, 88 );
			else			text[ 2 ].setColor( 0xFF, 0xFF, 0xFF );
		}
	}
}

bool Palette::backtomenu()
{
	return back;
}

string Palette::getFolder()
{
	return folder_name;
}

bool Palette::saveIsOn()
{
	return saveOn;
}

int Palette::getDisX()
{
	return disX;
}

int Palette::getDisY()
{
	return disY;
}

bool Palette::chosenIsOn()
{
	return chosenOn;
}