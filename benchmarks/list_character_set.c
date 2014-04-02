#include "caut.h"
#define MAXL 10
void list_character_set( char file[MAXL], int cset[MAXL], int csize )
{
	int i;
	int p = 0;
	int dg=0;
	//putc( '[', file );
	file[p] = '[';
	p++;
	if(csize >= MAXL)
		return;

	for ( i = 0; i < csize; ++i )
	{
		if ( cset[i] )
		{
			int start_char = i;

			//putc( ' ', file );
			if(p >= MAXL)
				return;
			file[p] = ' ';
			p++;

			//fputs( readable_form( i ), file );
			while ( ++i < csize && cset[i] )
				;
			if ( i - 1 > start_char ) ;
				dg++;
				/* this was a run */
				//fprintf( file, "-%s", readable_form( i - 1 ) );

			//putc( ' ', file );
			file[p] = ' ';
			p++;
		}
	}
	//putc( ']', file );
	if(p>=MAXL)
		return;
	file[p] = ']';
	p++;
}
void testme()
{
	char file[MAXL];
	int cset[MAXL];
	int csize;
	CAUT_INPUT(file);
	CAUT_INPUT(cset);
	CAUT_INPUT(csize);
	list_character_set(file,cset,csize);
}
