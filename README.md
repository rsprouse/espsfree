espsfree
========

BSD-licensed Entropic Signal Processing System (ESPS) released by Microsoft,
repackaged and slightly updated.

Many of the source files contain the original Entropics copyright and license
notifications. Microsoft purchased Entropics and subsequently released the
code under a BSD-style license. The files README.TXT and BSD.TXT in the
project root are reproduced as they were provided by Microsoft.

The XWaves utilities are not included in this package, and XView dependencies
have been removed, which makes the package much easier to compile in modern
(year 2014) development environments.

The original esps source code has been reorganized as follows:

- espsfree-dev: Files that are required for compiling esps from source.
- espsfree-lib: Source code for the esps libraries.
- espsfree-signal: Source code for signal processing and speech-related commands (e.g. formant, fft, get_f0).
- espsfree-util: Source code for utility commands (e.g. bhd, hditem, pplain).

The `debian` subdirectories of each contain information for creating Debian
packages.
