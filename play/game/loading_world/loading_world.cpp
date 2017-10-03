#include "loading_world.h"
#include "own/file.h"


void ParticleSystem::resetParticle( std::size_t index )
{
	// Give a random velocity and lifetime to the particle.
	float angle = (std::rand() % 360) * 3.14f / 180.f;
	float speed = (std::rand() % static_cast <int> (velocity)) + velocity;
	particles[ index ].velocity = sf::Vector2f( std::cos( angle ) *speed, std::sin( angle ) *speed );
	particles[ index ].lifetime = sf::milliseconds( (std::rand() %randTime) +stateTime );

	// Reset the position of the corresponding vertex.
	vertices[ index ].position = emitter;
	vertices[ index ].color.r = color.r;
	vertices[ index ].color.g = color.g;
	vertices[ index ].color.b = color.b;
}

void ParticleSystem::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
	// Apply the transform.
	states.transform *= getTransform();

	// Our particles don't use a texture.
	states.texture = NULL;

	// Draw the vertex array.
	target.draw( vertices, states );
}



ParticleSystem::ParticleSystem()
{
	free();
}

ParticleSystem::~ParticleSystem()
{
	free();
}

void ParticleSystem::free()
{
	if( !particles.empty() )
	{
		particles.clear();
	}
	
	vertices.clear();
	lifetime = sf::seconds( 0 );
	emitter = sf::Vector2f( 0, 0 );
	
	color = sf::Color( std::rand() %0xFF, std::rand() %0xFF, std::rand()%0xFF );
	colorLifetime = sf::milliseconds( 200 );
	
	randTime = 0;
	stateTime = 0;
	velocity = 0;
}



void ParticleSystem::update( sf::Time elapsed )
{
	if( colorLifetime <= sf::Time::Zero )
	{
		colorLifetime = sf::milliseconds( 250 );
		color = sf::Color( std::rand() %0xFF, std::rand() %0xFF, std::rand()%0xFF );
	}
	colorLifetime -= elapsed;
	
	for( std::size_t i = 0; i < particles.size(); ++i )
	{
		// Update the particle lifetime.
		Particle& p = particles[ i ];
		p.lifetime -= elapsed;

		// If the particle is dead, respawn it.
		if( p.lifetime <= sf::Time::Zero )
		{
			resetParticle( i );
		}

		// Update the position of the corresponding vertex.
		vertices[ i ].position += p.velocity * elapsed.asSeconds();

		// Update the alpha (transparency) of the particle according to its lifetime.
		float ratio = p.lifetime.asSeconds() / lifetime.asSeconds();
		vertices[ i ].color.a = static_cast <sf::Uint8> ( ratio *0xFF );
	}
}

void ParticleSystem::setEmitter( sf::Vector2f position )
{
	emitter = position;
}

void ParticleSystem::setLifeTimeParameters( int randTime, int stateTime, float velocity )
{
	lifetime = sf::milliseconds( stateTime );
	this->randTime = randTime;
	this->stateTime = stateTime;
	this->velocity = velocity;
}

void ParticleSystem::create( unsigned count, sf::PrimitiveType primitiveType, float startX, float startY )
{
	particles = std::vector <Particle> ( count );
	vertices = sf::VertexArray( primitiveType, count );
	emitter = sf::Vector2f( startX, startY );
}


Loading_world::Loading_world()
{
	free();
}

Loading_world::~Loading_world()
{
	free();
}

void Loading_world::free()
{
	screen_w = 0;
	screen_h = 0;
	ready = 0;
	stop = false;
	back = false;
	
	state = 0;
	info.free();
	resetbutton.free();
	backbutton.free();
	
	counter = 0;
	max = 0;
	progress_bar.free();
	
	particleSystem.free();
	
	data = "";
	message = "";
	thread.free();
}
	
