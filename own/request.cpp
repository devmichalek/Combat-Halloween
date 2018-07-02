#include "request.h"


MyRequest::MyRequest()
{
	free();
}

MyRequest::~MyRequest()
{
	free();
}

void MyRequest::free()
{
	result = "";
	message = "";
}



void MyRequest::setMessage( string message )
{
	this->message = message;
}

void MyRequest::setHttp( string url )
{
	this->http.setHost( url );
}

void MyRequest::setRequest( string uri, sf::Http::Request::Method method )
{
	request.setUri( uri );
	request.setMethod( method );
	request.setBody( message );	// Encode the parameters in the request body.
}



bool MyRequest::sendRequest()
{
    sf::Http::Response response = http.sendRequest( request );
	
	// Check the status.
    if( response.getStatus() == sf::Http::Response::Ok )
    {
		result = response.getBody();
		return true;
	}
	
	return false;
}

string MyRequest::getResult()
{
	return result;
}


MyThread::MyThread()
{
	t = NULL;
	free();
}

MyThread::~MyThread()
{
	free();
}

void MyThread::free()
{
	reset();
	s = false;
}

void MyThread::reset()
{
	r = false;
	
	if( t != NULL )
	{
		delete t;
		t = NULL;
	}
}