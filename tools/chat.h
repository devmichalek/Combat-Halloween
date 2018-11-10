#pragma once
#include "sprite.h"
#include "text.h"
#include "fps.h"
#include "audio.h"
#include "coxing.h"
#include "eventwindow.h"

class Chat final
{
	sf::Color color;	// typical text color
	sf::Color ccolor;	// command color

	float screen_w;
	float screen_h;
	float scale_x;
	float scale_y;
	int max_text_length;
	
	float globalYScale;
	float globalYLine;

	bool active;
	bool used;

	static FPS fps;
	cmm::Sprite background;

	// Text written.
	cmm::Text username;
	static std::vector <cmm::Text*> writtens;
	static std::vector <std::string> writtenStrs;

	// Arrow.
	float line;
	float counter;
	cmm::Text arrow;

public:
	Chat();
	~Chat();
	void free();
	void reset();

	void load(const float &screen_w, const float &screen_h);
	void handle(const sf::Event &event);
	void draw(sf::RenderWindow* &window);
	void mechanics(const double &elapsedTime);
	void fadeout(const float &v, const int &min);

	// Getters.
	bool& isActive();
	bool isCommand();
	bool compCommand(std::string line);

	// Special.
	bool isNewCoxing();	// only for menu state
	bool checkCoxing();
	bool isNewMusicVolume();
	bool isNewSoundVolume();
	float getNewVolume();

private:
	void setWritten();
	void prepareWritten(int n, int k);	// n = nr of text, k nr of str
	int recognizeKey(std::string str);
	int recognizeActivity(std::string str);
public:
	void setError(std::string msg = " - command doesn't exist.");	// adds string to incorrect text

	// Set style.
	void setStyleBlackish();	// For light background.
	void setStyleWhitish();		// For dark background.
};