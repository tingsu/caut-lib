#include "caut.h"

int Bsearch( int A[8], int x) // tested function
{
  int low, high, mid, found ;
  
  low = 0 ;
  high = 7 ;
  found = 0 ;
  while( high > low )                    // line 09
    { mid = (low + high) / 2 ;
    
      if( x == A[mid] )                  // line 12
         found = 1;

      if( x > A[mid] )                   // line 15
        low = mid + 1 ;
      else
        high = mid - 1;
    }  
  mid = (low + high) / 2 ;

  if( ( found != 1)  && ( x == A[mid]) ) // line 22
    found = 1; 
  
  return found ;
}

void testme(){
	
	int A[8];
	int x;

	CAUT_INPUT(A);
	CAUT_INPUT(x);

	Bsearch(A,x);
}
