
# This material contains unpublished, proprietary software of 
# Entropic Research Laboratory, Inc. Any reproduction, distribution, 
# or publication of this work must be authorized in writing by Entropic 
# Research Laboratory, Inc., and must bear the notice: 
#
#    "Copyright (c) 1986-1990  Entropic Speech, Inc. 
#    "Copyright (c) 1990-1991  Entropic Research Laboratory, Inc. 
#                   All rights reserved"
#
# The copyright notice above does not evidence any actual or intended 
# publication of this source code.     
#
# %W%	%G%	ESI/ERL
# 
# Written by:  
# Checked by:
# Revised by:
# 
# Makefile for: notch_filt
# 

CFLAGS = -O $(PROGCFLAGS) 

OBJS = notch_filt.o 
SRCS = notch_filt.c 
PROGNAME = notch_filt
MANNAME = notchfilt.1
DEFPARAM = Pnotch_filt


$(PROGNAME): $(SPSLIB) $(OBJS)
	cc  $(CFLAGS) $(OBJS) $(SPSLIB) -lm -o $(PROGNAME)

$(OBJS): $(SINC)/esps.h $(SINC)/filt.h

install: $(PROGNAME)
	-$(STRIP) $(PROGNAME)
	-mv -f $(BINDIR)/$(PROGNAME) $(OLDBIN)/$(PROGNAME)
	-chmod $(PROGMOD) $(OLDBIN)/$(PROGNAME)
	mv -f $(PROGNAME) $(BINDIR)/$(PROGNAME)
	chmod $(PROGMOD) $(BINDIR)/$(PROGNAME)
	-diffmk $(MANDIR)/man1/$(MANNAME) $(MANNAME) man.diff
	@echo diffmked man page left in man.diff
	-rm -f $(MANDIR)/man1/$(MANNAME)
	cp $(MANNAME) $(MANDIR)/man1/$(MANNAME)
	chmod $(MANMOD) $(MANDIR)/man1/$(MANNAME)
# install the default parameter file
	-rm -f $(PARAMDIR)/$(DEFPARAM)
	cp $(DEFPARAM) $(PARAMDIR)/$(DEFPARAM)
	chmod $(LIBMOD) $(PARAMDIR)/$(DEFPARAM)

clean:	
	-rm -f $(OBJS) $(PROGNAME)
	
lint:	$(SRCS) 
	$(LINT) $(LINTFLAGS) $(SRCS) $(LINTLIB) -lm > lint

test:	$(PROGNAME)
	-sh test.script
