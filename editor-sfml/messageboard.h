#pragma once
#include "sprite.h"
#include "text.h"

class MessageBoard
{
	enum TYPES	// types of message board, with two buttons "yes" and "no" or button "ok"
	{
		EMPTY = 0,
		YESNOACTIVE,
		OKACTIVE
	};

	enum DECISION
	{
		NO_DECISION = 0,
		YES,
		NO,
		OK
	};

	int active;
	int decision;

	cmm::Sprite board;
	cmm::Text infoText;
	cmm::Text yesText, noText, okText;
	sf::FloatRect yesRect, noRect;

public:
	MessageBoard();
	~MessageBoard();
private:
	void free();
public:
	void reset();

	void load(const float &screen_w, const float &screen_h);
	void handle(const sf::Event &event);
	void draw(sf::RenderWindow* &window);

	void setActive(int status = TYPES::YESNOACTIVE);
	void setMessage(std::string msg);

	const bool isActive() const;
	bool isDecision() const;
	const bool isYes();
	const bool isNo();
	const bool isOk();
};