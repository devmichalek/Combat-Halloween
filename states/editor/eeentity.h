#pragma once
#include "eeitem.h"
#include "eventwindow.h"
#include "sprite.h"

namespace ee
{
	struct Entity // Editor Entity "Entity" interface.
	{
		Item item;
		bool active;
		bool allowDuplicates;						// allow duplicates (more than one item on the same position)
		inline static bool wholeCollision = false;	// false - check by point | true - check by square

		sf::Vector2f screen;
		std::vector<cmm::Sprite*> sprites;

		Entity()
		{
			item.free();
			active = false;
			allowDuplicates = false;
			screen = sf::Vector2f(0.0f, 0.0f);
		};

		virtual ~Entity()								{};
		virtual void free()								= 0;
		virtual void reset()							= 0;

		virtual bool isModified()							{ return false; }
		virtual bool isOneAndOnly()							{ return false; } // like Knight
		virtual void setActive(bool active)					{ this->active = active; }
		const bool& isActive() const						{ return active; }
		virtual Item getItem()								{ return item; }
		virtual cmm::Sprite* getSprite(const int &chosen)	{ return sprites[chosen]; }
		std::vector<cmm::Sprite*> &getSprites()				{ return sprites; }
		virtual bool checkCollision(sf::Vector2i &mouse)	= 0;
		static bool &getWholeCollision()					{ return wholeCollision; }
		static void switchWholeCollision()					{ wholeCollision = !wholeCollision; }

		virtual void load(sf::Vector2f &screen, int amount)							= 0;
		virtual void handle(const sf::Event &event)									{}
		virtual void draw(sf::RenderWindow* &window, sf::Vector2i &add)				= 0;
		virtual void mechanics(const double &elapsedTime)							{}

		virtual bool add(Item &data)												= 0; // returns true if added correctly
		virtual bool remove(sf::Vector2i &mouse)									= 0; // returns true if deleted correctly
		virtual bool unfold(sf::Vector2i &mouse)									{ return false; }
	};
}