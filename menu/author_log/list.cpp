#include "list.h"
#include "file/file.h"

List::List()
{
	free();
}

List::~List()
{
	free();
}

void List::free()
{
	if( !categories.empty() )
	{
		for( auto &it :categories )
		{
			it->free();
		}
		
		categories.clear();
	}
	
	if( !categories_x.empty() )
	{
		categories_x.clear();
	}
	
	button.free();
	
	freeMembers( develop_members );
	freeMembers( music_members );
	freeMembers( chunk_members );
	freeMembers( sprite_members );
	freeMembers( font_members );
	freeMembers( tool_members );
}

void List::reset()
{
	for( unsigned i = 0; i < categories.size(); i++ )
	{
		categories[ i ]->setPosition( categories_x[ i ], categories[ i ]->getY() );
	}
	
	resetMembers( develop_members );
	resetMembers( music_members );
	resetMembers( chunk_members );
	resetMembers( sprite_members );
	resetMembers( font_members );
	resetMembers( tool_members );
}



void List::load( int screen_w, int screen_h )
{
	free();
	
	// Load button.
	button.setName( "list-button" );
	button.load( "data/menu/info.png", 4 );
	
	// Setting main x.
	int start_x = 50;
	categories_x.push_back( start_x );
	categories_x.push_back( start_x );
	categories_x.push_back( start_x );
	categories_x.push_back( start_x +screen_w/2 );
	categories_x.push_back( start_x +screen_w );
	categories_x.push_back( start_x +screen_w );
	
	// Setting texts -categories
	MyFile file;
	file.load( "data/txt/menu/authors_categories.txt" );
	if( file.is_good() )
	{
		string line;
		while( file.get() >> line )
		{
			categories.push_back( new MyText() );
			categories[ categories.size() -1 ]->setName( "list-category" );
			categories[ categories.size() -1 ]->setFont( "data/initialization/Jaapokki-Regular.otf", 40, 0xFF, 0xFF, 0xFF );
			categories[ categories.size() -1 ]->setText( line );
		}
	}
	file.free();
	categories[ 0 ]->setPosition( categories_x[ 0 ], 180 );
	categories[ 1 ]->setPosition( categories_x[ 1 ], 320 );
	categories[ 2 ]->setPosition( categories_x[ 2 ], 440 );
	categories[ 3 ]->setPosition( categories_x[ 3 ], 180 );
	categories[ 4 ]->setPosition( categories_x[ 4 ], 180 );
	categories[ 5 ]->setPosition( categories_x[ 5 ], 360 );
	
	// Load developers txt file.
	fillMembers( develop_members, "data/txt/menu/developers.txt", 0 );
	
	// Load music txt file.
	fillMembers( music_members, "data/txt/menu/music.txt", 1 );
	
	// Load chunk txt file.
	fillMembers( chunk_members, "data/txt/menu/chunks.txt", 2 );
	
	// Load sprite txt file.
	fillMembers( sprite_members, "data/txt/menu/sprite.txt", 3 );
	
	// Load font txt file.
	fillMembers( font_members, "data/txt/menu/font.txt", 4 );
	
	// Load tool txt file.
	fillMembers( tool_members, "data/txt/menu/tool.txt", 5 );
}

void List::draw( sf::RenderWindow* &window )
{
	for( auto &it :categories )
	{
		window->draw( it->get() );
	}
	
	drawMembers( develop_members, window );
	drawMembers( music_members, window );
	drawMembers( chunk_members, window );
	drawMembers( sprite_members, window );
	drawMembers( font_members, window );
	drawMembers( tool_members, window );
}

void List::handle( sf::Event &event )
{
	handleMembers( music_members, event );
	handleMembers( chunk_members, event );
	handleMembers( sprite_members, event );
	handleMembers( font_members, event );
	handleMembers( tool_members, event );
}



void List::fadein( int i, int max )
{
	button.fadein( i, max );
	
	for( auto &it :categories )
	{
		it->fadein( i, max );
	}
	
	fadeinMembers( develop_members, i, max );
	fadeinMembers( music_members, i, max );
	fadeinMembers( chunk_members, i, max );
	fadeinMembers( sprite_members, i, max );
	fadeinMembers( font_members, i, max );
	fadeinMembers( tool_members, i, max );
}

