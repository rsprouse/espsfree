# This material contains unpublished, proprietary software of 
# Entropic Research Laboratory, Inc. Any reproduction, distribution, 
# or publication of this work must be authorized in writing by Entropic 
# Research Laboratory, Inc., and must bear the notice: 
#
#    "Copyright (c) 1990-1993  Entropic Research Laboratory, Inc. 
#                   All rights reserved"
#
# The copyright notice above does not evidence any actual or intended 
# publication of this source code.     
#
# @(#)Makefile	1.4 1/29/97 ERL
# 
# Makefile for: 
#
# Written by:  Derek Lin
# Checked by:
# Revised by:
 	
#!#CFLAGS = -g  -I$(ESPS_BASE)/include/waves -DFOR_XVIEW -I$(XVIEW_INC) $(PROGCFLAGS) -DEPOCHS
CFLAGS = -g $(PROGCFLAGS) -DEPOCHS
#!#SIGPROC = $(ESPS_BASE)/lib/waves/libdsigproc.a
SIGPROC = $(LIBDIR)/libdsigproc.a
#!#LIBSIG = $(ESPS_BASE)/lib/waves/xlibsig.a $(SPSLIB) $(BSDLIB)
LIBSIG = $(LIBDIR)/xlibsig.a $(SPSLIB) $(BSDLIB)

OBJS = epochs.o stubs.o get_labels.o
OBJ1 = labelio.o
OBJ2 = labelprocs.o
#!#WAVESRC1 = /home/projects/devel_source/waves.esi/waves/src/c/labelio.c
#!#WAVESRC2 = /home/projects/devel_source/waves.esi/waves/src/c/labelprocs.c
SRC1 = labelio.c
SRC2 = labelprocs.c
SRCS = epochs.c stubs.c get_labels.c labelio.c labelprocs.c
PROGNAME = epochs
MANNAME = epochs.1
DEFPARAM = Pepochs

$(PROGNAME): $(SPSLIB) $(OBJS)
	cc -c $(SRC1) $(CFLAGS) $(LIBSIG) $(SIGPROC) -lm
	cc -c $(SRC2) $(CFLAGS) $(LIBSIG) $(SIGPROC) -lm
	cc  $(CFLAGS) $(OBJS) $(OBJ1) $(OBJ2) $(SPSLIB) $(LIBSIG) $(SIGPROC) -lm -o $(PROGNAME)

pure: $(SPSLIB) $(OBJS)
	cc -c $(SRC1) $(CFLAGS) $(LIBSIG) $(SIGPROC) -lm
	cc -c $(SRC2) $(CFLAGS) $(LIBSIG) $(SIGPROC) -lm
	purify cc  $(CFLAGS) $(OBJS) $(OBJ1) $(OBJ2) $(SPSLIB) $(LIBSIG) $(SIGPROC) -lm -o $(PROGNAME)

$(OBJS): $(SINC)/esps.h

install: $(PROGNAME)
	$(STRIP) $(PROGNAME)
	-mv -f $(BINDIR)/$(PROGNAME) $(OLDBIN)/$(PROGNAME)
	-chmod $(PROGMOD) $(OLDBIN)/$(PROGNAME)
	mv -f $(PROGNAME) $(BINDIR)/$(PROGNAME)
	chmod $(PROGMOD) $(BINDIR)/$(PROGNAME)
	-diffmk $(MANDIR)/man1/$(MANNAME) $(MANNAME) man.diff
	@echo diffmked man page left in man.diff
	-rm $(MANDIR)/man1/$(MANNAME)
	cp $(MANNAME) $(MANDIR)/man1/$(MANNAME)
	chmod $(MANMOD) $(MANDIR)/man1/$(MANNAME)
# install the default parameter file
	-rm -f $(PARAMDIR)/$(DEFPARAM)
	cp $(DEFPARAM) $(PARAMDIR)/$(DEFPARAM)
	chmod $(LIBMOD) $(PARAMDIR)/$(DEFPARAM)

codecenter_src: $(SRCS)
        #load $(CFLAGS) $(SPSLIB) $(XVLIB) -lm $(SRCS)

clean:	
	-rm -f $(OBJS) $(PROGNAME) core 
	
lint:	$(SRCS) 
	$(LINT) $(LINTFLAGS) $(SRCS) $(LINTLIB) > lint

test:	$(PROGNAME)
	csh $(PROGNAME).test

