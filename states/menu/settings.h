#pragma once
#include "coxing.h"
#include "text.h"
#include "sound.h"
#include "sprite.h"
#include "eventwindow.h"

class Settings final : public cmm::Keys
{
	float screen_w;
	float screen_h;

	enum GEAR_POS
	{
		TOP = 0,
		BOT,
		LEFT,
		RIGHT
	};
	std::vector<cmm::Sprite*> gears;

	// Table.
	std::vector<sf::Rect<float>> text_collisions;
	std::vector<cmm::Text*> state_texts;
	std::vector<cmm::Text*> active_texts;
	cmm::Text contactme;
	cmm::Sprite table;
	float tableMoves;
	float x1, x2;

	// Chart.
	cmm::Text info;
	cmm::Sprite chart;
	cmm::Sprite resetbutton;
	float chartMoves;
	float y1, y2;

	int target;

	cmm::Sound click;

public:
	Settings();
	~Settings();
	void free();

	void load(const float &screen_w, const float &screen_h);
	bool handle(const sf::Event &event);
	void draw(sf::RenderWindow* &window);
	void mechanics(const double &elapsedTime);
	void fadein(const float &v, const int &max);
	void fadeout(const float &v, const int &min);

	// Support.
	void exsertTable(const double &elapsedTime);
	void shovelTable(const double &elapsedTime);
private:
	void resetCoxing();
	void setCoxing();
public: void reloadCoxing(); private:
	void positionTable();
	void positionChart();
	const std::string getName(const int &n);
public:
	void reset();
	void setVolume(const float &volume);
};