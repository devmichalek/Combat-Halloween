#include "settings.h"
#include "own/file.h"

Settings::Settings()
{
	free();
}

Settings::~Settings()
{
	free();
}

void Settings::free()
{
	screen_w = 0;
	screen_h = 0;
	
	if( !keys_current.empty() )
	{
		keys_current.clear();
	}
	
	if( !state_texts.empty() )
	{
		for( auto &it :state_texts )
		{
			it->free();
			delete it;
			it = NULL;
		}
		
		state_texts.clear();
	}
	
	if( !active_texts.empty() )
	{
		for( auto &it :active_texts )
		{
			it->free();
			delete it;
			it = NULL;
		}
		
		active_texts.clear();
	}
	
	contactme.free();
	
	table.free();
	gear_top.free();
	gear_bot.free();
	moving = 0;
	x1 = x2 = 0;
	
	table_second.free();
	gear_left.free();
	gear_right.free();
	moving_second = 0;
	y1 = y2 = 0;
	target = -1;
	pressbutton.free();
	pressenter.free();
	resetbutton.free();
	
	click.free();
}



void Settings::load( float screen_w, float screen_h )
{
	free();
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	// Set font state_texts and active_texts.
	for( unsigned i = 0; i < AMOUNT; i++ )
	{
		state_texts.push_back( new MyText );
		state_texts[ i ]->setIdentity( "settings-state_texts" );
		state_texts[ i ]->setFont( "fonts/jcandlestickextracond.ttf" );
		active_texts.push_back( new MyText );
		active_texts[ i ]->setIdentity( "settings-active_texts" );
		active_texts[ i ]->setFont( "fonts/jcandlestickextracond.ttf" );
	}
	
	// Set state_texts text.
	state_texts[ MOVE_LEFT ]->setText( "move left" );
	state_texts[ MOVE_RIGHT ]->setText( "move right" );
	state_texts[ JUMP ]->setText( "jump" );
	state_texts[ ATTACK ]->setText( "attack" );
	state_texts[ JUMP_ATTACK ]->setText( "jump attack" );
	state_texts[ PAUSE ]->setText( "pause" );
	state_texts[ CHAT ]->setText( "chat" );
	
	// Set active_texts text.
	MyFile file;
	file.load( "txt/keys_current.txt" );
	if( file.is_good() )
	{
		for( unsigned i = 0; i < JUMP_ATTACK; i++ )
		{
			string line = "";
			file.get() >> line;
			keys_current.push_back( con::stoi( line ) );
			active_texts[ i ]->setText( getName( keys_current[ i ] ) );
		}
	}
	file.free();
	active_texts[ JUMP_ATTACK ]->setText( getName( keys_current[ JUMP ] ) +" + " +getName( keys_current[ ATTACK ] ) );
	active_texts[ PAUSE ]->setText( "p" );
	active_texts[ CHAT ]->setText( "o" );
	
	// Set size state_texts and active_texts.
	int size = screen_h /28;
	for( unsigned i = 0; i < AMOUNT; i++ )
	{
		state_texts[ i ]->setSize( size );
		active_texts[ i ]->setSize( size );
		state_texts[ i ]->setColor( sf::Color( 0xDD, 0xDD, 0xDD ) );
		active_texts[ i ]->setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
	}
	active_texts[ JUMP_ATTACK ]->setColor( sf::Color( 0xDD, 0xDD, 0xDD ) );
	active_texts[ PAUSE ]->setColor( sf::Color( 0xDD, 0xDD, 0xDD ) );
	active_texts[ CHAT ]->setColor( sf::Color( 0xDD, 0xDD, 0xDD ) );
	
	
	
	contactme.setIdentity( "settings-contactme" );
	contactme.setFont( "fonts/jcandlestickextracond.ttf" );
	contactme.setText( "Contact me: adrmic98@gmail.com" );
	contactme.setSize( size );
	contactme.setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
	
	
	
	// Set table.
	table.setIdentity( "settings-table" );
	table.load( "images/menu/table.png" );
	table.setScale( screen_w /2560, screen_h /1440 );
	x1 = screen_w -screen_w /128;
	x2 = screen_w +screen_w /128 -table.getWidth();	
	table.setPosition( x1, screen_h /2.3 );
	
	// Set gear_top.
	gear_top.setIdentity( "settings-gear_top" );
	gear_top.load( "images/menu/gear.png" );
	gear_top.setOrigin( gear_top.getWidth() *0.5, gear_top.getHeight() *0.5 );
	gear_top.setScale( screen_w /2560, screen_h /1440 );
	gear_top.setPosition( screen_w, table.getTop() );
	
	// Set gear_bot.
	gear_bot.setIdentity( "settings-gear_bot" );
	gear_bot.load( "images/menu/gear.png" );
	gear_bot.setOrigin( gear_bot.getWidth() *0.5, gear_bot.getHeight() *0.5 );
	gear_bot.setScale( screen_w /2560, screen_h /1440 );
	gear_bot.setPosition( screen_w, table.getBot() );
	
	position();
	
	
	
	// Set second table.
	table_second.setIdentity( "settings-table_second" );
	table_second.load( "images/menu/table_second.png" );
	table_second.setScale( screen_w /2560, screen_h /1440 );
	y1 = screen_h -screen_h /72;
	y2 = screen_h +screen_h /72 -table_second.getHeight();	
	table_second.setPosition( screen_w /2.13, y1 );
	
	// Set gear_left.
	gear_left.setIdentity( "settings-gear_left" );
	gear_left.load( "images/menu/gear.png" );
	gear_left.setOrigin( gear_left.getWidth() *0.5, gear_left.getHeight() *0.5 );
	gear_left.setScale( screen_w /2560, screen_h /1440 );
	gear_left.setPosition( table_second.getLeft(), screen_h );
	
	// Set gear_right.
	gear_right.setIdentity( "settings-gear_right" );
	gear_right.load( "images/menu/gear.png" );
	gear_right.setOrigin( gear_right.getWidth() *0.5, gear_right.getHeight() *0.5 );
	gear_right.setScale( screen_w /2560, screen_h /1440 );
	gear_right.setPosition( table_second.getRight(), screen_h );
	
	// Set pressbutton.
	pressbutton.setIdentity( "settings-pressbutton" );
	pressbutton.setFont( "fonts/jcandlestickextracond.ttf" );
	pressbutton.setText( "Press button to change" );
	pressbutton.setSize( size );
	pressbutton.setColor( sf::Color( 0xDD, 0xDD, 0xDD ) );
	
	// Set pressenter.
	pressenter.setIdentity( "settings-pressenter" );
	pressenter.setFont( "fonts/jcandlestickextracond.ttf" );
	pressenter.setText( "Click anywhere to save" );
	pressenter.setSize( size );
	pressenter.setColor( sf::Color( 0xDD, 0xDD, 0xDD ) );
	
	// Set reset button.
	resetbutton.setIdentity( "settings-resetbutton" );
	resetbutton.setFont( "fonts/jcandlestickextracond.ttf" );
	resetbutton.setText( "RESET" );
	resetbutton.setSize( size );
	resetbutton.setColor( sf::Color( 0xDD, 0xDD, 0xDD ) );
	
	positionSecond();
	
	// Load sound.
	click.setIdentity( "settings-chunk" );
	click.load( "sounds/click.wav" );
}

