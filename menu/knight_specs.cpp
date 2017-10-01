#include "knight_specs.h"
#include "own/file.h"
#include <locale>
#include <codecvt>

Knight_specs::Knight_specs()
{
	free();
}

Knight_specs::~Knight_specs()
{
	free();
}

void Knight_specs::free()
{
	screen_w = 0;
	screen_h = 0;
	username = "";
	
	left_arrow.free();
	table.free();
	gear_top.free();
	gear_bot.free();
	moving_state = 0;
	x1 = x2 = 0;
	
	knight.free();
	if( !parts.empty() )
	{
		for( auto &it :parts )
		{
			it->free();
			delete it;
			it = NULL;
		}
		
		parts.clear();
	}
	if( !rects.empty() )
	{
		rects.clear();
	}
	
	chosen = -1;
	lastChosen = -1;
	
	offset = 0;
	line = 0;
	
	click.free();
	
	// The Rest
	if( !categories.empty() )
	{
		for( auto &it :categories )
		{
			it->free();
			delete it;
			it = NULL;
		}
		
		categories.clear();
	}
	
	if( !values.empty() )
	{
		for( auto &it :values )
		{
			it->free();
			delete it;
			it = NULL;
		}
		
		values.clear();
	}
	
	thread.free();
	
	text_x = 0;
}



void Knight_specs::load( float screen_w, float screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	click.setIdentity( "knight_specs-click" );
	click.load( "sounds/click.wav" );
	
	line = 10;
	knight.setIdentity( "knight_specs-knight" );
	knight.load( "images/menu/knight.png", line );
	knight.setScale( screen_w /2560, screen_h /1440 );
	knight.setPosition( screen_w /7, screen_h -screen_h/72 -knight.getHeight() );
	
	x2 = -screen_w /256;	
	table.setIdentity( "knight_specs-table" );
	table.load( "images/menu/table.png" );
	table.setScale( screen_w /2560, screen_h /1440 );
	x1 = -table.getWidth() +screen_w /128;
	table.setPosition( x1, screen_h /5.5 );
	
	left_arrow.setIdentity( "knight_specs-left_arrow" );
	left_arrow.load( "images/menu/arrow_button.png", 3 );
	left_arrow.setScale( screen_w /2560, screen_h /1440 );
	left_arrow.setPosition( table.getRight() -left_arrow.getWidth(), table.getBot() -left_arrow.getHeight()/2 );
	
	x = x2 +table.getWidth() /3.9;
	y = table.getY() +table.getHeight() /2;
	
	gear_top.setIdentity( "knight_specs-gear_top" );
	gear_top.load( "images/menu/gear.png" );
	gear_top.setOrigin( gear_top.getWidth() *0.5, gear_top.getHeight() *0.5 );
	gear_top.setScale( screen_w /2560, screen_h /1440 );
	gear_top.setPosition( 0, table.getTop() );
	
	gear_bot.setIdentity( "knight_specs-gear_bot" );
	gear_bot.load( "images/menu/gear.png" );
	gear_bot.setOrigin( gear_bot.getWidth() *0.5, gear_bot.getHeight() *0.5 );
	gear_bot.setScale( screen_w /2560, screen_h /1440 );
	gear_bot.setPosition( 0, table.getBot() );
	
	
	for( unsigned i = 0; i < AMOUNT; i++ )
	{
		parts.push_back( new MySprite );
		parts[ i ]->setIdentity( "knight_specs-parts" );
		parts[ i ]->load( "images/menu/parts/" +con::itos(i) +".png" );
		parts[ i ]->setScale( screen_w /2560, screen_h /1440 );
		
		rects.push_back( new sf::Vector2f );
	}
	
	parts[ HELMET ]->setPosition( screen_w /5.5, screen_h /1.8 );
	parts[ BODY ]->setPosition( screen_w /4.6, screen_h /1.25 );
	parts[ SHIELD ]->setPosition( screen_w /5.9, screen_h /1.2 );
	parts[ SWORD ]->setPosition( screen_w /3.65, screen_h /1.3 );
	parts[ BOOTS ]->setPosition( screen_w /5.8, screen_h -screen_h/72 -parts[ BOOTS ]->getHeight() );
	
	for( unsigned i = 0; i < parts.size(); i++ )
	{
		rects[ i ]->x = parts[ i ]->getX();
		rects[ i ]->y = parts[ i ]->getY();
	}
	
	view.setSize( screen_w, screen_h );
	view.setCenter( screen_w /2, screen_h /2 );
	view.setViewport(sf::FloatRect(-0.735, 0, 1, 1));
	text_x = screen_w -(table.getWidth() -parts[ HELMET ]->getWidth() -screen_h /18);
	
	
	for( unsigned i = 0; i < VARIABLES_AMOUNT; i++ )
	{
		categories.push_back( new MyText );
		categories[ i ]->setIdentity( categories[ 0 ]->getIdentity() );
		categories[ i ]->setFont( "fonts/jcandlestickextracond.ttf" );
	}
	
	categories[ LEVEL ]->setText( "Level: " );
	categories[ ARMOUR ]->setText( "Armour: " );
	categories[ HEALTH ]->setText( "Health: " );
	categories[ DAMAGE ]->setText( "Damage: " );
	categories[ SPEED ]->setText( "Speed: " );
	for( auto &it :categories )
	{
		it->setColor( sf::Color( 0xDD, 0xDD, 0xDD ) );
		it->setSize( screen_h /28 );
	}
	
	for( unsigned i = 0; i < VARIABLES_AMOUNT *VARIABLES_AMOUNT; i++ )
	{
		values.push_back( new MyText );
		values[ values.size() -1 ]->setIdentity( "knight_specs-values" );
		values[ values.size() -1 ]->setFont( "fonts/jcandlestickextracond.ttf" );
		values[ values.size() -1 ]->setText( "..." );
		values[ values.size() -1 ]->setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
		values[ values.size() -1 ]->setSize( screen_h /28 );
	}
	
	setPositionValues( screen_w );
}

