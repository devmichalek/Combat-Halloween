#include "tiles_editor.h"
#include "own/file.h"

Block::Block( sf::Uint8 w, sf::Uint8 n, float x, float y )
{
	this->w = w;
	this->n = n;
	this->x = x;
	this->y = y;
}

Block::~Block()
{
	w = 0;
	n = 0;
	x = 0;
	y = 0;
}



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
	
	which = -1;
	chosen = 0;
	mouse_x = -1;
	mouse_y = -1;
	info.free();
	mouseInfo.free();
	arrow.free();
	
	width = 0;
	grid = true;
	
	key_info.free();
	
	leftbutton.free();
	rightbutton.free();
	topbutton.free();
	botbutton.free();
	additional_x = 0;
	additional_y = 0;
	
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
	
	if( !foeblocks.empty() )
	{
		foeblocks.clear();
	}
	lastwasfoe = false;
	isrubbishon = false;
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
	
	mouseInfo.setIdentity( "tiles_editor-mouseInfo" );
	mouseInfo.setFont( "fonts/Jaapokki-Regular.otf" );
	mouseInfo.setText( " " );
	mouseInfo.setSize( screen_h /42 );
	mouseInfo.setAlpha( 0xFF );
	
	key_info.setIdentity( "tiles_editor-key_info" );
	key_info.setFont( "fonts/Jaapokki-Regular.otf" );
	key_info.setText( "Keyboard action('key'): grid turn('g')      type --('a') ++('d') 0('s')      chosen --('z') ++('c') 0('x')      delete last('BackSpace')" );
	key_info.setSize( screen_h /36 );
	key_info.setAlpha( 0xFF );
	key_info.setPosition( screen_w /256, screen_h -key_info.getHeight() -screen_h /144 );
	
	// Rest sprites.
	float scale_x = screen_w /2560;
	float scale_y = screen_h /1440;
	
	arrow.setIdentity( "tiles_editor-arrow" );
	arrow.load( "images/editor/left_arrow.png" );
	arrow.setScale( scale_x /2, scale_y /2 );
	
	leftbutton.setIdentity( "tiles_editor-leftbutton" );
	leftbutton.load( "images/level/left.png", 3 );
	leftbutton.setScale( scale_x /2, scale_y /2 );
	leftbutton.setPosition( screen_w -(screen_w /256 *3) -(leftbutton.getWidth() *3),
	screen_h -(screen_h /144 *2) -leftbutton.getHeight() *2 );
	
	rightbutton.setIdentity( "tiles_editor-rightbutton" );
	rightbutton.load( "images/level/right.png", 3 );
	rightbutton.setScale( scale_x /2, scale_y /2 );
	rightbutton.setPosition( screen_w -screen_w/256 -rightbutton.getWidth(),
	screen_h -(screen_h /144 *2) -rightbutton.getHeight() *2 );
	
	topbutton.setIdentity( "tiles_editor-topbutton" );
	topbutton.load( "images/editor/top.png", 3 );
	topbutton.setScale( scale_x /2, scale_y /2 );
	topbutton.setPosition( screen_w -screen_w/128 -topbutton.getWidth() *2,
	screen_h -(screen_h /144 *3) -topbutton.getHeight() *3 );
	
	botbutton.setIdentity( "tiles_editor-botbutton" );
	botbutton.load( "images/editor/bot.png", 3 );
	botbutton.setScale( scale_x /2, scale_y /2 );
	botbutton.setPosition( screen_w -screen_w/128 -(botbutton.getWidth() *2),
	screen_h -screen_h /144 -botbutton.getHeight() );
	
	coin.setIdentity( "tiles_editor-coin" );
	coin.load( "images/play/coin.png", 7 );
	coin.setScale( scale_x, scale_y );
	
	for( unsigned i = 0; i < 17; i++ )
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
	
	// Set width.
	width = tiles[ 0 ]->getWidth() /2;
}

