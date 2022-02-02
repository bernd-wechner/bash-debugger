/*
Copyright (C) 2011, 2020 R. Bernstein <rocky@gnu.org>
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

/** \file libdebugger/command/delete.c
 *
 *  \brief Debugger `delete` command
 *
 *  Delete some breakpoints. Arguments are breakpoint numbers with spaces
 *  in between. To delete all breakpoints, give no arguments.
 */

#include "../../src/trace.h"
#include "../break.h"
#include "../fns.h"
#include "../msg.h"

extern debug_return_t
dbg_cmd_delete(char *psz_args)
{
  int i_brkpt;
  char *psz_word;

  if (!psz_args || !*psz_args) {
    unsigned int breakpoints_removed = 0;
    for (unsigned int i=1; i<=i_breakpoints; i++) {
      if (remove_breakpoint(i, true)) breakpoints_removed++;
    }
    dbg_msg(_("%u breakpoint(s) removed."), breakpoints_removed);

    return debug_readloop;
  }

  psz_word = get_word(&psz_args);
  while ( psz_word && *psz_word ) {
    if (get_int(psz_word, &i_brkpt, true)) {
      remove_breakpoint(i_brkpt, false);
    }
    psz_word = get_word(&psz_args);
  }

  return debug_readloop;
}

/*
 * Local variables:
 * eval: (c-set-style "gnu")
 * indent-tabs-mode: nil
 * End:
 */
