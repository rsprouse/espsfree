/*
 * This material contains unpublished, proprietary software of
 * Entropic Research Laboratory, Inc. Any reproduction, distribution,
 * or publication of this work must be authorized in writing by Entropic
 * Research Laboratory, Inc., and must bear the notice:
 * 
 *    "Copyright (c) 1986-1990  Entropic Speech, Inc.
 *     Copyright (c) 1990-1996  Entropic Research Laboratory, Inc.
 *                   All rights reserved"
 * 
 * The copyright notice above does not evidence any actual or intended
 * publication of this source code.
 * 
 * Written by:  Alan Parker
 * 
 * Brief description:  License manager functions
 * 
 */

static char    *sccs_id = "@(#)license.c	1.28 28 Oct 1999 ERL";

/*
   Changed by RLS; removed check for NO_LIC compilation option, which
   governed whether to use these function stubs or full-fledged license
   checking, which is no longer necessary.
*/
void check_header() {};
void check_header2() {};
void tsm_check() {};
void tsm_free() {};
void ZZZ() {ConnectSock();};
