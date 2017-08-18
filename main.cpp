#include "engine.h"
// #include "dirent.h"

int main( int argc, char **argv )
{
	Engine* engine = new Engine;

	engine->loop();

    delete engine;
    engine = NULL;
	
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
