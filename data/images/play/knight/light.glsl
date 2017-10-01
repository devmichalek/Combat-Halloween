#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 eye;
uniform vec2 resolution;
uniform float size;

float snoise( vec3 uv, float res )
{
	const vec3 s = vec3( 1e0, 1e2, 1e3 );
	
	uv *= res;
	
	vec3 uv0 = floor(mod(uv, res))*s;
	vec3 uv1 = floor(mod(uv+vec3(1.), res))*s;
	
	vec3 f = fract(uv); f = f*f*(3.0-2.0*f);

	vec4 v = vec4(uv0.x+uv0.y+uv0.z, uv1.x+uv0.y+uv0.z,
		      	  uv0.x+uv1.y+uv0.z, uv1.x+uv1.y+uv0.z);

	vec4 r = fract(sin(v*1e-1)*1e3);
	float r0 = mix(mix(r.x, r.y, f.x), mix(r.z, r.w, f.x), f.y);
	
	r = fract(sin((v + uv1.z - uv0.z)*1e-1)*1e3);
	float r1 = mix(mix(r.x, r.y, f.x), mix(r.z, r.w, f.x), f.y);
	
	return mix(r0, r1, f.z)*2.-1.;
}

void main( void )
{
	// Center.
	vec2 p = gl_FragCoord.xy / resolution.xy;
	p.x = p.x - eye.x / resolution.x;
	p.y = p.y + eye.y / resolution.y;
	p.y = p.y - 1.0;
	p.x*=resolution.x/resolution.y;
			  	
	float color = 3 -size*length( p );		
	
	vec3 coord = vec3( atan( p.x, p.y ) /6, length( p ) *2, 2 );
	
	color += snoise( coord + vec3( 1, -time*.07, time*.08 ), 12 );
	
	gl_FragColor = vec4( 0, 0, 0, -color );
}