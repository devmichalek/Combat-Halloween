#include "map_editor/map_editor.h"


Map_editor::Map_editor()
{
	state = 0;
	
	ch_m = NULL;
	palette = NULL;
	saveLog = NULL;
	brickXY = NULL;
	
	w = h = 0;
}

Map_editor::~Map_editor()
{
	state = 0;
	
	delete ch_m;
	delete palette;
	delete saveLog;
	delete brickXY;
	
	w = h = 0;
}


void Map_editor::load( int screen_w, int screen_h )
{
	ch_m = new Choose_map;
	ch_m->load( screen_w );
	
	palette = new Palette;
	w = screen_w;
	h = screen_h;
	
	saveLog = new SaveLog;
	
	brickXY = new BrickXY;
	brickXY->load( screen_w, screen_h );
}

void Map_editor::draw( sf::RenderWindow* &window )
{
	if( state == 0 )
	{
		ch_m->draw( window );
		
		if( ch_m->chosenMap() != -1 )
		{
			state = 1;
			palette->load( w, h, ch_m->chosenMap() );
			saveLog->load( w, h, palette->getPath() );
		}
	}
	
	if( state == 1 )
	{
		brickXY->draw( window );
		palette->draw( window );
		
		if( palette->saveModeIsOn() )
		{
			saveLog->supplyData( palette->getData() );
			saveLog->supplyPlatform( brickXY->getPlatform() );
			saveLog->draw( window );
		}
			
			
		brickXY->drawXY( window );
		
		if( palette->isChosen() )
			brickXY->getImag( palette->getDisX(), palette->getDisY() );
	}
	
	if( palette->backToMenu() )
	{
		delete palette;
		palette = new Palette;
		
		delete saveLog;
		saveLog = new SaveLog;
		
		state = 0;
		ch_m->resetState();
	}
}

void Map_editor::handle( sf::Event &event )
{
	if( state == 0 )
	{
		ch_m->handle( event );
	}
	
	if( state == 1 )
	{
		if( palette->saveModeIsOn() )
			saveLog->handle( event );
		else
			brickXY->handle( event );
			
		palette->handle( event );
	}
}
