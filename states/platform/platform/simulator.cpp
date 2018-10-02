#include "simulator.h"
#include "loading.h"
#include <fstream>
#include "request.h"
#include <boost/lexical_cast.hpp>
#include "logconsole.h"

Simulator::Simulator()
{
	free();
}

Simulator::~Simulator()
{
	free();
}

void Simulator::free()
{
	status = STATUS::NONE;
	screen_w = 0;
	screen_h = 0;
	offset = 0;
	max = 7;

	reset();
}

void Simulator::reset()
{
	status = STATUS::NONE;
	SContent::type = SContent::TYPE::NONE;	// Reset content type.

	backbutton.getClicked() = false;
	reloadbutton.getClicked() = false;

	thread.reset();
	msg = "";

	setInfo();
}



void Simulator::load(const float &screen_w, const float &screen_h)
{
	free();

	this->screen_w = screen_w;
	this->screen_h = screen_h;

	// Set info.
	msg = "Launching thread...";
	Loading::add(info.setFont(cmm::JAPOKKI_FONT_PATH));
	if (Loading::isError())	return;
	info.setSize(screen_h / 26);
	info.setAlpha(0);
	setInfo();

	// Set progress bar.
	Loading::add(progress_bar.load("images/other/progress_bar.png", 7));
	if (Loading::isError())	return;
	progress_bar.setScale(screen_w / 1707, screen_h / 960);
	progress_bar.setAlpha(0);
	progress_bar.setPosition(screen_w / 2 - progress_bar.getWidth() / 2, screen_h / 2 + screen_h / 36);

	// Set Rect Buttons
	backbutton.setFont(cmm::JAPOKKI_FONT_PATH);
	reloadbutton.setFont(cmm::JAPOKKI_FONT_PATH);
	if (Loading::isError())	return;

	int size = static_cast<int>(screen_h / 27);
	backbutton.create("BACK", size, static_cast<float>(size) / 20 + 2);
	reloadbutton.create("RELOAD", size, static_cast<float>(size) / 20 + 2);

	backbutton.setColor(sf::Color(0xD5, 0xE1, 0xDD));
	reloadbutton.setColor(sf::Color(0xD5, 0xE1, 0xDD));

	backbutton.setColorText(sf::Color(0x21, 0x21, 0x29));
	reloadbutton.setColorText(sf::Color(0x21, 0x21, 0x29));

	backbutton.setPosition(screen_w / 256, screen_h / 144);
	reloadbutton.setPosition(screen_w / 2 - reloadbutton.getWidth() / 2, screen_h / 5 * 4);
}

void Simulator::handle(const sf::Event &event)
{
	if (status == STATUS::FAILURE)
	{
		backbutton.handle(event);
		reloadbutton.handle(event);
	}
}

void Simulator::draw(sf::RenderWindow* &window)
{
	window->draw(info);
	window->draw(progress_bar);

	if (status == STATUS::FAILURE)
	{
		backbutton.draw(window);
		reloadbutton.draw(window);
	}
}

void Simulator::mechanics(const double &elapsedTime)
{
	if (thread.ready && thread.thread)
	{
		thread.reset();
	}

	if (status != STATUS::FAILURE)
	{
		offset += static_cast<float>(elapsedTime) * 0xFF / 5.0f;
		if (offset >= max)
			offset = 0.0f;
		progress_bar.setOffset(static_cast<int>(offset));
	}

	if (status == STATUS::NONE)	// Launch Thread
	{
		float value = 0xFF / 4 * 3 * static_cast<float>(elapsedTime);
		int max = 0xFF;
		info.fadein(value, max);
		progress_bar.fadein(value, max);
		backbutton.fadeinGlobal(value, max);
		reloadbutton.fadeinGlobal(value, max);

		if (info.getAlpha() == 0xFF)
		{
			thread.thread = new std::thread(&Simulator::disunite, this);
			thread.thread->detach();
		}
	}
	else if (status == STATUS::FAILURE)
	{
		backbutton.mechanics(elapsedTime);
		reloadbutton.mechanics(elapsedTime);

		if (backbutton.getClicked())
		{
			backbutton.getClicked() = false;
			prev = true;
		}
		else if (reloadbutton.getClicked())
		{
			reloadbutton.getClicked() = false;
			status = STATUS::NONE;
			++offset;
		}
	}
	
	if (isState())
	{
		float value = 0xFF / 4 * 3 * static_cast<float>(elapsedTime);
		int min = 0;
		info.fadeout(value, min);
		progress_bar.fadeout(value, min);
		backbutton.fadeoutGlobal(value, min);
		reloadbutton.fadeoutGlobal(value, min);
	}

	setInfo();
}

void Simulator::setState(int &state)
{
	if (isPrev())
	{
		if(SContent::type == SContent::TYPE::EDITOR)
			state = cmm::STATES::EDITOR;
		else
			state = cmm::STATES::LEVELMENU;
	}
	else if (isNext())
	{
		state = cmm::STATES::PLATFORM;
	}
}


bool Simulator::isReady() const
{
	return info.getAlpha() == 0;
}

