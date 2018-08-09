#pragma once
#include "sprite.h"
#include "foenode.h"
#include "xyquad.h"
#include "xyquadtree.h"
#include <SFML/Graphics/RenderWindow.hpp>

using Node = FoeNode;
using Quad = XYQuad<Node>;
using Rect = sf::Rect<float>;

class FoeTree : public XYQuadTree<Node, Quad>
{
	std::vector<std::vector<cmm::Sprite*>> sprites;

	// Process ------------------------
	sf::RenderWindow* window;
	double elapsedTime;
	Rect* screen;
	Rect* character;
	Rect* characterAttack;	// attack box
	bool characterHasAttacked;
	float characterDamage;
	float characterHP;
	float characterArmour;
	// --------------------------------

public:
	FoeTree();
	~FoeTree();

	void load(std::vector<std::vector<cmm::Sprite*>> newSprites);
	
	// Process ------------------------
	void processData(	sf::RenderWindow* &,
						double &,
						Rect* &,
						Rect* &,
						Rect* &,
						bool &,
						float &,
						float &,
						float &
					);
	void process();
	void cleanProcessedData();						/*set vars as NULL, 0 etc.*/
	// --------------------------------

private:
	bool containsPrivate(Quad* quad = nullptr, Rect* rect = nullptr);
	void processPrivate(Quad* quad = nullptr);
};