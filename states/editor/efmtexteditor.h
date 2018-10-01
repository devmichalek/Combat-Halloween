#pragma once
#include "eventwindow.h"
#include "sprite.h"
#include "text.h"

class EFMTextEditor
{
	enum DECISION
	{
		EMPTY = 0,
		CANCEL,
		PROCEED,
	};

	bool active;
	int decision;

	float screen_w;
	float screen_h;

	float arrow_line;
	float arrow_counter;

	cmm::Sprite board;
	cmm::Text infoText;
	cmm::Text formText;
	cmm::Text writtenText;
	cmm::Text arrowText;
	cmm::Text cancelText;
	cmm::Text proceedText;
	sf::FloatRect cancelRect, proceedRect;
	std::string msg;

public:
	EFMTextEditor();
	~EFMTextEditor();
private:
	void free();
public:
	void reset();	// reset decision
	void clear();	// reset active

	void load(const float &screen_w, const float &screen_h);
	void handle(const sf::Event &event);
	void draw(sf::RenderWindow* &window);
	void mechanics(const double &elapsedTime);

	void setActive();
	const bool& isActive() const;
	bool isDecision() const;
	bool isCancel();
	bool isProceed();

	void set(std::string info, std::string form, std::string written);
	std::string get();

	bool isMistake();
	const std::string& getMsg() const;

private:
	void setWrittenText();
	bool isPossibleKey(const sf::Uint8 &code) const;
};