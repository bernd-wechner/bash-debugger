/*
Copyright (C) 2004-2005, 2007-2009, 2011, 2020 R. Bernstein
<rocky@gnu.org>
This file is part of GNU Make (remake variant).

GNU Make is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU Make is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Make; see the file COPYING.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

/**
 *  \brief Debugger `show` command.
 *
 *   Show debugger settings.
 **/

#include "../../src/trace.h"
#include "../../src/debug.h"
#include "../../src/main.h"
#include "../../src/print.h"

#include "../cmd.h"
#include "../fns.h"
#include "../info.h"
#include "../msg.h"
#include "../subcmd.h"

subcommand_var_info_t show_subcommands[] = {
  { "args",
    "Show the command-line invocation",
    NULL,
    NULL,
    false, 1},
  { "basename",
    "Show if we are to show short or long filenames",
    NULL,
    &basename_filenames, true, 1},
  { "commands", "Show the history of commands you typed.",
    NULL,
    NULL,
    false, 1},
  { "debug",
    "Show the value of the GNU Make debug mask (set via `--debug` or `-d`)",
    NULL,
    &db_level, false, 1},
  { "ignore-errors",
    "Show the value of the GNU Make `--ignore-errors` (or `-i`) flag",
    NULL,
    &ignore_errors_flag, true, 1},
  { "keep-going",
    "Show the value of the GNU Make `--keep-going` (or `-k`) flag",
    NULL,
    &keep_going_flag,
    true, 1},
  { "silent",
    "Show the value of the GNU Make `--silent` (or `-s`) flag",
    NULL,
    &silent_flag,
    true, 1},
#ifdef FIXED
  { "trace",
    "Value of GNU Make `--trace` (or `-t`) flag",
    NULL,
    &no_shell_trace,
    true, 1},
#endif
  { "version",
    "Show the remake version.\n"
    "\n"
    "The first number part of the version is the GNU Make base version.\n"
    "After that comes a remake-specific value which indicates its release iteration."
    ,
    NULL,
    NULL,
    false, 1},
  { "warranty",      "Various kinds of warranty you do not have.",
    NULL,
    NULL,
    false, 1},
  { NULL, NULL, NULL, NULL,
    false, 0}
};

extern debug_return_t
dbg_cmd_show(char *psz_arg)
{
  if (!psz_arg || 0==strlen(psz_arg)) {
    unsigned int i;
    for (i=0; show_subcommands[i].name; i++) {
      if ( 0 == strcmp(show_subcommands[i].name, "warranty") ||
	   0 == strcmp(show_subcommands[i].name, "history"))
	continue;
      dbg_help_subcmd_entry("show", "%-10s -- %s",
                            &(show_subcommands[i]), false);
    }
  } else {
    if (is_abbrev_of (psz_arg, "args", 3)) {
      print_cmdline();
    } else if (is_abbrev_of (psz_arg, "basename", 4)) {
      printf("basename is %s.\n", var_to_on_off(basename_filenames));
    } else if (is_abbrev_of (psz_arg, "debug", 3)) {
      printf("debug is 0x%x.\n", (unsigned int) db_level);
      print_db_level(db_level);
    } else if (is_abbrev_of (psz_arg, "commands", 3)) {
      dbg_cmd_show_command(psz_arg);
    } else if (is_abbrev_of (psz_arg, "ignore-errors", 3)) {
      printf("ignore-errors is %s.\n", var_to_on_off(ignore_errors_flag));
    } else if (is_abbrev_of (psz_arg, "keep-going", 4)) {
      printf("keep-going is %s.\n", var_to_on_off(keep_going_flag));
    } else if (is_abbrev_of (psz_arg, "silent", 3)) {
      printf("silent is %s.\n", var_to_on_off(silent_flag));
    } else if (is_abbrev_of (psz_arg, "version", 3)) {
      printf("version: %s\n", version_string);
    } else if (is_abbrev_of (psz_arg, "warranty", 3)) {
      printf("warranty: ");
      printf("%s", WARRANTY);
    } else {
      printf("Undefined command \"%s\". Try \"help show\"\n", psz_arg);
    }
  }

  return debug_readloop;
}


/*
 * Local variables:
 * eval: (c-set-style "gnu")
 * indent-tabs-mode: nil
 * End:
 */