bool Settings::handle( sf::Event& event )
{
	if( moving_second == 0 && target != -1 )
	{
		// Reset.
		if( event.type == sf::Event::MouseButtonPressed )
		{
			if( event.mouseButton.button == sf::Mouse::Left )
			{
				if( resetbutton.checkCollision( event.mouseButton.x, event.mouseButton.y ) )
				{
					reset();
					return true;
				}
			}
		}
		
		// Keyboard stuff.
		if( event.type == sf::Event::KeyPressed )
		{
			bool success = true;
			for( auto &it :keys_current )
			{
				if( it == event.key.code )
				{
					success = false;
					break;
				}
			}
			
			// Set key.
			if( success )
			{
				if( isPossibleKey( event ) )
				{
					click.play();
					
					keys_current[ target ] = event.key.code;
					
					active_texts[ target ]->setText( getName( event.key.code ) );
					active_texts[ target ]->setSize( screen_h /28 );
					active_texts[ target ]->setColor( sf::Color( 0xF2, 0x58, 0x3E ) );
					
					if( target == ATTACK || target == JUMP )
					{
						active_texts[ JUMP_ATTACK ]->setText( getName( keys_current[ JUMP ] ) +" + " +getName( keys_current[ ATTACK ] ) );
						active_texts[ JUMP_ATTACK ]->setSize( screen_h /28 );
						active_texts[ JUMP_ATTACK ]->setColor( sf::Color( 0xDD, 0xDD, 0xDD ) );
					}
					
					position();
					save();
				}
			}
		}
	}
	
	if( moving == 0 && table.getX() == x2 )
	{
		if( event.type == sf::Event::MouseButtonPressed )
		{
			if( event.mouseButton.button == sf::Mouse::Left )
			{
				// Set default color if this one was a target.
				if( target != -1 )
				{
					active_texts[ target ]->setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
				}
				
				// Check whenever is the collision.
				target = -1;
				for( unsigned i = 0; i < JUMP_ATTACK; i++ )
				{
					if( active_texts[ i ]->checkCollision( event.mouseButton.x, event.mouseButton.y ) || 
						state_texts[ i ]->checkCollision( event.mouseButton.x, event.mouseButton.y ) )
					{
						target = i;
						click.play();
						active_texts[ i ]->setColor( sf::Color( 0xF2, 0x58, 0x3E ) );
						break;
					}
				}
				
				if( target != -1 )
				{
					return true;
				}
			}
		}
	}
	
	return false;
}

