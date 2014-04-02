/* snstods - converts a set of ndfa states into a dfa state
 *
 * synopsis
 *    is_new_state = snstods( int sns[numstates], int numstates,
 *				int accset[num_rules+1], int nacc,
 *				int hashval, int *newds_addr );
 *
 * On return, the dfa state number is in newds.
 */
//#include <stdlib.h>
#include "caut.h"
#define MAXLEN 5

int snstods (int sns[MAXLEN], int numstates, int accset[MAXLEN], int nacc, int hashval, int newds_addr[1],
	 int lastdfa, int dhash[MAXLEN],int dfasiz[MAXLEN],int dss[MAXLEN][MAXLEN],int dfaeql,int hshcol,int hshsave,int current_max_dfas, int reject,int accsiz[MAXLEN],int num_rules,int rule_useful[MAXLEN])
{
	int     didsort = 0;
	register int i, j;
	int     newds, *oldsns;
	int my_function_call = 0 ;


	for (i = 1; i <= lastdfa && lastdfa < MAXLEN /* add by me */ ; ++i) 
		if (hashval == dhash[i]) {  
			if (numstates == dfasiz[i]) {
				oldsns = dss[i];

				if (!didsort) {
					/* We sort the states in sns so we
					 * can compare it to oldsns quickly.
					 * We use bubble because there probably
					 * aren't very many states.
					 */
					//bubble (sns, numstates);
					my_function_call++;
					didsort = 1;
				}

				
				for (j = 1; j <= numstates && numstates<MAXLEN /*add by me*/ ; ++j) 
					if (sns[j] != oldsns[j])
						break;
				

				if (j > numstates) {
					++dfaeql;
					*newds_addr = i;
					return 0;
				}

				++hshcol;
			}

			else
				++hshsave;
		}

	/* Make a new dfa. */

	if (++lastdfa >= current_max_dfas)
		//increase_max_dfas ();
		my_function_call++;

	newds = lastdfa;

	//dss[newds] = allocate_integer_array (numstates + 1);
	//dss[newds] = {0};

	/* If we haven't already sorted the states in sns, we do so now,
	 * so that future comparisons with it can be made quickly.
	 */

	if (!didsort)
		//bubble (sns, numstates);
		my_function_call++;

	for (i = 1; i <= numstates ; ++i)
		if( newds >=0 && newds<MAXLEN)
			dss[newds][i] = sns[i];

	if( newds >=0 && newds<MAXLEN){		/*add by me */
		dfasiz[newds] = numstates;
		dhash[newds] = hashval;
	}

	if (nacc == 0) {
		if (reject)
			//dfaacc[newds].dfaacc_set = (int *) 0;
			my_function_call++;
		else
			//dfaacc[newds].dfaacc_state = 0;
			my_function_call++;
		
		if( newds >=0 && newds<MAXLEN) 
			accsiz[newds] = 0;
	}

	else if (reject) {
		/* We sort the accepting set in increasing order so the
		 * disambiguating rule that the first rule listed is considered
		 * match in the event of ties will work.  We use a bubble
		 * sort since the list is probably quite small.
		 */

		//bubble (accset, nacc);
		my_function_call++;

		//dfaacc[newds].dfaacc_set =
		//	allocate_integer_array (nacc + 1);
		my_function_call++;

		/* Save the accepting set for later */
		for (i = 1; i <= nacc; ++i) {
			//dfaacc[newds].dfaacc_set[i] = accset[i];
			my_function_call++;

			if (accset[i] <= num_rules && accset[i]< MAXLEN ) /* add by me , suting */
				/* Who knows, perhaps a REJECT can yield
				 * this rule.
				 */
				rule_useful[accset[i]] = 1;
		}

		if( newds >=0 && newds<MAXLEN) 
			accsiz[newds] = nacc;
	}

	else {
		/* Find lowest numbered rule so the disambiguating rule
		 * will work.
		 */
		j = num_rules + 1;

		for (i = 1; i <= nacc && nacc < MAXLEN ; ++i) /*add by me */
			if (accset[i] < j)
				j = accset[i];

		//dfaacc[newds].dfaacc_state = j;
		my_function_call++;

		if (j <= num_rules && num_rules < MAXLEN ) /*add by me */
			rule_useful[j] = 1;
	}

	*newds_addr = newds;
	return 1;
}


void testme(){

	int sns[MAXLEN];
	int numstates;
	int accset[MAXLEN];
	int nacc;
	int hashval;
	int newds_addr[1];
	int lastdfa;
	int dhash[MAXLEN];
	int dfasiz[MAXLEN];
	int dss[MAXLEN][MAXLEN];
	int dfaeql;
	int hshcol;
	int hshsave;
	int current_max_dfas;
	int reject;
	int accsiz[MAXLEN];
	int num_rules;
	int rule_useful[MAXLEN];

	CAUT_INPUT(sns);
	CAUT_INPUT(numstates);
	CAUT_INPUT(accset);
	CAUT_INPUT(nacc);
	CAUT_INPUT(hashval);
	CAUT_INPUT(newds_addr);
	CAUT_INPUT(lastdfa);
	CAUT_INPUT(dhash);
	CAUT_INPUT(dfasiz);
	CAUT_INPUT(dss);
	CAUT_INPUT(dfaeql);
	CAUT_INPUT(hshcol);
	CAUT_INPUT(hshsave);
	CAUT_INPUT(current_max_dfas);
	CAUT_INPUT(reject);
	CAUT_INPUT(accsiz);
	CAUT_INPUT(num_rules);
	CAUT_INPUT(rule_useful);	


	snstods (sns,numstates, accset, nacc, hashval, newds_addr,
	 lastdfa, dhash,dfasiz,dss,dfaeql,hshcol,hshsave, current_max_dfas, reject,accsiz,num_rules,rule_useful);
}


/*
int main(){

	int sns[MAXLEN];
	int numstates;
	int accset[MAXLEN];
	int nacc;
	int hashval;
	int newds_addr[1];
	int lastdfa;
	int dhash[MAXLEN];
	int dfasiz[MAXLEN];
	int dss[MAXLEN][MAXLEN];
	int dfaeql;
	int hshcol;
	int hshsave;
	int current_max_dfas;
	int reject;
	int accsiz[MAXLEN];
	int num_rules;
	int rule_useful[MAXLEN];

	snstods (sns,numstates, accset, nacc, hashval, newds_addr,
	 lastdfa, dhash,dfasiz,dss,dfaeql,hshcol,hshsave, current_max_dfas, reject,accsiz,num_rules,rule_useful);
}
*/

