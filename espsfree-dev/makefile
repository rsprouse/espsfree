all:
	-mkdir -p $(SPSDIR)/include/espsfree
	-ln -s $(SPSDIR)/include/espsfree $(SPSDIR)/include/esps
	cp *.h $(SPSDIR)/include/espsfree/
	-mkdir -p $(SPSDIR)/bin
	-mkdir -p $(SPSDIR)/man
	-mkdir -p $(SPSDIR)/man/man1
	-mkdir -p $(SPSDIR)/lib
	-mkdir -p $(SPSDIR)/lib/filters
	-mkdir -p $(SPSDIR)/lib/params
	-mkdir -p $(SPSDIR)/lib/waves
	-mkdir -p $(SPSDIR)/bin/old
	-mkdir -p $(SPSDIR)/share/doc/espsfree

clean:
	-rm -rf $(SPSDIR)/include/espsfree
	-rm -f $(SPSDIR)/include/esps
	-rm -rf $(SPSDIR)/bin
	-rm -rf $(SPSDIR)/man
	-rm -rf $(SPSDIR)/lib
	-rm -rf $(SPSDIR)/share
