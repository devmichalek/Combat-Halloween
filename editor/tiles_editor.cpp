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
	
	leftbutton.free();
	rightbutton.free();
	additional_x = 0;
	
	
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
	
	if( !blocks.empty() )
	{
		blocks.clear();
	}
}

void Tiles_editor::reset()
{
	which = -1;
	chosen = 0;
	additional_x = 0;
}

void Tiles_editor::clear()
{
	if( !blocks.empty() )
	{
		blocks.clear();
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
	
	
	leftbutton.setIdentity( "tiles_editor-leftbutton" );
	leftbutton.load( "images/level/left.png", 3 );
	leftbutton.setScale( scale_x /2, scale_y /2 );
	leftbutton.setPosition( screen_w /256, screen_h /2 -leftbutton.getHeight() /2 );
	
	rightbutton.setIdentity( "tiles_editor-rightbutton" );
	rightbutton.load( "images/level/right.png", 3 );
	rightbutton.setScale( scale_x /2, scale_y /2 );
	rightbutton.setPosition( screen_w -screen_w/256 -rightbutton.getWidth(), screen_h /2 -rightbutton.getHeight() /2 );
	
	
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
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		if( blocks[ i ].w == FOE )
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
				if( blocks.size() > 0 )
				{
					blocks.pop_back();
					
					// Repeat.
					if( blocks.size() > 0 )
					{
						if( blocks[ blocks.size() -1 ].w == FOE )
						{
							blocks.pop_back();
						}
					}
				}
			}
			
			else if( code == sf::Keyboard::G )
			{
				grid = !grid;
			}
			
			int size = 0;
			if( which == TILE )				size = tiles.size();
			if( which == UNVISIBLE_TILE )	size = tiles.size();
			else if( which == OBJECT )		size = objects.size();
			else if( which == FOE )			size = foes.size();
			
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
		blocks.pop_back();
	}
	
	if( event.type == sf::Event::MouseMoved )
	{
		mouse_x = event.mouseMove.x;
		mouse_y = event.mouseMove.y;
		
		if( !isRubbish )
		{
			// Check if we need the same y position as before.
			int counter = 0;
			for( unsigned i = 0; i < blocks.size(); i++ )
			{
				if( blocks[ i ].w == FOE )
				{
					counter ++;
				}
			}
			if( counter > 0 && counter %2 != 0 )
			{
				mouse_y = blocks[ blocks.size() -1 ].y;
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
			if( leftbutton.checkCollision( event.mouseButton.x, event.mouseButton.y ) )
			{
				additional_x += screen_w /2;
				
				for( auto &it :blocks )
				{
					it.x += screen_w /2;
				}
			}
			else if( rightbutton.checkCollision( event.mouseButton.x, event.mouseButton.y ) )
			{
				additional_x -= screen_w /2;
				
				for( auto &it :blocks )
				{
					it.x -= screen_w /2;
				}
			}
			else if( chosen > -1 && which > -1 && !isRubbish )
			{
				Block block;
				block.w = which;
				block.n = chosen;
				block.x = mouse_x -additional_x;
				block.y = mouse_y;
				blocks.push_back( block );
			}
			
			if( isRubbish )
			{
				int collision = -1;
				for( unsigned i = 0; i < blocks.size(); i++ )
				{
					if( blocks[ i ].w == COIN )
					{
						coin.setPosition( blocks[ i ].x, blocks[ i ].y );
						if( coin.checkCollision( mouse_x +additional_x, mouse_y ) )
						{
							collision = i;
						}
					}
					else if( blocks[ i ].w == TILE )
					{
						tiles[ blocks[ i ].n ]->setPosition( blocks[ i ].x, blocks[ i ].y );
						if( tiles[ blocks[ i ].n ]->checkCollision( mouse_x +additional_x, mouse_y ) )
						{
							collision = i;
						}
					}
					else if( blocks[ i ].w == UNVISIBLE_TILE )
					{
						tiles[ blocks[ i ].n ]->setPosition( blocks[ i ].x, blocks[ i ].y );
						if( tiles[ blocks[ i ].n ]->checkCollision( mouse_x +additional_x, mouse_y ) )
						{
							collision = i;
						}
					}
					else if( blocks[ i ].w == OBJECT )
					{
						objects[ blocks[ i ].n ]->setPosition( blocks[ i ].x, blocks[ i ].y );
						if( objects[ blocks[ i ].n ]->checkCollision( mouse_x +additional_x, mouse_y ) )
						{
							collision = i;
						}
					}
					else if( blocks[ i ].w == FOE )
					{
						foes[ blocks[ i ].n ]->setPosition( blocks[ i ].x, blocks[ i ].y );
						if( foes[ blocks[ i ].n ]->checkCollision( mouse_x +additional_x, mouse_y ) )
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
							if( blocks[ i ].w == FOE )
							{
								myseccounter ++;
							}
						}
						
						if( myseccounter %2 == 0 )	status = 0;
						else						status = -1;
					}
					else if( collision < blocks.size() -1 )
					{
						for( unsigned i = collision; i < blocks.size(); i++ )
						{
							if( blocks[ i ].w == FOE )
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
					else if( collision == blocks.size() )
					{
						status = 0;
					}
					
					
					if( blocks[ collision ].w == FOE )
					{
						blocks.erase( blocks.begin() +collision );
						collision += status;
					}
					
					blocks.erase( blocks.begin() +collision );
				}
			}
		}
	}
}

void Tiles_editor::draw( sf::RenderWindow* &window )
{
	// Draw added drawable stuff.
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		int w = blocks[ i ].w;
		int n = blocks[ i ].n;
		float x = blocks[ i ].x;
		float y = blocks[ i ].y;
		
		if( w == COIN )
		{
			coin.setPosition( x, y );
			window->draw( coin.get() );
		}
		else if( w == TILE )
		{
			tiles[ n ]->setPosition( x, y );
			tiles[ n ]->setAlpha( 0xFF );
			window->draw( tiles[ n ]->get() );
		}
		else if( w == UNVISIBLE_TILE )
		{
			tiles[ n ]->setPosition( x, y );
			tiles[ n ]->setAlpha( 0xFF /2 );
			window->draw( tiles[ n ]->get() );
		}
		else if( w == OBJECT )
		{
			objects[ n ]->setPosition( x, y );
			window->draw( objects[ n ]->get() );
		}
		else if( w == FOE )
		{
			foes[ n ]->setPosition( x, y );
			window->draw( foes[ n ]->get() );
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
				tiles[ chosen ]->setAlpha( 0xFF );
				window->draw( tiles[ chosen ]->get() );
			}
		}
		else if( which == UNVISIBLE_TILE )
		{
			if( chosen < static_cast <int> (tiles.size()) )
			{
				tiles[ chosen ]->setPosition( mouse_x, mouse_y );
				tiles[ chosen ]->setAlpha( 0xFF /2 );
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
		if( blocks.size() < 1 )
		{
			break;
		}
		
		if( blocks[ counter ].w == FOE )
		{
			float w;
			if( counter == blocks.size() -1 )
			{
				w = mouse_x -blocks[ counter ].x;
			}
			else
			{
				w = blocks[ counter +1 ].x -blocks[ counter ].x;
			}
			
			line.setSize( sf::Vector2f( w, 2 ) );
			line.setPosition( sf::Vector2f( blocks[ counter ].x, blocks[ counter ].y +foes[ blocks[ counter ].n ]->getHeight()/2 ) );
			window->draw( line );
			
			counter ++;
		}
		
		if( static_cast <int> (counter) >= static_cast <int> (blocks.size()) -1 )
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
	else if( which == UNVISIBLE_TILE )	which_str = "unvisible tile";
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
	+"  X: " +con::itos( static_cast <int> (mouse_x -additional_x) ) 
	+"  Y: " +con::itos( static_cast <int> (mouse_y) ) );
	
	info.setPosition( screen_w/2 -info.getWidth() /2, screen_h /18 );
	window->draw( info.get() );
	window->draw( key_info.get() );
	
	// Draw buttons.
	window->draw( leftbutton.get() );
	window->draw( rightbutton.get() );
}




void Tiles_editor::save( string path )
{
	MyFile file;
	file.load( "txt/worlds/" +path +".txt", std::ios::out );
	if( file.is_good() )
	{
		// Sort by w.
		sort( blocks.begin(), blocks.end(), []( const Block& a, const Block& b ) { return a.w < b.w; } );
		
		// Take foes and rest.
		vector <Block> myblocks;
		vector <Block> finalblocks;
		int counter = 0;
		for( unsigned i = 0; i < blocks.size(); i++ )
		{
			if( counter != blocks[ i ].w || i == blocks.size() -1 )
			{
				if( i == blocks.size() -1 )
				{
					myblocks.push_back( blocks[ i ] );
				}
				
				// Sort by x.
				if( counter != FOE )
				{
					sort( myblocks.begin(), myblocks.end(), []( const Block& a, const Block& b ) { return a.x < b.x; } );
				}
				
				finalblocks.insert( finalblocks.end(), myblocks.begin(), myblocks.end() );
				myblocks.clear();
				counter ++;
			}
			
			myblocks.push_back( blocks[ i ] );
		}
		myblocks.clear();
		
		
		// Write to file.
		file.get() << screen_w << endl;
		file.get() << screen_h << endl;
		for( unsigned i = 0; i < finalblocks.size(); i++ )
		{
			file.get() << finalblocks[ i ].w << "." << finalblocks[ i ].n << "." << finalblocks[ i ].x << "." << finalblocks[ i ].y;
			if( i < finalblocks.size() -1 )
			{
				file.get() << endl;
			}
		}
		finalblocks.clear();
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
		
		// Set multipliers.
		getline( file.get(), myline );
		float x_multiplier = screen_w /con::stof( myline );
		getline( file.get(), myline );
		float y_multiplier = screen_h /con::stof( myline );
		
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
			
			Block block;
			block.w = con::stoi( mydata[ 0 ] );
			block.n = con::stoi( mydata[ 1 ] );
			block.x = con::stof( mydata[ 2 ] ) *x_multiplier;
			block.y = con::stof( mydata[ 3 ] ) *y_multiplier;
			blocks.push_back( block );
		}
		
		additional_x = 0;
	}
	file.free();
}