void List::fadeout( int i, int min )
{
	button.fadeout( i, min );
	
	for( auto &it :categories )
	{
		it->fadeout( i, min );
	}
	
	fadeoutMembers( develop_members, i, min );
	fadeoutMembers( music_members, i, min );
	fadeoutMembers( chunk_members, i, min );
	fadeoutMembers( sprite_members, i, min );
	fadeoutMembers( font_members, i, min );
	fadeoutMembers( tool_members, i, min );
}



void List::move( float distance )
{
	for( unsigned i = 0; i < categories.size(); i++ )
	{
		categories[ i ]->setPosition( categories_x[ i ] +distance, categories[ i ]->getY() );
	}
	
	moveMembers( develop_members, distance );
	moveMembers( music_members, distance );
	moveMembers( chunk_members, distance );
	moveMembers( sprite_members, distance );
	moveMembers( font_members, distance );
	moveMembers( tool_members, distance );
}



void List::freeMembers( vector <Member*> &m )
{
	if( !m.empty() )
	{
		for( auto &it :m )
		{
			it->free();
		}
		
		m.clear();
	}
}

void List::resetMembers( vector <Member*> &m )
{
	for( auto &it :m )
	{
		it->reset();
	}
}

void List::fillMembers( vector <Member*> &m, string path, int which )
{
	MyFile file;
	file.load( path );
	if( file.is_good() )
	{
		string line;
		while( getline( file.get(), line ) )
		{
			string name = "";
			bool flag = false;
			string url = "";
			
			for( unsigned i = 0; i < line.size(); i++ )
			{
				if( line[ i ] == '#' )
				{
					if( line[ i +1 ] == '0' )
					{
						flag = false;
					}
					else if( line[ i +1 ] == '1' )
					{
						flag = true;
						
						for( unsigned j = i +2; j < line.size(); j++ )
						{
							url += line[ j ];
						}
					}
					
					break;
				}
				
				name += line[ i ];
			}
			
			m.push_back( new Member() );
			
			if( !flag )	m[ m.size() -1 ]->load( name );
			else		m[ m.size() -1 ]->load( name, flag, url );
			
			int start_y = 0;
			if( m.size() > 1 )
				start_y = m[ m.size() -2 ]->getY() +45;
			else
				start_y = categories[ which ]->getBot() +20;
			m[ m.size() -1 ]->setPosition( categories_x[ which ] +5, start_y );
		}
	}
	file.free();
}

void List::drawMembers( vector <Member*> &m, sf::RenderWindow* &window )
{
	for( auto &it :m )
	{
		it->draw( window );
		if( it->isButton() )
		{
			button.setPosition( it->getButtonX(), it->getButtonY() );
			button.setOffset( it->getOffset() );
			window->draw( button.get() );
		}
	}
}

void List::handleMembers( vector <Member*> &m, sf::Event &event )
{
	for( auto &it :m )
	{
		it->getOffset() = 0;
	}
	
	int x, y;

	if( event.type == sf::Event::MouseMoved )
	{
		x = event.mouseMove.x;
		y = event.mouseMove.y;
		
		for( auto &it :m )
		{
			button.setPosition( it->getButtonX(), it->getButtonY() );
			
			if( button.checkCollision( x, y ) )
			{
				it->getOffset() = 1;
			}
			else
			{
				it->getFocus() = false;
			}
		}
	}

	if( event.type == sf::Event::MouseButtonPressed )
	{
		x = event.mouseButton.x;
		y = event.mouseButton.y;
		
		for( auto &it :m )
		{
			button.setPosition( it->getButtonX(), it->getButtonY() );
			
			if( button.checkCollision( x, y ) )
			{
				it->getOffset() = 2;
				it->getFocus() = true;
				
				string command = "sensible-browser ";
				command += it->getURL();
				system( command.c_str() );
			}
		}
	}
		
	if( event.type == sf::Event::MouseButtonReleased )
	{
		for( auto &it :m )
		{
			it->getFocus() = false;
		}
	}
	
	for( auto &it :m )
	{
		if( it->getFocus() )
		{
			it->getOffset() = 2;
		}
	}
}

void List::moveMembers( vector <Member*> &m, float distance )
{
	for( auto &it :m )
	{
		it->move( distance );
	}
}

void List::fadeinMembers( vector <Member*> &m, int i, int max )
{
	for( auto &it :m )
	{
		it->fadein( i, max );
	}
}

void List::fadeoutMembers( vector <Member*> &m, int i, int min )
{
	for( auto &it :m )
	{
		it->fadeout( i, min );
	}
}