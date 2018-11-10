// This file is part of game called 'Combat Halloween'
// Author: Adrian Michalek
// Date: 09.11.2018
// Read more about license (MIT) and readme here:
// https://github.com/devmichalek/Combat-Halloween

#include "lightsystem.h"

pla::LightSystem::LightSystem()
{
	free();
}

pla::LightSystem::~LightSystem()
{
	free();
}

void pla::LightSystem::free()
{
	screen_w = screen_h = 0.0f;

	staticLPTree = nullptr;
	dynamicLPTree = nullptr;

	shader = nullptr;

	reset();
}

void pla::LightSystem::reset()
{
	if (!radii.empty())			radii.clear();
	//if (!maxDistances.empty())maxDistances.clear();
	if (!colors.empty())		colors.clear();
	//if (!subcolors.empty())	subcolors.clear();
	//if (!gpositions.empty())	gpositions.clear();
	if (!units.empty())
	{
		for (auto &it : units)
		{
			if (it)
			{
				delete it;
				it = nullptr;
			}
		}
		units.clear();
	}

	if (!positions.empty())
	{
		for (auto &it : positions)
		{
			if (it)
			{
				delete it;
				it = nullptr;
			}
		}

		positions.clear();
	}

	if (staticLPTree)
	{
		delete staticLPTree;
		staticLPTree = nullptr;
	}

	if (dynamicLPTree)
	{
		delete dynamicLPTree;
		dynamicLPTree = nullptr;
	}

	if (!lightPointResult.empty())	lightPointResult.clear();

	length = 0;
	ssize = dsize = 0;

	if (shader)
	{
		delete shader;
		shader = nullptr;
	}

	clock.restart();
	time = frameTime = clock.restart();
}

void pla::LightSystem::init(const float &screen_w, const float &screen_h)
{
	free();

	this->screen_w = screen_w;
	this->screen_h = screen_h;
}

void pla::LightSystem::prepare(const int &count)
{
	assert(length == 0);
	length = radii.size();

	const bool status = length == ssize + dsize;
	assert(status);

	shader = new sf::Shader;

	// Dynamicly created shader to speed up GLSL program execution
	// and to set the boundaries of array (not waste of memory)

	const std::string vertexShader = \
		"void main()" \
		"{" \
		"gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;" \
		"gl_TexCoord[ 0 ] = gl_TextureMatrix[ 0 ] * gl_MultiTexCoord0;" \
		"gl_FrontColor = gl_Color;" \
		"}";

	const std::string fragmentShader = \
		"uniform sampler2D texture;" \
		"const vec2 resolution = vec2(" + std::to_string(screen_w) + "," + std::to_string(screen_h) + ");" \
		"const vec4 ambientColor = vec4(0.0, 0.0, 0.3, 0.5);" \
		"uniform float addAlpha = 1.0;" \
		"uniform float globalAlpha = 0.0;" \
		"uniform int arraySize = 0;" \
		"uniform vec2 positions[" + std::to_string(count) + "];" \
		"uniform vec4 lightColors[" + std::to_string(count) + "];" \
		"uniform float maxDistances[" + std::to_string(count) + "];" \

		"void main()" \
		"{" \
		"vec3 light;" \
		"float distance;" \
		"float value;" \

		"for(int i = 0; i < arraySize; ++i)" \
		"{" \
		"distance = distance(gl_FragCoord.xy /resolution.xx, positions[i]);" \
		"value = 1.0 - smoothstep(-0.2, maxDistances[i], distance);" \
		"light += (lightColors[ i ].rgb *lightColors[ i ].a *clamp( value, 0.0, 1.0 ));" \
		"}" \

		"vec4 pixel = texture2D( texture, gl_TexCoord[0].xy );" \
		"vec3 ambient = pixel.rgb *ambientColor.rgb *ambientColor.a;" \
		"vec3 intensity = ambient +light;" \
		"vec3 final = pixel.rgb * vec3(1.0, 1.0, 1.0) * intensity;" \

		"gl_FragColor = vec4( final, pixel.a *addAlpha *globalAlpha );" \
		"}";

	if (shader->loadFromMemory(vertexShader, fragmentShader))
	{
		shader->setUniform("texture", sf::Shader::CurrentTexture);
		shader->setUniform("globalAlpha", 1.0f);
	}

	radii.shrink_to_fit();
	maxDistances.reserve(count);
	colors.shrink_to_fit();
	subcolors.reserve(count);
	positions.shrink_to_fit();
	gpositions.reserve(count);

	for (int i = 0; i < count; ++i)
	{
		maxDistances.push_back(0.0f);
		subcolors.push_back(sf::Glsl::Vec4());
		gpositions.push_back(sf::Vector2f());
	}
	maxDistances.shrink_to_fit();
	subcolors.shrink_to_fit();
	gpositions.shrink_to_fit();
}

