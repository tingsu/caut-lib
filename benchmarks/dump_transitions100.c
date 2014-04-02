#include "caut.h"
#define MAXL 6
#define CSIZE 6
void dump_transitions( char file[MAXL], int state[MAXL], int csize, int ecgroup[CSIZE+1] )
{
	int i, ec;
	int out_char_set[CSIZE];
	if(csize > CSIZE)
		return;
	for ( i = 0; i < csize; ++i )
	{
		//ec = ABS( ecgroup[i] );
		if(ecgroup[i] >= 0)
			ec = ecgroup[i];
		else
			ec = 0-ecgroup[i];
		if(ec > MAXL -1)
			return;
		out_char_set[i] = state[ec];
	}
	//list_character_set( file, out_char_set, csize );
	/* now invert the members of the set to get the jam transitions */
	for ( i = 0; i < csize; ++i )
		out_char_set[i] = ! out_char_set[i];
	//list_character_set( file, out_char_set, csize );
	//putc( '\n', file );
}

void testme()
{
	char file[MAXL];
	int state[MAXL];
	int csize;
	int ecgroup[CSIZE+1];
	CAUT_INPUT(file);
	CAUT_INPUT(state);
	CAUT_INPUT(csize);
	CAUT_INPUT(ecgroup);
	dump_transitions(file,state,csize,ecgroup);
}
