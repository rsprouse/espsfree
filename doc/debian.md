ESPS should compile on a Debian system, but the Debian packaging is not
quite right, and the binary packages are not created correctly for
distribution. However, grabbing the source packages and running through
the build process has the side effect of installing files in the more-or-less
correct locations, and you can use the build process to work around the
broken packages.

Process for building debian packages:

1. Get the latest code:

    git clone https://github.com/rsprouse/espsfree

1. Build and install espsfree-dev:

    cd espsfree/espsfree-dev
    sudo debuild -us -uc     # 'y' to continue at warning message
    cd ..
    dpkg -i espsfree-dev_VERSION.deb 

1. Build and install espsfree-lib:

    cd espsfree/espsfree-lib
    sudo debuild -us -uc    # 'y' to continue at warning message (FIXME: fakeroot wont work)
    cd ..
    dpkg -i espsfree-lib_VERSION.deb 

1. Build and install espsfree-util:

    cd espsfree/espsfree-util
    sudo debuild -us -uc    # 'y' to continue at warning message (FIXME: fakeroot wont work)
    cd ..
    dpkg -i espsfree-util_VERSION.deb 

1. Build and install espsfree-signal:

    cd espsfree/espsfree-signal
    sudo debuild -us -uc     # 'y' to continue at warning message (FIXME: fakeroot wont work)
    cd ..
    dpkg -i espsfree-signal_VERSION.deb 

== KNOWN ISSUES:

- The current packaging does not conform very well to Debian
packaging standards. In particular, compilation depends on `emake` to provide
a customized environment for compiling, and this customization should be
done in a more standard way.

- espsfree-lib, espsfree-util, and espsfree-signal will not build without sudo.
Probably the makefiles are too explicit and create files directly in /usr.
We want them to create files in the fake usr/ in the debian build directory
instead.

- Running `debuild` in espsfree-lib installs *.a files to /usr/lib/espsfree
directly and they do not end up in the .deb. These files should install to
the debian fake directory structure.

- Running `debuild` in espsfree-util installs binary files to /usr/bin
directly and they do not end up in the .deb. These files should install to
the debian fake directory structure.

- The fea2esig command in espsfree-util will not compile. This needs to be
fixed and compilation needs to be re-enabled in the espsfree-util makefile.

