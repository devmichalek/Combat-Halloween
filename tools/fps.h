#pragma once
#include "text.h"
#include "fpsconsole.h"
#include <SFML/Graphics/RenderWindow.hpp>

class FPS final
{
	enum POSITION
	{
		NONE = -1,
		LEFT_TOP = 0,
		RIGHT_TOP,
		LEFT_BOT,
		RIGHT_BOT
	};

	sf::Int8 position;
	cmm::Text text;
	cmm::FPSConsole fps;

	bool active;
	float screen_w;
	float screen_h;

public:
	FPS();
	~FPS();
private:
	void free();
public:
	void reset();

	void load(const float &screen_w, const float &screen_h);
	void draw(sf::RenderWindow* &window);
	void mechanics(const double &elapsedTime);
	void fadeout(const float &v, const int &min);

	const bool& isActive() const;
	void setActive(bool active);

	void setLeftTop();
	void setRightTop();
	void setLeftBot();
	void setRightBot();
private:
	void setText();
};