#include "tiles_editor.h"
#include "own/file.h"

Tiles_editor::Tiles_editor()
{
	free();
}

Tiles_editor::~Tiles_editor()
{
	free();
}

void Tiles_editor::free()
{
	screen_w = 0;
	screen_h = 0;
	
	width = 0;
	grid = true;
	which = -1;
	chosen = 0;
	mouse_x = -1;
	mouse_y = -1;
	info.free();
	key_info.free();
	
	
	coin.free();
	if( !tiles.empty() )
	{
		for( auto &it :tiles )
		{
			it->free();
			delete it;
			it = NULL;
		}
		
		tiles.clear();
	}
	if( !objects.empty() )
	{
		for( auto &it :objects )
		{
			it->free();
			delete it;
			it = NULL;
		}
		
		objects.clear();
	}
	if( !foes.empty() )
	{
		for( auto &it :foes )
		{
			it->free();
			delete it;
			it = NULL;
		}
		
		foes.clear();
	}
	
	
	
	if( !ws.empty() )
	{
		ws.clear();
	}
	if( !ns.empty() )
	{
		ns.clear();
	}
	if( !xs.empty() )
	{
		xs.clear();
	}
	if( !ys.empty() )
	{
		ys.clear();
	}
}

void Tiles_editor::reset()
{
	which = -1;
	chosen = 0;
}

void Tiles_editor::clear()
{
	if( !ws.empty() )
	{
		ws.clear();
	}
	if( !ns.empty() )
	{
		ns.clear();
	}
	if( !xs.empty() )
	{
		xs.clear();
	}
	if( !ys.empty() )
	{
		ys.clear();
	}
}




void Tiles_editor::load( float screen_w, float screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	info.setIdentity( "tiles_editor-info" );
	info.setFont( "fonts/Jaapokki-Regular.otf" );
	info.setText( " " );
	info.setSize( screen_h /32 );
	info.setAlpha( 0xFF );
	
	key_info.setIdentity( "tiles_editor-key_info" );
	key_info.setFont( "fonts/Jaapokki-Regular.otf" );
	key_info.setText( "KEYBOARD: grid turn('g')    type --('a') ++('d') 0('s')    chosen --('z') ++('c') 0('x')    delete last('BackSpace')" );
	key_info.setSize( screen_h /36 );
	key_info.setAlpha( 0xFF );
	key_info.setPosition( screen_w/2 -key_info.getWidth() /2, screen_h /9 );
	
	
	float scale_x = screen_w /2560;
	float scale_y = screen_h /1440;
	
	coin.setIdentity( "tiles_editor-coin" );
	coin.load( "images/play/coin.png", 7 );
	coin.setScale( scale_x, scale_y );
	
	for( unsigned i = 0; i < 16; i++ )
	{
		tiles.push_back( new MySprite() );
		tiles[ tiles.size() -1 ]->setIdentity( "tiles_editor-tiles" );
		tiles[ tiles.size() -1 ]->load( "images/play/tiles/" +con::itos( i ) +".png" );
		tiles[ tiles.size() -1 ]->setScale( scale_x, scale_y );
	}
	
	for( unsigned i = 0; i < 14; i++ )
	{
		objects.push_back( new MySprite() );
		objects[ objects.size() -1 ]->setIdentity( "tiles_editor-objects" );
		objects[ objects.size() -1 ]->load( "images/play/objects/" +con::itos( i ) +".png" );
		objects[ objects.size() -1 ]->setScale( scale_x, scale_y );
	}
	
	for( unsigned i = 0; i < 3; i++ )
	{
		foes.push_back( new MySprite() );
		foes[ foes.size() -1 ]->setIdentity( "tiles_editor-foes" );
		int n = 6;
		if( i == 1 )	n = 8;
		foes[ foes.size() -1 ]->load( "images/play/foes/" +con::itos( i ) +".png", n );
		foes[ foes.size() -1 ]->setScale( scale_x, scale_y );
	}
	
	line.setSize( sf::Vector2f( 1, 1 ) );
	line.setPosition( 0, 0 );
	
	// Set width.
	width = tiles[ 0 ]->getWidth() /2;
}

