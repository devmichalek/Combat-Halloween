#include "map_editor/saveLog.h"

SaveLog::SaveLog()
{
	edit_s = "name";
	action = false;
}

SaveLog::~SaveLog()
{
	free();
}

void SaveLog::free()
{
	edit_s = "name";
	action = false;
	
	bar.free();
	basic.free();
	edit.free();
}


void SaveLog::load( int screen_w, int screen_h, string folder )
{
	bar.setName( "palette-bar" );
	bar.create( screen_w, 70 );
	bar.center( 0, 0, screen_w, screen_h );
	bar.setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
	bar.setAlpha( 0xFF );
	
	// printf( "%d %d\n", bar.getWidth(), bar.getHeight() );
		

	basic.setID( "SaveLog-basic" );
	basic.setFont( "data/fonts/Jaapokki-Regular.otf", 30, 0, 0, 0 );
	basic.setText( folder );
	basic.setPosition( bar.getX() +20, bar.getY() +14 );
	basic.setAlpha( 0xFF );
	
	edit.setID( "SaveLog-edit" );
	edit.setFont( "data/fonts/Jaapokki-Regular.otf", 30, 0, 0, 0 );
	edit.setText( edit_s );
	edit.setPosition( basic.getRight() +30, basic.getY() );
	edit.setAlpha( 0xFF );
}

void SaveLog::draw( sf::RenderWindow* &window )
{
	window->draw( bar.get() );
	window->draw( basic.get() );
	window->draw( edit.get() );
}

void SaveLog::handle( sf::Event &event )
{
	if( event.type == sf::Event::KeyPressed && !action )
	{
		char c; // = 0
		bool flag = false;
		
		if( edit.getRight() +20 < bar.getRight() )
		{
			// A ... Z
			for( int i = 0; i < 26; i++ )
			{
				if( event.key.code == i )
				{
					c = static_cast <char> ( i +97 );
					flag = true;
					break;
				}
			}
			
			if( !flag )
			{
				// 1 ... 9 	part 1
				for( int i = 26; i < 36; i++ )
				{
					if( event.key.code == i )
					{
						c = static_cast <char> ( i + (48-26) );
						flag = true;
						break;
					}
				}
				
				if( !flag )
				{
					// 1 ... 9 	part 2
					for( int i = 75; i < 85; i++ )
					{
						if( event.key.code == i )
						{
							c = static_cast <char> ( i - (75-48) );
							flag = true;
							break;
						}
					}
				}
			}
			
			
		}
		
		
		
		if( flag )	edit_s += c;
		else
		{
			if( event.key.code == sf::Keyboard::BackSpace )
			{
				if( edit_s.size() > 0 )
				{
					edit_s.erase( edit_s.size() -1 );
				}
			}
			
			if( edit_s.size() == 0 )
			{
				edit_s = " ";
			}
		}
		
		if( edit_s.size() > 1 && edit_s[ 0 ] == ' ' )
		{
			string temporary = "";
			for( unsigned i = 1; i < edit_s.size(); i++ )
			{
				temporary += edit_s[ i ];
			}
			
			edit_s = temporary;
		}
		
		// printf( "-->%s<--\n", edit_s.c_str() );
		
		action = true;
	}
	else if( action )
	{
		action = false;
		edit.setText( edit_s );
		edit.setPosition( basic.getRight() +30, basic.getY() );
		edit.setAlpha( 0xFF );
	}
}
