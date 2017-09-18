#include "tiles_editor.h"
#include "own/file.h"
#include <iomanip>

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
	
	type = -1;
	chosen = 0;
	mouse_x = -1;
	mouse_y = -1;
	
	hatchFoeVisible.free();
	
	mouseInfo.free();
	arrow.free();
	
	width = 0;
	grid = false;
	
	additional_x = 0;
	additional_y = 0;
	
	knight.free();
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

void Tiles_editor::reset()
{
	grid = false;
	type = -1;
	chosen = 0;
}



void Tiles_editor::load( float screen_w, float screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	float scale_x = screen_w /2560;
	float scale_y = screen_h /1440;
	
	hatchFoeVisible.load( screen_w, screen_h );
	
	mouseInfo.setIdentity( "tiles_editor-mouseInfo" );
	mouseInfo.setFont( "fonts/jcandlestickextracond.ttf" );
	mouseInfo.setText( " " );
	mouseInfo.setSize( screen_h /42 );
	mouseInfo.setAlpha( 0xFF /2 );
	
	arrow.setIdentity( "tiles_editor-arrow" );
	arrow.load( "images/editor/left_arrow.png" );
	arrow.setScale( scale_x /2, scale_y /2 );
	
	knight.setIdentity( "tiles_editor-knight" );
	knight.load( "images/play/knight/0.png", 10 );
	knight.setScale( 0.5, 0.5 );
	knight.setAlpha( 0xFF /2 );
	
	coin.setIdentity( "tiles_editor-coin" );
	coin.load( "images/play/coin.png", 7 );
	coin.setScale( 0.5, 0.5 );
	
	for( unsigned i = 0; i < 17; i++ )
	{
		tiles.push_back( new MySprite() );
		tiles[ tiles.size() -1 ]->setIdentity( "tiles_editor-tiles" );
		tiles[ tiles.size() -1 ]->load( "images/play/tiles/" +con::itos( i ) +".png" );
		tiles[ tiles.size() -1 ]->setScale( 0.5, 0.5 );
	}
	
	for( unsigned i = 0; i < 14; i++ )
	{
		objects.push_back( new MySprite() );
		objects[ objects.size() -1 ]->setIdentity( "tiles_editor-objects" );
		objects[ objects.size() -1 ]->load( "images/play/objects/" +con::itos( i ) +".png" );
		objects[ objects.size() -1 ]->setScale( 0.5, 0.5 );
	}
	
	for( unsigned i = 0; i < 3; i++ )
	{
		foes.push_back( new MySprite() );
		foes[ foes.size() -1 ]->setIdentity( "tiles_editor-foes" );
	}
	foes[ 0 ]->load( "images/play/foes/skeleton/1.png", 6 );
	foes[ 0 ]->setScale( 0.5, 0.5 );
	foes[ 1 ]->load( "images/play/foes/vampire/1.png", 8 );
	foes[ 1 ]->setScale( 0.5, 0.5 );
	foes[ 2 ]->load( "images/play/foes/zombie/1.png", 6 );
	foes[ 2 ]->setScale( 0.5, 0.5 );
	
	// Set width.
	width = tiles[ 0 ]->getWidth() /2;
}

