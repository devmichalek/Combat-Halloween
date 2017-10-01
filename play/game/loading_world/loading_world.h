#pragma once
#include "own/sprite.h"
#include "own/request.h"
#include "initialization/rectbutton.h"
#include <SFML/Graphics/RenderWindow.hpp>

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
	struct Particle
    {
        sf::Vector2f velocity;
        sf::Time lifetime;
    };
	
	std::vector <Particle> particles;
    sf::VertexArray vertices;
    sf::Time lifetime;
    sf::Vector2f emitter;
	
	sf::Color color;
	sf::Time colorLifetime;
	
	int randTime;
	int stateTime;
	float velocity;
	
	void resetParticle( std::size_t index );
	virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;
	
public:

	ParticleSystem();
	~ParticleSystem();
	void free();
	
	void update( sf::Time elapsed );
	void setEmitter( sf::Vector2f position );
	void setLifeTimeParameters( int randTime = 2000, int stateTime = 1000, float velocity = 50.0 );
	void create( unsigned count, sf::PrimitiveType primitiveType, float startX = 0, float startY = 0 );
};


class Loading_world
{
	// Support.
	float screen_w;
	float screen_h;
	int ready;
	bool stop;
	bool back;
	
	// Current progress.
	sf::Uint8 state;		// Show percents.
	MyText info;
	Rectbutton resetbutton;
	Rectbutton backbutton;
	
	// Animation
	float counter;		// To set offsets.
	float max;			// How many offset's.
	MySprite progress_bar;
	
	// Just for effects.
    sf::Clock clock;	// Create a clock to track the elapsed time.
	ParticleSystem particleSystem;
	MyText background_text;
	
	// Thread
	string data;
	string message;
	MyThread thread;
	
public:
	
	// Basics.
	Loading_world();
	~Loading_world();
	void free();
	void load( float screen_w, float screen_h );
	void handle( sf::Event& event );
	void draw( sf::RenderWindow* &window );
	void mechanics( double elapsedTime );
	
	// In addition.
	const sf::Uint8& getState();
	bool isReady();
	int getReady();
	void reset();
	bool getStop();
	
	// Support.
	void setError( string addError );
	void setSuccess();
	
	// Back.
	bool backToPrevious();
	
	// Thread.
	void setMessage( string message );
	void setThread();
	void prepare();
	string getData();
	bool ableData();
};