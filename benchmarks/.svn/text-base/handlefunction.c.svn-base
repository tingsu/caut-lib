#include "caut.h"

int
handle_function (char openparen,char beg[10],int t,int t1,int t2,int t3,int t4)
{
  
  char closeparen = openparen == '(' ? ')' : '}';
  char *end;
  int count = 0;
  register char *p;
  int nargs;
  
  int dg=0;

  if(beg==0) return 0;

  if(t)
    return 0;

  /* We found a builtin function.  Find the beginning of its arguments (skip
     whitespace after the name).  */


  /* Find the end of the function invocation, counting nested use of
     whichever kind of parens we use.  Since we're looking, count commas
     to get a rough estimate of how many arguments we might have.  The
     count might be high, but it'll never be low.  */

  for (nargs=1, end=beg; *end != '\0'; ++end)
    if (*end == ',')
      ++nargs;
    else if (*end == openparen)
      ++count;
    else if (*end == closeparen && --count < 0)
      break;

  if (count >= 0) dg++;

  /* Chop the string into arguments, then a nul.  As soon as we hit
     MAXIMUM_ARGS (if it's >0) assume the rest of the string is part of the
     last argument.

     If we're expanding, store pointers to the expansion of each one.  If
     not, make a duplicate of the string and point into that, nul-terminating
     each argument.  */

  if(t1)
    {
      int len = end - beg;

      end = beg + len;
    }

  p = beg;
  nargs = 0;
    {
      char *next;

      ++nargs;

        if(t2)
        next = end;

     if(t3) dg++;
      else
        {
        
          if(next!=0)
                *next = '\0';
        }

     p = next + 1;
    }
  if(t4) dg++;
  else dg++;

  return 1;
}

void testme()
{
  char beg[10];
  char openparen;
  int t,t1,t2,t3,t4;
  CAUT_INPUT(openparen);
  CAUT_INPUT(beg);
  CAUT_INPUT(t);
  CAUT_INPUT(t1);
  CAUT_INPUT(t2);
  CAUT_INPUT(t3);
  CAUT_INPUT(t4);
  handle_function (openparen,beg,t,t1,t2,t3,t4);
}
