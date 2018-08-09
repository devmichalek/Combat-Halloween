// This class holds all buttons.
#pragma once
#include "buttonstate.h"
#include <qpushbutton.h>
#include <vector>

class ButtonFactory :public QObject
{
	Q_OBJECT
	std::vector<Button*> tiles;

public:
	ButtonFactory();
	~ButtonFactory();
	void free();

	void load(QSize size);
	void setParent(QWidget* widget);
	void setEnabledAll(bool unlocked = true);
};