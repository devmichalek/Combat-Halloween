<<<<<<< HEAD
/**
    main.cpp
    Purpose: Create engine, call loop then delete.

    @author Adrian Michalek
    @version 2016.08.14
	@email adrmic98@gmail.com
*/

#include "engine.h"

int main( int argc, char** argv )
{
    Engine* engine = new Engine;
=======
#include "engine.h"
// #include "dirent.h"

int main( int argc, char **argv )
{
	Engine* engine = new Engine;
>>>>>>> Combat-Halloween/master

	engine->loop();

    delete engine;
    engine = NULL;
<<<<<<< HEAD

    return EXIT_SUCCESS;
}
=======
	
	/*
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir ("C:\\Users\\adriqun\\Documents\\cppworkspace")) != NULL) {
	  // print all the files and directories within directory
	  while ((ent = readdir (dir)) != NULL) {
		printf ("%s\n", ent->d_name);
	  }
	  closedir (dir);
	} else {
	  // could not open directory
	  perror ("");
	  return EXIT_FAILURE;
	}
	
	string s;
	cin >> s;
	*/
	return EXIT_SUCCESS;
}
>>>>>>> Combat-Halloween/master
