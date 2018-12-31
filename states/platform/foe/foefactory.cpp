// Family
#include "foefactory.h"
#include "skeleton.h"
#include "zombie.h"

// Common
#include "converter.h"

// Boost
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

FoeFactory::FoeFactory()
{
	resolution = nullptr;
	wrapper = nullptr;
	free();
}

FoeFactory::~FoeFactory()
{
	free();
}

void FoeFactory::free()
{
	if(resolution)
	{
		delete resolution;
		resolution = nullptr;
	}

	if (wrapper)
	{
		delete wrapper;
		wrapper = nullptr;
	}
}

void FoeFactory::reset()
{
	wrapper->incinerate();
}

void FoeFactory::load(const float &screen_w, const float &screen_h)
{
	free();

	// Prepare resolution.
	{
		resolution = new sf::Rect<float>;
		resolution->width = screen_w;
		resolution->height = screen_h;
	}

	// Open directory, load paths to templates and prepare types.
	std::vector<std::pair<int, std::string>> types;
	{
		std::string pathToDir = "config/";
		if (!boost::filesystem::is_directory(pathToDir))
		{
			// sth else?
			__debugbreak();
		}
		else
		{
			// Fill.
			int length = pathToDir.size();
			std::string TEMPLATE_EXTENSION = ".template";
			for (auto& entry : boost::make_iterator_range(boost::filesystem::directory_iterator(pathToDir), {}))
			{
				std::string buf = entry.path().string().substr(length, entry.path().string().size() - length);
				if (cmm::compareExtension(buf, TEMPLATE_EXTENSION))
				{
					// Found template file.
					types.push_back(std::make_pair(-1, buf));

					// Extract type.
					{
						std::string seek = "type: ";

						// Load content.
						{
							std::ifstream file_in;
							std::string line = cmm::SEMPTY;
							file_in.open(entry.path().string());
							while (std::getline(file_in, line))
								if (line.find(seek) != std::string::npos)
									break;
							file_in.close();
							buf = line;
						}

						std::string value = cmm::extractFromString(buf, seek, cmm::CNEWLINE);
						if (value.empty())
							__debugbreak();
						else
							types[types.size() - 1].first = boost::lexical_cast<int>(value);
					}
				}
			}
		}
	}

	// Sort templates by type.
	{
		using TemplatePair = std::pair<int, std::string>;
		struct {
			bool operator()(TemplatePair a, TemplatePair b) const
			{
				return a.first < b.first;
			}
		} CustomLess;
		std::sort(types.begin(), types.end(), CustomLess);
	}

	// Now templates are sorted.
	// Prepare wrapper.
	{
		wrapper = new FoeWrapper;
		std::vector<int> states;		// 3 for example APPEAR, IDLE, WALK etc.
		std::vector<int> offsets;		// 10, 12, 8 etc.
		std::vector<std::string> paths;	// skeleton, zombie, vampire etc.

		for (auto &it : types)
		{
			std::string path = "config/" + it.second;
			std::string data = cmm::SEMPTY;

			// Load content.
			{
				std::ifstream file_in;
				std::string line = cmm::SEMPTY;
				file_in.open(path);
				while (std::getline(file_in, line))
					data += line + cmm::CNEWLINE;
				file_in.close();
			}

			// States.
			std::string value = cmm::extractFromString(data, "states: ", cmm::CNEWLINE);
			states.push_back(boost::lexical_cast<int>(value));

			// Offsets.
			value = cmm::extractFromString(data, "offsets: ", cmm::CNEWLINE) + " ";
			std::string buf = cmm::SEMPTY;
			for (auto jt : value)
			{
				if (jt == cmm::CSPACE)
				{
					offsets.push_back(boost::lexical_cast<int>(buf));
					buf.clear();
					continue;
				}
				buf += jt;
			}

			// Path.
			value = cmm::extractFromString(data, "path: ", cmm::CNEWLINE);
			paths.push_back(value);
		}
		wrapper->load(paths, states, offsets);
	}

	// Test
	Foe* foe = nullptr;
	foe = new Zombie;
	foe->setSpriteType(0);
	foe->setSpriteLines({ 11, 6, 10, 7, 8 });
	foe->setScale(0.5);
	foe->setWidth(66);
	foe->setPosition(200, screen_h - 500);
	foe->setLeft(0);
	foe->setRight(screen_w);
	foe->setFeatures({ "10", "10", "100", "100", "4", "2" });
	foe->marshial();
	wrapper->insert(foe);
}

// Process ------------------------
void FoeFactory::update(sf::RenderWindow* &window,
						double elapsedTime,
						Rect* &character,
						Rect* &characterAttack,
						bool &characterHasAttacked,
						float &characterDamage,
						float &characterHP,
						float &characterArmour,
						float &newX,
						float &newY)
{
	// Prepare resolution.
	resolution->left = newX;
	resolution->top = newY;

	wrapper->update(window, elapsedTime, resolution, character, characterAttack, characterHasAttacked,
					characterDamage, characterHP, characterArmour);

	wrapper->process();
}