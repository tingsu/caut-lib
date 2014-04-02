#include "caut.h"

static int
mkfmt (char buf[20],char abuf[20],int precs[20],int prec,int lng,long sec,int sec_fraction)
{
  long min;
  //char abuf[16];
  int ind, aind;

  ind = 0;
  abuf[15] = '\0';

  /* If LNG is non-zero, we want to decompose SEC into minutes and seconds. */
  if (lng)
    {
      min = sec / 60;
      sec %= 60;
      aind = 14;
      do
	abuf[aind--] = (min % 10) + '0';
      while ((min /= 10)&&aind>=0);
      aind++;
      while (abuf[aind]&&aind<16)
	buf[ind++] = abuf[aind++];
      buf[ind++] = 'm';
    }

  /* Now add the seconds. */
  aind = 14;
  do
    abuf[aind--] = (sec % 10) + '0';
  while ((sec /= 10)&&aind>=0);
  aind++;
  while (abuf[aind]&&aind<16)
    buf[ind++] = abuf[aind++];

  /* We want to add a decimal point and PREC places after it if PREC is
     nonzero.  PREC is not greater than 3.  SEC_FRACTION is between 0
     and 999. */
  if (prec != 0)
    {
      buf[ind++] = '.';
      for (aind = 1; aind <= prec; aind++)
	{
		if(precs[aind]!=0)
			{
					  buf[ind++] = (sec_fraction / precs[aind]) + '0';
					  sec_fraction %= precs[aind];
			}
	}
    }
    if (lng)
    buf[ind++] = 's';
  buf[ind] = '\0';

  return (ind);
}


void testme()
{
  char buf[20];
  char abuf[20];
  int precs[20];
  int prec,lng;
  long sec;
  int sec_fraction;
  CAUT_INPUT(buf);
  CAUT_INPUT(abuf);
  CAUT_INPUT(precs);
  CAUT_INPUT(prec);
  CAUT_INPUT(lng);
  CAUT_INPUT(sec);
  CAUT_INPUT(sec_fraction);
  
  mkfmt (buf,abuf,precs,prec,lng,sec,sec_fraction);
}
