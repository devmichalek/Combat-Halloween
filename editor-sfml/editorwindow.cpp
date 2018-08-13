#include "editorwindow.h"

EditorWindow::EditorWindow()
{

}

EditorWindow::~EditorWindow()
{
	if (!corners.empty())
		corners.clear();

	if (!framesvertical.empty())
		framesvertical.clear();

	if (!frameshorizontal.empty())
		frameshorizontal.clear();
}

void EditorWindow::load(float screen_w, float screen_h)
{
	float scale_x = screen_w / 2560;
	float scale_y = screen_h / 1440;

	//view.setSize(screen_w, screen_h);
	view.setViewport(sf::FloatRect(0, 0, 0.5, 1));
	
	background.load("images/platform/background/full.png");
	background.setScale(scale_x, scale_y);
	backgroundTile.loadRepeated("images/other/sayagata.png", screen_w*1.5, screen_h*1.5, true);
	backgroundTile.setScale(0.75, 0.75);

	int wmove = 6;
	int window_w = screen_w * 0.8;
	int window_h = screen_h * 0.8;
	float xLeft = (screen_w - window_w) / 2;
	float xRight = screen_w - (screen_w - window_w) / 2;
	float yTop = screen_h * 0.15;
	float yBot = screen_h * 0.95;

	framec.load("images/other/framec.png");
	frameh.loadRepeated("images/other/frameh.png", 24, window_h - framec.getHeight()*2 + wmove*2.05);
	framev.loadRepeated("images/other/framev.png", window_w - framec.getWidth()*2 + wmove*2.05, 20);

	corners.push_back(std::make_pair(sf::Vector2f(-1, 1), sf::Vector2f(xLeft + framec.getWidth() - wmove, yTop - wmove)));
	corners.push_back(std::make_pair(sf::Vector2f(1, 1), sf::Vector2f(xRight - framec.getWidth() + wmove, yTop - wmove)));
	corners.push_back(std::make_pair(sf::Vector2f(1, -1), sf::Vector2f(xRight - framec.getWidth() + wmove, yBot + wmove)));
	corners.push_back(std::make_pair(sf::Vector2f(-1, -1), sf::Vector2f(xLeft + framec.getWidth() - wmove, yBot + wmove)));

	framesvertical.push_back(std::make_pair(sf::Vector2f(1, 1), sf::Vector2f(corners[0].second.x, yTop - wmove)));
	framesvertical.push_back(std::make_pair(sf::Vector2f(1, -1), sf::Vector2f(framesvertical[0].second.x, yBot + wmove)));

	frameshorizontal.push_back(std::make_pair(sf::Vector2f(-1, 1), sf::Vector2f(corners[0].second.x, corners[0].second.y + framec.getHeight())));
	frameshorizontal.push_back(std::make_pair(sf::Vector2f(1, 1), sf::Vector2f(corners[1].second.x, frameshorizontal[0].second.y)));
}

void EditorWindow::draw(sf::RenderWindow* &window)
{
	window->draw(backgroundTile.get());

	view = window->getDefaultView();
	view.setViewport(sf::FloatRect(0.1, 0.15, 0.8, 0.8));
	window->setView(view);
	window->draw(background.get());
	window->setView(window->getDefaultView());

	for (auto &it : corners)
	{
		framec.setScale(it.first.x, it.first.y);
		framec.setPosition(it.second.x, it.second.y);
		window->draw(framec.get());
	}

	for (auto &it : framesvertical)
	{
		framev.setScale(it.first.x, it.first.y);
		framev.setPosition(it.second.x, it.second.y);
		window->draw(framev.get());
	}

	for (auto &it : frameshorizontal)
	{
		frameh.setScale(it.first.x, it.first.y);
		frameh.setPosition(it.second.x, it.second.y);
		window->draw(frameh.get());
	}
}