#include "caut.h"
#define MAXL 6


int foo(int x){

	if(x>-3)
		return x;
	else
		return x-1;
}


void bubble( int v[MAXL], int n )
{
	int i, j, k;
	int tmp;
	tmp = foo(n);
	if(n >= MAXL)
		return;
	for ( i = n; i > 1; --i )
		for ( j = 1; j < i; ++j )
			if ( v[j] > v[j + 1] )	/* compare */
			{
				k = v[j];	/* exchange */
				v[j] = v[j + 1];
				v[j + 1] = k;
			}
}


void testme()
{
	int v[MAXL];
	int n;
	CAUT_INPUT(v);
	CAUT_INPUT(n);
	bubble(v,n);
}


