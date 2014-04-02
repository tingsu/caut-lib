#include "caut.h"

void Merge(int t1[3], int t2[3], int t3[6]) {

  int i = 0, j = 0, k = 0 ;

  while (i < 3 && j < 3) { // line 09
    if (t1[i] < t2[j]) {   // line 10
      t3[k] = t1[i];
      i++;
    }
    else {
      t3[k] = t2[j];
      j++;
    }
    k++ ;
  }
  while (i < 3) {          // line 20
    t3[k] = t1[i];
    i++;
    k++;
  }
  while (j < 3) {          // line 25
    t3[k] = t2[j];
    j++;
    k++;
  }
}

void testme(){

	int t1[3];
	int t2[3];
	int t3[6];

	CAUT_INPUT(t1);
	CAUT_INPUT(t2);
	CAUT_INPUT(t3);

	Merge(t1,t2,t3);

}