void Knight_specs::handle( sf::Event& event )
{
	if( event.type == sf::Event::MouseButtonPressed )
	{
		if( event.mouseButton.button == sf::Mouse::Left )
		{
			if( lastChosen == -1 )
			{
				for( unsigned i = 0; i < parts.size(); i++ )
				{
					if( parts[ i ]->checkCollision( event.mouseButton.x, event.mouseButton.y ) && chosen != static_cast <int> (i) )
					{
						click.play();
						
						lastChosen = chosen;
						chosen = i;
						break;
					}
				}
				
				if( left_arrow.checkCollision( event.mouseButton.x, event.mouseButton.y ) )
				{
					left_arrow.setOffset( 1 );
					lastChosen = chosen;
					chosen = -1;
				}
			}
		}
	}
	
	if( event.type == sf::Event::MouseButtonReleased )
	{
		left_arrow.setOffset( 0 );
	}
}

void Knight_specs::draw( sf::RenderWindow* &window )
{
	window->draw( knight.get() );
	window->draw( table.get() );
	window->draw( left_arrow.get() );
	window->draw( gear_top.get() );
	window->draw( gear_bot.get() );
	
	// Delete thread if is ready
	if( thread.r )
	{
		thread.reset();
	}
	
	// VALUES AND CATEGORIES
	window->setView( view );
	for( auto &it :categories )
	{
		window->draw( it->get() );
	}
	
	if( chosen != -1 )
	{
		for( int i = chosen *VARIABLES_AMOUNT; i < (chosen+1) *VARIABLES_AMOUNT; i++ )
		{
			window->draw( values[ i ]->get() );
		}
	}
	else if( lastChosen != -1 )
	{
		for( int i = lastChosen *VARIABLES_AMOUNT; i < (lastChosen+1) *VARIABLES_AMOUNT; i++ )
		{
			window->draw( values[ i ]->get() );
		}
	}
	
	window->setView( window->getDefaultView() );
	
	if( chosen != -1 && moving_state == 0 )
	{
		window->draw( parts[ chosen ]->get() );
	}
	
	if( lastChosen != -1 && moving_state == 0 )
	{
		window->draw( parts[ lastChosen ]->get() );
	}
}

