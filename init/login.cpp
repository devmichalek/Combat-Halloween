#include "login.h"
#include "state.h"

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



void Login::load(float screen_w, float screen_h)
{
	free();

	// Set basics.
	this->screen_w = screen_w;
	this->screen_h = screen_h;

	arrow_line = 0.5;	// 0.5 sec.


	// Background.
	loginbg.create(static_cast<int>(screen_w / 2), static_cast<int>(screen_h));
	signupbg.create(static_cast<int>(screen_w / 2), static_cast<int>(screen_h));
	signupbg.setColor(sf::Color(0xF2, 0x58, 0x3E));
	signupbg.move(screen_w / 2, 0);


	const char* path = "fonts/Jaapokki-Regular.otf";
	loginbutton.setFont(path);
	signupbutton.setFont(path);
	gobutton.setFont(path);
	backbutton.setFont(path);
	forgetbutton.setFont(path);

	int size = static_cast<int>(screen_h / 18);
	loginbutton.create("LOG IN", size, static_cast<float>(size) / 30 + 2);
	signupbutton.create("SIGN UP", size, static_cast<float>(size) / 30 + 2);
	gobutton.create("LOG IN", static_cast<int>(static_cast<float>(size) / 1.5), static_cast<float>(size) / 30 + 2);
	backbutton.create("BACK", static_cast<int>(static_cast<float>(size) / 1.5), static_cast<float>(size) / 30 + 2);
	forgetbutton.create("FORGOT PASSWORD", static_cast<int>(static_cast<float>(size) / 1.5), static_cast<float>(size) / 30 + 2);

	loginbutton.setColor(sf::Color(0xFF, 0xFF, 0xFF));
	signupbutton.setColor(sf::Color(0xF2, 0x58, 0x3E));
	gobutton.setColor(sf::Color(0xD5, 0xE1, 0xDD));
	backbutton.setColor(sf::Color(0xD5, 0xE1, 0xDD));
	forgetbutton.setColor(sf::Color(0xFF, 0xD8, 0x00));

	sf::Color color(0x21, 0x21, 0x29);
	signupbutton.setColorText(color);
	loginbutton.setColorText(color);
	gobutton.setColorText(color);
	backbutton.setColorText(color);
	forgetbutton.setColorText(color);

	// Set font.
	title.setFont(path);
	arrow.setFont(path);
	username_form.setFont(path);
	password_form.setFont(path);
	username_written.setFont(path);
	password_written.setFont(path);
	info.setFont(path);

	// Set text.
	title.setText("LOGGING");
	arrow.setText("|");
	username_form.setText("Username: ");
	password_form.setText("Password: ");
	username_written.setText(" ");
	password_written.setText(" ");
	info.setText(" ");

	// Set size.
	size = screen_h / 20;
	title.setSize(screen_h / 12);
	arrow.setSize(size);
	username_form.setSize(size);
	password_form.setSize(size);
	username_written.setSize(size);
	password_written.setSize(size);
	info.setSize(screen_h / 28);

	// Set color.
	title.setFillColor(sf::Color(0xF7, 0xF3, 0xE8));
	arrow.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
	username_form.setFillColor(sf::Color(0xD5, 0xE1, 0xDD));
	password_form.setFillColor(sf::Color(0xD5, 0xE1, 0xDD));
	info.setFillColor(sf::Color(0xF2, 0x58, 0x3E));

	position();

	max_length_username = 12;
	min_length_username = 4;
	max_length_password = 20;
	min_length_password = 8;
}

void Login::handle(sf::Event& event)
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
				else if (event.key.code == sf::Keyboard::Return)
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
	window->draw(loginbg.get());
	loginbutton.draw(window);
	window->draw(signupbg.get());
	signupbutton.draw(window);


	// Second scene.
	backbutton.draw(window);
	window->draw(title.get());
	window->draw(username_form.get());
	window->draw(password_form.get());
	window->draw(username_written.get());
	window->draw(password_written.get());
	window->draw(info.get());
	if (forget_counter > 2)	forgetbutton.draw(window);

	// Draw gobutton.
	if (username.size() >= min_length_username && password.size() >= min_length_password)
	{
		gobutton.draw(window);
	}


	// Draw arrow.
	if (arrow_counter < arrow_line && state < 2)
	{
		window->draw(arrow.get());
	}
}

void Login::mechanics(double elapsedTime)
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

	loginbutton.fadeinGlobal(value);
	signupbutton.fadeinGlobal(value);
	backbutton.fadeinGlobal(value);
	title.fadein(value);
	username_form.fadein(value);
	password_form.fadein(value);
	username_written.fadein(value);
	password_written.fadein(value);
	arrow.fadein(value);
	gobutton.fadeinGlobal(value);
	info.fadeout(value / 2);
	forgetbutton.fadeinGlobal(value);

	if (signupbutton.getClicked())
	{
		const char* command = "start http://combathalloween.netne.net/user/register/registerform.php";
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
			info.setFillColor(sf::Color(0xF7, 0xF3, 0xE8));
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

bool Login::isNext() const
{
	return thread.success && info.getAlpha() == 0;
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
	request.setHttp("http://combathalloween.netne.net/");
	request.setRequest("/getters/request.php", sf::Http::Request::Post);

	if (!request.sendRequest())
	{
		info.setText("Cannot connect to database.");
		info.setFillColor(Username::getErrorColor());
	}
	else if (request.getResult() == "success")
	{
		info.setText("You are logged!");
		info.setFillColor(Username::getGreenColor());
		Username user;
		user.username = const_cast<char*>(username.c_str());
		thread.success = true;
	}
	else
	{
		forget_counter++;
		if(request.getResult() == "-1")		info.setText("Unexpected Error.");
		else if(request.getResult() == "0")	info.setText("Wrong username or password.");
		info.setFillColor(Username::getErrorColor());
	}

	// Set alpha and position of info.
	info.setAlpha(0xFF);
	info.setPosition(screen_w / 2 - info.getWidth() / 2, password_form.getBot() + screen_h / 20);

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

bool Login::isPossibleKey(sf::Uint8 code) const
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