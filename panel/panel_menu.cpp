/**
    panel_menu.h
    Purpose: class Panel_menu as a main class in panel state.

    @author Adrian Michalek
    @version 2017.02.22
	@email adrmic98@gmail.com
*/

#include "panel_menu.h"
#include "file/file.h"
// #include <curl/curl.h>
#include <SFML/Network.hpp>
#include <time.h>


Panel_menu::Panel_menu()
{
	state = 0;
	
	music = new Music;
	bg = new MySprite;
	replay_button = new Replay_button;
	backtomenu_panel = new Backtomenu_panel;
	show_scores = new Show_scores;
}

Panel_menu::~Panel_menu()
{
	free();
}

void Panel_menu::free()
{
	sound.free();
	
	delete music;
	
	if( bg != NULL )
		delete bg;
		
	if( replay_button != NULL )
		delete replay_button;
	
	if( backtomenu_panel != NULL )
		delete backtomenu_panel;
		
	if( show_scores != NULL )
		delete show_scores;
}

void Panel_menu::reset()
{
	music->halt();
	replay_button->setState( 0 );
	backtomenu_panel->setState( 0 );
}



void Panel_menu::load( unsigned screen_w, unsigned screen_h )
{
	bg->setName( "panel_menu-background" );
	bg->load( "data/menu/background.png" );
	
	replay_button->load( screen_h );
	
	backtomenu_panel->load( replay_button->getRight(), replay_button->getTop() );
	
	music->setID( "panel_menu-music" );
	music->load( "data/panel/music.mp3", 50 );
	
	show_scores->load( screen_w, screen_h, replay_button->getTop() );
}

void Panel_menu::handle( sf::Event &event )
{
	if( backtomenu_panel->getState() != 2 )
	{
		replay_button->handle( event );
	}
	
	if( replay_button->getState() != 2 )
	{
		backtomenu_panel->handle( event );
	}
}

void Panel_menu::draw( sf::RenderWindow* &window )
{
	if( sound.getMusicPlay() )
	{
		music->play();
	}
	
	window->draw( bg->get() );
	replay_button->draw( window );
	backtomenu_panel->draw( window );
	show_scores->draw( window );
	
	
	if( replay_button->getState() == 2 || backtomenu_panel->getState() == 2 )
	{
		sf::Uint8 value = 4;
		music->fadeout( 1, 0 );
		bg->fadeout( value );
		replay_button->fadeout( value );
		backtomenu_panel->fadeout( value );
		show_scores->fadeout( value );
	}
	else
	{
		sf::Uint8 value = 3;
		music->fadein( 1, sound.getMusicVolume() );
		bg->fadein( value );
		replay_button->fadein(value );
		backtomenu_panel->fadein( value );
		show_scores->fadein( value );
	}
}



int Panel_menu::getState()
{
	return state;
}

void Panel_menu::setState( int state )
{
	this->state = state;
}



bool Panel_menu::backToMenu()
{
	return backtomenu_panel->nextState();
}

bool Panel_menu::backToPlatform()
{
	return replay_button->nextState();
}



const string Panel_menu::currentDateTime()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
	
    strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);

    return buf;
}