void Knight_specs::mechanics( double elapsedTime )
{
	// printf( "%d %d\n", chosen, lastChosen );
	
	// move texts
	if( chosen == -1 )
	{
		if( categories[ 0 ]->getX() < screen_w )
		{
			moveValues( elapsedTime *0xFF );
		}
		else if( categories[ 0 ]->getX() > screen_w )
		{
			setPositionValues( screen_w );
		}
	}
	else if( table.getX() == x2 && moving_state == 0 )
	{
		if( categories[ 0 ]->getX() > text_x )
		{
			moveValues( -elapsedTime *0xFF );
		}
		else if( categories[ 0 ]->getX() < text_x )
		{
			setPositionValues( text_x );
		}
	}
	
	offset += elapsedTime *25;
	if( offset > line )
	{
		offset = 0;
	}
	knight.setOffset( offset );
	
	float vel = elapsedTime *2;
	
	if( chosen != -1 && moving_state == 0 )
	{
		float new_x = x -parts[ chosen ]->getWidth() /2;
		float new_y = y -parts[ chosen ]->getHeight() /2;
		if( parts[ chosen ]->getY() > new_y || parts[ chosen ]->getX() > new_x )
		{
			parts[ chosen ]->move( (new_x -rects[ chosen ]->x) *vel, (new_y -rects[ chosen ]->y) *vel );
		}
	}
	
	if( lastChosen != -1 && (chosen == -1 || lastChosen != chosen) && ( categories[ 0 ]->getX() == screen_w || categories[ 0 ]->getX() == text_x ) )
	{
		if( parts[ lastChosen ]->getY() < rects[ lastChosen ]->y || parts[ lastChosen ]->getX() < rects[ lastChosen ]->x )
		{
			float new_x = x -parts[ lastChosen ]->getWidth() /2;
			float new_y = y -parts[ lastChosen ]->getHeight() /2;
			parts[ lastChosen ]->move( (rects[ lastChosen ]->x -new_x) *vel, (rects[ lastChosen ]->y -new_y) *vel );
		}
		else
		{
			lastChosen = -1;
		}
	}
	
	if( chosen != -1 && moving_state == 0 )
	{
		float new_x = x -parts[ chosen ]->getWidth() /2;
		float new_y = y -parts[ chosen ]->getHeight() /2;
		
		if( parts[ chosen ]->getY() < new_y || parts[ chosen ]->getX() < new_x )
		{
			parts[ chosen ]->setPosition( new_x, new_y );
		}
	}
	
	if( lastChosen != -1 && moving_state == 0 )
	{
		if( parts[ lastChosen ]->getY() > rects[ lastChosen ]->y || parts[ lastChosen ]->getX() > rects[ lastChosen ]->x )
		{
			parts[ lastChosen ]->setPosition( rects[ lastChosen ]->x, rects[ lastChosen ]->y );
		}
	}
	
	if( categories[ 0 ]->getX() == screen_w )
	{
		float rotation = elapsedTime *0xFF;
		if( (lastChosen == -1 && chosen == -1) && table.getX() > x1 )
		{
			gear_top.setRotation( gear_top.getRotation() +rotation );
			gear_bot.setRotation( gear_bot.getRotation() -rotation );
			moving_state = -elapsedTime *0xFF;
		}
		else if( (lastChosen != -1 || chosen != -1) && table.getX() < x2 )
		{
			gear_top.setRotation( gear_top.getRotation() -rotation );
			gear_bot.setRotation( gear_bot.getRotation() +rotation );
			moving_state = elapsedTime *0xFF;
		}
		else
		{
			moving_state = 0;
		}
		
		if( moving_state != 0 )
		{
			table.move( moving_state, 0 );
			left_arrow.move( moving_state, 0 );
		}
		
		if( table.getX() < x1 )
		{
			table.setPosition( x1, table.getY() );
			left_arrow.setPosition( table.getRight() -left_arrow.getWidth(), table.getBot() -left_arrow.getHeight()/2 );
		}
		else if( table.getX() > x2 )
		{
			table.setPosition( x2, table.getY() );
			left_arrow.setPosition( table.getRight() -left_arrow.getWidth(), table.getBot() -left_arrow.getHeight()/2 );
		}
	}
}



