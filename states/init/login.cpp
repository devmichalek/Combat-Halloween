#include "login.h"
#include "user.h"
#include "loading.h"

Login::Login()
{
	free();
}

Login::~Login()
{
	free();
}

void Login::free()
{
	screen_w = 0;
	screen_h = 0;

	counter = 0;
	arrow_counter = 0;
	arrow_line = 0;

	info_str = "";

	loginbutton.free();
	signupbutton.free();
	gobutton.free();
	backbutton.free();

	state = 0;
	username = "";
	password = "";
	max_length_username = 0;
	min_length_username = 0;
	max_length_password = 0;
	min_length_password = 0;

	thread.free();

	forget_counter = 0;
	forgetbutton.free();
}



void Login::load(const float &screen_w, const float &screen_h)
{
	free();

	// Set basics.
	this->screen_w = screen_w;
	this->screen_h = screen_h;

	arrow_line = 0.5;	// 0.5 sec.


	// Background.
	Loading::add(loginbg.create(static_cast<int>(screen_w / 2), static_cast<int>(screen_h)));
	Loading::add(signupbg.create(static_cast<int>(screen_w / 2), static_cast<int>(screen_h)));
	if (Loading::isError()) return;
	signupbg.setColor(cmm::ERROR_COLOR);
	signupbg.move(screen_w / 2, 0);


	const char* path = cmm::JAPOKKI_FONT_PATH;
	loginbutton.setFont(path);
	signupbutton.setFont(path);
	gobutton.setFont(path);
	backbutton.setFont(path);
	forgetbutton.setFont(path);
	if (Loading::isError()) return;

	int size = static_cast<int>(screen_h / 18);
	loginbutton.create("LOG IN", size, static_cast<float>(size) / 30 + 2);
	signupbutton.create("SIGN UP", size, static_cast<float>(size) / 30 + 2);
	gobutton.create("LOG IN", static_cast<int>(static_cast<float>(size) / 1.5), static_cast<float>(size) / 30 + 2);
	backbutton.create("BACK", static_cast<int>(static_cast<float>(size) / 1.5), static_cast<float>(size) / 30 + 2);
	forgetbutton.create("FORGOT PASSWORD", static_cast<int>(static_cast<float>(size) / 1.5), static_cast<float>(size) / 30 + 2);

	loginbutton.setColor(cmm::LOADING_COLOR);
	signupbutton.setColor(cmm::ERROR_COLOR);
	gobutton.setColor(cmm::DULL_IRON_COLOR);
	backbutton.setColor(cmm::DULL_IRON_COLOR);
	forgetbutton.setColor(cmm::SUCCESS_COLOR);

	signupbutton.setColorText(cmm::BACKGROUND_COLOR);
	loginbutton.setColorText(cmm::BACKGROUND_COLOR);
	gobutton.setColorText(cmm::BACKGROUND_COLOR);
	backbutton.setColorText(cmm::BACKGROUND_COLOR);
	forgetbutton.setColorText(cmm::BACKGROUND_COLOR);

	// Set font.
	Loading::add(title.setFont(path));
	Loading::add(arrow.setFont(path));
	Loading::add(username_form.setFont(path));
	Loading::add(password_form.setFont(path));
	Loading::add(username_written.setFont(path));
	Loading::add(password_written.setFont(path));
	Loading::add(info.setFont(path));
	if (Loading::isError()) return;

	// Set text.
	title.setText("LOGGING");
	arrow.setText("|");
	username_form.setText("Username: ");
	password_form.setText("Password: ");
	username_written.setText(" ");
	password_written.setText(" ");
	info.setText(" ");

	// Set size.
	size = static_cast<int>(screen_h / 20);
	title.setSize(screen_h / 12);
	arrow.setSize(size);
	username_form.setSize(size);
	password_form.setSize(size);
	username_written.setSize(size);
	password_written.setSize(size);
	info.setSize(screen_h / 28);

	// Set color.
	title.setFillColor(cmm::IRON_COLOR);
	arrow.setFillColor(cmm::LOADING_COLOR);
	username_form.setFillColor(cmm::DULL_IRON_COLOR);
	password_form.setFillColor(cmm::DULL_IRON_COLOR);
	info.setFillColor(cmm::ERROR_COLOR);

	position();

	max_length_username = 12;
	min_length_username = 4;
	max_length_password = 20;
	min_length_password = 8;
}