void Settings::draw( sf::RenderWindow* &window )
{
	// First table.
	window->draw( table.get() );
	for( auto &it :state_texts )
	{
		window->draw( it->get() );
	}
	for( auto &it :active_texts )
	{
		window->draw( it->get() );
	}
	window->draw( contactme.get() );
	window->draw( gear_top.get() );
	window->draw( gear_bot.get() );
	
	// Second table.
	window->draw( table_second.get() );
	window->draw( pressbutton.get() );
	window->draw( pressenter.get() );
	window->draw( resetbutton.get() );
	window->draw( gear_left.get() );
	window->draw( gear_right.get() );
}

void Settings::mechanics( double elapsedTime )
{
	if( moving != 0 )
	{
		table.move( moving, 0 );
		position();
		
		float rotation = elapsedTime *0xFF;
		if( moving < 0 )
		{
			gear_top.setRotation( gear_top.getRotation() +rotation );
			gear_bot.setRotation( gear_bot.getRotation() -rotation );
		}
		else
		{
			gear_top.setRotation( gear_top.getRotation() -rotation );
			gear_bot.setRotation( gear_bot.getRotation() +rotation );
		}
	}
	
	if( target != -1 )
	{
		if( table_second.getY() > y2 )
		{
			moving_second = -elapsedTime *0xFF;
		}
		else
		{
			moving_second = 0;
		}
		
		if( table_second.getY() < y2 )
		{
			table_second.setPosition( table_second.getX(), y2 );
		}
	}
	else
	{
		if( table_second.getY() < y1 )
		{
			moving_second = elapsedTime *0xFF;
		}
		else
		{
			moving_second = 0;
		}
		
		if( table_second.getY() > y1 )
		{
			table_second.setPosition( table_second.getX(), y1 );
		}
	}
	
	if( moving_second != 0 )
	{
		positionSecond();
		table_second.move( 0, moving_second );
		
		float rotation = elapsedTime *0xFF;
		if( moving_second < 0 )
		{
			gear_left.setRotation( gear_left.getRotation() -rotation );
			gear_right.setRotation( gear_right.getRotation() +rotation );
		}
		else
		{
			gear_left.setRotation( gear_left.getRotation() +rotation );
			gear_right.setRotation( gear_right.getRotation() -rotation );
		}
	}
}



void Settings::fadein( float v, int max )
{
	for( auto &it :state_texts )
	{
		it->fadein( v, max );
	}
	
	for( auto &it :active_texts )
	{
		it->fadein( v, max );
	}
	
	contactme.fadein( v, max );
	table.fadein( v, max );
	gear_top.fadein( v, max );
	gear_bot.fadein( v, max );
	
	table_second.fadein( v, max );
	gear_left.fadein( v, max );
	gear_right.fadein( v, max );
	pressbutton.fadein( v, max );
	pressenter.fadein( v, max );
	resetbutton.fadein( v, max );
}

void Settings::fadeout( float v, int min )
{
	for( auto &it :state_texts )
	{
		it->fadeout( v, min );
	}
	
	for( auto &it :active_texts )
	{
		it->fadeout( v, min );
	}
	
	contactme.fadeout( v, min );
	table.fadeout( v, min );
	gear_top.fadeout( v, min );
	gear_bot.fadeout( v, min );
	
	table_second.fadeout( v, min );
	gear_left.fadeout( v, min );
	gear_right.fadeout( v, min );
	pressbutton.fadeout( v, min );
	pressenter.fadeout( v, min );
	resetbutton.fadeout( v, min );
}