void Tiles_editor::handle( sf::Event& event )
{
	if( event.type == sf::Event::MouseMoved )
	{
		mouse_x = event.mouseMove.x;
		mouse_y = event.mouseMove.y;
		
		griding();
	}
	
	hatchFoeVisible.handle( event );
	if( !hatchFoeVisible.isVisible() )
	{
		if( event.type == sf::Event::KeyPressed && !isrubbishon )
		{
			int code = event.key.code;
			
			int size = 0;
			if( type == TILE || type == UNVISIBLE_TILE )	size = tiles.size();
			else if( type == OBJECT )						size = objects.size();
			else if( type == FOE )							size = foes.size();
				
				
			if( code == sf::Keyboard::Space )
			{
				put();
			}
			
			// CHANGING CHOSEN ----------------------------------------
			else if( code == sf::Keyboard::X )						chosen /= 2;
			else if( code == sf::Keyboard::C && chosen < size -1 )	chosen ++;
			else if( code == sf::Keyboard::Z && chosen > 0 )		chosen --;
			
			
			// CHANGING TYPE ----------------------------------------
			if( code == sf::Keyboard::S )
			{
				type = -1;
				chosen = 0;
			}
			else if( code == sf::Keyboard::D && type < AMOUNT -1 )
			{
				type ++;
				chosen = 0;
			}
			else if( code == sf::Keyboard::A && type > -1 )
			{
				type --;
				chosen = 0;
			}
			
			if( type == -1 )
			{
				grid = false;
			}
			
			if( type == TILE || type == UNVISIBLE_TILE )	grid = true;
			else if( type == OBJECT )						grid = false;
			else if( type == COIN )							grid = true;
			else if( type == FOE )							grid = false;
		}
		
		
		if( event.type == sf::Event::MouseButtonPressed )
		{
			mouse_x = event.mouseButton.x;
			mouse_y = event.mouseButton.y;
			
			if( event.mouseButton.button == sf::Mouse::Left )
			{
				put();
				
				if( hatchFoeVisible.getType() != -1 )
				{
					int myType = hatchFoeVisible.getType();
					hatchFoeVisible.setType( -1 );
					foeblocks[ myType ].armour = hatchFoeVisible.getArmour();
					foeblocks[ myType ].damage = hatchFoeVisible.getDamage();
					foeblocks[ myType ].velocity = hatchFoeVisible.getVelocity();
					foeblocks[ myType ].heartpoints = hatchFoeVisible.getHeartpoints();
				}
			}
			else if( event.mouseButton.button == sf::Mouse::Right )
			{
				for( unsigned i = 0; i < foeblocks.size(); i++ )
				{
					int n = foeblocks[ i ].n;
					float x = foeblocks[ i ].x -additional_x;
					float y = foeblocks[ i ].y -additional_y;
			
					foes[ n ]->setPosition( x, y );
					if( foes[ n ]->checkCollision( mouse_x, mouse_y ) )
					{
						hatchFoeVisible.setFeatures( foeblocks[ i ].armour, foeblocks[ i ].damage, foeblocks[ i ].velocity, foeblocks[ i ].heartpoints );
						hatchFoeVisible.setPosition( x +foes[ n ]->getWidth()/2, y );
						hatchFoeVisible.setType( i );
						break;
					}
				}
			}
		}
	}
}

void Tiles_editor::draw( sf::RenderWindow* &window )
{
	knight.setPosition( screen_w /256 +additional_x, screen_h -width*2 -knight.getHeight() +additional_y );
	window->draw( knight.get() );
	
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
		if( type == TILE )
		{
			if( chosen < static_cast <int> (tiles.size()) )
			{
				tiles[ chosen ]->setPosition( mouse_x, mouse_y );
				tiles[ chosen ]->setAlpha( 0xFF );
				window->draw( tiles[ chosen ]->get() );
			}
		}
		else if( type == UNVISIBLE_TILE )
		{
			if( chosen < static_cast <int> (tiles.size()) )
			{
				tiles[ chosen ]->setPosition( mouse_x, mouse_y );
				tiles[ chosen ]->setAlpha( 0xFF /2 );
				window->draw( tiles[ chosen ]->get() );
			}
		}
		else if( type == OBJECT )
		{
			if( chosen < static_cast <int> (objects.size()) )
			{
				objects[ chosen ]->setPosition( mouse_x, mouse_y );
				window->draw( objects[ chosen ]->get() );
			}
		}
		else if( type == COIN )
		{
			coin.setPosition( mouse_x, mouse_y );
			window->draw( coin.get() );
		}
		else if( type == FOE )
		{
			if( chosen < static_cast <int> (foes.size()) )
			{
				foes[ chosen ]->setPosition( mouse_x, mouse_y );
				window->draw( foes[ chosen ]->get() );
			}
		}
	}
	
	hatchFoeVisible.draw( window );
	
	drawTumbnails( window );
	drawLines( window );
}