void Login::handle(const sf::Event &event)
{
	// If there is no moving and next state.
	if (counter == 0 && !thread.success && state < 2)
	{
		loginbutton.handle(event);
		signupbutton.handle(event);
		gobutton.handle(event);
		backbutton.handle(event);
		forgetbutton.handle(event);

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				float mouse_x = static_cast<float>(event.mouseButton.x);
				float mouse_y = static_cast<float>(event.mouseButton.y);

				if (usernameCollision.contains(mouse_x, mouse_y))
				{
				state = 0;
				setArrow();
				}
				else if (passwordCollision.contains(mouse_x, mouse_y))
				{
				state = 1;
				setArrow();
				}
			}
		}
		else
		{
			if (event.type == sf::Event::TextEntered)
			{
				if (isPossibleKey(event.text.unicode))
				{
					if (state == 0 && username.size() < max_length_username)
					{
						username += event.text.unicode;
						username_written.setText(username);
						organizeWritten();
					}
					else if (state == 1 && password.size() < max_length_password)
					{
						password += event.text.unicode;
						password_written.setText(getPassword());
						organizeWritten();
					}
				}
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::BackSpace)	// Delete last one.
				{
					if (state == 0 && username.size() >= 1)
					{
						username.pop_back();
						if (username.empty())	username_written.setText(" ");
						else					username_written.setText(username);
						organizeWritten();
					}
					else if (state == 1 && password.size() >= 1)
					{
						password.pop_back();
						if (password.empty())	password_written.setText(" ");
						else					password_written.setText(getPassword());
						organizeWritten();
					}
				}
				else if (event.key.code == sf::Keyboard::Enter)
				{
					if (state == 0)
					{
						state = 1;
						setArrow();
					}
					else if (state == 1)
					{
						if (username.size() >= min_length_username && password.size() >= min_length_password)
						{
							gobutton.getFocus() = true;
							gobutton.getClicked() = true;
						}
					}
				}
			}
		}
	}
}

void Login::draw(sf::RenderWindow* &window)
{
	// First scene.
	window->draw(loginbg);
	loginbutton.draw(window);
	window->draw(signupbg);
	signupbutton.draw(window);

	// Second scene.
	backbutton.draw(window);
	window->draw(title);
	window->draw(username_form);
	window->draw(password_form);
	window->draw(username_written);
	window->draw(password_written);
	window->draw(info);

	if (forget_counter > 2)	forgetbutton.draw(window);

	// Draw gobutton.
	if (username.size() >= min_length_username && password.size() >= min_length_password)
	{
		gobutton.draw(window);
	}


	// Draw arrow.
	if (arrow_counter < arrow_line && state < 2)
	{
		window->draw(arrow);
	}
}

