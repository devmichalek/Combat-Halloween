#include "worldtable.h"
#include "own/file.h"

Star::Star()
{
	free();
}

Star::~Star()
{
	free();
}

void Star::free()
{
	gold = 0;
	silver = 0;
	x_medal = false;
	coin_medal = false;
	star_medal = false;
}




Worldtable::Worldtable()
{
	free();
}

Worldtable::~Worldtable()
{
	free();
}

void Worldtable::free()
{
	screen_w = 0;
	screen_h = 0;
	username = "adriqun";
	
	left.free();
	right.free();
	
	click.free();
	thread.free();
	
	information.free();
	reloadbutton.free();
	
	gold_star.free();
	silver_star.free();
	x_medal.free();
	coin_medal.free();
	star_medal.free();
	
	ready = 0;
	chosen = -1;
	text_nr.free();
	sprite.free();
	
	if( !stars.empty() )
	{
		for( auto &it :stars )
		{
			it.free();
		}
		
		stars.clear();
	}
	
	if( !locks.empty() )
	{
		locks.clear();
	}
	
	if( !positions.empty() )
	{
		positions.clear();
	}
}

void Worldtable::reset()
{
	chosen = -1;
}

void Worldtable::load( float screen_w, float screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	float x_scale = screen_w /2560;
	float y_scale = screen_h /1440;
	
	
	left.setIdentity( "worldtable-left" );
	left.load( "images/level/left.png", 3 );
	left.setScale( x_scale, y_scale );
	left.setPosition( screen_w/256, screen_h/2 -left.getHeight()/2 );
	
	right.setIdentity( "worldtable-right" );
	right.load( "images/level/right.png", 3 );
	right.setScale( x_scale, y_scale );
	right.setPosition( screen_w -right.getWidth() -screen_w/256, screen_h/2 -right.getHeight()/2 );
	
	
	click.setIdentity( "worldtable-click" );
	click.load( "sounds/click.wav" );
	
	
	information.setIdentity( "worldtable-information" );
	information.setFont( "fonts/jcandlestickextracond.ttf" );
	information.setText( "loading..." );
	information.setColor( sf::Color( 0, 0, 0 ) );
	information.setSize( screen_h /28 );
	
	reloadbutton.setIdentity( "worldtable-reloadbutton" );
	reloadbutton.load( "images/menu/reload.png", 3 );
	reloadbutton.setScale( x_scale, y_scale );
	
	
	gold_star.setIdentity( "worldtable-gold_star" );
	gold_star.load( "images/level/gold_star.png" );
	gold_star.setScale( x_scale, y_scale );
	
	silver_star.setIdentity( "worldtable-silver_star" );
	silver_star.load( "images/level/silver_star.png" );
	silver_star.setScale( x_scale, y_scale );
	
	x_medal.setIdentity( "worldtable-x_medal" );
	x_medal.load( "images/level/x_medal.png" );
	x_medal.setScale( x_scale, y_scale );
	
	coin_medal.setIdentity( "worldtable-coin_medal" );
	coin_medal.load( "images/level/c_medal.png" );
	coin_medal.setScale( x_scale, y_scale );
	
	star_medal.setIdentity( "worldtable-star_medal" );
	star_medal.load( "images/level/s_medal.png" );
	star_medal.setScale( x_scale, y_scale );
	
	text_nr.setIdentity( "worldtable-text_nr" );
	text_nr.setFont( "fonts/Jaapokki-Regular.otf" );
	text_nr.setSize( screen_h /28 );
	text_nr.setColor( sf::Color( 0xDD, 0xDD, 0xDD ) );
	
	sprite.setIdentity( "worldtable-sprite" );
	sprite.load( "images/level/level.png", 3 );
	sprite.setScale( x_scale, y_scale );
}

