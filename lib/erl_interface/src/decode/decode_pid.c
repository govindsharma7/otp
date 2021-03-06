/*
 * %CopyrightBegin%
 * 
 * Copyright Ericsson AB 1998-2013. All Rights Reserved.
 * 
 * The contents of this file are subject to the Erlang Public License,
 * Version 1.1, (the "License"); you may not use this file except in
 * compliance with the License. You should have received a copy of the
 * Erlang Public License along with this software. If not, it can be
 * retrieved online at http://www.erlang.org/.
 * 
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License for the specific language governing rights and limitations
 * under the License.
 * 
 * %CopyrightEnd%
 */
#include <string.h>
#include "eidef.h"
#include "eiext.h"
#include "putget.h"


int ei_decode_pid(const char *buf, int *index, erlang_pid *p)
{
  const char *s = buf + *index;
  const char *s0 = s;
  
  if (get8(s) != ERL_PID_EXT) return -1;

  if (p) {
    if (get_atom(&s, p->node, NULL) < 0) return -1;
    p->num = get32be(s) & 0x7fff; /* 15 bits */
    p->serial = get32be(s) & 0x1fff; /* 13 bits */
    p->creation = get8(s) & 0x03; /* 2 bits */
  }
  else {
      if (get_atom(&s, NULL, NULL) < 0) return -1;
      s+= 9;
  }
  
  *index += s-s0;
  
  return 0;
}
