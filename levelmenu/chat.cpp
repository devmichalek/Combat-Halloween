#include "chat.h"
#include "state.h"

Chat::Chat()
{
	free();
}

Chat::~Chat()
{
	free();
}

void Chat::free()
{
	commandColor = sf::Color(0xFF, 0xFF, 0xFF);
	typicalColor = sf::Color(0, 0, 0);
	globalYScale = 0;
	globalYLine = 2;

	screen_w = 0;
	screen_h = 0;
	scale_x = 0;
	scale_y = 0;

	active = false;
	used = false;

	if (!writtens.empty())
	{
		for (auto &it : writtens)
		{
			delete it;
			it = nullptr;
		}

		writtens.clear();
	}

	if (!writtenStrs.empty())
	{
		writtenStrs.clear();
	}
	
	line = 1;
	counter = 0;
}

void Chat::reset()
{
	globalYScale = 0;

	for (auto &it : writtenStrs)
	{
		it = "";
	}

	setWritten();

	for (auto &it : writtens)
	{
		it->setAlpha(0);
	}

	background.setAlpha(0);
	username.setAlpha(0);
	arrow.setAlpha(0);
}



void Chat::load(float screen_w, float screen_h)
{
	free();

	this->screen_w = screen_w;
	this->screen_h = screen_h;

	float fontSize = screen_h / 36;
	scale_x = screen_w / 2560;
	scale_y = screen_h / 1440;

	// Set writtens.
	for (int i = 0; i < 6; i++)
	{
		writtens.push_back(new cmm::Text);
		writtens[i]->setFont("fonts/Jaapokki-Regular.otf");
		writtens[i]->setText(" ");
		writtens[i]->setSize(fontSize);
		writtens[i]->setAlpha(0);
		writtenStrs.push_back("");
	}

	background.load("images/other/chat.png");
	background.setScale(scale_x, scale_y);
	background.setPosition(0, screen_h - background.getHeight());
	background.setAlpha(0);

	arrow.setFont("fonts/Jaapokki-Regular.otf");
	arrow.setText("|");
	arrow.setSize(fontSize);
	arrow.setAlpha(0);

	username.setFont("fonts/Jaapokki-Regular.otf");
	username.setSize(fontSize);
	username.setFillColor(User::getErrorColor());
	username.setAlpha(0);
	username.setText((std::string(User::username) + ": "));
	setWritten();

	background.setScale(scale_x, scale_y *globalYScale / globalYLine);
	username.setScale(1, 1 * globalYScale / globalYLine);

	for (auto &it : writtens)
	{
		it->setScale(1, 1 * globalYScale / globalYLine);
	}
}

void Chat::handle(sf::Event& event)
{
	if (active)
	{
		if (globalYScale == globalYLine)
		{
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode < 128 && event.text.unicode > 31)
				{
					writtenStrs[0] += event.text.unicode;
					setWritten();
				}
			}

			if (event.type == sf::Event::KeyPressed)
			{
				used = false;

				// BackSpace
				if (event.key.code == sf::Keyboard::BackSpace)
				{
					if (!writtenStrs[0].empty())
					{
						writtenStrs[0].pop_back();
						setWritten();
					}
				}

				// Enter, return.
				else if (event.key.code == sf::Keyboard::Return && !writtenStrs[0].empty())
				{
					for (unsigned i = 0; i < writtenStrs[0].size(); i++)
					{
						// printf( "1. ->%s<-\n", writtenStrs[ 0 ].c_str() );
						if (writtenStrs[0][i] == ' ')
						{
							writtenStrs[0].erase(i, 1);
							i--;
						}
						else
						{
							break;
						}
					}

					if (!writtenStrs[0].empty())
					{
						for (int i = writtenStrs[0].size() - 1; i >= 0; i--)
						{
							// printf( "2. ->%s<-\n", writtenStrs[ 0 ].c_str() );
							if (writtenStrs[0][i] == ' ')
							{
								writtenStrs[0].erase(i, 1);
							}
							else
							{
								break;
							}
						}
					}

					if (!writtenStrs[0].empty())
					{
						// Add \n if needed.
						std::string tempStr = "";
						for (unsigned i = 0; i < writtenStrs[0].size(); i++)
						{
							tempStr += writtenStrs[0][i];
							writtens[0]->setText(tempStr);

							if (writtens[0]->getWidth() + username.getWidth() + screen_w / 64 >= background.getRight())
							{
								std::string newNextStr = "";
								for (unsigned j = 0; j < newNextStr.size() - 1; j++)
								{
									newNextStr += tempStr[j];
								}
								newNextStr += "\n";
								newNextStr += tempStr[tempStr.size() - 1];
								tempStr = newNextStr;
							}
						}

						writtenStrs[0] = tempStr;

						for (unsigned i = writtenStrs.size() - 1; i >= 1; i--)
						{
							writtenStrs[i] = writtenStrs[i - 1];
						}

						writtenStrs[0] = "";

						setWritten();

						if (writtenStrs[1][0] == '@')
						{
							used = true;
						}
					}
					else
					{
						setWritten();
					}
				}

				// Esc.
				else if (event.key.code == sf::Keyboard::Escape)
				{
					active = false;
				}
			}
		}
	}
	else
	{
		if (event.type == sf::Event::KeyPressed)
		{
			// 'o'
			if (event.key.code == 14)
			{
				active = true;
				globalYScale = 0.1;
			}
		}
	}
}