void Panel_menu::set( int scores, int type, bool status, int coruption, string timePlayed, int mines, int money )
{
	show_scores->setScores( scores );
	show_scores->setResult( status );
	show_scores->setMoney( money );
	show_scores->setMine( mines, type );
	show_scores->setTimePlayed( timePlayed );
	
	// Query
	string nick = "";
	string world = "world=" +show_scores->setWorld( type ) +"&";
	string difficulty = "difficulty=" +show_scores->setCoruption( coruption ) +"&";
	string points = "points=" +con::itos( scores ) +"&";
	string time_playing = "time_playing=" +timePlayed +"&";
	string date = "date=" +currentDateTime();
	
	MyFile f;
	f.load( "data/txt/nick/nick_current.txt" );
	if( f.is_good() )
	{
		string line;
		f.get() >> line;
		nick = "nick=" +line +"&";
	}
	f.free();
	
	/*
	printf( "%s\n", nick.c_str() );
	printf( "%s\n", world.c_str() );
	printf( "%s\n", difficulty.c_str() );
	printf( "%s\n", points.c_str() );
	printf( "%s\n", time_playing.c_str() );
	printf( "%s\n", date.c_str() );
	*/
	string general_result = nick +world +difficulty +points +time_playing +date;
	// printf( "%s\n", general_result.c_str() );
	
	// prepare the request
     sf::Http::Request request( "/file.php", sf::Http::Request::Post );

    // encode the parameters in the request body
    request.setBody( general_result );

    // send the request
    sf::Http http("path");
    sf::Http::Response response = http.sendRequest(request);

    // check the status
    if( response.getStatus() != sf::Http::Response::Ok )
    {
        // printf( "request failed\n" );
    }
	
	/*
	CURL* curl;
    CURLcode res;
 
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
 
    if( curl )
	{
        curl_easy_setopt( curl, CURLOPT_URL, "https://catchbumblebee.000webhostapp.com//query.php" );
        curl_easy_setopt( curl, CURLOPT_POSTFIELDS, general_result.c_str() ) ;
 
        res = curl_easy_perform(curl);
 
        if( res != CURLE_OK )
		{
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
 
        curl_easy_cleanup(curl);
    }
 
    curl_global_cleanup();
	*/
	
	if( status && type < 4 )
	{
		MyFile file;
		vector <int> world_values;
		
		file.load( "data/txt/world/world_temporary.txt" );
		if( file.is_good() )
		{
			string line;
			while( file.get() >> line )
			{
				world_values.push_back( con::stoi( line ) );
			}
		}
		file.free();
		
		int look = 0;
		file.load( "data/txt/world/world_whatsnext.txt" );
		if( file.is_good() )
		{
			string line;
			int c = type;
			while( file.get() >> line )
			{
				if( c == 0 )
				{
					look = con::stoi( line );
					break;
				}
				c --;
			}
		}
		file.free();
		
		world_values[ look ] = 1;
		
		file.load( "data/txt/world/world_temporary.txt", std::ios::out );
		if( file.is_good() )
		{
			for( auto &it :world_values )
			{
				file.get() << con::itos( it ) << "\n";
			}
		}
		file.free();
		
		world_values.clear();
		
// ---------------------------------------------------------------------------------------------------
		
		int actual = 0;
		file.load( "data/txt/heart/heart_current.txt" );
		if( file.is_good() )
		{
			string line;
			file.get() >> line;
			actual = con::stoi( line );
		}
		file.free();
		
		look = 0;
		file.load( "data/txt/heart/heart_whatsnext.txt" );
		if( file.is_good() )
		{
			string line;
			int c = type;
			while( file.get() >> line )
			{
				if( c == 0 )
				{
					look = con::stoi( line );
					break;
				}
				c --;
			}
		}
		file.free();
		// printf( "%d\n", look );

		if( look > actual )
		{
			file.load( "data/txt/heart/heart_current.txt", std::ios::out );
			if( file.is_good() )
			{
				file.get() << con::itos( look ) << "\n";
			}
			file.free();
		}
	}
}

void Panel_menu::setSound()
{
	// Set chunks
	if( !sound.getChunkPlay() )
	{
		replay_button->turnOff();
		backtomenu_panel->turnOff();
	}
	else
	{
		replay_button->turnOn();
		backtomenu_panel->turnOn();
		
		// Set chunk volume
		replay_button->setVolume( sound.getChunkVolume() );
		backtomenu_panel->setVolume( sound.getChunkVolume() );
	}
	
	// Set music volume
	music->setVolume( sound.getMusicVolume() );
}

void Panel_menu::reloadMusic()
{
	music->reload();
	Mix_HaltMusic();
}