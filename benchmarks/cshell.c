#include "caut.h"
#define MAXL 8
#define Char unsigned char
void cshell( Char v[MAXL], int n, int special_case_0 )
{
	int gap, i, j, jg;
	Char k;
	for ( gap = n - 2; gap > 0; gap = gap - 2 )
		for ( i = gap; i < n; ++i )
			for ( j = i - gap; j >= 0; j = j - gap )
			{
				jg = j + gap;

				if ( special_case_0 )
				{
					if(jg >= MAXL || j >= MAXL)
						return;
					if ( v[jg] == 0 )
						break;
					else if ( v[j] != 0 && v[j] <= v[jg] )
						break;
				}
				else if ( v[j] <= v[jg] )
					break;
				k = v[j];
				v[j] = v[jg];
				v[jg] = k;
			}
}
void testme()
{
	Char v[MAXL];
	int n;
	int special_case_0;

	CAUT_INPUT(v);
	CAUT_INPUT(n);
	CAUT_INPUT(special_case_0);

	cshell( v, n, special_case_0);
}
