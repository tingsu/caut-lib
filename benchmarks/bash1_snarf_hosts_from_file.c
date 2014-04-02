#include "caut.h"

static void snarf_hosts_from_file (char *temp, char buffer[256],int my_function_call)
{
  //FILE *file;
  char name[256];
  register int i, start;
  int dg=0;

  //file = fopen (filename, "r");
  //if (filename == NULL)
  //  return;

  my_function_call++;

  if( temp == 0)
	return ;

 // while (temp = fgets (buffer, 255, file))
 //while (*temp !='\0')
 if (*temp !='\0')
    {

      
      /* Skip to first character. */
      for (i = 0; buffer[i] && ((buffer[i]) == '\r' || (buffer[i]) == '\n' || (buffer[i]) == ' ' || (buffer[i]) == '\t'); i++)
	if( i>5)
		break;

      /* If comment or blank line, ignore. */
      if (buffer[i] == '\0' || buffer[i] == '#')
	//continue;
	dg++;

      /* If `preprocessor' directive, do the include. */
      if (my_function_call > 0 )//strncmp (buffer + i, "$include ", 9) == 0)
	{
	  char *incfile, *t;

	  /* Find start of filename. */
	  for (incfile = buffer + i + 9; *incfile && (((*incfile) == ' ') || ((*incfile) == '\t')); incfile++)
	    if( i>18)
		break;

	  /* Find end of filename. */
	  for (t = incfile; *t && ((*t) == '\r' || (*t) == '\n' || (*t) == ' ' || (*t) == '\t') == 0; t++)
	     if( i>30)
		break;

	  *t = '\0';

	  //snarf_hosts_from_file (incfile);
	  my_function_call++;
	  //continue;
		dg++;
	}

      /* Skip internet address if present. */
      if ((buffer[i]) >= '0' && (buffer[i]) <= '9')
	for (; buffer[i] && ((buffer[i]) == '\r' || (buffer[i]) == '\n' || (buffer[i]) == ' ' || (buffer[i]) == '\t') == 0; i++)
		 if( i>70)
		break;

      /* Gobble up names.  Each name is separated with whitespace. */
      while (buffer[i])
	{
	  for (; ((buffer[i]) == '\r' || (buffer[i]) == '\n' || (buffer[i]) == ' ' || (buffer[i]) == '\t'); i++)
	     if( i>90)
		break;
	  if (buffer[i] == '\0' || buffer[i] ==  '#')
	    break;

	  /* Isolate the current word. */
	  for (start = i; buffer[i] && ((buffer[i]) == '\r' || (buffer[i]) == '\n' || (buffer[i]) == ' ' || (buffer[i]) == '\t') == 0; i++)
	     if( i>200)
		break;
	  if (i == start)
	    continue;
	  //strncpy (name, buffer + start, i - start);
	  name[i - start] = '\0';
	  //add_host_name (name);
	  my_function_call++;
	}
    }
  //fclose (file);
}


void testme(){

	char *temp;
	char buffer[256];
	int my_function_call;
	
	CAUT_INPUT(temp);
	CAUT_INPUT(buffer);
	CAUT_INPUT(my_function_call);

	snarf_hosts_from_file (temp, buffer,my_function_call);
}


/*
void main(){
	
	char *temp;
	char buffer[256];
	int my_function_call;
	
	snarf_hosts_from_file (temp, buffer,my_function_call);
}*/
