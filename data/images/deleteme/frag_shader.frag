
// Set once.
uniform sampler2D texture;
uniform vec2 resolution;
uniform vec4 ambientColor; // The RGB values are the ambient light color and the alpha is the ambient intensity.

// Set every time
uniform float time;
uniform vec2 positions[ 20 ];
uniform vec4 lightColors[ 20 ];	// The RGB values are the light color and the alpha is the light intensity.
uniform float radii[ 20 ];	// Radius

void main()
{
	vec3 light;
	for( int i = 0; i < 20; i++ )
	{
		// Light's position.
		vec2 position = positions[ i ] /resolution.xx;

		// Makes the light change its size slightly to make a fire effect.
		float maxDistance = radii[ i ] +0.005 *sin( time );

		// Gets the distance from the light's position and the fragment coord.
		float distance = distance( gl_FragCoord.xy /resolution.xx, position );

		// Calculates the amount of light for the fragment.
		float value = 1.0 - smoothstep( -0.2, maxDistance, distance );

		// Calculates the light color for the pixel.
		light += (lightColors[ i ].rgb *lightColors[ i ].a *clamp( value, 0.0, 1.0 ));
	}
	
	// Gets the original color from the texture.
	vec4 pixel = texture2D( texture, gl_TexCoord[ 0 ].xy );

	// Applies the ambient light to the original pixel color.
	vec3 ambient = pixel.rgb *ambientColor.rgb *ambientColor.a;

	// Applies the light to the pixel.
	vec3 intensity = ambient +light;
	vec3 final = pixel.rgb *intensity;
	
	gl_FragColor = vec4( final, 1.0 );
}