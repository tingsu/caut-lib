#include "caut.h"
#define MAXL 6
#define MAX_ASSOC_RULES 100
void dump_associated_rules( char file[MAXL], int ds, int rule_linenum[MAXL], int size)
{
	int i, j;
	int num_associated_rules = 0;
	//int rule_set[MAX_ASSOC_RULES + 1];
	int rule_set[MAXL];
	int p = 0;
	if(size >= MAXL)
		return;
	for ( i = 1; i <= size; ++i )
	{
		int rule_num = rule_linenum[i];
		for ( j = 1; j <= num_associated_rules; ++j )
			if ( rule_num == rule_set[j] )
				break;
		if ( j > num_associated_rules )
		{ /* new rule */
			if ( num_associated_rules < MAXL -1 )
				rule_set[++num_associated_rules] = rule_num;
		}
	}
	//bubble( rule_set, num_associated_rules );
	for ( i = 1; i <= num_associated_rules; ++i )
	{
		if ( i % 8 == 1 )
			//putc( '\n', file );
			if(p<MAXL)
			{
				file[p] = '\n';
				p++;
			}
	}
	//putc( '\n', file );
	if(p<MAXL)
	{
		file[p] = '\n';
		p++;
	}
	return;
}

void testme()
{
	char file[MAXL];
	int ds;
	int rule_linenum[MAXL];
	int size;
	CAUT_INPUT(file);
	CAUT_INPUT(ds);
	CAUT_INPUT(rule_linenum);
	CAUT_INPUT(size);
	dump_associated_rules(file,ds,rule_linenum,size);
}
