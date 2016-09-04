#include "color.h"
#include <stdio.h>


void clear()
{
	printf( "%s", "\x1B[0m" );
}

void centre( int w, char* s )
{
	unsigned long len = strlen( s );
	int nr = ( w - len ) /2;
	
	for( int i = 0; i < nr; ++i )
	{
		printf( " " );
	}
	
	printf( "%s", s );
}