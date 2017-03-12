#pragma once

#include "04_platform/world/weather/rain/rain_cloud.h"

class Snow_cloud :public Rain_cloud
{
public:
	
	using Rain_cloud::Rain_cloud;
	
	void create( string path, int screen_w, int screen_h );
	void mechanics( int screen_w, int screen_h );
};