void Tiles_editor::handle( sf::Event& event, bool isRubbish )
{
	// Check if FOE is active.
	bool able = true;
	int mycounter = 0;
	for( unsigned i = 0; i < ws.size(); i++ )
	{
		if( ws[ i ] == FOE )
		{
			mycounter ++;
		}
	}
	if( mycounter %2 != 0 )
	{
		able = false;
	}
	
	if( !isRubbish )
	{
		if( event.type == sf::Event::KeyPressed && able )
		{
			int code = event.key.code;
			
			if( code == sf::Keyboard::BackSpace )
			{
				if( ws.size() > 0 )
				{
					ws.pop_back();
					ns.pop_back();
					xs.pop_back();
					ys.pop_back();
					
					// Repeat.
					if( ws.size() > 0 )
					{
						if( ws[ ws.size() -1 ] == FOE )
						{
							ws.pop_back();
							ns.pop_back();
							xs.pop_back();
							ys.pop_back();
						}
					}
				}
			}
			
			else if( code == sf::Keyboard::G )
			{
				grid = !grid;
			}
			
			int size = 0;
			if( which == TILE )			size = tiles.size();
			else if( which == OBJECT )	size = objects.size();
			else if( which == FOE )		size = foes.size();
			
			// CHANGING CHOSEN ----------------------------------------
			if( code == sf::Keyboard::X )
			{
				chosen = 0;
			}
			else if( code == sf::Keyboard::C && chosen < size -1 )
			{
				chosen ++;
			}
			else if( code == sf::Keyboard::Z && chosen > 0 )
			{
				chosen --;
			}
			
			// CHANGING WHICH ----------------------------------------
			if( code == sf::Keyboard::S )
			{
				which = 0;
				chosen = 0;
			}
			else if( code == sf::Keyboard::D && which < AMOUNT -1 )
			{
				which ++;
				chosen = 0;
			}
			else if( code == sf::Keyboard::A && which > -1 )
			{
				which --;
				chosen = 0;
			}
			
			if( which == COIN )
			{
				chosen = 0;
			}	
		}
	}
	else if( !able )
	{
		ws.pop_back();
		ns.pop_back();
		xs.pop_back();
		ys.pop_back();
	}
	
	if( event.type == sf::Event::MouseMoved )
	{
		mouse_x = event.mouseMove.x;
		mouse_y = event.mouseMove.y;
		
		if( !isRubbish )
		{
			// Check if we need the same y position as before.
			int counter = 0;
			for( unsigned i = 0; i < ws.size(); i++ )
			{
				if( ws[ i ] == FOE )
				{
					counter ++;
				}
			}
			if( counter > 0 && counter %2 != 0 )
			{
				mouse_y = ys[ ys.size() -1 ];
			}
			
			// Grid works.
			if( grid )
			{
				int count = 0;
				while( mouse_x >= width )
				{
					mouse_x -= width;
					count ++;
				}
				mouse_x = count *width;
				
				count = 0;
				int diff = static_cast <int> (screen_h) %static_cast <int> (width);
				while( mouse_y -diff >= width )
				{
					mouse_y -= width;
					count ++;
				}
				mouse_y = count *width +diff;
			}
		}
	}
	
	
	else if( event.type == sf::Event::MouseButtonPressed )
	{
		if( event.mouseButton.button == sf::Mouse::Left )
		{
			if( chosen > -1 && which > -1 && !isRubbish )
			{
				ws.push_back( which );
				ns.push_back( chosen );
				xs.push_back( mouse_x );
				ys.push_back( mouse_y );
			}
			
			if( isRubbish )
			{
				int collision = -1;
				for( unsigned i = 0; i < xs.size(); i++ )
				{
					if( ws[ i ] == COIN )
					{
						coin.setPosition( xs[ i ], ys[ i ] );
						if( coin.checkCollision( mouse_x, mouse_y ) )
						{
							collision = i;
						}
					}
					else if( ws[ i ] == TILE )
					{
						tiles[ ns[ i ] ]->setPosition( xs[ i ], ys[ i ] );
						if( tiles[ ns[ i ] ]->checkCollision( mouse_x, mouse_y ) )
						{
							collision = i;
						}
					}
					else if( ws[ i ] == OBJECT )
					{
						objects[ ns[ i ] ]->setPosition( xs[ i ], ys[ i ] );
						if( objects[ ns[ i ] ]->checkCollision( mouse_x, mouse_y ) )
						{
							collision = i;
						}
					}
					else if( ws[ i ] == FOE )
					{
						foes[ ns[ i ] ]->setPosition( xs[ i ], ys[ i ] );
						if( foes[ ns[ i ] ]->checkCollision( mouse_x, mouse_y ) )
						{
							collision = i;
						}
					}
					
				}
				
				if( collision != -1 )
				{
					// check more
					int myseccounter = 0;
					int status = 0;
					
					if( collision > 0 )
					{
						for( unsigned i = 0; i < collision; i++ )
						{
							if( ws[ i ] == FOE )
							{
								myseccounter ++;
							}
						}
						
						if( myseccounter %2 == 0 )	status = 0;
						else						status = -1;
					}
					else if( collision < ws.size() -1 )
					{
						for( unsigned i = collision; i < ws.size(); i++ )
						{
							if( ws[ i ] == FOE )
							{
								myseccounter ++;
							}
						}
						
						if( myseccounter %2 != 0 )	status = 0;
						else						status = -1;
					}
					else if( collision == 1 )
					{
						status = -1;
					}
					else if( collision == ws.size() )
					{
						status = 0;
					}
					
					
					if( ws[ collision ] == FOE )
					{
						ws.erase( ws.begin() +collision );
						ns.erase( ns.begin() +collision );
						xs.erase( xs.begin() +collision );
						ys.erase( ys.begin() +collision );
						collision += status;
					}
					
					ws.erase( ws.begin() +collision );
					ns.erase( ns.begin() +collision );
					xs.erase( xs.begin() +collision );
					ys.erase( ys.begin() +collision );
				}
			}
		}
	}
}

