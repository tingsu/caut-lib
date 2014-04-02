#include "caut.h"
#define MAXL 10
void skelout(char *skelfile, char data[MAXL],int len,int C_plus_plus)
{
	char buf_storage[MAXL];
	char *buf = buf_storage;
	int do_copy = 1;
	int i = 0;
	int dg=0;

	skelfile = &(data[0]);
	buf = skelfile;
	if(len > MAXL)
		return;
	while ( buf < &(data[MAXL-2]))
	{ /* copy from skel array */
		if ( buf[0] == '%' )
		{ /* control line */
			switch ( buf[1] )
			{
				case '%':
					return;

				case '+':
					do_copy = C_plus_plus;
					break;

				case '-':
					do_copy = ! C_plus_plus;
					break;

				case '*':
					do_copy = 1;
					break;

				default:
					return;
			}
		}
		else if ( do_copy )
		{
			if ( skelfile )
				/* Skeleton file reads include final
				 * newline, skel[] array does not.
				 */
				//out( buf );
				dg++;
			else
				//outn( buf );
				dg++;
		}
		buf ++;
	}
	return;
}
void testme()
{
	char *skelfile;
	char data[MAXL];
	int len;
	int C_plus_plus;
	CAUT_INPUT(skelfile);
	CAUT_INPUT(data);
	CAUT_INPUT(len);
	CAUT_INPUT(C_plus_plus);
	skelout(skelfile,data,len,C_plus_plus);
}
