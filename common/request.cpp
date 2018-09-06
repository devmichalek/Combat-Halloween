#include "request.h"

bool cmm::Request::sendRequest()
{
	sf::Http::Response response = http.sendRequest(request);

	// Check the status.
	if (response.getStatus() == sf::Http::Response::Ok)
	{
		result = response.getBody();
		return true;
	}

	result = "";
	return false;
}

const std::string& cmm::Request::getResult() const
{
	return result;
}

void cmm::Request::setHttp(std::string url)
{
	http.setHost(url);
}

void cmm::Request::setMessage(std::string message)
{
	request.setBody(message);	// Encode the parameters in the request body.
}

void cmm::Request::setRequest(std::string uri, sf::Http::Request::Method method)
{
	request.setUri(uri);
	request.setMethod(method);
}