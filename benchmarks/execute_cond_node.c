#include <stdio.h>
#include "caut.h"

typedef struct word_desc {
  char word[3];		/* Zero terminated string. */
  int flags;		/* Flags associated with this word. */
} WORD_DESC;

/* A linked list of words. */
typedef struct word_list {
  struct word_list *next;
  WORD_DESC *word;
} WORD_LIST;

#define COND_AND	1
#define COND_OR		2
#define COND_UNARY	3
#define COND_BINARY	4
#define COND_TERM	5
#define COND_EXPR	6

#define CMD_WANT_SUBSHELL  0x01	/* User wants a subshell: ( command ) */
#define CMD_FORCE_SUBSHELL 0x02	/* Shell needs to force a subshell. */
#define CMD_INVERT_RETURN  0x04	/* Invert the exit value. */
#define CMD_IGNORE_RETURN  0x08	/* Ignore the exit value.  For set -e. */
#define CMD_NO_FUNCTIONS   0x10 /* Ignore functions during command lookup. */
#define CMD_INHIBIT_EXPANSION 0x20 /* Do not expand the command words. */
#define CMD_NO_FORK	   0x40	/* Don't fork; just call execve */
#define CMD_TIME_PIPELINE  0x80 /* Time a pipeline */
#define CMD_TIME_POSIX	   0x100 /* time -p; use POSIX.2 time output spec. */
#define CMD_AMPERSAND	   0x200 /* command & */
#define CMD_STDIN_REDIR	   0x400 /* async command needs implicit </dev/null */

#define EXECUTION_FAILURE 1
#define EXECUTION_SUCCESS 0

typedef struct cond_com {
  int flags;
  int line;
  int type;
  WORD_DESC *op;
  struct cond_com *left, *right;
} COND_COM;

static int
execute_cond_node (COND_COM* cond,int echo_command_at_execute,int t,int t1,int t2,int t3,int t4,int t5,int t6,int t7,int t8,int t9,int t10)
{
  int result, invert, patmatch, flags;
  char *arg1, *arg2, *print2;
  int nullstr=0;
	int dg=0;

  if(cond==0) return 0;
  invert = (cond->flags & CMD_INVERT_RETURN);

  if (cond->type == COND_EXPR)
  	result=t3;
    //result = execute_cond_node (cond->left);
  else if (cond->type == COND_OR)
    {
     // result = execute_cond_node (cond->left);
     result=t4;
      if (result != EXECUTION_SUCCESS)
      	result=t5;
	//result = execute_cond_node (cond->right);
    }
  else if (cond->type == COND_AND)
    {
     // result = execute_cond_node (cond->left);
     result=t6;
      if (result == EXECUTION_SUCCESS)
      	result=t7;
	//result = execute_cond_node (cond->right);
    }
  else if (cond->type == COND_UNARY)
    {
      //arg1 = cond_expand_word (cond->left->op, 0);
      arg1=t;
      if (arg1 == 0)
	arg1 = nullstr;
      if (echo_command_at_execute)
	//xtrace_print_cond_term (cond->type, invert, cond->op, arg1, (char *)NULL);
    //  result = unary_test (cond->op->word, arg1) ? EXECUTION_SUCCESS : EXECUTION_FAILURE;
    result=t10;
      if (arg1 != nullstr) 
      	//free (arg1);
	dg++;
    }
  else if (cond->type == COND_BINARY)
    {
    	if(cond->op==0) return 0;
      /*patmatch = ((cond->op->word[1] == '=') && (cond->op->word[2] == '\0') &&
		  (cond->op->word[0] == '!' || cond->op->word[0] == '=') ||
		  (cond->op->word[0] == '=' && cond->op->word[1] == '\0'));*/

     // arg1 = cond_expand_word (cond->left->op, 0);
     arg1=t9;
      if (arg1 == 0)
	arg1 = nullstr;
     // arg2 = cond_expand_word (cond->right->op, patmatch);
     arg2=t2;
      if (arg2 == 0)
	arg2 = nullstr;

      if (echo_command_at_execute)
      	dg++;
	//xtrace_print_cond_term (cond->type, invert, cond->op, arg1, arg2);

      //result = binary_test (cond->op->word, arg1, arg2, TEST_PATMATCH|TEST_ARITHEXP)
			//	? EXECUTION_SUCCESS
			//	: EXECUTION_FAILURE;
			result=t8;
      if (arg1 != nullstr)
      	//free (arg1);
	dg++;
      if (arg2 != nullstr)
      	//free (arg2);
	dg++;
    }
  else
    {
      //command_error ("execute_cond_node", CMDERR_BADTYPE, cond->type, 0);
      //jump_to_top_level (DISCARD);
      result = EXECUTION_FAILURE;
    }

  if (invert)
    //result = (result == EXECUTION_SUCCESS) ? EXECUTION_FAILURE : EXECUTION_SUCCESS;
	if( result == EXECUTION_SUCCESS )
		result = EXECUTION_FAILURE ;
	else
		result = EXECUTION_SUCCESS ;

  return result;
}

void testme()
{
  COND_COM* cond;
  int echo_command_at_execute,t,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10;
  CAUT_INPUT(cond);
  CAUT_INPUT(echo_command_at_execute);
  CAUT_INPUT(t);
  CAUT_INPUT(t1);
  CAUT_INPUT(t2);
  CAUT_INPUT(t3);
  CAUT_INPUT(t4);
  CAUT_INPUT(t5);
  CAUT_INPUT(t6);
  CAUT_INPUT(t7);
  CAUT_INPUT(t8);
  CAUT_INPUT(t9);
  CAUT_INPUT(t10);
  
  execute_cond_node (cond,echo_command_at_execute,t,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10);
}
