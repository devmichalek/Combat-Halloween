#include "eye.h"

Eye::Eye()
{
	free();
}

Eye::~Eye()
{
	free();
}

void Eye::free()
{
	screen_w = 0;
	screen_h = 0;
	
	line_y = 0;
	distance_y = 0;
	
	x = y = 0;
	scale_x = 0;
	
	sprite.free();
	onlay.free();
	shaderSprite.free();
	clock.restart(); // start the timer
}

void Eye::reset()
{
	distance_y = 0;
	
	x = y = 0;
	scale_x = 0;
	sprite.setPosition( x, y );
	shader.setParameter( "eye", sf::Vector2f(sprite.getX() +sprite.getWidth()/2, sprite.getY() +sprite.getHeight()) );
}



void Eye::load( float screen_w, float screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	sprite.setIdentity( "eye-sprite" );
	sprite.load( "images/play/knight/eye.png" );
	sprite.setScale( 0.5, 0.5 );
	line_y = sprite.getHeight();
	scale_x = 0.5;
	
	onlay.setIdentity( "eye-onlay" );
	onlay.create( screen_w, screen_h );
	onlay.setColor( sf::Color::Black );
	onlay.setAlpha( 150 );
	
	shaderSprite.setIdentity( "eye-shaderSprite" );
	shaderSprite.create( screen_w, screen_h );
	
	// Set shader.
	shader.loadFromFile( "images/play/knight/light.glsl", sf::Shader::Fragment );
	if( !shader.isAvailable() )
	{
		std::cout << "The shader is not available\n";
	}

	// Set the resolution parameter ( the resoltion is divided to make the fire smaller )
	shader.setParameter( "resolution", sf::Vector2f( screen_w /2, screen_h ) );
}

void Eye::draw( sf::RenderWindow* &window )
{
	if( scale_x < 0 )
	{
		float x = sprite.getX();
		sprite.setPosition( sprite.getX() +sprite.getWidth(), sprite.getY() );
		window->draw( sprite.get() );
		sprite.setPosition( x, sprite.getY() );
	}
	else
	{
		window->draw( sprite.get() );
	}
}

void Eye::drawShader( sf::RenderWindow* &window )
{
	window->draw( onlay.get() );
	window->draw( shaderSprite.get(), &shader );
}

void Eye::mechanics( double elapsedTime, float viewX, float viewY )
{
	// Hovering.
	distance_y += elapsedTime *4;
	if( distance_y > line_y )
	{
		distance_y = 0;
	}
	
	// Set the others parameters who need to be updated every frames
	shader.setParameter( "time", clock.getElapsedTime().asSeconds() );
	
	// Set position.
	shader.setParameter( "eye", sf::Vector2f(sprite.getX() +sprite.getWidth()/2 -viewX, sprite.getY() +sprite.getHeight() -viewY) );
	
	// Set eye.
	if( sprite.getX() < x -sprite.getWidth()/2 )
	{
		sprite.move( elapsedTime *((x-sprite.getWidth()/2) -sprite.getX()), 0 );
		sprite.setScale( -screen_w /2560, screen_h /1440 );
		scale_x = -screen_w /2560;
	}
	else if( sprite.getX() > x -sprite.getWidth()/2 )
	{
		sprite.move( -elapsedTime *(sprite.getX() -(x-sprite.getWidth()/2)), 0 );
		sprite.setScale( screen_w /2560, screen_h /1440 );
		scale_x = screen_w /2560;
	}

	

	if( sprite.getY() < y +distance_y )
	{
		sprite.move( 0, elapsedTime *((y+distance_y) -sprite.getY()) );
	}
	else if( sprite.getY() > y +distance_y )
	{
		sprite.move( 0, -elapsedTime *(sprite.getY() -(y+distance_y)) );
	}
}



void Eye::fadein( float v, int max )
{
	sprite.fadein( v, max );
}

void Eye::fadeout( float v, int min )
{
	sprite.fadeout( v, min );
}



void Eye::setPosition( float x, float y )
{
	this->x = x;
	this->y = y;
}
