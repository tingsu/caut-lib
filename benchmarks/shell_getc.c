#include <stdio.h>
#include "caut.h"

typedef int Function ();
typedef union {
 // FILE *file;
  char *string;
#if defined (BUFFERED_INPUT)
  int buffered_fd;
#endif
} INPUT_STREAM;
enum stream_type {st_none, st_stdin, st_stream, st_string, st_bstream};
typedef struct {
  enum stream_type type;
  char *name;
  //INPUT_STREAM location;
  //Function *getter;
  //Function *ungetter;
} BASH_INPUT;

static int
shell_getc (int remove_quoted_newline,int eol_ungetc_lookahead,BASH_INPUT* bash_input,int remove_quoted_newline,char c1,int shell_input_line[10],
int echo_input_at_read,int t,int t2,int t3)
{
  register int i,j=0;
  int c;
  static int mustpop = 0;
  int shell_input_line_terminator;
  int line_number=0;
  int current_command_line_count=0;
  int shell_input_line_index;
  int shell_input_line_len;
  int shell_input_line_size;
	int dg=0;

 // QUIT;

  if(bash_input==0) return 0;
  if (eol_ungetc_lookahead)
    {
      c = eol_ungetc_lookahead;
      eol_ungetc_lookahead = 0;
      
      return (c);
    }

    {
      line_number++;

    restart_read:

      /* Allow immediate exit if interrupted during input. */
      //QUIT;

      i = 0;
      shell_input_line_terminator = 0;

//	print_prompt ();

      if (bash_input->type == st_stream) dg++;
      //if(t);
	//clearerr (stdin);

      while (j<5)
	{
		j++;
	  //c = yy_getc ();
	  c=c1;

	  /* Allow immediate exit if interrupted during input. */
	  //QUIT;

	  if (c == '\0')
	    {
	      continue;
	    }

	  //RESIZE_MALLOCED_BUFFER (shell_input_line, i, 2, shell_input_line_size, 256);

	  if (c == EOF)
	    {
	      if (bash_input->type == st_stream) dg++;
	      //if(t);
		//clearerr (stdin);

	      if (i == 0)
		shell_input_line_terminator = EOF;

	      shell_input_line[i] = '\0';
	      break;
	    }

	  shell_input_line[i++] = c;

	  if (c == '\n')
	    {
	      shell_input_line[--i] = '\0';
	      current_command_line_count++;
	      break;
	    }
	}

      shell_input_line_index = 0;
      shell_input_line_len = i;		/* == strlen (shell_input_line) */

      if (shell_input_line)
	{
	  /* Lines that signify the end of the shell's input should not be
	     echoed. */
	     echo_input_at_read=t2;
	     shell_input_line_terminator=t3;
	  if (echo_input_at_read && (shell_input_line[0] ||
				     shell_input_line_terminator != EOF)) dg++;
	   // fprintf (stderr, "%s\n", shell_input_line);
	}
      else
	{
	  shell_input_line_size = 0;
	  //prompt_string_pointer = &current_prompt_string;
	  //prompt_again ();
	  //goto restart_read;
	}

      /* Add the newline to the end of this string, iff the string does
	 not already end in an EOF character.  */
      if (shell_input_line_terminator != EOF)
	{
	  if (shell_input_line_len + 3 > shell_input_line_size&&t) dg++;
	    //shell_input_line = xrealloc (shell_input_line,
				//	1 + (shell_input_line_size += 2));
				

	  shell_input_line[shell_input_line_len] = '\n';
	  shell_input_line[shell_input_line_len + 1] = '\0';
	}
    }

  c = shell_input_line[shell_input_line_index];
 // c=c2;

  if (c)
    shell_input_line_index++;

  if (c == '\\' && remove_quoted_newline &&
      shell_input_line[shell_input_line_index] == '\n')
  // if(t1)
    {
	//prompt_again ();
	line_number++;
	//goto restart_read;
    }

  if (!c && shell_input_line_terminator == EOF)
    //return ((shell_input_line_index != 0) ? '\n' : EOF);
	if(shell_input_line_index != 0 )
		return '\n';
	else
		return EOF;

  return ((unsigned char)c);
}

void testme()
{
  int remove_quoted_newline,eol_ungetc_lookahead;
  BASH_INPUT* bash_input;
  char c1;
  int shell_input_line[10];
  int echo_input_at_read;
  int t,t2,t3;
	CAUT_INPUT(remove_quoted_newline);
	CAUT_INPUT(eol_ungetc_lookahead);
	CAUT_INPUT(bash_input);
	CAUT_INPUT(c1);
	CAUT_INPUT(shell_input_line);
	CAUT_INPUT(echo_input_at_read);
	CAUT_INPUT(t);
	CAUT_INPUT(t2);
	CAUT_INPUT(t3);
	
  shell_getc (remove_quoted_newline,eol_ungetc_lookahead,bash_input,remove_quoted_newline,c1,shell_input_line,echo_input_at_read,
  t,t2,t3);
}