void pla::LightSystem::add(LightPoint lp)
{
	radii.push_back(lp.radius);
	//maxDistances.push_back(lp.maxDistance);
	colors.push_back(lp.color);
	//subcolors.push_back(lp.color);
	//gpositions.push_back(lp.gposition);
}

void pla::LightSystem::addStaticLightPoint(StaticLightPoint &slp)
{
	add(*dynamic_cast<LightPoint*>(&slp));
	positions.push_back(new sf::Vector2f(slp.position));

	float hradius = slp.radius / 2;		// half radius
	float l = slp.position.x - hradius;	// left
	float r = slp.position.x + hradius; // right
	float t = slp.position.y - hradius; // top
	float b = slp.position.y + hradius; // bot

	Box box(Point(l, t), Point(r, b));
	staticLPTree->insert(std::make_pair(box, ssize + dsize));

	units.push_back(new StaticLightUnit()); // same as nullptr for ptrs

	++ssize;
}

void pla::LightSystem::addDynamicLightPoint(DynamicLightPoint &dlp)
{
	add(*dynamic_cast<LightPoint*>(&dlp));
	sf::Vector2f* trace = new sf::Vector2f(dlp.points[0]);
	positions.push_back(trace);

	float hradius = dlp.radius / 2;			// half radius
	float l = dlp.points[0].x - hradius;	// left
	float r = dlp.points[0].x + hradius;	// right
	float t = dlp.points[0].y - hradius;	// top
	float b = dlp.points[0].y + hradius;	// bot

	for (auto it : dlp.points) // find the boundaries
	{
		if (it.x - hradius < l)	l = it.x - hradius;
		if (it.x + hradius > r)	r = it.x + hradius;
		if (it.y - hradius < t)	t = it.y - hradius;
		if (it.y + hradius > b)	b = it.y + hradius;
	}

	Box box(Point(l, t), Point(r, b));
	dynamicLPTree->insert(std::make_pair(box, ssize + dsize));

	units.push_back(new DynamicLightUnit(trace, dlp.points));

	++dsize;
}

