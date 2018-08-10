all:
	(cd src/lib/; emake)
	(cd src/lib_header/; emake)
	(cd src/lib_sp/; emake)
	(cd src/libsig/; emake; emake install)
	(cd src/sigproc/; emake; emake install)

clean:
	(cd src/lib/; emake clean)
	(cd src/lib_header/; emake clean)
	(cd src/lib_sp/; emake clean)
	(cd src/libsig/; emake clean)
	(cd src/sigproc/; emake clean)
