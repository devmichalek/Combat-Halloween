#pragma once
#include "circlebutton.h"
#include "sprite.h"
#include "text.h"

class EFMButtons	// Editor File Manager Buttons
{
	enum TYPES
	{
		NEW = 0,
		OPEN,
		SAVE,
		UPLOAD,
		COPY,
		RENAME,
		DELETE,
		REFRESH,
		EXIT,
		SIZE
	};

	bool active;
	CircleButton fileButton;
	cmm::Text fileButtonText;
	std::vector<bool> states;
	std::vector<cmm::Text*> labels;
	std::vector<cmm::Sprite*> buttons;

public:
	EFMButtons();
	~EFMButtons();
private:
	void free();
public:
	void reset();

	void load(const float &screen_w, const float &screen_h, const float l, const float &r, const float &y);
	bool handle(const sf::Event &event);
	void draw(sf::RenderWindow* &window);
	void drawButton(sf::RenderWindow* &window);
	void mechanics(/*const double &elapsedTime*/);

	bool isNewFile();
	bool isOpenFile();
	bool isSaveFile();
	bool isUploadFile();
	bool isCopyFile();
	bool isRenameFile();
	bool isDeleteFile();
	bool isRefresh();
	bool isExit();		// after exit we have to reset page etc.
	const bool& isActive() const;
	void setActive();	// for chat

	float getBot() const;
};