void Tiles_editor::drawTumbnails( sf::RenderWindow* &window )
{
	// Draw thumbnails.
	if( chosen > -1 && type > -1 && type != COIN )
	{
		float start_x = 36;
		float start_y = 100;
		
		float old_scale_x = 0.5;
		float old_scale_y = 0.5;
		float scale_x = screen_w /5120;
		float scale_y = screen_h /2880;
		float gap = screen_h /144;
		
		if( type == TILE || type == UNVISIBLE_TILE )
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
				if( chosen != static_cast <int> (i) )	tiles[ i ]->setAlpha( 0xFF /3 );
				else									tiles[ i ]->setAlpha( 0xFF );
				window->draw( tiles[ i ]->get() );
				tiles[ i ]->setScale( old_scale_x, old_scale_y );
			}
		}
		else if( type == OBJECT )
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
				if( chosen != static_cast <int> (i) )	objects[ i ]->setAlpha( 0xFF /3 );
				window->draw( objects[ i ]->get() );
				objects[ i ]->setScale( old_scale_x, old_scale_y );
				objects[ i ]->setAlpha( 0xFF );
			}
		}
		else if( type == FOE )
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
				if( chosen != static_cast <int> (i) )	foes[ i ]->setAlpha( 0xFF /3 );
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
	line.setFillColor( sf::Color( 0xFF, 0xFF, 0xFF, 0xFF/2 ) );
	line.setSize( sf::Vector2f( knight.getWidth() /1.5, 1 ) );
	line.setPosition( sf::Vector2f( knight.getX() +knight.getWidth()/10, knight.getBot() ) );
	window->draw( line );
	
	if( isrubbishon )
	{
		line.setFillColor( sf::Color( 0xFF, 0x00, 0x00, 0xFF/3 ) );
		mouseInfo.setColor( sf::Color::Red );
	}
	else
	{
		line.setFillColor( sf::Color( 0xFF, 0xFF, 0xFF, 0xFF/3 ) );
		mouseInfo.setColor( sf::Color::White );
	}
	
	line.setSize( sf::Vector2f( screen_w, 1 ) );
	line.setPosition( sf::Vector2f( 0, mouse_y ) );
	window->draw( line );
	
	line.setSize( sf::Vector2f( 1, screen_h ) );
	line.setPosition( sf::Vector2f( mouse_x, 0 ) );
	window->draw( line );
	
	float mynewx = mouse_x +width/10;
	if( grid && !isrubbishon )
	{	
		line.setSize( sf::Vector2f( screen_w, 1 ) );
		line.setPosition( sf::Vector2f( 0, mouse_y +width*2 ) );
		window->draw( line );
		
		line.setSize( sf::Vector2f( 1, screen_h ) );
		line.setPosition( sf::Vector2f( mouse_x +width*2, 0 ) );
		window->draw( line );
		
		// Support.
		line.setSize( sf::Vector2f( 1, width ) );
		line.setPosition( sf::Vector2f( mouse_x +width, mouse_y -width/2 ) );
		window->draw( line );
		
		line.setSize( sf::Vector2f( width, 1 ) );
		line.setPosition( sf::Vector2f( mouse_x -width/2, mouse_y +width ) );
		window->draw( line );
		
		mynewx += width*2;
	}
	
	mouseInfo.setText( "X: " +con::itos( static_cast <int> (mouse_x -additional_x) ) +"  Y: " +con::itos( (static_cast <int> (mouse_y -additional_y -screen_h))*-1 ) );
	mouseInfo.setPosition( mynewx, mouse_y -mouseInfo.getHeight() *1.5 );
	window->draw( mouseInfo.get() );
}



void Tiles_editor::setRubbish( bool rubbish )
{
	this->isrubbishon = rubbish;
}

