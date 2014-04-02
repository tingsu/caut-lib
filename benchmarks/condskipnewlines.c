#include <stdio.h>
#include "caut.h"


enum stream_type {st_none, st_stdin, st_stream, st_string, st_bstream};
typedef union {
 // FILE *file;
  char *string;
#if defined (BUFFERED_INPUT)
  int buffered_fd;
#endif
} INPUT_STREAM;

typedef struct {
  enum stream_type type;
  char *name;
  //INPUT_STREAM location;
 // Function *getter;
  //Function *ungetter;
} BASH_INPUT;
static int
cond_skip_newlines (int t,int interactive,BASH_INPUT* bash_input)
{
  int dg=0;
  //while ((cond_token = read_token (READ)) == '\n')
  if(bash_input==0) return 0;
  while(t>0)
    {
    	t--;
      if (interactive && (bash_input->type == st_stdin || bash_input->type == st_stream))
      	dg++;
	//prompt_again ();
    }
  //return (cond_token);
  return 0;
}

void testme()
{
  int t;
  int interactive;
  BASH_INPUT* bash_input;
	CAUT_INPUT(t);
	CAUT_INPUT(interactive);
	CAUT_INPUT(bash_input);

  cond_skip_newlines (t,interactive,bash_input);
}