void Chat::draw(sf::RenderWindow* &window)
{
	window->draw(background.get());

	for (unsigned i = 0; i < writtens.size(); i++)
	{
		if (writtens[i]->getY() >= background.getY())
		{
			if (writtenStrs[i] != "" && i != 0)
			{
				username.setPosition(screen_w / 256, writtens[i]->getY());
				window->draw(username.get());
			}

			window->draw(writtens[i]->get());
		}
	}

	// draw arrow.
	if (counter < line / 2)
	{
		window->draw(arrow.get());
	}
}

void Chat::mechanics(double elapsedTime)
{
	counter += elapsedTime;
	if (counter > line)
	{
		counter = 0;
	}

	if (active)
	{
		float value = elapsedTime * 0xFF * 2;
		background.fadein(value);
		username.fadein(value);
		arrow.fadein(value);
		for (auto &it : writtens)
		{
			it->fadein(value);
		}

		if (globalYScale < globalYLine)
		{
			globalYScale += elapsedTime * 5;
		}
		else
		{
			globalYScale = globalYLine;
		}
	}
	else
	{
		float value = elapsedTime * 0xFF * 2;
		background.fadeout(value);
		username.fadeout(value);
		arrow.fadeout(value);
		for (auto &it : writtens)
		{
			it->fadeout(value);
		}

		if (globalYScale > 0)
		{
			globalYScale -= elapsedTime * 5;
		}
		else
		{
			globalYScale = 0;
		}
	}

	if (globalYScale != 0 && globalYScale != globalYLine)
	{
		background.setPosition(0, screen_h - background.getHeight() + screen_h / 288);


		background.setScale(scale_x, scale_y *globalYScale / globalYLine);
		username.setScale(1, 1 * globalYScale / globalYLine);

		for (auto &it : writtens)
		{
			it->setScale(1, 1 * globalYScale / globalYLine);
		}
	}
}

void Chat::fadeout(float v, int min)
{

	background.fadeout(v, min);
	username.fadeout(v, min);
	for (auto &it : writtens)
	{
		it->fadeout(v, min);
	}
}



bool& Chat::isActive()
{
	return active;
}

bool Chat::isCommand()
{
	if (active && used)
	{
		used = false;
		return true;
	}

	return false;
}

bool Chat::findCommand(std::string line)
{
	return writtenStrs[1] == line;
}


void Chat::setWritten()
{
	float y0 = screen_h - screen_h / 28;

	writtens[0]->setPosition(screen_w / 256, y0);
	if (!writtenStrs[0].empty())
	{
		if (writtenStrs[0][0] == '@')	writtens[0]->setFillColor(commandColor);
		else							writtens[0]->setFillColor(typicalColor);
	}

	for (unsigned i = 1; i < writtens.size(); i++)
	{
		writtens[i]->setText(writtenStrs[i]);

		float y_adder = screen_h / 26;
		for (unsigned j = 0; j < writtenStrs[i].size(); j++)
		{
			if (static_cast <int> (writtenStrs[i][j]) == 10)
			{
				y_adder += screen_h / 26;
			}
		}

		writtens[i]->setPosition(username.getRight() + screen_w / 256, writtens[i - 1]->getY() - y_adder);

		if (!writtenStrs[i].empty())
		{
			if (writtenStrs[i][0] == '@')		writtens[i]->setFillColor(commandColor);
			else								writtens[i]->setFillColor(typicalColor);
		}
	}

	writtens[0]->setText(writtenStrs[0]);

	if (writtens[0]->getRight() < background.getRight())	writtens[0]->setPosition(screen_w / 256, y0);
	else	writtens[0]->setPosition((background.getRight() - writtens[0]->getWidth()) - screen_w / 256, y0);

	if (writtenStrs[0].empty())	arrow.setPosition(0, y0);
	else	arrow.setPosition(writtens[0]->getRight(), y0);
}

void Chat::setError()
{
	writtenStrs[1] = writtenStrs[1] + " - command doesn't exist.";

	// Add \n if needed.
	std::string tempStr = "";
	for (unsigned i = 0; i < writtenStrs[1].size(); i++)
	{
		tempStr += writtenStrs[1][i];
		writtens[0]->setText(tempStr);

		if (writtens[0]->getWidth() + username.getWidth() + screen_w / 64 >= background.getRight())
		{
			std::string newNextString = "";
			for (unsigned j = 0; j < tempStr.size() - 1; ++j)
			{
				newNextString += tempStr[j];
			}
			newNextString += "\n";
			newNextString += tempStr[tempStr.size() - 1];
			tempStr = newNextString;
		}
	}

	writtenStrs[1] = tempStr;

	setWritten();
}



void Chat::setCommandColor(sf::Color newColor)
{
	commandColor = newColor;
}

void Chat::setTypicalColor(sf::Color newColor)
{
	typicalColor = newColor;
}