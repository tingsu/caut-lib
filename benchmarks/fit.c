#include "caut.h"
#define MAXLEN 6

int global_int;
int* global_p;
struct A{

	int i;
	int* pp;
};
struct A* global_A;

int testloop(int x, int arr[MAXLEN]/*, struct A a*/){

	int i;

	//if(a.i == 0)
	//	return 0;

	//if(global_A == 0 )
	//	return 0;
	//if(global_A->i==2)
	//	return 0;

	//if(global_p == 0)
	//	return 0;
	
	if(global_int == 4){

		if( x == 2){

			for(i=0; i < MAXLEN ; i++)
				if( arr[i] == 3 )
					x++;
			if( x == 6 )
				return 1;
		}
	}

	return 0;
}


void testme(){

	int x;
	int arr[MAXLEN];
	//struct A a;
	
	CAUT_INPUT(x);
	CAUT_INPUT(arr);
	CAUT_INPUT(global_int);
	//CAUT_INPUT(global_p);
	//CAUT_INPUT(global_A);
	//CAUT_INPUT(a);

	testloop(x,arr/*,a*/);
}
