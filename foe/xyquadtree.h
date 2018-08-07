#pragma once
#include "xyquad.h"
#include "sprite.h"
#include <SFML/Graphics/RenderWindow.hpp>


class XYQuadTree
{
	float mW, mH;	// Mean (large) width and height of the foe
	int count;		// Size of tree
	float damage;
	XYQuad* root;

public:
	XYQuadTree();
	~XYQuadTree();
	bool empty();
	// void remove(XYNode* node = nullptr);
	// void remove(float x, float y, int ID);
	bool insert(XYNode* node = nullptr);

	// Advanced
	void harm(sf::Rect<float> rect, float damage);				// send character's attack rect + its damage
	void attack(sf::Rect<float> rect);							// send larger character's rect
	void mechanics(sf::Rect<float> rect, double elapsedTime);	// send larger window rect + elapsedTime


	float getGreatestX();
	float getGreatestY();
	float getSmallestX();
	float getSmallestY();
	const int& getSize() const;
	const float& getDamage() const;

private:
	void free(XYQuad* quad = nullptr);
	// void removeRoot();
	// void removeMatch(XYQuad* parent = nullptr, XYQuad* match = nullptr, int dir = 0);
	// void removePrivate(XYNode* node = nullptr, XYQuad* quad = nullptr);
	bool insertPrivate(XYNode* node = nullptr, XYQuad* quad = nullptr);
	void harmPrivate(sf::Rect<float> &rect, float &damage, XYQuad* quad = nullptr);	// check if foe got hit
	bool attackPrivate(sf::Rect<float> &rect, XYQuad* quad = nullptr);				// check if character got hit
	void mechanicsPrivate(sf::Rect<float> &rect, int &state, double &elapsedTime, XYQuad* quad = nullptr);
	XYNode* findSmallest(XYQuad* quad = nullptr);
	XYNode* findGreatest(XYQuad* quad = nullptr);

	void findSmallestX(XYQuad* quad, float& v);
	void findGreatestX(XYQuad* quad, float& v);
	void findSmallestY(XYQuad* quad, float& v);
	void findGreatestY(XYQuad* quad, float& v);
};