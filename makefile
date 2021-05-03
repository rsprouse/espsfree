all:
	(cd espsfree-dev; emake)
	(cd espsfree-lib; emake)
	(cd espsfree-util; emake)
	(cd espsfree-signal; emake)

install:
	(cd espsfree-util; emake install)
	(cd espsfree-signal; emake install)
	-ln -s $(SPSDIR)/bin/* $(LOCALBINDIR)/

clean:
	(cd espsfree-dev; emake clean)
	(cd espsfree-lib; emake clean)
	(cd espsfree-util; emake clean)
	(cd espsfree-signal; emake clean)

clean_links:
	-for f in $(ls $(SPSDIR)/bin/); do echo rm $(LOCALBINDIR)/${f}; done
