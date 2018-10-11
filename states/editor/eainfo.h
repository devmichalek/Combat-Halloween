#pragma once
#include "text.h"
#include "eakind.h"
#include "eventwindow.h"

class EAInfo : public EAKind
{
	enum TEXTS
	{
		GRIDFORM = 0,
		GRID,
		CHOSENFORM,
		CHOSEN,
		CATEGORYFORM,
		CATEGORY,
		DESCRIPTIONFORM,
		DESCRIPTION,
		OPTIONSFORM,
		OPTIONS,
		SIZE
	};

	std::vector<cmm::Text*> texts;

public:
	EAInfo();
	~EAInfo();
private:
	void free();
public:
	void reset();

	void load(const float &screen_w, const float &screen_h);
	void draw(sf::RenderWindow* &window);
	void set(const int &newType, const int &newChosen);

private:
	void setChosenText(std::string line);
	void setCategoryText(std::string line);
	void setDescriptionText(std::string line);
	void setOptionsText(bool getable);
	void setGridText(bool grid);

	std::string getChosenStr();
	std::string getTypeStr();
	std::string getDescriptionStr();
	bool areOptionsGetable();
public:
	bool isGridNeeded();
};