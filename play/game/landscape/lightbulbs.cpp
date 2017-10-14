#include "lightbulbs.h"
#include "own/file.h"

LightBulbPoint::LightBulbPoint( float x, float y )
{
	this->x = x;
	this->y = y;
	xS = x;
	yS = y;
	radius = 100;
	velocity = 50;
	color = sf::Glsl::Vec4( 1.0, 1.0, 1.0, 2.0 );
	
	state = 1;
	direction = true;
	
	if( !points.empty() )
	{
		points.clear();
	}
}

LightBulbPoint::~LightBulbPoint()
{
	x = 0;
	y = 0;
	radius = 0;
	velocity = 0;
	color = sf::Glsl::Vec4( 1.0, 1.0, 1.0, 2.0 );
	
	state = 1;
	direction = true;
	
	if( !points.empty() )
	{
		points.clear();
	}
}

void LightBulbPoint::calculate( double elapsedTime )
{
	bool xState = x < points[ state ].x ? x > points[ state ].x : false;
	bool yState = y < points[ state ].y ? y > points[ state ].y : false;
	
	// X Y.
	float vel = elapsedTime *velocity /100;
	float xValue = (points[ state ].x -xS) *vel;
	float yValue = (points[ state ].y -yS) *vel;
	
	x += xValue;
	y += yValue;
	
	if( xState !=  (x < points[ state ].x ? x > points[ state ].x : false) )	x = points[ state ].x;
	if( yState !=  (y < points[ state ].y ? y > points[ state ].y : false) )	y = points[ state ].y;
	
	float xDiff = static_cast <unsigned> (points[ state ].x) -static_cast <unsigned> (x);
	float yDiff = static_cast <unsigned> (points[ state ].y) -static_cast <unsigned> (y);
	
	// New.
	if( xDiff < 5 && yDiff < 5 )
	{
		if( state == 0 )						direction = true;
		else if( state == points.size() -1 )	direction = false;
		
		if( direction )	state ++;
		else			state --;
		
		xS = x;
		yS = y;
	}
}

bool LightBulbPoint::isVisible( float bx, float by, float screen_w, float screen_h )
{
	if( x -radius > bx +screen_w || y -radius > by +screen_h )
	{
		return false;
	}
	
	if( x +radius < bx || y +radius < by )
	{
		return false;
	}
	
	return true;
}


LightBulbs::LightBulbs()
{
	free();
}

LightBulbs::~LightBulbs()
{
	free();
}

void LightBulbs::free()
{
	screen_w = 0;
	screen_h = 0;
	
	reset();
}

void LightBulbs::reset()
{
	border_x = 0;
	border_y = 0;
	
	alpha = 0;
	arraySize = 0;
	
	if( !radii.empty() )
	{
		radii.clear();
	}
	
	if( !colors.empty() )
	{
		colors.clear();
	}
	
	if( !positions.empty() )
	{
		positions.clear();
	}
	
	if( !lightBulbPoints.empty() )
	{
		lightBulbPoints.clear();
	}
	
	error = "";
	thread.free();
	threadShader.free();
	threadShader.r = true;
	
	// Set shader.
	const std::string vertexShader = \
	"void main()" \
	"{" \
	"gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;" \
	"gl_TexCoord[ 0 ] = gl_TextureMatrix[ 0 ] * gl_MultiTexCoord0;" \
	"gl_FrontColor = gl_Color;" \
	"}";

	const std::string fragmentShader = \
	"uniform sampler2D texture;" \
	"uniform vec2 resolution;" \
	"uniform vec4 ambientColor;" \
	"uniform float addAlpha = 1.0;" \
	"uniform float globalAlpha = 0.0;" \
	"uniform vec4 hiddenColor = vec4(1.0, 1.0, 1.0, 1.0);" \
	"uniform int arraySize = 0;" \
	"uniform float time;" \
	"uniform vec2 positions[ 12 ];" \
	"uniform vec4 lightColors[ 12 ];" \
	"uniform float radii[ 12 ];" \
	"void main()" \
	"{" \
	"vec3 light;" \
	"for( int i = 0; i < arraySize; i++ )" \
	"{" \
	"vec2 position = positions[ i ] /resolution.xx;" \
	"float maxDistance = radii[ i ] +0.005 *sin( time );" \
	"float distance = distance( gl_FragCoord.xy /resolution.xx, position );" \
	"float value = 1.0 - smoothstep( -0.2, maxDistance, distance );" \
	"light += (lightColors[ i ].rgb *lightColors[ i ].a *clamp( value, 0.0, 1.0 ));" \
	"}" \
	"vec4 pixel = texture2D( texture, gl_TexCoord[ 0 ].xy );" \
	"vec3 ambient = pixel.rgb *ambientColor.rgb *ambientColor.a;" \
	"vec3 intensity = ambient +light;" \
	"vec3 final = pixel.rgb *hiddenColor.rgb *intensity;" \
	"gl_FragColor = vec4( final, pixel.a *addAlpha *globalAlpha );" \
	"}";
	
	if( shader.loadFromMemory( vertexShader, fragmentShader ) )
	{
		shader.setUniform( "texture", sf::Shader::CurrentTexture );
		shader.setUniform( "resolution", sf::Glsl::Vec2( screen_w, screen_h ) );
		shader.setUniform( "ambientColor", sf::Glsl::Vec4( 0.0, 0.0, 0.3, 0.5 ) ); // 0.0, 0.0, 0.3, 0.5 - navy blue.
	}
}

