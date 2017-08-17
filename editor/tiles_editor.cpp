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
	
	info.free();
	bg.free();
	coin.free();
	savebutton.free();
	loadbutton.free();
	
	which = -1;
	chosen = -1;
	mouse_x = -1;
	mouse_y = -1;
	grid = true;
	width = 0;
	
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

void Tiles_editor::load( float screen_w, float screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	float scale_x = screen_w /2560;
	float scale_y = screen_h /1440;
	
	info.setIdentity( "tiles_editor-info" );
	info.setFont( "fonts/Jaapokki-Regular.otf" );
	info.setText( " " );
	info.setSize( screen_h /28 );
	info.setAlpha( 0xFF );
	
	bg.setIdentity( "tiles_editor-bg" );
	bg.load( "images/background.png" );
	bg.setScale( scale_x, scale_y );
	
	coin.setIdentity( "tiles_editor-coin" );
	coin.load( "images/coin.png", 7 );
	coin.setScale( scale_x, scale_y );
	
	savebutton.setIdentity( "tiles_editor-savebutton" );
	savebutton.load( "images/savebutton.png", 3 );
	savebutton.setScale( scale_x, scale_y );
	savebutton.setPosition( screen_w -savebutton.getWidth(), 0 );;
	
	loadbutton.setIdentity( "tiles_editor-loadbutton" );
	loadbutton.load( "images/loadbutton.png", 3 );
	loadbutton.setScale( scale_x, scale_y );
	loadbutton.setPosition( screen_w -loadbutton.getWidth() *2, 0 );
	
	line.setSize( sf::Vector2f( 1, 1 ) );
	line.setPosition( 0, 0 );
	
	for( unsigned i = 0; i < 16; i++ )
	{
		tiles.push_back( new MySprite() );
		tiles[ tiles.size() -1 ]->setIdentity( "tiles_editor-tiles" );
		tiles[ tiles.size() -1 ]->load( "images/tiles/" +con::itos( i ) +".png" );
		tiles[ tiles.size() -1 ]->setScale( scale_x, scale_y );
	}
	
	for( unsigned i = 0; i < 14; i++ )
	{
		objects.push_back( new MySprite() );
		objects[ objects.size() -1 ]->setIdentity( "tiles_editor-objects" );
		objects[ objects.size() -1 ]->load( "images/objects/" +con::itos( i ) +".png" );
		objects[ objects.size() -1 ]->setScale( scale_x, scale_y );
	}
	
	for( unsigned i = 0; i < 3; i++ )
	{
		foes.push_back( new MySprite() );
		foes[ foes.size() -1 ]->setIdentity( "tiles_editor-foes" );
		int n = 6;
		if( i == 1 )	n = 8;
		foes[ foes.size() -1 ]->load( "images/foes/" +con::itos( i ) +".png", n );
		foes[ foes.size() -1 ]->setScale( scale_x, scale_y );
	}
	
	width = tiles[ 0 ]->getWidth() /2;
}

