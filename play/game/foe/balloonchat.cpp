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
	screen_w = 0;
	screen_h = 0;
	
	text.free();
	arrow.free();
	lefttopborder.free();
	square.free();
	righttopborder.free();
	rightbotborder.free();
	bodyvertical.free();
	bodyhorizontal.free();
}

void Balloonchat::load( float screen_w, float screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	float scale_x = 0.5;
	float scale_y = 0.5;
	
	text.setIdentity( "balloonchat-text" );
	text.setFont( "fonts/jcandlestickextracond.ttf" );
	text.setText( " " );
	text.setSize( 20 );
	text.setColor( sf::Color( 0x22, 0x22, 0x22 ) );
	
	arrow.setIdentity( "balloonchat-arrow" );
	arrow.load( "images/play/foes/chatarrow.png" );
	arrow.setScale( scale_x, scale_y );
	
	lefttopborder.setIdentity( "balloonchat-lefttopborder" );
	lefttopborder.load( "images/play/foes/chatborder.png" );
	lefttopborder.setScale( scale_x, scale_y );
	square.setIdentity( "balloonchat-square" );
	square.create( lefttopborder.getWidth() +1, lefttopborder.getHeight() +1 );
	square.setColor( sf::Color( 0xF8, 0xF8, 0xF8 ) );
	
	righttopborder.setIdentity( "balloonchat-righttopborder" );
	righttopborder.load( "images/play/foes/chatborder.png" );
	righttopborder.setScale( -scale_x, scale_y );
	rightbotborder.setIdentity( "balloonchat-rightbotborder" );
	rightbotborder.load( "images/play/foes/chatborder.png" );
	rightbotborder.setScale( -scale_x, -scale_y );
	
	bodyvertical.setIdentity( "balloonchat-bodyvertical" );
	bodyvertical.create( 1, 1 );
	bodyvertical.setColor( sf::Color( 0xF8, 0xF8, 0xF8 ) );
	bodyhorizontal.setIdentity( "balloonchat-bodyhorizontal" );
	bodyhorizontal.create( 1, 1 );
	bodyhorizontal.setColor( sf::Color( 0xF8, 0xF8, 0xF8 ) );
	
	setPosition( 0, 0 );
	
	// Set alpha.
	text.setAlpha( 0xFF );
	arrow.setAlpha( 0xFF );
	lefttopborder.setAlpha( 0xFF );
	square.setAlpha( 0xFF );
	righttopborder.setAlpha( 0xFF );
	rightbotborder.setAlpha( 0xFF );
	bodyvertical.setAlpha( 0xFF );
	bodyhorizontal.setAlpha( 0xFF );
}

void Balloonchat::draw( sf::RenderWindow* &window, sf::Shader &shader )
{
	window->draw( arrow.get(), &shader );
	window->draw( lefttopborder.get(), &shader );
	window->draw( square.get(), &shader );
	window->draw( righttopborder.get(), &shader );
	window->draw( rightbotborder.get(), &shader );
	window->draw( bodyvertical.get(), &shader );
	window->draw( bodyhorizontal.get(), &shader );
	
	shader.setUniform( "hiddenColor", sf::Glsl::Vec4( 0.0, 0.0, 0.0, 1.0 ) );
	window->draw( text.get(), &shader );
	shader.setUniform( "hiddenColor", sf::Glsl::Vec4( 1.0, 1.0, 1.0, 1.0 ) );
}

void Balloonchat::draw( sf::RenderWindow* &window )
{
	window->draw( lefttopborder.get() );
	window->draw( square.get() );
	window->draw( righttopborder.get() );
	window->draw( rightbotborder.get() );
	window->draw( bodyvertical.get() );
	window->draw( bodyhorizontal.get() );
	window->draw( text.get() );
}



void Balloonchat::setText( string newtext )
{
	text.setText( newtext );
	bodyvertical.setScale( text.getWidth() +lefttopborder.getWidth()*2 -1, text.getHeight() );
	bodyhorizontal.setScale( text.getWidth(), text.getHeight() +lefttopborder.getHeight()*2 );
}

void Balloonchat::setPosition( float x, float y, bool left )
{
	if( left )
	{
		arrow.setScale( -0.5, 0.5 );
		rightbotborder.setScale( 0.5, -0.5 );
		arrow.setPosition( x -arrow.getWidth(), y -arrow.getHeight() );
		x -= (arrow.getWidth()*1.5 +lefttopborder.getWidth() +text.getWidth());
		y -= (text.getHeight() +arrow.getHeight()*1.5);
		text.setPosition( x, y );
		lefttopborder.setPosition( x -lefttopborder.getWidth(), y -lefttopborder.getHeight() );
		rightbotborder.setPosition( x -lefttopborder.getWidth(), text.getBot() +lefttopborder.getHeight() );
		square.setPosition( x +text.getWidth(), text.getBot() );
	}
	else
	{
		arrow.setScale( 0.5, 0.5 );
		rightbotborder.setScale( -0.5, -0.5 );
		arrow.setPosition( x, y -arrow.getHeight() );
		x += arrow.getWidth()/2 +lefttopborder.getWidth();
		y -= (text.getHeight() +arrow.getHeight()*1.5);
		text.setPosition( x, y );
		lefttopborder.setPosition( x -lefttopborder.getWidth(), y -lefttopborder.getHeight() );
		square.setPosition( x -lefttopborder.getWidth(), text.getBot() );
		rightbotborder.setPosition( x +text.getWidth() +lefttopborder.getWidth(), text.getBot() +lefttopborder.getHeight() );
	}
	
	bodyvertical.setPosition( x -lefttopborder.getWidth(), lefttopborder.getBot() );
	bodyhorizontal.setPosition( x, lefttopborder.getY() );
	righttopborder.setPosition( x +text.getWidth() +lefttopborder.getWidth(), lefttopborder.getY() );
	
	// Corrections.
	arrow.move( 0, 1 );
	text.move( -1, -2 );
	righttopborder.move( -1, 0 );
	bodyhorizontal.move( -1, 0 );
	if( left )
	{
		square.move( -1.5, -0.5 );
	}
	else
	{
		rightbotborder.move( -1, 0 );
	}
}



float Balloonchat::getLeft()
{
	return text.getLeft();
}

float Balloonchat::getRight()
{
	return text.getRight();
}

float Balloonchat::getTop()
{
	return text.getTop();
}

float Balloonchat::getBot()
{
	return text.getBot();
}

float Balloonchat::getWidth()
{
	return text.getWidth();
}

float Balloonchat::getHeight()
{
	return text.getHeight();
}