void Tiles_editor::handle( sf::Event& event, bool isRubbish )
{
	isrubbishon = isRubbish;
	
	if( event.type == sf::Event::KeyPressed && !isRubbish )
	{
		int code = event.key.code;
		
		if( code == sf::Keyboard::BackSpace )
		{
			if( lastwasfoe )
			{
				if( foeblocks.size() > 0 )
				{
					foeblocks.pop_back();
				}
				
				if( foeblocks.size() == 0 )
				{
					lastwasfoe = false;
				}
			}
			else
			{
				if( blocks.size() > 0 )
				{
					blocks.pop_back();
				}
				
				if( blocks.size() == 0 )
				{
					lastwasfoe = true;
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
		if( code == sf::Keyboard::X )							chosen = 0;
		else if( code == sf::Keyboard::C && chosen < size -1 )	chosen ++;
		else if( code == sf::Keyboard::Z && chosen > 0 )		chosen --;
		
		
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
	}
	
	
	if( event.type == sf::Event::MouseMoved )
	{
		mouse_x = event.mouseMove.x;
		mouse_y = event.mouseMove.y;
		
		// Grid works.
		if( grid && !isRubbish )
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
		mouse_x = event.mouseButton.x;
		mouse_y = event.mouseButton.y;
		
		if( event.mouseButton.button == sf::Mouse::Left )
		{
			if( leftbutton.checkCollision( mouse_x, mouse_y ) && additional_x < 0 )
			{
				additional_x += screen_w /4;
				leftbutton.setOffset( 1 );
			}
			else if( rightbutton.checkCollision( mouse_x, mouse_y ) )
			{
				additional_x -= screen_w /4;
				rightbutton.setOffset( 1 );
			}
			else if( topbutton.checkCollision( mouse_x, mouse_y ) )
			{
				additional_y += screen_h /4;
				topbutton.setOffset( 1 );
			}
			else if( botbutton.checkCollision( mouse_x, mouse_y ) && additional_y > 0 )
			{
				additional_y -= screen_h /4;
				botbutton.setOffset( 1 );
			}
			else if( chosen > -1 && which > -1 && !isRubbish )
			{
				if( which == FOE )
				{
					lastwasfoe = true;
					foeblocks.push_back( Block( which, chosen, mouse_x -additional_x, mouse_y -additional_y ) );
				}
				else
				{
					lastwasfoe = false;
					blocks.push_back( Block( which, chosen, mouse_x -additional_x, mouse_y -additional_y ) );
				}
			}
			
			if( isRubbish )
			{
				deleteOne();
			}
		}
	}
	
	if( event.type == sf::Event::MouseButtonReleased )
	{
		leftbutton.setOffset( 0 );
		rightbutton.setOffset( 0 );
		topbutton.setOffset( 0 );
		botbutton.setOffset( 0 );
	}
}

void Tiles_editor::draw( sf::RenderWindow* &window )
{
	// Draw vector.
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		int w = blocks[ i ].w;
		int n = blocks[ i ].n;
		float x = blocks[ i ].x +additional_x;
		float y = blocks[ i ].y +additional_y;
		
		if( w == TILE )
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
		else if( w == COIN )
		{
			coin.setPosition( x, y );
			window->draw( coin.get() );
		}
	}
	
	for( unsigned i = 0; i < foeblocks.size(); i++ )
	{
		int n = foeblocks[ i ].n;
		float x = foeblocks[ i ].x +additional_x;
		float y = foeblocks[ i ].y +additional_y;
		
		foes[ n ]->setPosition( x, y );
		window->draw( foes[ n ]->get() );
	}
	
	
	// Draw current drawable thing.
	if( chosen > -1 )
	{
		if( which == TILE )
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
		else if( which == COIN )
		{
			coin.setPosition( mouse_x, mouse_y );
			window->draw( coin.get() );
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
	
	
	// Draw information.
	string grid_str = "On";
	if( !grid )
	{
		grid_str = "Off";
	}
	string which_str = "None";
	if( which == TILE )					which_str = "tile";
	else if( which == UNVISIBLE_TILE )	which_str = "unvisible tile";
	else if( which == COIN )			which_str = "coin";
	else if( which == OBJECT )			which_str = "object";
	else if( which == FOE )				which_str = "foe";
	string chosen_str = "";
	if( which != COIN )
	{
		chosen_str = "  Chosen: " +con::itos( chosen );
	}
	info.setText( "Grid: " +grid_str +"  Type: " +which_str +chosen_str );
	
	info.setPosition( screen_w/2 -info.getWidth() /2, screen_h /18 );
	window->draw( info.get() );
	window->draw( key_info.get() );
	
	
	
	// Draw direction buttons.
	if( additional_x >= 0 )
	{
		leftbutton.setOffset( 2 );
	}
	if( additional_y <= 0 )
	{
		botbutton.setOffset( 2 );
	}
	
	drawTumbnails( window );
	drawLines( window );
	window->draw( leftbutton.get() );
	window->draw( rightbutton.get() );
	window->draw( botbutton.get() );
	window->draw( topbutton.get() );
}

void Tiles_editor::drawTumbnails( sf::RenderWindow* &window )
{
	// Draw thumbnails.
	if( chosen > -1 && which > -1 && which != COIN )
	{
		float start_x = screen_w /256 +leftbutton.getWidth();
		float start_y = screen_h /144 +(leftbutton.getHeight() *2);
		
		float scale_x = screen_w /2560 /2;
		float scale_y = screen_h /1440 /2;
		float old_scale_x = screen_w /2560;
		float old_scale_y = screen_h /1440;
		float gap = screen_h /144;
		
		if( which == TILE || which == UNVISIBLE_TILE )
		{
			tiles[ 0 ]->setScale( scale_x, scale_y );
			tiles[ 0 ]->setPosition( start_x -tiles[ 0 ]->getWidth() /2, start_y );
			for( unsigned i = 1; i < tiles.size(); i++ )
			{
				tiles[ i ]->setScale( scale_x, scale_y );
				tiles[ i ]->setPosition( start_x -tiles[ i ]->getWidth() /2, tiles[ i -1 ]->getBot() +gap );
			}
			
			arrow.setPosition( tiles[ chosen ]->getRight(), tiles[ chosen ]->getY() +tiles[ chosen ]->getHeight()/2 -arrow.getHeight()/2 );
			
			for( unsigned i = 0; i < tiles.size(); i++ )
			{
				if( chosen != i )	tiles[ i ]->setAlpha( 0xFF /3 );
				window->draw( tiles[ i ]->get() );
				tiles[ i ]->setScale( old_scale_x, old_scale_y );
			}
		}
		else if( which == OBJECT )
		{
			objects[ 0 ]->setScale( scale_x, scale_y );
			objects[ 0 ]->setPosition( start_x -objects[ 0 ]->getWidth() /2, start_y );
			for( unsigned i = 1; i < objects.size(); i++ )
			{
				objects[ i ]->setScale( scale_x, scale_y );
				objects[ i ]->setPosition( start_x -objects[ i ]->getWidth() /2, objects[ i -1 ]->getBot() +gap );
			}
			
			arrow.setPosition( objects[ chosen ]->getRight(), objects[ chosen ]->getY() +objects[ chosen ]->getHeight()/2 -arrow.getHeight()/2 );
			
			for( unsigned i = 0; i < objects.size(); i++ )
			{
				if( chosen != i )	objects[ i ]->setAlpha( 0xFF /3 );
				window->draw( objects[ i ]->get() );
				objects[ i ]->setScale( old_scale_x, old_scale_y );
				objects[ i ]->setAlpha( 0xFF );
			}
		}
		else if( which == FOE )
		{
			foes[ 0 ]->setScale( scale_x, scale_y );
			foes[ 0 ]->setPosition( start_x -foes[ 0 ]->getWidth() /2, start_y );
			for( unsigned i = 1; i < foes.size(); i++ )
			{
				foes[ i ]->setScale( scale_x, scale_y );
				foes[ i ]->setPosition( start_x -foes[ i ]->getWidth() /2, foes[ i -1 ]->getBot() +gap );
			}
			
			arrow.setPosition( foes[ chosen ]->getRight(), foes[ chosen ]->getY() +foes[ chosen ]->getHeight()/2 -arrow.getHeight()/2 );
			
			for( unsigned i = 0; i < foes.size(); i++ )
			{
				if( chosen != i )	foes[ i ]->setAlpha( 0xFF /3 );
				window->draw( foes[ i ]->get() );
				foes[ i ]->setScale( old_scale_x, old_scale_y );
				foes[ i ]->setAlpha( 0xFF );
			}
		}
		
		window->draw( arrow.get() );
	}
}

void Tiles_editor::drawLines( sf::RenderWindow* &window )
{
	if( !isrubbishon )
	{
		// Draw lines.
		sf::RectangleShape line;
		line.setFillColor( sf::Color( 0xFF, 0xFF, 0xFF, 0xFF/3 ) );
		
		line.setSize( sf::Vector2f( screen_w, 1 ) );
		line.setPosition( sf::Vector2f( 0, mouse_y ) );
		window->draw( line );
		
		line.setSize( sf::Vector2f( 1, screen_h ) );
		line.setPosition( sf::Vector2f( mouse_x, 0 ) );
		window->draw( line );
		
		float mynewx = mouse_x;
		if( grid )
		{	
			line.setSize( sf::Vector2f( screen_w, 1 ) );
			line.setPosition( sf::Vector2f( 0, mouse_y +width ) );
			window->draw( line );
			
			line.setSize( sf::Vector2f( 1, screen_h ) );
			line.setPosition( sf::Vector2f( mouse_x +width, 0 ) );
			window->draw( line );
			
			mynewx += width;
		}
		
		mouseInfo.setText( "X: " +con::itos( static_cast <int> (mouse_x -additional_x) ) +"  Y: " +con::itos( static_cast <int> (mouse_y -additional_y) ) );
		mouseInfo.setPosition( mynewx, mouse_y -mouseInfo.getHeight() *1.5 );
		window->draw( mouseInfo.get() );
	}
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
		vector <Block> finalblocks;
		
		// Sort by x but keep which sequence!
		int counter = 0;
		vector <Block> myblocks;
		for( unsigned i = 0; i < blocks.size(); i++ )
		{
			if( counter != blocks[ i ].w || i == blocks.size() -1 )
			{
				if( i == blocks.size() -1 )
				{
					myblocks.push_back( blocks[ i ] );
				}
				
				// Sort by x.
				sort( myblocks.begin(), myblocks.end(), []( const Block& a, const Block& b ) { return a.x < b.x; } );
				
				finalblocks.insert( finalblocks.end(), myblocks.begin(), myblocks.end() );
				myblocks.clear();
				counter ++;
			}
			
			myblocks.push_back( blocks[ i ] );
		}
		myblocks.clear();
		
		// Sort by x but foeblocks.
		sort( foeblocks.begin(), foeblocks.end(), []( const Block& a, const Block& b ) { return a.x < b.x; } );
		finalblocks.insert( finalblocks.end(), foeblocks.begin(), foeblocks.end() );
		
		
		// Write to file.
		file.get() << "adriqun" << "|";	// Author.
		file.get() << screen_w << "|";
		file.get() << screen_h << "|";
		
		// printf( "%d\n", finalblocks.size() );
		
		for( unsigned i = 0; i < finalblocks.size(); i++ )
		{
			file.get() << static_cast <int> ( finalblocks[ i ].w ) << ".";
			file.get() << static_cast <int> ( finalblocks[ i ].n ) << ".";
			file.get() << finalblocks[ i ].x << ".";
			file.get() << finalblocks[ i ].y << "|";
		}
		
		// Clear.
		finalblocks.clear();
	}
	file.free();
}

void Tiles_editor::load( string path )
{
	// Clear.
	clearVector();
	
	// Set additional x as 0.
	additional_x = 0;
	additional_y = 0;
	
	MyFile file;
	file.load( "txt/worlds/world_.txt" );
	if( file.is_good() )
	{
		// Line and bufor.
		string line = "";
		string bufor = "";
		unsigned start = 0;
		
		// Getline.
		getline( file.get(), line );
		
		
		// AUTHOR --------------------------------------------------------------------------
		for( unsigned i = start; i < line.size(); i++ )
		{
			if( line[ i ] == '|' )
			{
				start = i +1;
				// printf( "%s\n", bufor.c_str() );
				bufor = "";
				break;
			}
			
			bufor += line[ i ];
		}
		
		
		// MULTIPLIERS --------------------------------------------------------------------------
		float x_multiplier = 1;
		float y_multiplier = 1;
		
		// Set x_multiplier.
		for( unsigned i = start; i < line.size(); i++ )
		{
			if( line[ i ] == '|' )
			{
				start = i +1;
				x_multiplier = screen_w /con::stof( bufor );
				bufor = "";
				break;
			}
			
			bufor += line[ i ];
		}
		// printf( "%f\n", x_multiplier );
		
		// Set y_multiplier.
		for( unsigned i = start; i < line.size(); i++ )
		{
			if( line[ i ] == '|' )
			{
				start = i +1;
				y_multiplier = screen_h /con::stof( bufor );
				bufor = "";
				break;
			}
			
			bufor += line[ i ];
		}
		// printf( "%f\n", y_multiplier );
		
		
		// FS --------------------------------------------------------------------------
		for( unsigned i = start; i < line.size(); i++ )
		{
			if( line[ i ] == '|' )
			{
				bufor += ".";
				string nrstr = "";
				vector <string> data;
				
				for( unsigned j = 0; j < bufor.size(); j++ )
				{
					if( bufor[ j ] == '.' )
					{
						data.push_back( nrstr );
						nrstr = "";
					}
					else
					{
						nrstr += bufor[ j ];
					}
				}
				
				sf::Uint8 w = con::stoi( data[ 0 ] );
				sf::Uint8 t = con::stoi( data[ 1 ] );
				float x = con::stoi( data[ 2 ] ) *x_multiplier;
				float y = con::stoi( data[ 3 ] ) *y_multiplier;
				
				if( w == FOE )
				{
					foeblocks.push_back( Block( w, t, x, y ) );
				}
				else
				{
					blocks.push_back( Block( w, t, x, y ) );
				}
				
				// Clear.
				bufor = "";
			}
			else
			{
				bufor += line[ i ];
			}
		}
	}
	file.free();
}



void Tiles_editor::resetChosen()
{
	which = -1;
	chosen = 0;
}

void Tiles_editor::clearVector()
{
	if( !blocks.empty() )
	{
		blocks.clear();
	}
	
	if( !foeblocks.empty() )
	{
		foeblocks.clear();
	}
}

void Tiles_editor::deleteOne()
{
	float newX = mouse_x -additional_x;
	float newY = mouse_y -additional_y;
	
	int collision = -1;
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		if( blocks[ i ].w == TILE )
		{
			tiles[ blocks[ i ].n ]->setPosition( blocks[ i ].x, blocks[ i ].y );
			if( tiles[ blocks[ i ].n ]->checkCollision( newX, newY ) )
			{
				collision = i;
			}
		}
		else if( blocks[ i ].w == UNVISIBLE_TILE )
		{
			tiles[ blocks[ i ].n ]->setPosition( blocks[ i ].x, blocks[ i ].y );
			if( tiles[ blocks[ i ].n ]->checkCollision( newX, newY ) )
			{
				collision = i;
			}
		}
		else if( blocks[ i ].w == OBJECT )
		{
			objects[ blocks[ i ].n ]->setPosition( blocks[ i ].x, blocks[ i ].y );
			if( objects[ blocks[ i ].n ]->checkCollision( newX, newY ) )
			{
				collision = i;
			}
		}
		else if( blocks[ i ].w == COIN )
		{
			coin.setPosition( blocks[ i ].x, blocks[ i ].y );
			if( coin.checkCollision( newX, newY ) )
			{
				collision = i;
			}
		}
	}
	
	if( collision != -1 )
	{
		blocks.erase( blocks.begin() +collision );
	}
	else
	{
		for( unsigned i = 0; i < foeblocks.size(); i++ )
		{
			foes[ foeblocks[ i ].n ]->setPosition( foeblocks[ i ].x, foeblocks[ i ].y );
			if( foes[ foeblocks[ i ].n ]->checkCollision( newX, newY ) )
			{
				collision = i;
			}
		}
		
		if( collision != -1 )
		{
			foeblocks.erase( foeblocks.begin() +collision );
		}
	}
}