void LightBulbs::load( float screen_w, float screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
}

void LightBulbs::mechanics( double elapsedTime )
{
	if( threadShader.r )
	{
		threadShader.reset();
		threadShader.t = new std::thread( [=] { calculation( elapsedTime ); } );
		threadShader.t->detach();
	}
}

void LightBulbs::calculation( double elapsedTime )
{
	arraySize = 0;
	
	for( unsigned i = 0; i < lightBulbPoints.size(); i++ )
	{
		// 2 times higher view.
		if( lightBulbPoints[ i ].isVisible( border_x -screen_w/2, border_y -screen_h/2, screen_w*2, screen_h*2 ) )
		{
			lightBulbPoints[ i ].calculate( elapsedTime );
			radii[ arraySize ] = lightBulbPoints[ i ].radius;
			colors[ arraySize ] = lightBulbPoints[ i ].color;
			positions[ arraySize ] = sf::Glsl::Vec2( lightBulbPoints[ i ].x -border_x, screen_h -lightBulbPoints[ i ].y +border_y );
			arraySize ++;
		}
	}
	
	/*
	for( int i = arraySize; i < radii.size(); i++ )
	{
		radii[ i ] = 0.0;
		colors[ i ] = sf::Glsl::Vec4( 0.0, 0.0, 0.0, 0.0 );
		positions[ i ] = sf::Glsl::Vec2( 0.0, 0.0 );
	}
	*/
	
	// printf( "%d\n", arraySize );
	
	frameTime = clock.restart();
	time += frameTime;
	
	shader.setUniform( "arraySize", arraySize );
	shader.setUniform( "time", 10 *time.asSeconds() );
	shader.setUniformArray( "radii", &vector<float>( radii.begin(), radii.begin() +arraySize )[ 0 ], arraySize );
	shader.setUniformArray( "lightColors", &vector<sf::Glsl::Vec4>( colors.begin(), colors.begin() +arraySize )[ 0 ], arraySize );
	shader.setUniformArray( "positions", &vector<sf::Glsl::Vec2>( positions.begin(), positions.begin() +arraySize )[ 0 ], arraySize );
	
	threadShader.r = true;
}

void LightBulbs::setAlpha( float alpha )
{
	this->alpha = alpha /0xFF;
	shader.setUniform( "globalAlpha", this->alpha );
}



bool LightBulbs::isNull()
{
	// Delete thread.
	if( thread.t != NULL && thread.r )
	{
		thread.reset();
		return true;
	}
	
	if( thread.t == NULL )
	{
		return true;
	}
	
	return false;
}

bool LightBulbs::isReady()
{
	return thread.s;
}

void LightBulbs::setThread( string message )
{
	if( !thread.s )
	{
		if( !thread.r && thread.t == NULL )
		{
			thread.t = new std::thread( [=] { prepare( message ); } );
			thread.t->detach();
		}
	}
}

