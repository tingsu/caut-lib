#include "caut.h"
#include<stdio.h>
#define whitespace(c) (((c) == ' ') || ((c) == '\t'))
#define ISLETTER(c)  ( ((c)>='A'&&(c)<='Z') || ((c)>='a'&&(c)<='z') )
#define quote_char(c)  (((c) == '\'') || ((c) == '"'))
#define command_separator(character) ( (character)=='\r' || (character)=='\n' || (character)=='(' )
#define max_num 15
static int skipws (char string[max_num], int start, int command_word, int pass_next,int backslash_quoted_word )
{
  register int i;
  unsigned char peekc;
  int dg =0;

  /* skip quoted strings, in ' or ", and words in which a character is quoted
     with a `\'. */
  //i = backslash_quoted_word = pass_next = 0;
  i=0;

  /* Skip leading whitespace (or separator characters), and quoted words.
     But save it in the output.  */
  if(start>=max_num|| start<0)
	  return 0;
  
  for (i = start; string[i] && i<max_num; i++)
    {
      if (pass_next)
	{
	  pass_next = 0;
	  continue;
	}

      if (whitespace (string[i]))
	{
	  backslash_quoted_word = 0; /* we are no longer in a backslash-quoted word */
	  continue;
	}

      if (string[i] == '\\')
	{
	  peekc = string[i+1];
	  if (ISLETTER (peekc))
	    backslash_quoted_word++;	/* this is a backslash-quoted word */
	  else
	    pass_next++;
	  continue;
	}

      /* This only handles single pairs of non-escaped quotes.  This
	 overloads backslash_quoted_word to also mean that a word like
	 ""f is being scanned, so that the quotes will inhibit any expansion
	 of the word. */
      if (quote_char(string[i]))
	{
	  i = 0; //skipquotes (string, i);
	  /* This could be a line that contains a single quote character,
	     in which case skipquotes () terminates with string[i] == '\0'
	     (the end of the string).  Check for that here. */
	  if (string[i] == '\0')
	    break;

	  peekc = string[i + 1];
	  if (ISLETTER (peekc))
	    backslash_quoted_word++;
	  continue;
	}

      /* If we're in the middle of some kind of quoted word, let it
	 pass through. */
      if (backslash_quoted_word)
	continue;
	dg++;

      /* If this character is a shell command separator, then set a hint for
	 alias_expand that the next token is the first word in a command. */

      if (command_separator (string[i]))
	{
	  command_word++;
	  continue;
	}
      break;
    }
  return (i);
}

void testme(){
	
	char string[max_num];
	int start;
	int command_word;
	int pass_next;
	int backslash_quoted_word;
	
	CAUT_INPUT(string);
	CAUT_INPUT(start);
	CAUT_INPUT(command_word);
	CAUT_INPUT(pass_next);
	CAUT_INPUT(backslash_quoted_word);

	skipws (string, start, command_word, pass_next, backslash_quoted_word);
}
