#include "wsim.h"
#include <fstream>
#include "request.h"
#include "eakind.h"
#include <boost/lexical_cast.hpp>

WSim::WSim()
{

}

WSim::~WSim()
{

}

void WSim::free()
{

}



void WSim::load(const float &screen_w, const float &screen_h)
{

}

void WSim::handle(const sf::Event &event)
{

}

void WSim::draw(sf::RenderWindow* &window)
{
	if (status == STATUS::FAILURE)
	{
		errorButton.draw(window);
	}

}

void WSim::mechanics(const double &elapsedTime)
{
	if (thread.ready && thread.thread)
	{
		thread.reset();
	}

	if (status == STATUS::NONE)	// Run Simulator
	{
		thread.thread = new std::thread(&WSim::disunite, this);
		thread.thread->detach();
	}
}

void WSim::setState(int &state)
{
	if (isPrev())
	{
		if(WContent::type == WContent::TYPE::EDITOR)
			state = cmm::STATES::EDITOR;
		else
			state = cmm::STATES::LEVELMENU;
	}
	else if (isNext())
	{
		state = cmm::STATES::PLATFORM;
	}
}


bool WSim::isReady() const
{
	return text.getAlpha() == 0;
}

void WSim::disunite()
{
	if (prepare())
	{

	}
	else if (sort())
	{

	}
	else if (simulate())
	{

	}
}

bool WSim::prepare()
{
	if (WContent::type == WContent::TYPE::NONE)	// error
	{
		
		return false;
	}
	else if(WContent::type == WContent::TYPE::FILE)	// it happens when someone wants to load own local file
	{
		WContent::content.clear();
		std::fstream file;

		file.open(WContent::path);
		if (file.good())
		{
			std::string line = "";
			while (std::getline(file, line))
			{
				WContent::content.push_back(line);
			}

			// success
			// ...
		}
		else	// error
		{
			return false;
		}
	}
	else if (WContent::type == WContent::TYPE::SERVER)
	{
		WContent::content.clear();
	}

	// content is already loaded because it is shared with editor
	// another difference is that we do not need to have saved file here because we load directly
	else if (WContent::type == WContent::TYPE::EDITOR)
	{
		// success
		
	}

	return true;
}

bool WSim::sort()
{
	// Sort by type...
	EAKind eakind;
	std::string buf = "";

	for (int c = 0; c < eakind.getKindSize(); ++c)
	{
		for (auto &it : WContent::content)
		{
			if (boost::lexical_cast<int>(it.substr(it.find("t:") + 2, it.find(" c:") - (it.find("t:") + 2))) == c)
			{
				WContent::content_sorted.push_back(it);
			}
		}
	}

	return true;
}

bool WSim::simulate()
{

}