void Login::mechanics(const double &elapsedTime)
{
	// FPS.
	/*FPS::mechanics(elapsedTime);
	if (FPS::timePassed())
	{
		printf("%d\n", FPS::getFPS());
	}*/

	// Delete thread if is done.
	if (thread.ready)
	{
		thread.reset();
	}

	if (!info_str.empty())
	{
		info.setText(info_str);
		info_str = "";
		// Set alpha and position of info.
		info.setAlpha(0xFF);
		info.setPosition(screen_w / 2 - info.getWidth() / 2, password_form.getBot() + screen_h / 20);
	}

	// Arrow.
	arrow_counter += static_cast<float>(elapsedTime);
	if (arrow_counter > arrow_line * 2)
	{
		arrow_counter = 0;
	}

	loginbutton.mechanics(elapsedTime);
	signupbutton.mechanics(elapsedTime);
	backbutton.mechanics(elapsedTime);

	if (forget_counter > 2)
	{
		forgetbutton.mechanics(elapsedTime);
	}

	if (username.size() >= min_length_username && password.size() >= min_length_password)
	{
		gobutton.mechanics(elapsedTime);
	}


	// Background
	float value = static_cast<float>(elapsedTime) * 0xFF;
	if (loginbutton.getFocus() && loginbutton.getState() == 1 && counter == 0)
	{
			loginbg.fadein(value * 3, 0xFF);
	}
	else
	{
		loginbg.fadeout(value * 4, 0);
	}
	if (signupbutton.getFocus() && signupbutton.getState() == 1 && counter == 0)
	{
		signupbg.fadein(value * 3, 0xFF);
	}
	else
	{
		signupbg.fadeout(value * 4, 0);
	}

	int max = 0xFF, min = 0;
	loginbutton.fadeinGlobal(value, max);
	signupbutton.fadeinGlobal(value, max);
	backbutton.fadeinGlobal(value, max);
	title.fadein(value, max);
	username_form.fadein(value, max);
	password_form.fadein(value, max);
	username_written.fadein(value, max);
	password_written.fadein(value, max);
	arrow.fadein(value, max);
	gobutton.fadeinGlobal(value, max);
	info.fadeout(value / 2, min);
	forgetbutton.fadeinGlobal(value, max);

	if (signupbutton.getClicked())
	{
		const char* command = "start http://amichalek.pl/combathalloween/user/register/registerform.php";
		system(command);
		signupbutton.getClicked() = false;
	}
	else if (forgetbutton.getClicked())
	{
		const char* command = "start empty";
		system(command);
		forgetbutton.getClicked() = false;
	}
	else if (loginbutton.getClicked())
	{
		loginbutton.getClicked() = false;
		loginbutton.getFocus() = false;
		counter = -1;
	}
	else if (backbutton.getClicked())
	{
		backbutton.getClicked() = false;
		backbutton.getFocus() = false;
		counter = 1;
	}

	if (gobutton.getClicked() && username.size() >= min_length_username && password.size() >= min_length_password)
	{
		gobutton.getClicked() = false;
		gobutton.getFocus() = false;

		if (!thread.ready && !thread.thread)
		{
			state = 2;

			info.setText("Loading data...");
			info.setFillColor(cmm::IRON_COLOR);
			info.setPosition(screen_w / 2 - info.getWidth() / 2, password_form.getBot() + screen_h / 20);
			info.setAlpha(0xFF);

			thread.thread = new std::thread(&Login::setThread, this);
			thread.thread->detach();
		}
	}

	if (counter < 0)
	{
		float add = static_cast<float>(elapsedTime) * screen_h;
		move(0, add);
		counter -= add;
	}
	else if (counter > 0)
	{
		float add = -static_cast<float>(elapsedTime) * screen_h / 2 * 3;
		move(0, add);
		counter += -add;
	}

	// In case...
	if (counter > screen_h / 4 * 3)
	{
		counter = 0;
		position();
	}
	else if (counter < -screen_h / 4 * 3)
	{
		counter = 0;
		position(0, screen_h / 4 * 3);
	}
}



void Login::setArrow()
{
	if (state == 0)
	{
		if (username.empty())	arrow.setPosition(username_written.getX(), username_form.getY());
		else					arrow.setPosition(username_written.getRight(), username_form.getY());
	}
	else if (state == 1)
	{
		if (password.empty())	arrow.setPosition(password_written.getX(), password_form.getY());
		else					arrow.setPosition(password_written.getRight(), password_form.getY());
	}
}