void Simulator::disunite()
{
	setProcessingMsg("Processing data...");
	if (prepare())
	{
		setSuccessMsg("Sorting data...");
		if (sort())
		{
			setSuccessMsg("Simulating data...");
			if (simulate())
			{
				setSuccessMsg("Finishing thread...");
				thread.success = true;
				next = true;
			}
		}
	}
	
	thread.ready = true;
}

bool Simulator::prepare()
{
	if (SContent::type == SContent::TYPE::NONE)
	{
		setErrorMsg("Error occured, type of content is not specified");
		return false;
	}
	else if(SContent::type == SContent::TYPE::FILE)
	{
		SContent::content.clear();
		std::fstream file;
		file.open(SContent::path);
		if (file.good())
		{
			std::string line = "";
			while (std::getline(file, line))
			{
				SContent::content.push_back(line);
			}

			if (!checkContent("Correctly loaded file \"" + SContent::path + "\"."))
				return false;
		}
		else
		{
			setErrorMsg("Error occured, cannot load file \"" + SContent::path + "\".");
			return false;
		}
	}
	else if (SContent::type == SContent::TYPE::SERVER)
	{
		SContent::content.clear();
		cmm::Request request;
		request.setMessage(SContent::path);
		request.setRequest("/combathalloween/getters/getworld.php", sf::Http::Request::Post);
		request.setHttp("http://amichalek.pl/");

		bool success = request.sendRequest();
		if (success)
		{
			if (request.getResult() == "0")
			{
				setErrorMsg("Error occured, cannot find specific world to be downloaded.");
			}
			else
			{
				// success
				std::string line = "";
				std::string result = request.getResult();
				for(auto it : result)
				{
					line += it;
					if (it == '\n')
					{
						SContent::content.push_back(line);
						line = "";
					}
				}

				if (!checkContent("Correctly downloaded world."))
					return false;
			}
		}
		else
		{
			setErrorMsg("Error occured, cannot connect with database.");
		}
	}

	// Content is already loaded because it is shared with editor
	// Another difference is that we do not need to have saved file here because we load directly
	else if (SContent::type == SContent::TYPE::EDITOR)
	{
		if (!checkContent("Correctly copied data from editor."))
			return false;
	}

	return true;
}

bool Simulator::sort()
{
	// Sort by type...
	SContent::content_sorted.clear();
	for (int c = 0; c < SContent::amount(); ++c)
	{
		for (auto &it : SContent::content)
		{
			if (boost::lexical_cast<int>(it.substr(it.find("t:") + 2, it.find(" c:") - (it.find("t:") + 2))) == c)
			{
				SContent::content_sorted.push_back(it);
			}
		}
	}

	SContent::content.shrink_to_fit();
	SContent::content_sorted.shrink_to_fit();
	setSuccessMsg("Data was correctly sorted.");
	return true;
}

bool Simulator::simulate()
{
	// Check if sorted content is not empty.
	if (SContent::content_sorted.empty())
	{
		setErrorMsg("Error occured, sorted content is empty!");
		return false;
	}

	// Check if knight is inside of the container..
	if (SContent::content_sorted[0].find("t:0") == std::string::npos)	// Knight has a type 0
	{
		setErrorMsg("Cannot start game, knight's position is not set.");
		return false;
	}

	// There is no any tile.
	if (SContent::content_sorted.size() > 1 && SContent::content_sorted[1].find("t:1") == std::string::npos)
	{
		setWarningMsg("Recommended amount of tiles is at least 1.");
	}

	// Check if there is more than 1 knight.
	if (SContent::content_sorted.size() > 1 && SContent::content_sorted[1].find("t:0") != std::string::npos)
	{
		setErrorMsg("Cannot start game, there is more than 1 knight's position.");
		return false;
	}

	return true;
}

void Simulator::setInfo()
{
	if (!msg.empty())
	{	
		if (status == STATUS::WARNING)
			info.setFillColor(cmm::LogConsole::getWarningColor());
		else if (status == STATUS::FAILURE)
			info.setFillColor(cmm::LogConsole::getErrorColor());
		else
			info.setFillColor(cmm::LogConsole::getLoadingColor());
			
		info.setText(msg);
		info.setPosition(screen_w / 2 - info.getWidth() / 2 + screen_w / 160, screen_h / 2 - info.getHeight() / 2 - screen_h / 72);
		msg.clear();
	}
}

bool Simulator::checkContent(std::string str)
{
	if (!SContent::content.empty())
	{
		setSuccessMsg(str);
		return true;
	}
	
	setErrorMsg("Error occured, content is empty.");
	return false;
}

void Simulator::condition()
{
	while (!msg.empty()){}
}

void Simulator::setProcessingMsg(std::string str)
{
	condition();
	msg = str;
	status = PROCESSING;
}

void Simulator::setSuccessMsg(std::string str)
{
	condition();
	msg = str;
	status = SUCCESS;
}

void Simulator::setWarningMsg(std::string str)
{
	condition();
	msg = str;
	status = WARNING;
}

void Simulator::setErrorMsg(std::string str)
{
	condition();
	msg = str;
	status = FAILURE;
}