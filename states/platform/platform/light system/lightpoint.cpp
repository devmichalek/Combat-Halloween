#include <lightpoint.h>
#include <cassert>

LightPoint::LightPoint()
{
	free();
}

LightPoint::LightPoint(const LightPoint &lp)
{
	radius = lp.radius;
	maxDistance = lp.maxDistance;
	color = lp.color;
	gposition = lp.gposition;
}

LightPoint::~LightPoint()
{
	free();
}

void LightPoint::free()
{
	radius = 0.0f;
	maxDistance = 0.0f;
	color = sf::Glsl::Vec4(1.0f, 1.0f, 1.0f, 2.0f);
	gposition = sf::Glsl::Vec2(0.0f, 0.0f);
}



StaticLightPoint::StaticLightPoint()
{
	position = sf::Glsl::Vec2(0.0f, 0.0f);
}

StaticLightPoint::StaticLightPoint(const LightPoint &lp, const sf::Vector2f &position) : LightPoint(lp)
{
	this->position = position;
}

StaticLightPoint::StaticLightPoint(const float &radius, const sf::Glsl::Vec4 &color, const sf::Vector2f &position)
{
	this->radius = radius;
	maxDistance = 0.0f;
	this->color = color;
	this->position = sf::Vector2f(position);
	gposition = sf::Glsl::Vec2(0.0f, 0.0f);
}

StaticLightPoint::~StaticLightPoint()
{
	position = sf::Glsl::Vec2(0.0f, 0.0f);
}



DynamicLightUnit::DynamicLightUnit(sf::Vector2f* &address, const std::vector<sf::Vector2f> &points)
{
	current = 0;
	next = 1;
	direction = true;
	position = address;
	this->points = points;
	this->points.shrink_to_fit();
	length = points.size();
}

DynamicLightUnit::~DynamicLightUnit()
{
	free();
}

void DynamicLightUnit::free()
{
	current = 0;
	next = 1;
	length = 0;
	direction = true;

	if (position) // should never happen...
	{
		delete position;
		position = nullptr;
	}

	if(!points.empty())
		points.clear();
}

void DynamicLightUnit::calculate(const double &elapsedTime)
{
	//...
}



DynamicLightPoint::DynamicLightPoint()
{
	points = {};
}

DynamicLightPoint::DynamicLightPoint(const LightPoint &lp, const std::vector<sf::Vector2f> &points) : LightPoint(lp)
{
	this->points = points;
	this->points.shrink_to_fit();
}

DynamicLightPoint::DynamicLightPoint(const float &radius, const sf::Glsl::Vec4 &color, const std::vector<sf::Vector2f> &points)
{
	this->points = points;
	this->points.shrink_to_fit();
}

DynamicLightPoint::~DynamicLightPoint()
{
	if (!points.empty())
		points.clear();
}


LightPoints::LightPoints()
{
	free();
}

LightPoints::~LightPoints()
{
	free();
}

void LightPoints::free()
{
	screen_w = screen_h = 0.0f;

	staticLPTree = nullptr;
	dynamicLPTree = nullptr;

	shader = nullptr;

	reset();
}

void LightPoints::reset()
{
	if (!radii.empty())			radii.clear();
	if (!maxDistances.empty())	maxDistances.clear();
	if (!colors.empty())		colors.clear();
	if (!gpositions.empty())	gpositions.clear();

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

	if (!staticLPResult.empty())	staticLPResult.clear();
	if (!dynamicLPResult.empty())	dynamicLPResult.clear();

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

void LightPoints::init(const float &screen_w, const float &screen_h)
{
	free();

	this->screen_w = screen_w;
	this->screen_h = screen_h;
}

void LightPoints::prepare(const int &count)
{
	assert(length == 0, "Length is bigger than 0!");
	length = radii.size();

	const bool status = length == ssize + dsize;
	assert(status, "Size of vectors do not match!");

	shader = new sf::Shader;

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
	maxDistances.shrink_to_fit();
	colors.shrink_to_fit();
	positions.shrink_to_fit();
	gpositions.shrink_to_fit();
}

void LightPoints::add(LightPoint lp)
{
	radii.push_back(lp.radius);
	maxDistances.push_back(lp.maxDistance);
	colors.push_back(lp.color);
	gpositions.push_back(lp.gposition);
}

void LightPoints::addStaticLightPoint(StaticLightPoint &slp)
{
	add(*dynamic_cast<LightPoint*>(&slp));
	positions.push_back(new sf::Vector2f(slp.position));

	float hradius = slp.radius / 2;		// half radius
	float l = slp.position.x - hradius;	// left
	float r = slp.position.x + hradius; // right
	float t = slp.position.y - hradius; // top
	float b = slp.position.y + hradius; // bot

	Box box(Point(l, t), Point(r, b));
	staticLPTree->insert(box);

	++ssize;
}

void LightPoints::addDynamicLightPoint(DynamicLightPoint &dlp)
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
	dynamicLPTree->insert(std::make_pair(box, DynamicLightUnit(trace, dlp.points)));

	++dsize;
}

void LightPoints::mechanics(const double &elapsedTime, const float &x, const float &y)
{
	staticLPResult.clear();
	Box queryBox(Point(x, y), Point(x + screen_w, y + screen_h));
	staticLPTree->query(bgi::intersects(queryBox), std::back_inserter(staticLPResult));

	float tx = 0, ty = 0;
	BOOST_FOREACH(StaticLPBox const& item, staticLPResult)
	{
		tx = bg::get<0>(item.min_corner());
		ty = bg::get<1>(item.min_corner()) + screen_h;
		
	}

	frameTime = clock.restart();
	time += frameTime;

	// local
	size_t lssize = staticLPResult.size();
	size_t ldsize = dynamicLPResult.size();
	for (int i = 0; i < lssize; ++i)
	{
		gpositions[i].x = positions[i].x / core.getWidth();
		gpositions[i].y = positions[i].y / core.getWidth();
		maxDistances[i] = radii[i] + 0.005 * sin(10 * time.asSeconds());
	}

	shader->setUniform("arraySize", size);
	shader->setUniformArray("maxDistances", &std::vector<float>(maxDistances.begin(), maxDistances.begin() + size)[0], size);
	shader->setUniformArray("lightColors", &std::vector<sf::Glsl::Vec4>(colors.begin(), colors.begin() + size)[0], size);
	shader->setUniformArray("positions", &std::vector<sf::Glsl::Vec2>(gpositions.begin(), gpositions.begin() + size)[0], size);
	shader->setUniform("addAlpha", 1.0f);
}

sf::Shader* &LightPoints::getShader()
{
	return shader;
}