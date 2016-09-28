#include "loading.h"
#include "templates/file.h"

Loading::Loading()
{
	state = 0;
	counter = 0;
	max = 0;
}

Loading::~Loading()
{
	free();
}

void Loading::free()
{
	text.free();
	background.free();
	
	progress_bar.free();
	counter = 0;
	max = 0;
}
	
void Loading::load( const int &screen_w, const int &screen_h )
{
	File file;
	file.load( "data/loading_settings.txt" );
	
	text.setID( "loading-text" );
	
	text.setFont( file.s(0), file.i(1), file.i(2), file.i(3), file.i(4) );
	text.setText( "Loading " + to_string( state ) + "%"  );
	text.setAlpha( file.i(5) );
	text.center( screen_w, screen_h );

	
	progress_bar.setName( "loading-progress_bar" );
	progress_bar.load( file.s(6), file.i(7) );
	progress_bar.setAlpha( file.i(8) );
	progress_bar.setPosition( screen_w/2 - progress_bar.getWidth()/2, text.getBot() +15 );
	
	
	background.setName( "loading-background" );
	background.create( screen_w, screen_h );
	background.setColor( sf::Color( file.i(9), file.i(10), file.i(11) ) );
	background.setAlpha( file.i(12) );
	
	max = file.i(7);
	file.free();
}

void Loading::draw( sf::RenderWindow* &window )
{
	window->draw( background.get() );
	
	window->draw( text.get() );
	text.setText( "Loading " + to_string( state ) + "%" );
	text.reloadPosition();
	
	state ++;
	
	progress_bar.setOffset( counter /5 );
	window->draw( progress_bar.get() );
	
	counter++;
	if( counter == max *5 )
	{
		counter = 0;
	}
}

int Loading::getState()
{
	return state;
}
