/** Move reported target frame position to absolute position psz_frame. */
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

#include "../../src/trace.h"
#include "../fns.h"
#include "../stack.h"

debug_return_t
dbg_cmd_frame(char *psz_frame)
{
  int i_frame;

  if (!psz_frame || !*psz_frame) {
    return debug_readloop;
  } else {
    if (!get_int(psz_frame, &i_frame, true))
      return debug_readloop;
  }
  return dbg_adjust_frame(i_frame, true);
}


/*
 * Local variables:
 * eval: (c-set-style "gnu")
 * indent-tabs-mode: nil
 * End:
 */
