#include "caut.h"
#define MAXLEN 15

static int
parse_shell_options (char argv[MAXLEN], int arg_start,int arg_end, int want_pending_command, int make_login_shell, int read_from_stdin,int dump_translatable_strings,char arg_string[MAXLEN])
{
  int arg_index;
  int arg_character, on_or_off, next_arg, i;
  char o_option;
  int my_function_call = 0;

  if( arg_start<0 || arg_start>=MAXLEN) /*add by me*/
	return 0;
  if( arg_end<0 || arg_end>=MAXLEN)
	return 0;
  if( arg_start > arg_end)
	return 0;

  arg_index = arg_start;
  while (arg_index != arg_end && (arg_string[0] == '-' || arg_string[0] == '+'))
    {
	
      arg_string[arg_index] = argv[arg_index] ;
      if( arg_string[arg_index] == 0)
	   return 0;
      
      /* There are flag arguments, so parse them. */
      next_arg = arg_index + 1;

      /* A single `-' signals the end of options.  From the 4.3 BSD sh.
	 An option `--' means the same thing; this is the standard
	 getopt(3) meaning. */
      if (arg_string[0] == '-' &&
	   (arg_string[1] == '\0' ||
	     (arg_string[1] == '-' && arg_string[2] == '\0')))
	return (next_arg);

      i = 1;
      on_or_off = arg_string[0];
      while ( i<MAXLEN /*add by me */)
	{
	  arg_character = arg_string[i++];
	  if( arg_character == 0)
		return 0;
	  switch (arg_character)
	    {
	    case 'c':
	      want_pending_command = 1;
	      break;

	    case 'l':
	      make_login_shell = 1;
	      break;

	    case 's':
	      read_from_stdin = 1;
	      break;

	    case 'o':
	      o_option = argv[next_arg];
	      if (o_option == 0)
		{
		  //list_minus_o_opts (-1, (on_or_off == '-') ? 0 : 1);
		  my_function_call++;
		  break;
		}
	      if (my_function_call > 0 )//set_minus_o_option (on_or_off, o_option) != EXECUTION_SUCCESS)
		//exit (EX_BADUSAGE);
		my_function_call++;
	      next_arg++;
	      break;

	    case 'O':
	      /* Since some of these can be overridden by the normal
		 interactive/non-interactive shell initialization or
		 initializing posix mode, we save the options and process
		 them after initialization. */
	      o_option = argv[next_arg];
	      if (o_option == 0)
		{
		  //shopt_listopt (o_option, (on_or_off == '-') ? 0 : 1);
		  my_function_call++;
		  break;
		}
	      //add_shopt_to_alist (o_option, on_or_off);
	      my_function_call++;
	      next_arg++;
	      break;

	    case 'D':
	      dump_translatable_strings = 1;
	      break;

	    default:
	      if (my_function_call > 0)//change_flag (arg_character, on_or_off) == FLAG_ERROR)
		{
		  //report_error (_("%c%c: invalid option"), on_or_off, arg_character);
		  //show_shell_usage (stderr, 0);
		  //exit (EX_BADUSAGE);
		  my_function_call++;
		}
	    }
	}
      /* Can't do just a simple increment anymore -- what about
	 "bash -abouo emacs ignoreeof -hP"? */
      arg_index = next_arg;
    }

  return (arg_index);
}

void testme(){

	char argv[MAXLEN];
	int arg_start;
	int arg_end;
	int want_pending_command;
	int make_login_shell;
	int read_from_stdin;
	int dump_translatable_strings;
	char arg_string[MAXLEN];

	CAUT_INPUT(argv);
	CAUT_INPUT(arg_start);
	CAUT_INPUT(arg_end);
	CAUT_INPUT(want_pending_command);
	CAUT_INPUT(make_login_shell);
	CAUT_INPUT(read_from_stdin);
	CAUT_INPUT(dump_translatable_strings);
	CAUT_INPUT(arg_string);

	parse_shell_options (argv, arg_start, arg_end,  want_pending_command, make_login_shell,read_from_stdin, dump_translatable_strings, arg_string);

}

/*
int main(){

	char argv[MAXLEN]={'+'};
	int arg_start=0;
	int arg_end=8;
	int want_pending_command;
	int make_login_shell;
	int read_from_stdin;
	int dump_translatable_strings;
	char arg_string[MAXLEN];

	parse_shell_options (argv, arg_start, arg_end,  want_pending_command, make_login_shell,read_from_stdin, dump_translatable_strings, arg_string);
}
*/
