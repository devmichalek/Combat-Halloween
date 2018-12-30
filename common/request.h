#pragma once
#include <string>
#include <SFML/Network.hpp>

namespace cmm
{
	const std::string WEBSITE_PATH = "http://amichalek.pl/";
	const std::string WEBSITE_SUBPATH = "/combathalloween/";
	const std::string WEBSITE_FULLPATH = "http://amichalek.pl/combathalloween/";
	const std::string GITHUB_FULLPATH = "https://github.com/devmichalek/Combat-Halloween";

	class Request final
	{
		sf::Http http;
		std::string result;
		sf::Http::Request request;
		sf::Http::Response response;

	public:
		explicit Request();
		~Request();

		bool sendRequest();
		const std::string& getResult() const;
		void setHttp(std::string url);
		void setMessage(std::string message);
		void setRequest(std::string uri, sf::Http::Request::Method method = sf::Http::Request::Post);
	};
}
