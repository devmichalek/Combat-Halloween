#pragma once
#define _GLIBCXX_USE_CXX11_ABI 0
#include <SFML/Network.hpp>
#include <thread>
#include <iostream>

using namespace std;

class MyRequest
{
	string result;
	string message;
	
	sf::Http http;
	sf::Http::Request request;
	sf::Http::Response response;
	
public:
	
	MyRequest();
	~MyRequest();
	void free();
	
	void setMessage( string message );
	void setHttp( string url );
	void setRequest( string uri, sf::Http::Request::Method method = sf::Http::Request::Post );
	
	bool sendRequest();
	string getResult();
};

struct MyThread
{
	bool r, s;	// Ready, success.
	thread* t;	// Thread.
	
	MyThread();
	~MyThread();
	void free();
	void reset();
};