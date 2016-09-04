#ifndef TEXT_H
#define TEXT_H

#include <stdlib.h>

// COLORS	
#define DEFAULT "\x1B[0m"
#define BLACK "\x1B[0m"
#define RED  "\x1B[31m"
#define GREEN  "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE  "\x1B[34m"
#define MAGENTA  "\x1B[35m"
#define CYAN  "\x1B[36m"
#define LGRAY  "\x1B[37m"
#define DGRAY  "\x1B[90m"
#define LRED  "\x1B[91m"
#define LGREEN "\x1B[92m"
#define LYELLOW  "\x1B[93m"
#define LBLUE  "\x1B[94m"
#define LMAGENTA  "\x1B[95m"
#define LCYAN  "\x1B[96m"
#define WHITE  "\x1B[97m"


// SET
#define BOLD "\x1B[1m"
#define WHITEBOLD "\x1B[97;1m"
#define LREDBOLD "\x1B[31;1m"

void clear();
void centre( int w, char* s );

#endif // TEXT_H