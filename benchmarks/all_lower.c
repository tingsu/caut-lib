#include "caut.h"
#define MAXL 10
#define isascii(c) ((c) <= 0177)
int all_lower( char str[MAXL] )
{
	int i = 0;
	while ( i < MAXL )
	{
		if ( !isascii(str[i]) || ! (str[i] >= 'a'&& str[i]<='z') )
			return 0;
		i++;
	}
	return 1;
}

void testme()
{
	char str[MAXL];
	CAUT_INPUT(str);
	all_lower(str);
}
