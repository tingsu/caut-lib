#include <stdio.h>
#include "caut.h"
struct child
  {
    struct child *next;		/* Link in the chain.  */

    //struct file *file;		/* File being remade.  */

    char **environment;		/* Environment for commands.  */

    char **command_lines;	/* Array of variable-expanded cmd lines.  */
    unsigned int command_line;	/* Index into above.  */
    char *command_ptr;		/* Ptr into command_lines[command_line].  */

    //pid_t pid;			/* Child process's ID number.  */
#ifdef VMS
    int efn;			/* Completion event flag number */
    int cstatus;		/* Completion status */
#endif
    char *sh_batch_file;        /* Script file for shell commands */
    //unsigned int remote:1;	/* Nonzero if executing remotely.  */

   // unsigned int noerror:1;	/* Nonzero if commands contained a `-'.  */

    //unsigned int good_stdin:1;	/* Nonzero if this child has a good stdin.  */
    //unsigned int deleted:1;	/* Nonzero if targets have been deleted.  */
  };
static void
free_child (struct child *child,struct child* children,int handling_fatal_signal,int t,int t1)
{
  /* If this child is the only one it was our "free" job, so don't put a
     token back for it.  This child has already been removed from the list,
     so if there any left this wasn't the last one.  */

  int dg=0; 

  if(child==0||children==0) return;
  if(t&&children)
    {
      char token = '+';

      /* Write a job token back to the pipe.  */

        if(t1) dg++;
    }

  if (handling_fatal_signal) /* Don't bother free'ing if about to die.  */
    return;

  if (child->command_lines != 0)
    {
  
      dg++;
    }

  if (child->environment != 0)
    {
      register char **ep = child->environment;
       *ep++;
    }

}

void testme()
{
	struct child *child;
	struct child* children;
  int handling_fatal_signal,t,t1;
  CAUT_INPUT(handling_fatal_signal);
  CAUT_INPUT(t);
  CAUT_INPUT(t1);
  CAUT_INPUT(child);
  CAUT_INPUT(children);
	free_child (child,children,handling_fatal_signal,t,t1);
  }
