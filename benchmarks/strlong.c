#include "caut.h"
#define MAXLEN 10

/* Convert a string to an intmax_t integer, with an arbitrary base.
   0nnn -> base 8
   0[Xx]nn -> base 16
   Anything else: [base#]number (this is implemented to match ksh93)

   Base may be >=2 and <=64.  If base is <= 36, the numbers are drawn
   from [0-9][a-zA-Z], and lowercase and uppercase letters may be used
   interchangably.  If base is > 36 and <= 64, the numbers are drawn
   from [0-9][a-z][A-Z]_@ (a = 10, z = 35, A = 36, Z = 61, @ = 62, _ = 63 --
   you get the picture). */

static int
strlong (char num[MAXLEN])
{
  register char *s;
  register unsigned char c;
  int base, foundbase;
  int val;
  int my_function_call = 0;

  s = num;

  base = 10;
  foundbase = 0;
  if (*s == '0')
    {
      s++;

      if (*s == '\0')
	return 0;

       /* Base 16? */
      if (*s == 'x' || *s == 'X')
	{
	  base = 16;
	  s++;
	}
      else
	base = 8;
      foundbase++;
    }

  val = 0;
  for (c = *s++; c; c = *s++)
    {
      if (c == '#')
	{
	  if (foundbase)
	    //evalerror (_("invalid number"));
	    my_function_call++;

	  /* Illegal base specifications raise an evaluation error. */
	  if (val < 2 || val > 64)
	    //evalerror (_("invalid arithmetic base"));
	    my_function_call++;

	  base = val;
	  val = 0;
	  foundbase++;
	}
      else if (/*ISALNUM(c) ||*/ (c == '_') || (c == '@'))
	{
	  if (((c) >= '0' && (c) <= '9'))//DIGIT(c))
	    c = ((c) - '0');//TODIGIT(c);
	  else if (c >= 'a' && c <= 'z')
	    c -= 'a' - 10;
	  else if (c >= 'A' && c <= 'Z')
	    c -= 'A' - ((base <= 36) ? 10 : 36);
	  else if (c == '@')
	    c = 62;
	  else if (c == '_')
	    c = 63;

	  if (c >= base)
	    //evalerror (_("value too great for base"));
	    my_function_call++;

	  val = (val * base) + c;
	}
      else
	break;
    }

  return (val);
}

void testme(){

	char num[MAXLEN];
	
	CAUT_INPUT(num);

	strlong(num);
}

