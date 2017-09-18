#pragma once
#include "own/sprite.h"
#include "own/text.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

class Editor_buttons
{
	// Basics.
	float screen_w;
	float screen_h;
	
	enum
	{
		HOME = 0,
		OPTIONS,
		NAME,
		DELETE,
		LOAD,
		SAVE,
		UPLOAD,
		PLAY,
		AMOUNT
	};
	
	vector <bool> states;
	vector <MyText*> texts;
	vector <MySprite*> buttons;
	
	bool shift;
	bool deleteState;
	
public:
	
	// Basics.
	Editor_buttons();
	~Editor_buttons();
	void free();
	void reset();
	void load( float screen_w, float screen_h );
	void handle( sf::Event& event );
	void draw( sf::RenderWindow* &window );
	
	// Getters.
	bool isAnything();
	bool isHome();
	bool isOptions();
	bool isName();
	bool isDelete();
	bool isSave();
	bool isLoad();
	bool isPlay();
	bool isUpload();
	
	string getInfo();
	string getWorldname( string worldname );
	
	// Setters.
	void set( int w );
	void setHome();
	void setOptions();
	void setName();
	void setDelete();
	void setSave();
	void setLoad();
	void setPlay();
	void setUpload();
};