void pla::LightSystem::read(std::vector<std::string> &vec)
{
	staticLPTree = new StaticLPTree;
	dynamicLPTree = new DynamicLPTree;

	int x = -1, y = -1;
	float r;
	std::string str;
	if (!vec.empty())
	{
		for (auto &it : vec)
		{
			//c = boost::lexical_cast<int>(it.substr(it.find("c:") + 2, it.find(" x:") - (it.find("c:") + 2)));

			// start position
			x = boost::lexical_cast<int>(it.substr(it.find("x:") + 2, it.find(" y:") - (it.find("x:") + 2)));
			y = boost::lexical_cast<int>(it.substr(it.find("y:") + 2, it.find(" id:") - (it.find("y:") + 2)));
			
			// radius
			r = boost::lexical_cast<float>(it.substr(it.find("radius:") + 7, it.find(" color:") - (it.find("radius:") + 7)));

			// color
			std::vector<float> c;
			std::string buf = "";
			str = it.substr(it.find("color:(") + 7, it.size() - (it.find("color:(") + 7));
			str.replace(str.size() - 2, str.size() - 1, ",");
			for (size_t i = 0; i < str.size(); ++i)
			{
				if (str[i] == ',')
				{
					c.push_back(boost::lexical_cast<float>(buf));
					buf = "";
				}
				else
					buf += str[i];
			}

			// ai:((points:((x,y),(x,y),(x,y)) radius:r color:(r,g,b,a)))
			if (it.find("points:()") == std::string::npos)
			{
				str = it.substr(it.find("points:(") + 8, it.find(") radius:") - (it.find("points:(") + 8));
				std::vector<sf::Vector2f> pts;
				pts.push_back(sf::Vector2f(x, y));
				size_t p1, p2;
				for(;;)
				{
					p1 = str.find('(') + 1;
					p2 = str.find(')'); if (p2 == std::string::npos)	break;
					buf = str.substr(p1, p2 - p1);

					float tx, ty;
					std::string tmp = "";
					for (size_t i = 0; i < buf.size(); ++i)
					{
						if (buf[i] == ',') // -> y
						{
							tx = boost::lexical_cast<float>(tmp);
							tmp = "";
							for (size_t j = 0; j < buf.size(); ++j)
								tmp += buf[j];
							ty = boost::lexical_cast<float>(tmp);
							pts.push_back(sf::Vector2f(tx, ty));
						}
						tmp += buf[i];
					}

					str.erase(0, p2 + 1);
				}

				DynamicLightPoint dlp(LightPoint(r, sf::Glsl::Vec4(c[0], c[1], c[2], c[3])), pts);
				addDynamicLightPoint(dlp);
			}
			else
			{
				StaticLightPoint slp(LightPoint(r, sf::Glsl::Vec4(c[0], c[1], c[2], c[3])), sf::Vector2f(x, y));
				addStaticLightPoint(slp);
			}
		}
	}
}

void pla::LightSystem::mechanics(const double &elapsedTime, const float &x, const float &y)
{
	// Prepare timers before calculating.
	frameTime = clock.restart();
	time += frameTime;

	// Prepare query box.
	Box queryBox(Point(x, y), Point(x + screen_w, y + screen_h));

	lightPointResult.clear();
	dynamicLPTree->query(bgi::intersects(queryBox), std::back_inserter(lightPointResult));	// DYNAMIC TREE
	staticLPTree->query(bgi::intersects(queryBox), std::back_inserter(lightPointResult));	// STATIC TREE

	int lsize = lightPointResult.size(), id = 0;	// local size, id
	for (size_t i = 0; i < lsize; ++i)
	{
		id = lightPointResult[i].second;
		gpositions[i].x = positions[id]->x / screen_w;
		gpositions[i].y = positions[id]->y / screen_h;
		maxDistances[i] = radii[id] / screen_w + 0.005 * sin(10 * time.asSeconds());
		subcolors[i] = colors[id];
		units[id]->calculate(elapsedTime); // calculate dynamic/static lights
	}

	if (lsize == 0)
		return;

	shader->setUniform("arraySize", lsize);
	shader->setUniformArray("maxDistances", &std::vector<float>(maxDistances.begin(), maxDistances.begin() + lsize)[0], lsize);
	shader->setUniformArray("lightColors", &std::vector<sf::Glsl::Vec4>(subcolors.begin(), subcolors.begin() + lsize)[0], lsize);
	shader->setUniformArray("positions", &std::vector<sf::Glsl::Vec2>(gpositions.begin(), gpositions.begin() + lsize)[0], lsize);
	//shader->setUniform("addAlpha", 1.0f); <- unique uniform
}

sf::Shader* &pla::LightSystem::getShader()
{
	return shader;
}