void Worldtable::handle( sf::Event& event )
{
	if( event.type == sf::Event::MouseButtonPressed )
	{
		if( event.mouseButton.button == sf::Mouse::Left )
		{
			float x = event.mouseButton.x;
			float y = event.mouseButton.y;
			
			if( ready < 2 && thread.t == NULL ) // We can click reload button.
			{
				if( reloadbutton.checkCollisionCircle( x, y ) )
				{
					click.play();
					reloadbutton.setOffset( 1 );
					setThread();
				}
			}
			else
			{
				bool immunity = false;
				
				// chosing world
				if( !positions.empty() )
				{
					for( unsigned i = 0; i < positions.size(); i++ )
					{
						if( !locks[ i ] )
						{
							if( positions[ i ].x > 0 && positions[ i ].x < screen_w )
							{
								sprite.setPosition( positions[ i ].x, positions[ i ].y );
								if( sprite.checkCollisionCircle( x, y ) )
								{
									chosen = i;
									immunity = true;
									break;
								}
							}
						}
					}
				}
				
				// left
				for( auto &it :positions )
				{
					if( it.x < 0 )
					{
						if( left.checkCollisionCircle( x, y ) )
						{
							click.play();
							left.setOffset( 1 );
							immunity = true;
							
							for( unsigned i = 0; i < positions.size(); i++ )
							{
								positions[ i ].x += screen_w;
							}
						}
						
						break;
					}
				}
				
				// right
				for( auto &it :positions )
				{
					if( it.x > screen_w )
					{
						if( right.checkCollisionCircle( x, y ) )
						{
							click.play();
							right.setOffset( 1 );
							immunity = true;
							
							for( unsigned i = 0; i < positions.size(); i++ )
							{
								positions[ i ].x -= screen_w;
							}
						}
						
						break;
					}
				}
				
				if( !immunity )
				{
					chosen = -1;
				}
			}
		}
	}
	else if( event.type == sf::Event::MouseButtonReleased )
	{
		left.setOffset( 0 );
		right.setOffset( 0 );
		reloadbutton.setOffset( 0 );
	}
}

void Worldtable::draw( sf::RenderWindow* &window )
{
	if( ready < 2 )
	{
		window->draw( information.get() );
		window->draw( reloadbutton.get() );
	}
	else
	{
		// Delete thread if is ready
		if( thread.r )
		{
			thread.reset();
		}
		
		// left
		for( auto &it :positions )
		{
			if( it.x < 0 )
			{
				window->draw( left.get() );
				break;
			}
		}
		
		// right
		for( int i = positions.size() -1; i >= 0; i-- )
		{
			if( positions[ i ].x > screen_w )
			{
				window->draw( right.get() );
				break;
			}
		}
		
		// Draw sprite.
		for( unsigned i = 0; i < positions.size(); i++ )
		{
			if( positions[ i ].x > 0 && positions[ i ].x < screen_w )
			{
				sprite.setPosition( positions[ i ].x, positions[ i ].y );
				
				if( locks[ i ] )											sprite.setOffset( 2 );
				else if( chosen != -1 && static_cast <int> (i) == chosen )	sprite.setOffset( 1 );
				else														sprite.setOffset( 0 );
				window->draw( sprite.get() );
				
				if( !locks[ i ] )
				{
					text_nr.setText( con::itos( i +1 ) );
					float newX = positions[ i ].x +sprite.getWidth()/2 -text_nr.getWidth()/2;
					float newY = positions[ i ].y +sprite.getHeight()/2 -text_nr.getHeight();
					text_nr.setPosition( newX, newY );
					window->draw( text_nr.get() );
				}
			}
		}
		
		// Draw reward.
		if( !stars.empty() )
		{
			for( unsigned i = 0; i < stars.size(); i++ )
			{
				if( positions[ i ].x < 0 || positions[ i ].x > screen_w )
				{
					continue;
				}
				
				if( stars[ i ].gold > 0 )
				{
					for( int j = 0; j < stars[ i ].gold; j++ )
					{
						gold_star.setPosition( positions[ i ].x +gold_star.getWidth()/3 *j, positions[ i ].y -gold_star.getHeight() );
						window->draw( gold_star.get() );
					}
				}
				else if( stars[ i ].silver > 0 )
				{
					for( int j = 0; j < stars[ i ].silver; j++ )
					{
						silver_star.setPosition( positions[ i ].x +silver_star.getWidth()/3 *j, positions[ i ].y -silver_star.getHeight() );
						window->draw( silver_star.get() );
					}
				}
				
				if( stars[ i ].coin_medal )
				{
					coin_medal.setPosition( positions[ i ].x +gold_star.getWidth()*4/3, positions[ i ].y -coin_medal.getHeight() );
					window->draw( coin_medal.get() );
				}
				
				if( stars[ i ].star_medal )
				{
					star_medal.setPosition( positions[ i ].x +gold_star.getWidth()*5/3, positions[ i ].y -star_medal.getHeight() );
					window->draw( star_medal.get() );
				}
				
				if( stars[ i ].x_medal )
				{
					x_medal.setPosition( positions[ i ].x +gold_star.getWidth()*2, positions[ i ].y -x_medal.getHeight() );
					window->draw( x_medal.get() );
				}
			}
		}
	}
}



