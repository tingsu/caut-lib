#include "caut.h"

int foo(int x,int y){
	
	if( x!=0 && y>3  ){ 		
		//while( y==4 && (x-y > 7) ){
			y++;
		//}
	}
	else{
		y--;
	}

	return 0;
}

void testme(){
  int x;
  int y;
  CAUT_INPUT(x);
  CAUT_INPUT(y);
  foo(x,y);
}

