#include <stdio.h>
#include "caut.h"

  
int ar_touch (int t,int t1)
{
  char *arname, *memname;
  int arname_used = 0;
  register int val;
  int i=0;
  int dg=0;

  /* Make sure we know the modtime of the archive itself before we
     touch the member, since this will change the archive itself.  */
  {
    if(t)
      {
	arname_used = 1;
      }

  }

  val = 1;
  switch(t1)
    {
    case -1:
      dg++;
      break;
    case -2:
      dg++;
      break;
    case -3:
      dg++;
      break;
    case 1:
	dg++;
      break;
    case 0:
	dg++;
      val = 0;
      break;
    default:
         dg++;
    }

  if(!arname) i++;

  return val;
}

void testme()
{
  int t,t1;
	CAUT_INPUT(t);
	CAUT_INPUT(t1);
	
  ar_touch (t,t1);
}
