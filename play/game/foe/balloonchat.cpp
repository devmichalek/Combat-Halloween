#include "balloonchat.h"

Balloonchat::Balloonchat()
{
	free();
}

Balloonchat::~Balloonchat()
{
	free();
}

void Balloonchat::free()
{
	width = 0;
	max_width = 0;
	
	text.free();
	lefttopborder.free();
	leftbotborder.free();
	righttopborder.free();
	rightbotborder.free();
	bodyvertical.free();
	bodyhorizontal.free();
}



void Balloonchat::load( float screen_w, float screen_h )
{
	free();
	
	max_width = screen_w /8;
	
	text.setIdentity( "balloonchat-text" );
	text.setFont( "fonts/jcandlestickextracond.ttf" );
	text.setText( "m" );
	text.setSize( screen_h /48 );
	width = text.getWidth();
	
	lefttopborder.setIdentity( "balloonchat-lefttopborder" );
	lefttopborder.load( "images/play/foes/chatborder.png" );
	lefttopborder.setScale( screen_w/2560, screen_h/1440 );
	
	leftbotborder.setIdentity( "balloonchat-leftbotborder" );
	leftbotborder.load( "images/play/foes/chatborder.png" );
	leftbotborder.setScale( screen_w/2560, screen_h/1440 );
	leftbotborder.flipVertically();
	
	righttopborder.setIdentity( "balloonchat-righttopborder" );
	righttopborder.load( "images/play/foes/chatborder.png" );
	righttopborder.setScale( screen_w/2560, screen_h/1440 );
	righttopborder.flipHorizontally();
	
	rightbotborder.setIdentity( "balloonchat-rightbotborder" );
	rightbotborder.load( "images/play/foes/chatborder.png" );
	rightbotborder.setScale( screen_w/2560, screen_h/1440 );
	rightbotborder.flipHorizontally();
	rightbotborder.flipVertically();
	
	bodyvertical.setIdentity( "balloonchat-bodyvertical" );
	bodyvertical.create( 1, 1 );
	bodyvertical.setColor( sf::Color( 0xF8, 0xF8, 0xF8 ) );
	
	bodyhorizontal.setIdentity( "balloonchat-bodyhorizontal" );
	bodyhorizontal.create( 1, 1 );
	bodyhorizontal.setColor( sf::Color( 0xF8, 0xF8, 0xF8 ) );
	
	setPosition( 0, 0 );
}

void Balloonchat::draw( sf::RenderWindow* &window )
{
	window->draw( lefttopborder.get() );
	window->draw( leftbotborder.get() );
	window->draw( righttopborder.get() );
	window->draw( rightbotborder.get() );
	window->draw( bodyvertical.get() );
	window->draw( bodyhorizontal.get() );
	window->draw( text.get() );
}



void Balloonchat::fadein( float v, int max )
{
	text.fadein( v, max );
	lefttopborder.fadein( v, max );
	leftbotborder.fadein( v, max );
	righttopborder.fadein( v, max );
	rightbotborder.fadein( v, max );
	bodyvertical.fadein( v, max );
	bodyhorizontal.fadein( v, max );
}

void Balloonchat::fadeout( float v, int min )
{
	text.fadeout( v, min );
	lefttopborder.fadeout( v, min );
	leftbotborder.fadeout( v, min );
	righttopborder.fadeout( v, min );
	rightbotborder.fadeout( v, min );
	bodyvertical.fadeout( v, min );
	bodyhorizontal.fadeout( v, min );
}



void Balloonchat::setPosition( float x, float y )
{
	lefttopborder.setPosition( x, y );
	bodyvertical.setPosition( x, lefttopborder.getBot() );
	leftbotborder.setPosition( x, bodyvertical.getBot() );
	bodyhorizontal.setPosition( lefttopborder.getRight(), y );
	righttopborder.setPosition( bodyhorizontal.getRight(), y );
	rightbotborder.setPosition( bodyhorizontal.getRight(), bodyvertical.getBot() );
}

void Balloonchat::setText( wstring newtext )
{
	text.setTextW( newtext );
	bodyvertical.setScale( 10, 10 );
	bodyhorizontal.setScale( 10, 10 );
}