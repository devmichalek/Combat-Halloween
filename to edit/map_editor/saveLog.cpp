#include "map_editor/saveLog.h"

SaveLog::SaveLog()
{
	name = "name";
	path = "";
	action = false;
	data = "";
	platform = 0;
}

SaveLog::~SaveLog()
{
	free();
}

void SaveLog::free()
{
	name = "name";
	path = "";
	action = false;
	
	data = "";
	
	bar.free();
	limb.free();
	editable.free();
	save.free();
	savebar.free();
	
	platform = 0;
}


void SaveLog::load( int screen_w, int screen_h, string folder )
{
	bar.setName( "palette-bar" );
	bar.create( screen_w, 70 );
	bar.center( 0, 0, screen_w, screen_h );
	bar.setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
	bar.setAlpha( 0xFF );
	
	// printf( "%d %d\n", bar.getWidth(), bar.getHeight() );
		

	limb.setID( "SaveLog-limb" );
	limb.setFont( "data/fonts/Jaapokki-Regular.otf", 30, 0, 0, 0 );
	limb.setText( folder );
	limb.setPosition( bar.getX() +20, bar.getY() +14 );
	limb.setAlpha( 0xFF );
	
	path = folder;
	
	editable.setID( "SaveLog-editable" );
	editable.setFont( "data/fonts/Jaapokki-Regular.otf", 30, 0, 0, 0 );
	editable.setText( name );
	editable.setPosition( limb.getRight() +30, limb.getY() );
	editable.setAlpha( 0xFF );
	
	// saveAsFile( "16 200 100\n27 300 45" ); test
	
	save.setID( "SaveLog-save" );
	save.setFont( "data/fonts/Jaapokki-Regular.otf", 20, 0xCC, 0xCC, 0x00 );
	save.setText( "save" );
	save.setPosition( bar.getRight() -save.getWidth() -4, bar.getBot() );
	save.setAlpha( 0xFF );
	
	
	savebar.setName( "palette-savebar" );
	savebar.create( save.getWidth() +3, save.getHeight() +4 );
	savebar.setPosition( save.getX() -1, save.getY() +9 );
	savebar.setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
	savebar.setAlpha( 0xFF );
}

void SaveLog::draw( sf::RenderWindow* &window )
{
	window->draw( bar.get() );
	window->draw( limb.get() );
	window->draw( editable.get() );
	
	// draw button
	window->draw( savebar.get() );
	window->draw( save.get() );
}

void SaveLog::handle( sf::Event &event )
{
	if( event.type == sf::Event::MouseButtonPressed )
	{
		int x = event.mouseButton.x;
		int y = event.mouseButton.y;
		
		if( savebar.checkCollision( x, y ) )
		{
			saveAsFile();
		}
	}
	
	if( event.type == sf::Event::KeyPressed && !action )
	{
		char c; // = 0
		bool flag = false;
		
		if( editable.getRight() +20 < bar.getRight() )
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
		
		
		
		if( flag )	name += c;
		else
		{
			if( event.key.code == sf::Keyboard::BackSpace )
			{
				if( name.size() > 0 )
				{
					name.erase( name.size() -1 );
				}
			}
			
			if( name.size() == 0 )
			{
				name = " ";
			}
		}
		
		if( name.size() > 1 && name[ 0 ] == ' ' )
		{
			string temporary = "";
			for( unsigned i = 1; i < name.size(); i++ )
			{
				temporary += name[ i ];
			}
			
			name = temporary;
		}
		
		// printf( "-->%s<--\n", name.c_str() );
		
		action = true;
	}
	else if( action )
	{
		action = false;
		editable.setText( name );
		editable.setPosition( limb.getRight() +30, limb.getY() );
		editable.setAlpha( 0xFF );
	}
}

void SaveLog::saveAsFile()
{
	file.open( path + name + ".txt", std::ios::app );
	if( file.good() )
	{
		printf( "Created file\n" );
		file << data;
		// file << to_string( platform ); 29.11.2016 
	}
	else
	{
		printf( "Cannot open file %s\n", (path + name).c_str() );
	}
	file.close();
}

void SaveLog::supplyData( string data )
{
	this->data = data;
}

void SaveLog::supplyPlatform( int p )
{
	platform = p;
}
