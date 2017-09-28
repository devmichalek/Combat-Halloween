
uniform float time;
uniform vec2 position;
uniform vec2 resolution;
uniform sampler2D texture;

// The RGB values are the ambient light color.
// and the alpha is the ambient intensity.
uniform vec4 ambientColor;

// The RGB values are the light color.
// and the alpha is the light intensity.
uniform vec4 lightColor;

// Maximum radius of the light.
uniform float radius;

void main()
{
	// Light's position.
	vec2 position = position /resolution.xx;

	// Makes the light change its size slightly to make a fire effect.
	float maxDistance = radius +0.010 *sin( time );

	// Gets the distance from the light's position and the fragment coord.
	float distance = distance( gl_FragCoord.xy /resolution.xx, position );

	// Calculates the amount of light for the fragment.
	float value = 1.0 - smoothstep( -0.2, maxDistance, distance );

	// Gets the original color from the texture.
	vec4 pixel = texture2D( texture, gl_TexCoord[ 0 ].xy );

	// Applies the ambient light to the original pixel color.
	vec3 ambient = pixel.rgb *ambientColor.rgb *ambientColor.a;

	// Calculates the light color for the pixel.
	vec3 light = lightColor.rgb *lightColor.a *clamp( value, 0.0, 1.0 );

	// Applies the light to the pixel.
	vec3 intensity = ambient +light;
	vec3 final = pixel.rgb *intensity;

	gl_FragColor = vec4( final, 1.0 );
}