void Tiles_editor::put()
{
	if( chosen > -1 && type > -1 && !isrubbishon )
	{
		griding();
		
		if( type == FOE )
		{
			lastwasfoe = true;
			foeblocks.push_back( HatchFoe( type, chosen, mouse_x -additional_x, mouse_y -additional_y ) );
		}
		else
		{
			lastwasfoe = false;
			blocks.push_back( Block( type, chosen, mouse_x -additional_x, mouse_y -additional_y ) );
		}
	}
	
	if( isrubbishon )
	{
		deleteOne();
	}
}



void Tiles_editor::setAdditionalX( float newX )
{
	this->additional_x = newX;
}

void Tiles_editor::setAdditionalY( float newY )
{
	this->additional_y = newY;
}



bool Tiles_editor::getGrid()
{
	return grid;
}

string Tiles_editor::getType()
{
	string line = "None";
	
	if( type == TILE )					line = "Tiles";
	else if( type == UNVISIBLE_TILE )	line = "Unvisible Tiles";
	else if( type == OBJECT )			line = "Landscape";
	else if( type == COIN )				line = "Treasure";
	else if( type == FOE )				line = "Foes";
	
	return line;
}

string Tiles_editor::getChosen()
{
	string line = "";
	
	if( type == TILE || type == UNVISIBLE_TILE )
	{
		switch( chosen )
		{
			case 0: line += "Left Solid Grass"; 			break;
			case 1: line += "Middle Solid Grass"; 			break;
			case 2: line += "Right Solid Grass"; 			break;
			
			case 3: line += "Left Hill Grass"; 				break;
			case 4: line += "Right Hill Grass"; 			break;
			
			case 5: line += "Left Hovering Grass"; 			break;
			case 6: line += "Middle Hovering Grass"; 		break;
			case 7: line += "Right Hovering Grass";			break;
			case 8: line += "Single Hovering Grass"; 		break;
			
			case 9: line += "Left Ground Border"; 			break;
			case 10: line += "Ground";						break;
			case 11: line += "Right Ground Border"; 		break;
			
			case 12: line += "Left Lower Ground Border"; 	break;
			case 13: line += "Middle Lower Ground Border";	break;
			case 14: line += "Right Lower Ground Border"; 	break;
			
			case 15: line += "Left Hill Addition"; 			break;
			case 16: line += "Right Hill Addition";			break;
		}
	}
	else if( type == OBJECT )
	{
		switch( chosen )
		{
			case 0: line += "Skull With Bone"; 		break;
			case 1: line += "Skull"; 				break;
			case 2: line += "Three Bones"; 			break;
			case 3: line += "Two Bones"; 			break;
			
			case 4: line += "Wooden Arrow"; 		break;
			case 5: line += "Wooden Sign"; 			break;
			
			case 6: line += "Round Bush"; 			break;
			case 7: line += "Spiky Bush"; 			break;
			
			case 8: line += "Wooden Chest"; 		break;
			case 9: line += "Bush Without Leaves"; 	break;
			case 10: line += "Tree Without Leaves";	break;
			
			case 11: line += "Remains"; 			break;
			case 12: line += "Tombstone"; 			break;
			case 13: line += "Cross"; 				break;
		}
	}
	else if( type == COIN )
	{
		line = "Coin";
	}
	else if( type == FOE )
	{
		switch( chosen )
		{
			case 0: line += "Skeleton";	 break;
			case 1: line += "Vampire";	 break;
			case 2: line += "Zombie";	 break;
		}
	}
	else
	{
		line = "None";
	}
	
	return line;
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
		
		// Sort by x but keep type sequence!
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
		
		if( !foeblocks.empty() )
		{
			// Sort by x but foeblocks.
			sort( foeblocks.begin(), foeblocks.end(), []( const HatchFoe& a, const HatchFoe& b ) { return a.x < b.x; } );
		}
		
		// Write to file.
		file.get() << "adriqun" << "|";	// Author.
		file.get() << screen_w << "|";
		file.get() << screen_h << "|";
		
		// printf( "%d\n", finalblocks.size() );
		
		for( unsigned i = 0; i < finalblocks.size(); i++ )
		{
			file.get() << static_cast <int> ( finalblocks[ i ].w ) << "*";
			file.get() << static_cast <int> ( finalblocks[ i ].n ) << "*";
			file.get() << std::fixed << std::setprecision( 2 ) << finalblocks[ i ].x << "*";
			file.get() << std::fixed << std::setprecision( 2 ) << finalblocks[ i ].y << "|";
		}
		
		for( unsigned i = 0; i < foeblocks.size(); i++ )
		{
			file.get() << static_cast <int> ( foeblocks[ i ].w ) << "*";
			file.get() << static_cast <int> ( foeblocks[ i ].n ) << "*";
			file.get() << std::fixed << std::setprecision( 2 ) << foeblocks[ i ].x << "*";
			file.get() << std::fixed << std::setprecision( 2 ) << foeblocks[ i ].y << "*";
			file.get() << std::fixed << std::setprecision( 2 ) << foeblocks[ i ].armour << "*";
			file.get() << std::fixed << std::setprecision( 2 ) << foeblocks[ i ].damage << "*";
			file.get() << std::fixed << std::setprecision( 2 ) << foeblocks[ i ].velocity << "*";
			file.get() << std::fixed << std::setprecision( 2 ) << foeblocks[ i ].heartpoints;
			for( unsigned j = 0; j < foeblocks[ i ].texts.size(); j++ )
			{
				file.get() << "*";
				file.get() << foeblocks[ i ].texts[ j ];
			}
			file.get() << "|";
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
	file.load( "txt/worlds/" +path +".txt" );
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
		
		
		// NEW SIZES --------------------------------------------------------------------------
		float my_screen_w = 0;
		float my_screen_h = 0;
		
		// Set my_screen_w.
		for( unsigned i = start; i < line.size(); i++ )
		{
			if( line[ i ] == '|' )
			{
				start = i +1;
				my_screen_w = screen_w -con::stof( bufor );
				bufor = "";
				break;
			}
			
			bufor += line[ i ];
		}
		
		// Set my_screen_h.
		for( unsigned i = start; i < line.size(); i++ )
		{
			if( line[ i ] == '|' )
			{
				start = i +1;
				my_screen_h = screen_h -con::stof( bufor );
				bufor = "";
				break;
			}
			
			bufor += line[ i ];
		}
		
		
		// FS --------------------------------------------------------------------------
		for( unsigned i = start; i < line.size(); i++ )
		{
			if( line[ i ] == '|' )
			{
				bufor += "*";
				string nrstr = "";
				vector <string> data;
				
				for( unsigned j = 0; j < bufor.size(); j++ )
				{
					if( bufor[ j ] == '*' )
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
				float x = con::stoi( data[ 2 ] );
				float y = con::stoi( data[ 3 ] ) +my_screen_h;
				
				if( w == FOE )
				{
					foeblocks.push_back( HatchFoe( w, t, x, y ) );
					
					// Features.
					foeblocks[ foeblocks.size() -1 ].armour = con::stoi( data[ 4 ] );
					foeblocks[ foeblocks.size() -1 ].damage = con::stoi( data[ 5 ] );
					foeblocks[ foeblocks.size() -1 ].velocity = con::stoi( data[ 6 ] );
					foeblocks[ foeblocks.size() -1 ].heartpoints = con::stoi( data[ 7 ] );
					
					// Texts.
					for( unsigned i = 8; i < data.size(); i++ )
					{
						foeblocks[ foeblocks.size() -1 ].texts.push_back( data[ i ] );
					}
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
	else
	{
		save( path );
	}
	file.free();
}




void Tiles_editor::griding()
{
	// Grid works.
	if( grid && !isrubbishon )
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