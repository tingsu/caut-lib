#include "caut.h"
#include <stdio.h>
#define max_line_buffer 10
enum stream_type {st_none, st_stdin, st_stream, st_string, st_bstream};
typedef struct {
  enum stream_type type;
  char *name;
  //INPUT_STREAM location;
} BASH_INPUT;

static char *read_a_line (char line_buffer[max_line_buffer] , int peekc, int remove_quoted_newline, int interactive, BASH_INPUT* bash_input, int c)
{
  static int buffer_size = 0;
  int indx = 0, peekc, pass_next;
  int dg =0 ;

  if(bash_input ==0 )
	return 0;

  if (interactive && (bash_input->type == st_stdin || bash_input->type == st_stream) )
     dg++;
    //print_prompt ();

  pass_next = 0;
  //while (1)
  //  {
      /* Allow immediate exit if interrupted during input. */
 //     QUIT;

      //c = yy_getc ();

      /* Ignore null bytes in input. */
      if (c == 0)
	{
	  //continue;
	  dg++;
	}

      /* If there is no more input, then we return NULL. */
      if (c == EOF)
	{
	  if (interactive && bash_input->type == st_stream)
	    //clearerr (stdin);
		dg++;
	  if (indx == 0)
	    return ((char *)NULL);
	  c = '\n';
	}

      /* `+2' in case the final character in the buffer is a newline. */
     // RESIZE_MALLOCED_BUFFER (line_buffer, indx, 2, buffer_size, 128);

      /* IF REMOVE_QUOTED_NEWLINES is non-zero, we are reading a
	 here document with an unquoted delimiter.  In this case,
	 the line will be expanded as if it were in double quotes.
	 We allow a backslash to escape the next character, but we
	 need to treat the backslash specially only if a backslash
	 quoting a backslash-newline pair appears in the line. */
      if (pass_next)
	{
	  line_buffer[indx++] = c;
	  pass_next = 0;
	}
      else if (c == '\\' && remove_quoted_newline)
	{
	  //peekc = yy_getc ();
	  if (peekc == '\n')
	    {
	      //line_number++;
		dg++;
	      //continue;	/* Make the unquoted \<newline> pair disappear. */
	    }
	  else
	    {
	      //yy_ungetc (peekc);
	      pass_next = 1;
	      line_buffer[indx++] = c;		/* Preserve the backslash. */
	    }
	}
      else
	line_buffer[indx++] = c;

      if (c == '\n')
	{
	  line_buffer[indx] = '\0';
	  return (line_buffer);
	}
    //}
}

void testme(){

	char line_buffer[max_line_buffer];
	int peekc;
	int remove_quoted_newline;
	int interactive;
	BASH_INPUT* bash_input;
	int c;

	CAUT_INPUT(line_buffer);
	CAUT_INPUT(peekc);
	CAUT_INPUT(remove_quoted_newline);
	CAUT_INPUT(interactive);
	CAUT_INPUT(bash_input);
	CAUT_INPUT(c);

	
	read_a_line (line_buffer , peekc, remove_quoted_newline,interactive,  bash_input, c);
}



