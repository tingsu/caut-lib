#include "caut.h"

#define RP_LONG_LEFT	1
#define RP_SHORT_LEFT	2
#define RP_LONG_RIGHT	3
#define RP_SHORT_RIGHT	4

#define wchar_t	int
#define MAXLEN 10

static wchar_t *
remove_wpattern (wchar_t wparam[MAXLEN], int wstrlen,int *ret ,int op)
{
  wchar_t wc/*, *ret*/;
  int n;
  int my_function_call = 0;

  if( wstrlen<0 || wstrlen>=MAXLEN)
	return 0;

  switch (op)
    {
      case RP_LONG_LEFT:	/* remove longest match at start */
        for (n = wstrlen; n >= 0; n--)
	  {
	    wc = wparam[n]; wparam[n] = L'\0';
		my_function_call++;
	    if (my_function_call >= 0 )//wcsmatch (wpattern, wparam, FNMATCH_EXTFLAG) != FNM_NOMATCH)
	      {
		wparam[n] = wc;
		return (wparam);
	      }
	    wparam[n] = wc;
	  }
	break;

      case RP_SHORT_LEFT:	/* remove shortest match at start */
	for (n = 0; n <= wstrlen; n++)
	  {
	    wc = wparam[n]; wparam[n] = L'\0';
		my_function_call++;
	    if (my_function_call >= 20)//wcsmatch (wpattern, wparam, FNMATCH_EXTFLAG) != FNM_NOMATCH)
	      {
		wparam[n] = wc;
		return (wparam);
	      }
	    wparam[n] = wc;
	  }
	break;

      case RP_LONG_RIGHT:	/* remove longest match at end */
        for (n = 0; n <= wstrlen; n++)
	  {
	    my_function_call++;
	    if (my_function_call >= 40 )//wcsmatch (wpattern, wparam + n, FNMATCH_EXTFLAG) != FNM_NOMATCH)
	      {
		wc = wparam[n]; wparam[n] = L'\0';
		//ret = wcsdup (wparam);
		wparam[n] = wc;
		return (ret);
	      }
	  }
	break;

      case RP_SHORT_RIGHT:	/* remove shortest match at end */
	for (n = wstrlen; n >= 0; n--)
	  {
	    my_function_call++;
	    if (my_function_call >=60)//wcsmatch (wpattern, wparam + n, FNMATCH_EXTFLAG) != FNM_NOMATCH)
	      {
		wc = wparam[n]; wparam[n] = L'\0';
		//ret = wcsdup (wparam);
		wparam[n] = wc;
		return (ret);
	      }
	  }
	break;
    }

  return (wparam);	/* no match, return original string */
}

void testme(){
	
	wchar_t wparam[MAXLEN];
	int wstrlen;
	int *ret ;
	int op;

	CAUT_INPUT(wparam);
	CAUT_INPUT(wstrlen);
	CAUT_INPUT(ret);
	CAUT_INPUT(op);
	
	remove_wpattern (wparam, wstrlen, ret, op);
}