void Knight_specs::fadein( float v, int max )
{
	knight.fadein( v, max );
	left_arrow.fadein( v, max );
	table.fadein( v, max );
	gear_top.fadein( v, max );
	gear_bot.fadein( v, max );
	
	for( auto &it :parts )
	{
		it->fadein( v, max );
	}
	
	for( auto &it :categories )
	{
		it->fadein( v, max );
	}
	
	for( auto &it :values )
	{
		it->fadein( v, max );
	}
}

void Knight_specs::fadeout( float v, int min )
{
	knight.fadeout( v, min );
	left_arrow.fadeout( v, min );
	table.fadeout( v, min );
	gear_top.fadeout( v, min );
	gear_bot.fadeout( v, min );
	
	for( auto &it :parts )
	{
		it->fadeout( v, min );
	}
	
	for( auto &it :categories )
	{
		it->fadeout( v, min );
	}
	
	for( auto &it :values )
	{
		it->fadeout( v, min );
	}
}



void Knight_specs::setThread()
{
	if( !thread.s )
	{
		if( !thread.r && thread.t == NULL )
		{
			// Values.
			for( auto &it :values )
			{
				it->setText( "..." );
				it->setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
			}
			
			if( isChosen() )
			{
				setPositionValues( text_x );
			}
			else
			{
				setPositionValues( screen_w );
			}
			
			thread.t = new std::thread( this->setValues, this );
			thread.t->detach();
		}
	}
}

