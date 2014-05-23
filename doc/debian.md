Process for building debian packages:

- Get the latest code:
  git clone https://github.com/rsprouse/espsfree

- Build and install espsfree-dev:
  cd espsfree/espsfree-dev
  debuild     # 'y' to continue at warning message
  cd ..
  dpkg -i espsfree-dev_VERSION.deb 

- Build and install espsfree-lib:
  cd espsfree/espsfree-lib
  debuild     # 'y' to continue at warning message (FIXME: must be root)
  cd ..
  dpkg -i espsfree-lib_VERSION.deb 

- Build and install espsfree-util:
  cd espsfree/espsfree-util
  debuild     # 'y' to continue at warning message (FIXME: must be root)
  cd ..
  dpkg -i espsfree-util_VERSION.deb 

== KNOWN ISSUES:

- The current packaging does not conform very well to Debian
packaging standards. In particular, compilation depends on `emake` to provide
a customized environment for compiling, and this customization should be
done in a more standard way.

- espsfree-lib and espsfree-util will not build without root privileges.
Probably the makefiles are too explicit and create files directly in /usr.
We want them to create files in the fake usr/ in the debian build directory
instead.