void Loading_world::load( float screen_w, float screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	// Set info.
	info.setIdentity( "loading_world-info" );
	info.setFont( "fonts/Jaapokki-Regular.otf" );
	info.setSize( screen_h /28 );
	
	
	// Set progress bar.
	max = 20;
	progress_bar.setIdentity( "loading_world-progress_bar" );
	progress_bar.load( "images/initialization/progress_bar.png", static_cast <int> (max) );
	progress_bar.setScale( screen_w /1707, screen_h /960 );
	progress_bar.setPosition( screen_w/2 - progress_bar.getWidth()/2, screen_h/2 +screen_h/36 );
	
	background_text.setIdentity( "loading_world-background_text" );
	background_text.setFont( "fonts/Jaapokki-Regular.otf" );
	background_text.setSize( screen_h /36 );
	
	reset();
	
	resetbutton.setIdentity( "loading_world-resetbutton" );
	resetbutton.setFont( "fonts/Jaapokki-Regular.otf" );
	int size = screen_h /28;
	resetbutton.create( "RELOAD", size, size /30 +2 );
	resetbutton.setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
	resetbutton.setColorText( sf::Color( 0x21, 0x21, 0x29 ) );
	resetbutton.setPosition( screen_w/2 -resetbutton.getWidth()/2, progress_bar.getBot() +screen_h/72 );
	resetbutton.fadeinGlobal( 0xFF );
	
	backbutton.setIdentity( "loading_world-backbutton" );
	backbutton.setFont( "fonts/Jaapokki-Regular.otf" );
	backbutton.create( "BACK", size, size /30 +2 );
	backbutton.setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
	backbutton.setColorText( sf::Color( 0x21, 0x21, 0x29 ) );
	backbutton.setPosition( screen_w /128, screen_h /72 );
	backbutton.fadeinGlobal( 0xFF );
	
	srand( time( NULL ) );
}

void Loading_world::handle( sf::Event& event )
{
	if( stop && ready < 2 && !back )
	{
		resetbutton.handle( event );
		backbutton.handle( event );
	}
}

void Loading_world::draw( sf::RenderWindow* &window )
{
	window->draw( info.get() );
	window->draw( progress_bar.get() );
	
	if( stop && ready < 2 )
	{
		resetbutton.draw( window );
		backbutton.draw( window );
		window->draw( background_text.get() );
		
		// Make the particle system emitter follow the mouse.
        sf::Vector2i mouse = sf::Mouse::getPosition( *window );
        particleSystem.setEmitter( window->mapPixelToCoords( mouse ) );
		
		window->draw( particleSystem );
	}
}

void Loading_world::mechanics( double elapsedTime )
{
	if( !back )
	{
		if( !stop )
		{
			progress_bar.setOffset( static_cast <int> (counter) );
		}
		
		if( ready < 2 )
		{
			if( resetbutton.getClicked() )
			{
				resetbutton.getClicked() = false;
				resetbutton.getFocus() = false;
				reset();
			}
			else if( backbutton.getClicked() )
			{
				backbutton.getClicked() = false;
				backbutton.getFocus() = false;
				back = true;
			}
		}
	}
	
	if( stop && ready < 2 )
	{
		resetbutton.mechanics( elapsedTime );
		backbutton.mechanics( elapsedTime );

        // Update it.
		sf::Time elapsed = clock.restart();
        particleSystem.update( elapsed );
	}
	
	counter += elapsedTime *0xFF /8;
	if( counter >= max )
	{
		counter = 0;
	}
	
	if( ready == 2 )
	{
		info.fadeout( elapsedTime *0xFF *2 );
		progress_bar.fadeout( elapsedTime *0xFF *2 );
	}
}



const sf::Uint8& Loading_world::getState()
{
	if( state < 0xFF )
	{
		state ++;
	}
	
	return state;
}

bool Loading_world::isReady()
{
	if( ready == 2 && progress_bar.getAlpha() == 0 )
	{
		return true;
	}
	
	return false;
}

int Loading_world::getReady()
{
	return ready;
}