void Knight_specs::setValues()
{
	bool success = true;
	
	// prepare message
	string message = "username=" +username;
	
	// prepare the request
	sf::Http::Request request( "/combathalloween/getparts.php", sf::Http::Request::Post );
	
	// encode the parameters in the request body
	request.setBody( message );
	
	// send the request
	sf::Http http( "http://adrianmichalek.pl/" );
	sf::Http::Response response = http.sendRequest( request );
	
	// check the status
	if( response.getStatus() != sf::Http::Response::Ok )
	{
		success = false;
	}
	else
	{
		string echostring = response.getBody();
		
		if( echostring == "0" )	// error
		{
			success = false;
		}
		else
		{
			int counter = 0;
			for( unsigned i = 0; i < echostring.size(); i++ )
			{
				if( echostring[ i ] == 'c' )
				{
					for( unsigned j = i +1; j < echostring.size(); j++ )
					{
						if( echostring[ j ] == 'a' )
						{
							i = j -1;
							break;
						}
					}
				}
				else if( echostring[ i ] == 'l' || 
					echostring[ i ] == 'a' || 
					echostring[ i ] == 'h' || 
					echostring[ i ] == 'd' || 
					echostring[ i ] == 's' )
				{
					int was = i;
					wstring value = L"";
					for( unsigned j = i +1; j < echostring.size(); j++ )
					{
						if( isalpha( echostring[ j ] ) )
						{
							i = j -1;
							break;
						}
						else
						{
							value += echostring[ j ];
						}
					}
					
					
					if( value.find( ' ' ) !=  string::npos )
					{
						value.erase( value.find( ' ' ) );
					}
					
					if( echostring[ was ] == 'a' )		value += L"‰";
					else if( echostring[ was ] == 'h' )	value += L"p";
					else if( echostring[ was ] == 'd' )	value += L"p";
					else if( echostring[ was ] == 's' )	value += L"%";
					
					//setup converter
					using convert_type = std::codecvt_utf8<wchar_t>;
					std::wstring_convert<convert_type, wchar_t> converter;

					//use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
					std::string converted_str = converter.to_bytes( value );
					
					if( echostring[ was ] == 'l' )
					{
						if( con::stoi( converted_str ) == 20 )
						{
							value = L"MAX";
						}
						values[ counter ]->setTextW( L" " +value );
						values[ counter ]->setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
					}
					else if( std::stoi( value ) > 0 )
					{
						values[ counter ]->setTextW( L"+" +value );
						values[ counter ]->setColor( sf::Color( 0x78, 0xA5, 0xA3 ) );
					}
					else if( std::stoi( value ) == 0 )
					{
						values[ counter ]->setTextW( L" " +value );
						values[ counter ]->setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
					}
					else
					{
						values[ counter ]->setTextW( value );
						values[ counter ]->setColor( sf::Color( 0xF2, 0x58, 0x3E ) );
					}
					
					counter++;
				}
			}
			
			thread.s = true;
		}
	}
	
	// error
	if( !success )
	{
		for( auto &it :values )
		{
			it->setText( "error" );
			it->setColor( sf::Color( 0xF2, 0x58, 0x3E ) );
		}
	}
	
	if( isChosen() )
	{
		setPositionValues( text_x );
	}
	else
	{
		setPositionValues( screen_w );
	}
			
	thread.r = true;
}

bool Knight_specs::isReady()
{
	return thread.s;
}

void Knight_specs::reload()
{
	moving_state = 0;
	chosen = -1;
	lastChosen = -1;
	table.setPosition( x1, table.getY() );
	setPositionValues( screen_w );
	left_arrow.setPosition( table.getRight() -left_arrow.getWidth(), table.getBot() -left_arrow.getHeight()/2 );
	
	for( unsigned i = 0; i < parts.size(); i++ )
	{
		parts[ i ]->setPosition( rects[ i ]->x, rects[ i ]->y );
	}
}

void Knight_specs::setUsername( string line )
{
	username = line;
}

void Knight_specs::setChosen( int n )
{
	lastChosen = chosen;
	chosen = n;
}

bool Knight_specs::isChosen()
{
	if( chosen != -1 || lastChosen != -1 )
	{
		return true;
	}
	
	return false;
}



void Knight_specs::moveValues( float x )
{
	for( auto &it: categories )
	{
		it->move( x, 0 );
	}
	
	for( auto &it: values )
	{
		it->move( x, 0 );
	}
}

void Knight_specs::setPositionValues( float x )
{
	float gap = screen_h /22;
	for( unsigned i = 0; i < categories.size(); i++ )
	{
		categories[ i ]->setPosition( x, table.getY() +table.getHeight()/8 +screen_h/72 +(gap *i) );
	}
	
	float biggest = 0;
	for( auto &it :categories )
	{
		if( it->getWidth() > biggest )
		{
			biggest = it->getWidth() +screen_w /128;
		}
	}
	
	unsigned counter = 0;
	for( unsigned i = 0; i < values.size(); i++ )
	{
		values[ i ]->setPosition( x +biggest, categories[ counter ]->getY() );
		counter ++;
		if( counter == VARIABLES_AMOUNT )
		{
			counter = 0;
		}
	}
}

void Knight_specs::reloadValues()
{
	thread.s = false;
}



void Knight_specs::setPlayable( bool playable )
{
	click.setPlayable( playable );
}

void Knight_specs::setVolume( float volume )
{
	click.setVolume( volume );
}