void Settings::exsertTable( double elapsedTime )
{
	if( table.getX() > x2 )
	{
		moving = -elapsedTime *0xFF;
	}
	else
	{
		moving = 0;
	}
	
	if( table.getX() < x2 )
	{
		table.setPosition( x2, table.getY() );
		position();
	}
}

void Settings::shovelTable( double elapsedTime )
{
	if( table.getX() < x1 )
	{
		moving = elapsedTime *0xFF;
	}
	else
	{
		moving = 0;
	}
	
	if( table.getX() > x1 )
	{
		table.setPosition( x1, table.getY() );
		position();
	}
}

void Settings::reset()
{
	// First, open state file.
	MyFile file;
	file.load( "txt/keys.txt" );
	if( file.is_good() )
	{
		for( unsigned i = 0; i < JUMP_ATTACK; i++ )
		{
			string line = "";
			file.get() >> line;
			keys_current[ i ] = stoi( line );
			active_texts[ i ]->setText( getName( stoi( line ) ) );
			active_texts[ i ]->setSize( screen_h /28 );
			active_texts[ i ]->setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
		}
	}
	file.free();
	
	// Then overwrite.
	file.load( "txt/keys_current.txt" );
	if( file.is_good() )
	{
		for( unsigned i = 0; i < JUMP_ATTACK; i++ )
		{
			string line = con::itos( keys_current[ i ] );
			file.get() << line << endl;
		}
	}
	file.free();
	
	position();
}

void Settings::save()
{
	MyFile file;
	file.load( "txt/keys_current.txt" );
	if( file.is_good() )
	{
		for( unsigned i = 0; i < JUMP_ATTACK; i++ )
		{
			string line = con::itos( keys_current[ i ] );
			file.get() << line << endl;
		}
	}
	file.free();
}

void Settings::position()
{
	// Position state_texts.
	for( unsigned i = 0; i < state_texts.size(); i++ )
	{
		state_texts[ i ]->setPosition( table.getX() +screen_w /80, table.getY() +(screen_h /28 *i) +screen_h /54 );
	}
	
	// Position active_texts.
	for( unsigned i = 0; i < active_texts.size(); i++ )
	{
		active_texts[ i ]->setPosition( table.getX() +table.getWidth() /2, state_texts[ i ]->getY() );
	}
	
	// Contactme.
	contactme.setPosition( table.getX() +screen_w /80, table.getBot() -contactme.getHeight() -screen_h /54 );
}

void Settings::positionSecond()
{
	pressbutton.setPosition( table_second.getX() +screen_w /80, table_second.getY() +screen_h /54 );
	pressenter.setPosition( table_second.getX() +screen_w /80, pressbutton.getBot() +screen_h /80 );
	resetbutton.setPosition( table_second.getRight() -screen_w /16, table_second.getBot() -screen_h /16 );
}

bool Settings::isPossibleKey( sf::Event &event )
{
	sf::Uint8 code = event.key.code;
	
	// if pause key or chat key
	if( code == 14 || code == 15 )
	{
		return false;
	}
	
	if( code > -1 && code <= 35 )
	{
		return true;
	}
	else if( code >= 75 && code <= 84 )
	{
		return true;
	}
	else if( code >= 71 && code <= 74 )
	{
		return true;
	}
	else if( code == 57 )
	{
		return true;
	}

	return false;
}

string Settings::getName( int n )
{
	string name = "";
	
	if( n > -1 && n <= 25 )	// from a to z
	{
		// in ASCII 97 means letter 'a'
		name = static_cast <char> ( n + 97 );
	}
	else if( n >= 26 && n <= 35 )
	{
		// 26 + 22 = 48
		// in ASCII 48 means character 0
		name = static_cast <char> ( n + 22 );
	}
	else if( n >= 75 && n <= 84 )
	{
		// 75 - 27 = 48
		// in ASCII 48 means character 0
		name = static_cast <char> ( n - 27 );
	}
	
	// Rest.
	else if( n == 71 )
	{
		name = "Left";
	}
	else if( n == 72 )
	{
		name = "Right";
	}
	else if( n == 73 )
	{
		name = "Up";
	}
	else if( n == 74 )
	{
		name = "Down";
	}
	else if( n == 57 )
	{
		name = "Space";
	}
	
	return name;
}

void Settings::reload()
{
	moving = 0;
	table.setPosition( x1, table.getY() );
	position();
	
	moving_second = 0;
	table_second.setPosition( table_second.getX(), y1 );
	positionSecond();
}



void Settings::setPlayable( bool playable )
{
	click.setPlayable( playable );
}

void Settings::setVolume( float volume )
{
	click.setVolume( volume );
}