void Loading_world::reset()
{
	// printf( "%d\n", ready );
	state = 0;
	stop = false;
	ready = 0;
	
	back = false;
	
	info.setText( "Downloading data..." );
	info.setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
	info.setPosition( screen_w/2 -info.getWidth()/2, screen_h/2 -info.getHeight()/2 -screen_h/72 );
	info.setAlpha( 0xFF );
	progress_bar.setAlpha( 0xFF );
	
	// Set particle system.
	particleSystem.free();
	float particleX = screen_w /2;
	float particleY = screen_h /2;
	int result = rand() %7;
	if( result == 0 )
	{
		particleSystem.create( 50000, sf::Points, particleX, particleY );
		particleSystem.setLifeTimeParameters( 2000, 1000, 75 );
		background_text.setText( "Background: 50 thousands particles, life time: 2.5 sec approx." );
	}
	else if( result == 1 )
	{
		particleSystem.create( 1000, sf::Lines, particleX, particleY );
		particleSystem.setLifeTimeParameters( 500, 500 );
		background_text.setText( "Background: 1000 lines, life time: 0.75 sec approx." );
	}
	else if( result == 2 )
	{
		particleSystem.create( 500, sf::LinesStrip, particleX, particleY );
		particleSystem.setLifeTimeParameters( 300, 500 );
		background_text.setText( "Background: 500 connected lines, life time: 0.65 sec approx." );
		
	}
	else if( result == 3 )
	{
		particleSystem.create( 50, sf::Triangles, particleX, particleY );
		particleSystem.setLifeTimeParameters( 500, 500 );
		background_text.setText( "Background: 50 triangles, life time: 0.75 sec approx." );
	}
	else if( result == 4 )
	{
		particleSystem.create( 100, sf::TrianglesStrip, particleX, particleY );
		particleSystem.setLifeTimeParameters( 500, 500 );
		background_text.setText( "Background: 100 connected triangles, life time: 0.75 sec approx." );
	}
	else if( result == 5 )
	{
		particleSystem.create( 300, sf::TrianglesFan, particleX, particleY );
		particleSystem.setLifeTimeParameters( 500, 500 );
		background_text.setText( "Background: 300 centered connected triangles, life time: 0.75 sec approx." );
	}
	else if( result == 6 )
	{
		particleSystem.create( 100, sf::Quads, particleX, particleY );
		particleSystem.setLifeTimeParameters( 400, 500 );
		background_text.setText( "Background: 100 quads, life time: 0.7 sec approx." );
	}
	
	background_text.setPosition( screen_w /256, screen_h -background_text.getHeight() *1.5 );
	background_text.setAlpha( 0xFF );
	
	thread.free();
	if( !message.empty() )
	{
		setThread();
	}
}

bool Loading_world::getStop()
{
	return stop;
}



void Loading_world::setError( string addError )
{
	info.setText( "We've got an error - " +addError );
	info.setColor( sf::Color( 0xF2, 0x58, 0x3E ) );
	info.setPosition( screen_w/2 -info.getWidth()/2, screen_h/2 -info.getHeight()/2 -screen_h/72 );
	stop = true;
}

void Loading_world::setSuccess()
{
	info.setText( "Rightly loaded data!" );
	info.setColor( sf::Color( 0x58, 0x70, 0x58 ) );
	info.setPosition( screen_w/2 -info.getWidth()/2, screen_h/2 -info.getHeight()/2 -screen_h/72 );
	stop = true;
	
	if( ready == 1 )
	{
		ready = 2;
	}
}

bool Loading_world::backToPrevious()
{
	return back;
}



void Loading_world::setMessage( string message )
{
	this->message = message;
}

void Loading_world::setThread()
{
	if( !thread.s && ready == 0 )
	{
		if( !thread.r && thread.t == NULL )
		{
			thread.t = new std::thread( [=] { prepare(); } );
			thread.t->detach();
		}
	}
}

void Loading_world::prepare()
{
	if( message[ 0 ] == '0' )	// local file
	{
		string newMessage = message;
		message.erase( 0, 1 );
		
		MyFile file;
		file.load( message );
		if( file.is_good() )
		{
			// Getline.
			getline( file.get(), data );
			thread.s = true;
			ready = 1;
		}
		else
		{
			thread.s = false;
			setError( "Can't' find local file." );
		}
		file.free();
		
		message = newMessage;
	}
	else if( message[ 0 ] == '1' )	// global file
	{
		string newMessage = message;
		message.erase( 0, 1 );
		
		
		message = newMessage;
	}
	
	thread.r = true;
}

string Loading_world::getData()
{
	return data;
}

bool Loading_world::ableData()
{
	if( thread.s && thread.r && ready == 1 )
	{
		thread.reset();
		return true;
	}
	
	return false;
}