void Tiles_editor::handle( sf::Event& event )
{
	if( event.type == sf::Event::KeyPressed )
	{
		int c = event.key.code;
		
		// backspace
		if( c == 59 )
		{
			ws.pop_back();
			ns.pop_back();
			xs.pop_back();
			ys.pop_back();
			
			if( ws[ ws.size() -1 ] == 2 ) // repeat
			{
				ws.pop_back();
				ns.pop_back();
				xs.pop_back();
				ys.pop_back();
			}
		}
		
		// g
		else if( c == 6 )
		{
			grid = !grid;
		}
		
		// space // x
		else if( c == 57 || c == 23 )
		{
			chosen = 0;
		}
		
		// v
		else if( c == 21 )
		{
			chosen += 2;
		}
		
		// + || c
		else if( c == 67 || c == 2 )
		{
			chosen ++;
		}
		
		// - || z
		else if( (c == 68 || c == 25) && chosen > -1 )
		{
			chosen --;
		}
		
		// shift
		else if( c == 38 && chosen > 0 )
		{
			chosen -= 2;
		}
		
		// number 26 ... 35
		else if( c >= 26 && c <= 35 )
		{
			which = c -26;
		}
	}
	
	if( event.type == sf::Event::MouseMoved )
	{
		mouse_x = event.mouseMove.x;
		mouse_y = event.mouseMove.y;
		
		int counter = 0;
		for( unsigned i = 0; i < ws.size(); i++ )
		{
			if( ws[ i ] == 2 )
			{
				counter ++;
			}
		}
		if( counter > 0 && counter %2 != 0 )
		{
			mouse_y = ys[ ys.size() -1 ];
		}
		
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
	
	if( event.type == sf::Event::MouseButtonPressed )
	{
		if( event.mouseButton.button == sf::Mouse::Left )
		{
			if( savebutton.checkCollision( mouse_x, mouse_y ) )
			{
				save();
			}
			else if( loadbutton.checkCollision( mouse_x, mouse_y ) )
			{
				load();
			}
			else if( chosen > -1 )
			{
				ws.push_back( which );
				ns.push_back( chosen );
				xs.push_back( mouse_x );
				ys.push_back( mouse_y );
			}
		}
	}
}

void Tiles_editor::draw( sf::RenderWindow* &window )
{
	string grid_str = "ON";
	if( !grid )	grid_str = "OFF";
	info.setText( "Grid: " +grid_str +"  which: " +con::itos( which ) +"  chosen: " +con::itos( chosen )
	+"  X: " +con::itos( static_cast <int> (mouse_x) ) +"  Y: " +con::itos( static_cast <int> (mouse_y) ) );
	
	window->draw( bg.get() );
	window->draw( savebutton.get() );
	window->draw( loadbutton.get() );
	
	for( unsigned i = 0; i < xs.size(); i++ )
	{
		// tiles
		if( ws[ i ] == 0 )
		{
			tiles[ ns[ i ] ]->setPosition( xs[ i ], ys[ i ] );
			window->draw( tiles[ ns[ i ] ]->get() );
		}
		
		// objects
		else if( ws[ i ] == 1 )
		{
			objects[ ns[ i ] ]->setPosition( xs[ i ], ys[ i ] );
			window->draw( objects[ ns[ i ] ]->get() );
		}
		
		// foes
		else if( ws[ i ] == 2 )
		{
			foes[ ns[ i ] ]->setPosition( xs[ i ], ys[ i ] );
			window->draw( foes[ ns[ i ] ]->get() );
		}
		
		// coins
		else if( ws[ i ] == 3 )
		{
			coin.setPosition( xs[ i ], ys[ i ] );
			window->draw( coin.get() );
		}
	}
	
	// Current
	if( chosen > -1 )
	{
		if( which == 0 )
		{
			if( chosen < static_cast <int> (tiles.size()) )
			{
				tiles[ chosen ]->setPosition( mouse_x, mouse_y );
				window->draw( tiles[ chosen ]->get() );
			}
		}
		else if( which == 1 )
		{
			if( chosen < static_cast <int> (objects.size()) )
			{
				objects[ chosen ]->setPosition( mouse_x, mouse_y );
				window->draw( objects[ chosen ]->get() );
			}
		}
		else if( which == 2 )
		{
			if( chosen < static_cast <int> (foes.size()) )
			{
				foes[ chosen ]->setPosition( mouse_x, mouse_y );
				window->draw( foes[ chosen ]->get() );
			}
		}
		else if( which == 3 )
		{
			coin.setPosition( mouse_x, mouse_y );
			window->draw( coin.get() );
		}
	}
	
	
	float w, h = 2;
	int counter = 0;
	for( ;; )
	{
		if( ws.size() < 1 )
		{
			break;
		}
		
		if( ws[ counter ] == 2 )
		{
			if( counter == xs.size() -1 )
			{
				w = mouse_x -xs[ counter ];
			}
			else
			{
				w = xs[ counter +1 ] -xs[ counter ];
			}
			
			line.setSize( sf::Vector2f( w, h ) );
			line.setPosition( sf::Vector2f( xs[ counter ], ys[ counter ] +foes[ ns[ counter ] ]->getHeight()/2 ) );
			window->draw( line );
			
			counter ++;
		}
		
		if( counter >= static_cast <int> (ws.size()) -1 )
		{
			break;
		}
		
		counter ++;
	}
	
	window->draw( info.get() );
}

void Tiles_editor::save()
{
	MyFile file;
	file.load( "world/world.txt", std::ios::app );
	if( file.is_good() )
	{
		for( unsigned i = 0; i < ws.size(); i++ )
		{
			file.get() << ws[ i ] << "." << ns[ i ] << "." << xs[ i ] << "." << ys[ i ] << endl;
		}
	}
	file.free();
}

void Tiles_editor::load()
{
	MyFile file;
	file.load( "world/world.txt" );
	if( file.is_good() )
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