void Worldtable::fadein( float v, int max )
{
	information.fadein( v, max );
	reloadbutton.fadein( v, max );
	
	if( ready == 2 )
	{
		left.fadein( v, max );
		right.fadein( v, max );
		
		gold_star.fadein( v, max );
		silver_star.fadein( v, max );
		x_medal.fadein( v, max );
		coin_medal.fadein( v, max );
		star_medal.fadein( v, max );
		
		sprite.fadein( v, max );
		text_nr.fadein( v, max );
	}
}

void Worldtable::fadeout( float v, int min )
{
	information.fadeout( v, min );
	reloadbutton.fadeout( v, min );
	
	if( ready == 2 )
	{
		left.fadeout( v, min );
		right.fadeout( v, min );
		
		gold_star.fadeout( v, min );
		silver_star.fadeout( v, min );
		x_medal.fadeout( v, min );
		coin_medal.fadeout( v, min );
		star_medal.fadeout( v, min );
		
		sprite.fadeout( v, min );
		text_nr.fadeout( v, min );
	}
}



int Worldtable::isChosen()
{
	if( chosen != -1 )
	{
		return true;
	}
	
	return false;
}

bool Worldtable::abletoreload()
{
	if( ready < 2 )
	{
		return true;
	}
	
	return false;
}


void Worldtable::setThread()
{
	if( ready < 2 && thread.t == NULL ) // We can click reload button.
	{
		// Setting loading text.
		information.setText( "loading..." );
		information.setColor( sf::Color( 0, 0, 0 ) );
		information.setPosition( screen_w/2 -information.getWidth()/2 -reloadbutton.getWidth()/2 -screen_w/256, screen_h /2.2 );
		reloadbutton.setPosition( information.getRight() +screen_w/256, information.getY() -reloadbutton.getHeight() /3 );
		
		thread.t = new std::thread( Worldtable::setValues, this );
		thread.t->detach();
	}
}

