#define _GLIBCXX_USE_CXX11_ABI 0
#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
	// Create window.
	float screen_w = 1280;
	float screen_h = 720;
	sf::RenderWindow window( sf::VideoMode( screen_w, screen_h ), "Lighting test" );
	
	// Set background.
	sf::Texture texture;
	texture.loadFromFile( "sprite.png" );
	texture.setSmooth( true );
	sf::Sprite sprite;
	sprite.setTexture( texture );
	
	// Load shader.
	sf::Shader shader;
	if( !shader.loadFromFile( "vert_shader.vert", "frag_shader.frag" ) )
	{
		std::cout << "Unable to load the shaders" << std::endl;
		return 0;
	}
	
	// Set parameters.
	shader.setParameter( "texture", sf::Shader::CurrentTexture );
	shader.setParameter( "resolution", window.getSize().x, window.getSize().y );
	shader.setParameter( "ambientColor", 0.3, 0.3, 0.8, 0.3 );
	shader.setParameter( "lightColor", 1.0, 0.8, 0.2, 2 );
	shader.setParameter( "radius", 0.2 );
	
	sf::Clock clock;
	sf::Time frameTime, time;
	
	sf::Event event;
	bool open = true;
	while( open )
	{
		while( window.pollEvent( event ) )
		{
			if( event.type == sf::Event::Closed )
			{
				open = false;
			}
		}
		
		// Calculate.
		frameTime = clock.restart();
		time += frameTime;
    
		sf::Vector2i pos = sf::Mouse::getPosition( window );

		shader.setParameter( "position", pos.x, screen_h - pos.y );
		shader.setParameter( "time", 10 *time.asSeconds() );
    
		window.clear();
		window.draw( sprite, &shader );
		window.display();    
	}

	return 0;
}