#include "lvmboard.h"
#include "loading.h"

lvm::Board::Board()
{
	free();
}

lvm::Board::~Board()
{
	free();
}

void lvm::Board::free()
{
	screen_w = screen_h = 0;
	
	if (!iconvec.empty())
	{
		for (auto &it : iconvec)
		{
			delete it;
			it = nullptr;
		}

		iconvec.clear();
	}

	if (!titlevec.empty())
	{
		for (auto &it : titlevec)
		{
			if (!it.empty())
			{
				for (auto &jt : it)
				{
					delete jt;
					jt = nullptr;
				}

				it.clear();
			}
		}

		titlevec.clear();
	}

	if (!detailvec.empty())
	{
		for (auto &it : detailvec)
		{
			if (!it.empty())
			{
				for (auto &jt : it)
				{
					delete jt;
					jt = nullptr;
				}

				it.clear();
			}
		}

		detailvec.clear();
	}

	thread.free();
	msg.clear();
}

void lvm::Board::load(const float &screen_w, const float &screen_h)
{
	free();

	this->screen_w = screen_w;
	this->screen_h = screen_h;

	Loading::add(sound.load("sounds/click.wav"));
	if (Loading::isError())	return;

	for (int i = 0; i < Icon::COUNT; ++i)
		iconvec.push_back(new cmm::Sprite);
	titlevec.resize(Type::SIZE);
	detailvec.resize(Type::SIZE);

	float icon_scale_x = screen_w / 1920;	if (icon_scale_x > 1.0f)	icon_scale_x = 1;
	float icon_scale_y = screen_h / 1080;	if (icon_scale_y > 1.0f)	icon_scale_y = 1;
	Loading::add(iconvec[Icon::LOCALFILE]->load("images/icons/fileicon.png"));
	Loading::add(iconvec[Icon::SERVERFILE]->load("images/icons/serverfileicon.png"));
	Loading::add(iconvec[Icon::CHECKED]->load("images/icons/checkedicon.png"));
	Loading::add(iconvec[Icon::LEFT]->load("images/buttons/left.png"));
	Loading::add(iconvec[Icon::RIGHT]->load("images/buttons/right.png"));
	if (Loading::isError())	return;

	float factor = 1.0f;
	for (auto &it : iconvec)
		it->setScale(icon_scale_x * factor, icon_scale_y * factor);

}

void lvm::Board::draw(sf::RenderWindow* &window)
{

}

void lvm::Board::handle(const sf::Event &event)
{

}

void lvm::Board::fadein(const float &v, const int &max)
{
	for (auto &it : iconvec)
		it->fadein(v, max);

	
}

void lvm::Board::fadeout(const float &v, const int &min)
{

}

bool lvm::Board::isChosen()
{
	return false;
}

void lvm::Board::setVolume(const float &newVolume)
{
	sound.setVolume(newVolume);
}