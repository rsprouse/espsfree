espsfree
========

BSD-licensed Entropic Signal Processing System (ESPS) released by Microsoft, repackaged and slightly updated.

The original esps source code has been reorganized as follows:

- espsfree-dev: Files that are required for compiling esps from source.
- espsfree-lib: Source code for the esps libraries.
- espsfree-signal: Source code for signal processing and speech-related commands (e.g. formant, fft, get_f0).
- espsfree-util: Source code for utility commands (e.g. bhd, hditem, pplain).

The `debian` subdirectories of each contain information for creating Debian
packages.