void Login::setThread()
{
	cmm::Request request;
	request.setMessage("username=" + username + "&password=" + password);
	request.setHttp("http://amichalek.pl/");
	request.setRequest("/combathalloween/getters/request.php", sf::Http::Request::Post);
	
	if (!request.sendRequest())
	{
		info_str = "Cannot connect to database.";
		info.setFillColor(cmm::ERROR_COLOR);
	}
	else if (request.getResult() == "success")
	{
		info_str = "You are logged!";
		info.setFillColor(cmm::GREEN_COLOR);
		cmm::User::setUsername(username);
		thread.success = true;
	}
	else
	{
		++forget_counter;
		if(request.getResult() == "-1")		info_str = "Unexpected Error.";
		else if(request.getResult() == "0")	info_str = "Wrong username or password.";
		info.setFillColor(cmm::ERROR_COLOR);
	}

	// Set Arrow - state.
	state = 1;

	// Thread is done.
	thread.ready = true;
}

std::string Login::getPassword()
{
	std::string new_password = "";
	for (unsigned i = 0; i < password.size(); ++i)
	{
		new_password += '*';
	}

	return new_password;
}

void Login::organizeWritten()
{
	username_written.setPosition(username_form.getRight() + screen_w / 256, username_form.getY());
	password_written.setPosition(password_form.getRight() + screen_w / 256, password_form.getY() + screen_h / 72);
	setArrow();
}

bool Login::isPossibleKey(const sf::Uint8 &code) const
{
	if (code >= 48 && code <= 57)	// 0 .. 9
	{
		return true;
	}
	else if (code >= 65 && code <= 90)	// A .. Z
	{
		return true;
	}
	else if (code >= 97 && code <= 122) // a .. z
	{
		return true;
	}

	return false;
}

void Login::move(float y_add, float x_add)
{
	loginbutton.move(y_add, x_add);
	signupbutton.move(y_add, x_add);

	gobutton.move(y_add, x_add);
	backbutton.move(y_add, x_add);
	title.move(y_add, x_add);
	arrow.move(y_add, x_add);
	username_form.move(y_add, x_add);
	password_form.move(y_add, x_add);
	username_written.move(y_add, x_add);
	password_written.move(y_add, x_add);
	info.move(y_add, x_add);
	forgetbutton.move(y_add, x_add);
}

void Login::position(float x_add, float y_add)
{
	loginbutton.setPosition(screen_w / 4 - loginbutton.getWidth() / 2 + x_add, screen_h / 2 - loginbutton.getHeight() / 2 + y_add);
	signupbutton.setPosition(screen_w / 4 * 3 - signupbutton.getWidth() / 2 + x_add, screen_h / 2 - signupbutton.getHeight() / 2 + y_add);
	backbutton.setPosition(screen_w / 128 + x_add, screen_h / 72 - screen_h / 4 * 3 + y_add);
	title.setPosition(screen_w / 2 - title.getWidth() / 2 + x_add, screen_h / 4 - screen_h / 4 * 3 + y_add);
	username_form.setPosition(screen_w / 3 - username_form.getWidth() / 2 + x_add, screen_h / 2 - screen_h / 4 * 3 + y_add);
	password_form.setPosition(screen_w / 3 - password_form.getWidth() / 2 + x_add, username_form.getBot() + password_form.getHeight() * 2);
	usernameCollision = sf::Rect<float>(sf::Vector2f(0, username_form.getTop()), sf::Vector2f(screen_w, username_form.getHeight() * 2));
	passwordCollision = sf::Rect<float>(sf::Vector2f(0, password_form.getTop()), sf::Vector2f(screen_w, password_form.getHeight() * 2));
	info.setPosition(screen_w / 4 - info.getWidth() / 2 + x_add, password_form.getBot() + screen_h / 20);
	gobutton.setPosition(screen_w / 2 - gobutton.getWidth() / 2, info.getBot() + screen_h / 9 + y_add - screen_h / 4 * 3);
	forgetbutton.setPosition(screen_w - forgetbutton.getWidth() - screen_w / 128 + x_add, screen_h / 72 + y_add - screen_h / 4 * 3);
	organizeWritten();
}

bool Login::isReady() const
{
	return thread.success && info.getAlpha() == 0;
}

void Login::setState(int &state)
{
	if (isReady())
	{
		state = cmm::MENU;
	}
}