void LightBulbs::prepare( string message )
{
	string line = message;
	
	// Bufor and start.
	string bufor = "";
	unsigned start = 0;
	
	
	// AUTHOR --------------------------------------------------------------------------
	for( unsigned i = start; i < line.size(); i++ )
	{
		if( line[ i ] == '|' )
		{
			start = i +1;
			// printf( "%s\n", bufor.c_str() );
			bufor = "";
			break;
		}
		
		bufor += line[ i ];
	}
	
	
	// NEW SIZES --------------------------------------------------------------------------
	float my_screen_w = 0;
	float my_screen_h = 0;
	
	// Set my_screen_w.
	for( unsigned i = start; i < line.size(); i++ )
	{
		if( line[ i ] == '|' )
		{
			start = i +1;
			my_screen_w = screen_w -con::stof( bufor );
			bufor = "";
			break;
		}
		
		bufor += line[ i ];
	}
	
	// Set my_screen_h.
	for( unsigned i = start; i < line.size(); i++ )
	{
		if( line[ i ] == '|' )
		{
			start = i +1;
			my_screen_h = screen_h -con::stof( bufor ) +1;
			bufor = "";
			break;
		}
		
		bufor += line[ i ];
	}
	
	// Fill vectors.
	for( unsigned i = 0; i < 11; i++ )
	{
		radii.push_back( 0.0 );
		colors.push_back( sf::Glsl::Vec4( 0.0, 0.0, 0.0, 0.0 ) );
		positions.push_back( sf::Glsl::Vec2( 0.0, 0.0 ) );
	}
	
	bool isError = false;
	// FS --------------------------------------------------------------------------
	for( unsigned i = start; i < line.size(); i++ )
	{
		if( line[ i ] == '|' )
		{
			bufor += "*";
			string nrstr = "";
			vector <string> data;
			
			bool wrong = false;
			for( unsigned j = 0; j < bufor.size(); j++ )
			{
				if( bufor[ j ] == '*' )
				{
					if( data.size() == 0 )
					{
						if( con::stoi( nrstr ) != 6 )
						{
							wrong = true;
							break;
						}
					}
					
					data.push_back( nrstr );
					nrstr = "";
				}
				else
				{
					nrstr += bufor[ j ];
				}
			}
			
			if( !wrong )
			{
				if( data.size() < 2 )
				{
					error = "Light point is depracated.";
					isError = true;
					break;
				}
				else if( data.size() < 12 )
				{
					error = "Light point x=" +data[ 2 ] +" y=" +data[ 3 ] +" has no path.";
					isError = true;
					break;
				}
				
				sf::Uint8 w = con::stoi( data[ 0 ] );
				sf::Uint8 t = con::stoi( data[ 1 ] );
				float x = con::stoi( data[ 2 ] );
				float y = con::stoi( data[ 3 ] ) +my_screen_h;
				
				if( w == 6 )
				{
					// x, y.
					lightBulbPoints.push_back( LightBulbPoint( con::stof( data[ 9 ] ), con::stof( data[ 10 ] ) ) );
					// r, v, color.
					lightBulbPoints[ lightBulbPoints.size() -1 ].radius = con::stof( data[ 4 ] ) /720;
					lightBulbPoints[ lightBulbPoints.size() -1 ].velocity = con::stoi( data[ 5 ] );
					sf::Color color( con::stoi( data[ 6 ] ), con::stoi( data[ 7 ] ), con::stoi( data[ 8 ] ) );
					float r = static_cast <float> (color.r) /0xFF;
					float g = static_cast <float> (color.g) /0xFF;
					float b = static_cast <float> (color.b) /0xFF;
					lightBulbPoints[ lightBulbPoints.size() -1 ].color = sf::Glsl::Vec4( r, g, b, 2.0 );
					// lines.
					for( unsigned i = 9; i < data.size(); i += 2 )
					{
						float newX = con::stoi( data[ i ] );
						float newY = con::stoi( data[ i +1 ] );
						lightBulbPoints[ lightBulbPoints.size() -1 ].points.push_back( sf::Vector2f( newX, newY ) );
					}
				}
			}
			
			// Clear.
			bufor = "";
		}
		else
		{
			bufor += line[ i ];
		}
	}
	
	if( !isError )
	{
		// Inform that everything is ok.
		thread.s = true;
	}
	
	// Inform that thread is ready for next action.
	thread.r = true;
}

string LightBulbs::getError()
{
	return error;
}



void LightBulbs::setBorderX( float x )
{
	border_x = x;
}

void LightBulbs::setBorderY( float y )
{
	border_y = y;
}



sf::Shader& LightBulbs::getShader()
{
	return shader;
}