void Worldtable::setValues()
{
	bool success = true;
	if( ready == 0 )
	{
		MyRequest request;
		request.setHttp( "http://adrianmichalek.pl/" );
		request.setRequest( "/combathalloween/getnrworlds.php", sf::Http::Request::Post );
		
		if( !request.sendRequest() )
		{
			success = false;
		}
		else
		{
			string result = request.getResult();
			if( result == "0" )	// error
			{
				success = false;
			}
			else
			{
				int amount = con::stoi( result );
				int rows = static_cast <int> (screen_h /sprite.getHeight()) -6;
				int columns = static_cast <int> (screen_w /sprite.getWidth()) -7;
				
				float border_w = screen_w /64;
				float border_h = screen_h /18;
				float start_x = screen_w/2 -( sprite.getWidth()*columns +(border_w*(columns-1)) )/2;
				float start_y = screen_h/2 -( sprite.getHeight()*rows +(border_h*(rows-1)) )/2;
				
				float add = 0;
				while( amount )
				{
					for( int i = 0; i < rows; i++ )
					{
						for( int j = 0; j < columns; j++ )
						{
							locks.push_back( true );
							positions.push_back( sf::Vector2f( start_x, start_y ) );
							
							start_x += border_w +sprite.getWidth();
							
							amount --;
							if( amount == 0 )	break;
						}
						
						start_x = screen_w/2 -( sprite.getWidth()*columns +(border_w*(columns-1)) )/2 +add;
						start_y += border_h +sprite.getHeight();
						
						if( amount == 0 )	break;
					}
					
					start_y = screen_h/2 -( sprite.getHeight()*rows +(border_h*(rows-1)) )/2;
					add += screen_w;
					start_x = screen_w/2 -( sprite.getWidth()*columns +(border_w*(columns-1)) )/2 +add;
				}
				
				ready = 1;
			}
		}
	}
	
	if( ready == 1 )
	{
		MyRequest request;
		request.setMessage( "username=" +username );
		request.setHttp( "http://adrianmichalek.pl/" );
		request.setRequest( "/combathalloween/getcup.php", sf::Http::Request::Post );
		
		if( !request.sendRequest() )
		{
			success = false;
		}
		else
		{
			string result = request.getResult();
			if( result == "0" )	// error
			{
				success = false;
			}
			else
			{
				string line = "";
				for( unsigned i = 0; i < result.size() -1; i++ )
				{
					// nr world
					if( result[ i ] == '&' )
					{
						line = "";
						for( unsigned j = i +1; j < result.size(); j++ )
						{
							if( result[ j ] == '*' )
							{
								i = j;
								break;
							}
							
							line += result[ j ];
						}
						
						locks[ con::stoi( line ) -1 ] = false;
					}
					
					// reward, cups, medals etc.
					if( result[ i ] == '*' )
					{
						line = "";
						for( unsigned j = i +1; j < result.size(); j++ )
						{
							if( result[ j ] == '&' )
							{
								i = j -1;
								break;
							}
							
							line += result[ j ];
						}
						
						stars.push_back( Star() );
						for( unsigned j = 0; j < line.size(); j++ )
						{
							// medals
							if( line[ j ] == 'c' )	stars[ stars.size() -1 ].coin_medal = true;
							else if( line[ j ] == 'p' )	stars[ stars.size() -1 ].star_medal = true;
							else if( line[ j ] == 'x' )	stars[ stars.size() -1 ].x_medal = true;
							
							// stars
							if( line[ j ] == 'g' ) // gold
							{
								stars[ stars.size() -1 ].gold = static_cast <int> (line[ j +1 ]) -48;
							}
							else if( line[ j ] == 's' ) // silver
							{
								stars[ stars.size() -1 ].silver = static_cast <int> (line[ j +1 ]) -48;
							}
						}
					}
				}
				
				// printf( "%s\n", result.c_str() );
				ready = 2;
			}
		}
	}
	
	// error
	if( !success )
	{
		information.setText( "No internet connection." );
		information.setColor( sf::Color( 0xF2, 0x58, 0x3E ) );
		information.setPosition( screen_w/2 -information.getWidth()/2 -reloadbutton.getWidth()/2 -screen_w/256, screen_h /2.2 );
		reloadbutton.setPosition( information.getRight() +screen_w/256, information.getY() -reloadbutton.getHeight() /3 );
	}
	
	thread.r = true;
}

void Worldtable::reload()
{
	ready = 0;
	chosen = -1;
	
	left.setAlpha( 0 );
	right.setAlpha( 0 );
	
	thread.free();
	
	gold_star.setAlpha( 0 );
	silver_star.setAlpha( 0 );
	x_medal.setAlpha( 0 );
	coin_medal.setAlpha( 0 );
	star_medal.setAlpha( 0 );
	
	text_nr.setAlpha( 0 );
	sprite.setAlpha( 0 );
	
	if( !locks.empty() )
	{
		locks.clear();
	}
	
	if( !positions.empty() )
	{
		positions.clear();
	}
	
	if( !stars.empty() )
	{
		for( auto &it :stars )
		{
			it.free();
		}
		
		stars.clear();
	}
}

void Worldtable::setUsername( string line )
{
	username = line;
}



void Worldtable::setPlayable( bool playable )
{
	click.setPlayable( playable );
}

void Worldtable::setVolume( float volume )
{
	click.setVolume( volume );
}
