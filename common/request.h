#pragma once
#include <thread>
#include <string>
#include <memory>
#include <SFML/Network.hpp>

namespace cmm
{
	class Request
	{
		sf::Http http;
		std::string result;
		sf::Http::Request request;
		sf::Http::Response response;

	public:
		bool sendRequest();
		const std::string& getResult() const;
		void setHttp(std::string url);
		void setMessage(std::string message);
		void setRequest(std::string uri, sf::Http::Request::Method method = sf::Http::Request::Post);
	};

	struct Thread
	{
		bool ready;
		bool success;
		std::thread* thread;

		Thread();
		~Thread();
		void free();
		void reset();
	};
}