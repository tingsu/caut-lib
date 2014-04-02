#include <stdio.h>
#include "caut.h"

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

enum command_type { cm_for, cm_case, cm_while, cm_if, cm_simple, cm_select,
		    cm_connection, cm_function_def, cm_until, cm_group,
		    cm_arith, cm_cond, cm_arith_for, cm_subshell };
		    
typedef struct command {
  enum command_type type;	/* FOR CASE WHILE IF CONNECTION or SIMPLE. */
  int flags;			/* Flags controlling execution environment. */
  int line;			/* line number the command starts on */
 // REDIRECT *redirects;		/* Special redirects for FOR CASE, etc. */
  /*union {
    struct for_com *For;
    struct case_com *Case;
    struct while_com *While;
    struct if_com *If;
    struct connection *Connection;
    struct simple_com *Simple;
    struct function_def *Function_def;
    struct group_com *Group;
#if defined (SELECT_COMMAND)
    struct select_com *Select;
#endif
#if defined (DPAREN_ARITHMETIC)
    struct arith_com *Arith;
#endif
#if defined (COND_COMMAND)
    struct cond_com *Cond;
#endif
#if defined (ARITH_FOR_COMMAND)
    struct arith_for_com *ArithFor;
#endif
    struct subshell_com *Subshell;
  } value;*/
} COMMAND;

typedef struct variable {
  char *name;			/* Symbol that the user types. */
  char *value;			/* Value that is returned. */
  char *exportstr;		/* String for the environment. */
 // DYNAMIC_FUNC *dynamic_value;	/* int called to return a `dynamic'
//				   value for a variable, like $SECONDS
//				   or $RANDOM. */
 // DYNAMIC_FUNC *assign_func; 	/* int called when this `special
	//			   variable' is assigned a value in
	//			   bind_variable. */
  int attributes;		/* export, readonly, array, invisible... */
  int context;			/* Which context this variable belongs to. */
  struct variable *prev_context; /* Value from previous context or NULL. */
} SHELL_VAR;

static int
execute_function (SHELL_VAR* var, int flags,int subshell,int posixly_correct,COMMAND* c1,char* c2,int temporary_env,int t1,int t2,int t3)
{
  int return_val, result;
  COMMAND *tc, *fc;
  char *debug_trap;
  SHELL_VAR *this_shell_function;
  int line_number,function_line_number;
  int variable_context=0;
  int return_catch_flag=0;
  int return_catch_value=0;
	int dg=0;

  //tc = (COMMAND *)copy_command (function_cell (var));
  tc=c1;
  
  if(tc==0) return 0;
  	
  if (tc && (flags & CMD_IGNORE_RETURN))
    tc->flags |= CMD_IGNORE_RETURN;

  if (subshell == 0)
    {
      //begin_unwind_frame ("function_calling");
     // push_context ();
      //add_unwind_protect (pop_context, (char *)NULL);
      //unwind_protect_int (line_number);
      //unwind_protect_int (return_catch_flag);
      //unwind_protect_jmp_buf (return_catch);
     // add_unwind_protect (dispose_command, (char *)tc);
   //   unwind_protect_pointer (this_shell_function);
    //  unwind_protect_int (loop_level);
    dg++;
    }

  this_shell_function = var;
 // make_funcname_visible (1);

  //debug_trap = (signal_is_trapped (DEBUG_TRAP) && signal_is_ignored (DEBUG_TRAP) == 0)
	//		? trap_list[DEBUG_TRAP]
	//		: (char *)NULL;
	debug_trap=c2;
  if (debug_trap)
    {
      if (subshell == 0)
	{
		dg++;
	 // debug_trap = savestring (debug_trap);
	 // add_unwind_protect (xfree, debug_trap);
	 // add_unwind_protect (set_debug_trap, debug_trap);
	}
   //   restore_default_signal (DEBUG_TRAP);
    }

  if (temporary_env)
    {
     // function_env = copy_array (temporary_env);

      if (subshell == 0)
	{
	  if (posixly_correct)
	  	dg++;
	    //add_unwind_protect (merge_function_env, (char *)NULL);
	  else
	  	dg++;
	   // add_unwind_protect (dispose_function_env, (char *)NULL);
	}
      //dispose_used_env_vars ();
    }
    /* Otherwise, we inherit function_env from our caller. */

 // remember_args (words->next, 1);

  /* Number of the line on which the function body starts. */
  line_number = function_line_number = tc->line;

  if (subshell)
    {
      //fc = (tc->type == cm_group) ? tc->value.Group->command : tc;
      fc=t1;

      if(fc==0) return 0;
      	
      if (fc && (flags & CMD_IGNORE_RETURN))
	fc->flags |= CMD_IGNORE_RETURN;

      variable_context++;
    }
  else
    fc = tc;

  return_catch_flag++;
  //return_val = setjmp (return_catch);
  return_val=t2;

  if (return_val)
    result = return_catch_value;
  else
   // result = execute_command_internal (fc, 0, NO_PIPE, NO_PIPE, fds_to_close);
   result=t3;
   

  if (subshell == 0)
  	dg++;
    //run_unwind_frame ("function_calling");

  if (variable_context == 0 || this_shell_function == 0)
  	dg++;
   // make_funcname_visible (0);

  return (result);
}

void testme()
{
  SHELL_VAR* var;
  int flags,subshell,posixly_correct;
  COMMAND* c1;
  char* c2;
  int temporary_env,t1,t2,t3;
  CAUT_INPUT(var);
  CAUT_INPUT(flags);
  CAUT_INPUT(subshell);
  CAUT_INPUT(posixly_correct);
  CAUT_INPUT(c1);
  CAUT_INPUT(c2);
  CAUT_INPUT(temporary_env);
  CAUT_INPUT(t1);
  CAUT_INPUT(t2);
  CAUT_INPUT(t3);
  
  execute_function (var,flags,subshell,posixly_correct,c1,c2,temporary_env,t1,t2,t3);
}
