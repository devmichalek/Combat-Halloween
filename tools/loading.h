#pragma once
#include "core.h"
#include "state.h"
#include "text.h"
#include "sprite.h"
#include <SFML/Graphics/RenderWindow.hpp>

class LoadingState
{
protected:
	inline static sf::Uint8 state = 0;
public:
	static const sf::Uint8& getState();
};

class Loading final : public cmm::StaticCore, public cmm::State, public LoadingState
{
	// Support.
	inline static bool error_occured = false;
	inline static float screen_w;
	inline static float screen_h;
	
	// Current progress.
	static cmm::Text text;	// Text "loading 50%".
	static cmm::Text info;	// "Success: Blah blah"
	static cmm::Sprite progress_bar;
	
public:
	Loading();
	~Loading();
private:
	void free();
public:
	
	void load(const float &screen_w, const float &screen_h);
	void handle(const sf::Event &event) {}
	void draw(sf::RenderWindow* &window);
	void mechanics(const double &elapsedTime);

	static void add(std::string str);
	static const bool& isError();
	void setState(int &state);
private:
	void isFileExist(std::string pathToFile);
	void isDirExist(std::string pathToDir);
	bool isReady() const;
	void setText();
	static void setInfo(std::string str);
	static void drawPrivate();
};