void Tiles_editor::draw( sf::RenderWindow* &window )
{
	// Draw added drawable stuff.
	for( unsigned i = 0; i < xs.size(); i++ )
	{
		if( ws[ i ] == COIN )
		{
			coin.setPosition( xs[ i ], ys[ i ] );
			window->draw( coin.get() );
		}
		else if( ws[ i ] == TILE )
		{
			tiles[ ns[ i ] ]->setPosition( xs[ i ], ys[ i ] );
			window->draw( tiles[ ns[ i ] ]->get() );
		}
		else if( ws[ i ] == OBJECT )
		{
			objects[ ns[ i ] ]->setPosition( xs[ i ], ys[ i ] );
			window->draw( objects[ ns[ i ] ]->get() );
		}
		else if( ws[ i ] == FOE )
		{
			foes[ ns[ i ] ]->setPosition( xs[ i ], ys[ i ] );
			window->draw( foes[ ns[ i ] ]->get() );
		}
	}
	
	
	// Draw current drawable thing.
	if( chosen > -1 )
	{
		if( which == COIN )
		{
			coin.setPosition( mouse_x, mouse_y );
			window->draw( coin.get() );
		}
		else if( which == TILE )
		{
			if( chosen < static_cast <int> (tiles.size()) )
			{
				tiles[ chosen ]->setPosition( mouse_x, mouse_y );
				window->draw( tiles[ chosen ]->get() );
			}
		}
		else if( which == OBJECT )
		{
			if( chosen < static_cast <int> (objects.size()) )
			{
				objects[ chosen ]->setPosition( mouse_x, mouse_y );
				window->draw( objects[ chosen ]->get() );
			}
		}
		else if( which == FOE )
		{
			if( chosen < static_cast <int> (foes.size()) )
			{
				foes[ chosen ]->setPosition( mouse_x, mouse_y );
				window->draw( foes[ chosen ]->get() );
			}
		}
	}
	
	
	// Draw lines.
	unsigned counter = 0;
	while( true )
	{
		if( ws.size() < 1 )
		{
			break;
		}
		
		if( ws[ counter ] == FOE )
		{
			float w;
			if( counter == xs.size() -1 )
			{
				w = mouse_x -xs[ counter ];
			}
			else
			{
				w = xs[ counter +1 ] -xs[ counter ];
			}
			
			line.setSize( sf::Vector2f( w, 2 ) );
			line.setPosition( sf::Vector2f( xs[ counter ], ys[ counter ] +foes[ ns[ counter ] ]->getHeight()/2 ) );
			window->draw( line );
			
			counter ++;
		}
		
		if( static_cast <int> (counter) >= static_cast <int> (ws.size()) -1 )
		{
			break;
		}
		
		counter ++;
	}
	
	
	
	// Draw info.
	string grid_str = "ON";
	if( !grid )	grid_str = "OFF";
	
	string which_str = "none";
	if( which == COIN )			which_str = "coin";
	else if( which == TILE )	which_str = "tile";
	else if( which == OBJECT )	which_str = "object";
	else if( which == FOE )	which_str = "foe";
	
	string chosen_str = "";
	if( which != COIN )
	{
		chosen_str = "  chosen: " +con::itos( chosen );
	}
	
	info.setText( "Grid: " +grid_str 
	+"  type: " +which_str 
	+chosen_str 
	+"  X: " +con::itos( static_cast <int> (mouse_x) ) 
	+"  Y: " +con::itos( static_cast <int> (mouse_y) ) );
	
	info.setPosition( screen_w/2 -info.getWidth() /2, screen_h /18 );
	window->draw( info.get() );
	window->draw( key_info.get() );
}




void Tiles_editor::save( string path )
{
	MyFile file;
	file.load( "txt/worlds/" +path +".txt", std::ios::out );
	if( file.is_good() )
	{
		for( unsigned i = 0; i < ws.size(); i++ )
		{
			file.get() << ws[ i ] << "." << ns[ i ] << "." << xs[ i ] << "." << ys[ i ] << endl;
		}
	}
	file.free();
}

void Tiles_editor::load( string path )
{
	MyFile file;
	file.load( "txt/worlds/" +path +".txt" );
	if( file.is_good() )
	{
		clear();
		
		string myline = "";
		while( getline( file.get(), myline ) )
		{
			vector <string> mydata;
			string mynumber = "";
			
			for( unsigned i = 0; i < myline.size(); i++ )
			{
				if( myline[ i ] == '.' )
				{
					mydata.push_back( mynumber );
					mynumber = "";
					i++;
				}
				
				mynumber += myline[ i ];
			}
			mydata.push_back( mynumber );
			
			ws.push_back( con::stof( mydata[ 0 ] ) );
			ns.push_back( con::stof( mydata[ 1 ] ) );
			xs.push_back( con::stof( mydata[ 2 ] ) );
			ys.push_back( con::stof( mydata[ 3 ] ) );
		}
	}
	file.free();
}