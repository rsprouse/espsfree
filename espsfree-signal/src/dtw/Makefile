#  This material contains proprietary software of Entropic Speech, Inc.
#  Any reproduction, distribution, or publication without the prior
#  written permission of Entropic Speech, Inc. is strictly prohibited.
#  Any public distribution of copies of this work authorized in writing by
#  Entropic Speech, Inc. must bear the notice
#
#      "Copyright (c) 1991 Entropic Speech, Inc.; All rights reserved"
#
#  makefile for DTW programs @(#)Makefile	1.2 2/20/96 ERL

CFLAGS = -O $(PROGCFLAGS) 


OBJS = dtw.o 
SRCS = dtw.c 
PROGNAME = dtw
MANNAME = dtw.1

all: $(PROGNAME) install

$(PROGNAME): $(SPSLIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS)  $(SPSLIB) $(LIBS) -lm -o $(PROGNAME)

pure: $(SPSLIB) $(OBJS)
	purify $(CC) $(CFLAGS) $(OBJS)  $(SPSLIB) $(LIBS) -lm -o $(PROGNAME)

$(OBJS): $(SINC)/esps.h

install: $(PROGNAME)
	-strip $(PROGNAME)
	-mv $(BINDIR)/$(PROGNAME) $(OLDBIN)/$(PROGNAME)
	mv -f $(PROGNAME) $(BINDIR)/$(PROGNAME)
	chmod $(PROGMOD) $(BINDIR)/$(PROGNAME)
	-diffmk $(MANDIR)/man1/$(MANNAME) $(MANNAME) man.diff
	@echo diffmked man page left in man.diff
	cp $(MANNAME) $(MANDIR)/man1/$(MANNAME)
	chmod $(MANMOD) $(MANDIR)/man1/$(MANNAME)

clean:
	-rm -f $(OBJS) $(PROGNAME)

lint:   $(SRCS)
	$(LINT) $(LINTFLAGS) $(XVINC) $(SRCS) $(LINTLIB) > lint

test:   $(PROGNAME)
	-csh $(PROGNAME).t
