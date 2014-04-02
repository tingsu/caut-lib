#include <stdio.h>
#include "caut.h"

#define	COMMANDS_RECURSE	1 /* Recurses: + or $(MAKE).  */
#define	COMMANDS_SILENT		2 /* Silent: @.  */
#define	COMMANDS_NOERROR	4 /* No errors: -.  */
 struct dep
  {
    struct dep *next;
    char *name;
    struct file *file;
    int changed;
  };
  struct commands
  {
    //struct floc fileinfo;	/* Where commands were defined.  */
    char *commands;		/* Commands text.  */
    unsigned int ncommand_lines;/* Number of command lines.  */
    char **command_lines;	/* Commands chopped up into lines.  */
    char lines_flags[10];		/* One set of flag bits for each line.  */
    int any_recurse;		/* Nonzero if any `lines_recurse' elt has */
				/* the COMMANDS_RECURSE bit set.  */
  };
 struct file
  {
    struct file *next;
    char *name;
    char *hname;                /* Hashed filename */
    char *vpath;                /* VPATH/vpath pathname */
    struct dep *deps;
    struct commands *cmds;	/* Commands to execute for this target.  */
    int command_flags;		/* Flags OR'd in for cmds; see commands.h.  */
    char *stem;			/* Implicit stem, if an implicit
    				   rule has been used */
    struct dep *also_make;	/* Targets that are made by making this.  */
   // FILE_TIMESTAMP last_mtime;	/* File's modtime, if already known.  */
  //  FILE_TIMESTAMP mtime_before_update;	/* File's modtime before any updating
   //                                        has been performed.  */
    struct file *prev;		/* Previous entry for same file name;
				   used when there are multiple double-colon
				   entries for the same file.  */

    /* File that this file was renamed to.  After any time that a
       file could be renamed, call `check_renamed' (below).  */
    struct file *renamed;

    /* List of variable sets used for this file.  */
    //struct variable_set_list *variables;

    /* Pattern-specific variable reference for this target, or null if there
       isn't one.  Also see the pat_searched flag, below.  */
   // struct variable_set_list *pat_variables;

    /* Immediate dependent that caused this target to be remade,
       or nil if there isn't one.  */
    struct file *parent;

    /* For a double-colon entry, this is the first double-colon entry for
       the same file.  Otherwise this is null.  */
    struct file *double_colon;

    short int update_status;	/* Status of the last attempt to update,
				   or -1 if none has been made.  */

    enum			/* State of the commands.  */
      {		/* Note: It is important that cs_not_started be zero.  */
	cs_not_started,		/* Not yet started.  */
	cs_deps_running,	/* Dep commands running.  */
	cs_running,		/* Commands running.  */
	cs_finished		/* Commands finished.  */
      } command_state; //ENUM_BITFIELD (2);

    unsigned int precious;	/* Non-0 means don't delete file on quit */
    unsigned int tried_implicit; /* Nonzero if have searched
				      for implicit rule for making
				      this file; don't search again.  */
    unsigned int updating;	/* Nonzero while updating deps of this file */
    unsigned int updated;	/* Nonzero if this file has been remade.  */
    unsigned int is_target;	/* Nonzero if file is described as target.  */
    unsigned int cmd_target;	/* Nonzero if file was given on cmd line.  */
    unsigned int phony;	/* Nonzero if this is a phony file
				   i.e., a dependency of .PHONY.  */
    unsigned int intermediate;/* Nonzero if this is an intermediate file.  */
    /* Nonzero, for an intermediate file,
       means remove_intermediates should not delete it.  */
    unsigned int secondary;
    unsigned int dontcare;	/* Nonzero if no complaint is to be made if
				   this target cannot be remade.  */
    unsigned int ignore_vpath;/* Nonzero if we threw out VPATH name.  */
    unsigned int pat_searched;/* Nonzero if we already searched for
                                   pattern-specific variables.  */
    unsigned int considered;  /* equal to `considered' if file has been
                                   considered on current scan of goal chain */
  };
  
void
notice_finished_file (struct file *file,int touch_flag,int ran,int question_flag,int just_print_flag,int t)
{
  struct dep *d = 0 ;
  int dg=0;

  if(file==0) return ;
  if(file->next == 0) return ;
  if(file->cmds ==0 ) return ;
  if(file->double_colon == 0) return;
  if(file->also_make == 0) return ;
  	
  int ran = file->command_state == cs_running;

  file->command_state = cs_finished;
  file->updated = 1;

  if (touch_flag&& file->update_status == 0)
    {
      if (file->cmds != 0 && file->cmds->any_recurse)
	{
	  unsigned int i;
	  for (i = 0; i < file->cmds->ncommand_lines; ++i)
	  {
	    if(i>=10) return;
	    if (!(file->cmds->lines_flags[i] & COMMANDS_RECURSE))
	      goto have_nonrecursing;
	    }
	}
      else
	{
	have_nonrecursing:
	  if (file->phony)
	    file->update_status = 0;
	  else
	    //file->update_status = touch_file (file);
	    dg++;
	}
    }

  //if (file->mtime_before_update == 0)
  if(t)
  	dg++;
    //file->mtime_before_update = file->last_mtime;

  if (ran && !file->phony)
    {
      struct file *f = 0;
      int i = 0;

      if (question_flag || just_print_flag)
        {
          for (i = file->cmds->ncommand_lines; i > 0; --i)
          {
          	if(i>=10) return;
            if (! (file->cmds->lines_flags[i-1] & COMMANDS_RECURSE)) dg++;
              break;
            }
        }

      else if (file->is_target && file->cmds == 0)
	i = 1;
	
      //file->last_mtime = i == 0 ? 0 : NEW_MTIME;
      	
      for (f = file->double_colon; f != 0; f = f->next)
      dg++;
	//f->last_mtime = file->last_mtime;
    }
  if (ran && file->update_status != -1)
    for (d = file->also_make; d != 0; d = d->next)
      {
      	if(d->file==0) return;
	d->file->command_state = cs_finished;
	d->file->updated = 1;
	d->file->update_status = file->update_status;

	if (ran && !d->file->phony)
		dg++;
	//  (void) f_mtime (d->file, 0);
      }
  else if (file->update_status == -1)
    file->update_status = 0;
}

void testme()
{
  struct file *file;
  int touch_flag,ran,question_flag,just_print_flag,t;
  
  CAUT_INPUT(file);
  CAUT_INPUT(touch_flag);
  CAUT_INPUT(ran);
  CAUT_INPUT(question_flag);
  CAUT_INPUT(just_print_flag);
  CAUT_INPUT(t);
    
  notice_finished_file (file,touch_flag,ran,question_flag,just_print_flag,t);
}
