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

- espsfree-dev: Files that are required for compiling ESPS from source.
- espsfree-lib: Source code for the ESPS libraries.
- espsfree-signal: Source code for signal processing and speech-related commands (e.g. formant, fft, get\_f0).
- espsfree-util: Source code for utility commands (e.g. bhd, hditem, pplain).

The `debian` subdirectories of each contain information for creating Debian
packages. Debian packaging is incomplete and does not install correctly.

# Installing the ESPS utilities

## Installing with Docker

The simplest way to use the ESPS utilities is to pull a Docker container that
contains precompiled executables. You must first install
[Docker](https://www.docker.com/), then pull one of the images from the
[UC Berkeley Linguistics repository](https://gallery.ecr.aws/ucblx/esps).
The Alpine Linux image is smaller and is a 32-bit native system. The Ubuntu
Linux image is a larger 64-bit system. For most users the Alpine image is
recommended for its smaller size.

To pull an image:

```bash
# Pull the alpine image.
docker pull public.ecr.aws/ucblx/esps:i386_alpine

# Pull the Ubuntu image.
docker pull public.ecr.aws/ucblx/esps:ubuntu64
```

See the [`docker` directory](docker) if you are interested in creating Docker
images from scratch.

## Installing with Singularity

On HPC and Linux systems that provide [Singularity](https://sylabs.io/singularity/)
you can pull Docker containers with the `singularity` command and
prefixing `docker://` to the repository:

```bash
# Pull the alpine image.
singularity pull docker://public.ecr.aws/ucblx/esps:i386_alpine

# Pull the Ubuntu image.
singularity pull docker://public.ecr.aws/ucblx/esps:ubuntu64
```

## Compiling and installing on Linux

You may also compile the utilities yourself on Linux systems. You should be
aware that compiling requires 32-bit compatibility support on 64-bit systems,
and you will need to set compile-time variables appropriate to your
environment. Consult the `emake*` files in [`espsfree-dev`](espsfree-dev) for sample
configurations and make adjustments. The codebase is rather old C code, and
can be challenging to compile.

On the [Berkeley Phonetics Machine](https://linguistics.berkeley.edu/plab/guestwiki/index.php?title=Berkeley_Phonetics_Machine), installation can be accomplished with:

```bash
git clone https://github.com/rsprouse/espsfree
cd espsfree
sudo cp `pwd`/espsfree-dev/emake.bpm /usr/local/bin/emake
emake
sudo emake install
```

Support for 32-bit compiling might not be installed on all versions of the
BPM. To add 32-bit support do:

```bash
sudo apt-get update
sudo apt-get install gcc-multilib
```

Other Linux systems will be similar, assuming a build system is in place. For
example, on Ubuntu:

```bash
sudo apt-get update
sudo apt-get install build-essential bison flex gcc-multilib
```

# Running the ESPS utilities

## Running native executables on linux

If you compiled and installed the utlities yourself on a linux system, run the
utilities as you would any other command.

## Running with Docker

### Listing the available ESPS utilities

Docker users can view the available ESPS utilities with one of:

```bash
# Alpine image
docker run --rm --platform linux/386 public.ecr.aws/ucblx/esps:i386_alpine ls /usr/local/bin

# Ubuntu image
docker run --rm public.ecr.aws/ucblx/esps:ubuntu64 ls /usr/local/bin
```

Every time `docker run` is invoked on an image a new container is created, and
most of the time you will not want the stopped container to persist after
your executable has finished (stopped containers are viewable with
`docker container ls -a`).  The `--rm` option automatically removes containers
when the command finishes. The `--platform` option prevents a warning from
being emitted when the image platform does not match the host platform.
Most host platforms will not match the `i386_alpine` image, so
`--platform linux/386` is included in the `i386_alpine` example shown above.

The remaining examples assume the `esps:i386_alpine` image. Remove
`--platform linux/386` and replace the image tag with `esps:ubuntu64` if that is
your image.

### Getting documentation for the ESPS utilities

To see the manual page for any of the utilities run `man <utility>`, e.g. for
`get_f0`:

```bash
docker run --rm --platform linux/386 public.ecr.aws/ucblx/esps:i386_alpine man get_f0
```

### Processing files with the ESPS utilities

The general form of an ESPS command is:

```bash
docker run --rm --platform linux/386 public.ecr.aws/ucblx/esps:i386_alpine esps_cmd [OPTIONS] ARGS
```

Where `[OPTIONS]` are option values described in the manual page and
`ARGS` are the required arguments. The `get_f0` utility will be used to
illustrate usage.

Many of the ESPS utilities require input and output filenames, and usually you
will need to process files that are on your computer and that are not in the
container image itself. In order to do this you must map a data directory on
your computer to a path inside the container. You do this with the `-v` option,
where you provide a mapping of a local path to a path inside the container,
separated by '`:`':

```bash
docker run --rm --platform linux/386 -v /path/to/datadir:/data public.ecr.aws/ucblx/esps:i386_alpine get_f0 /data/infile.wav /data/infile.f0
```

The above command maps the local directory `/path/to/datadir` on the host
machine, where the file `infile.wav` is located, to the path `/data` inside
the container. The latter path is the one used in the input and output file
arguments to `get_f0`. The mapping allows `get_f0` to find the input file
and write its output file where you can find it in `/path/to/datadir`.

### Aliases

The `docker run` commands are rather long. For interactive work you might find
it convenient to create an alias if your shell supports it (linux, mac):

```bash
# Create alias that includes volume mapping and image and command names:
alias get_f0="docker run --rm --platform linux/386 -v /path/to/datadir:/data public.ecr.aws/ucblx/esps:i386_alpine get_f0"

# Then run with:
get_f0 /data/this_is_a_label_file.wav /data/out.f0
```

For scripts you should not use aliases, as the explicit unaliased form will make
your work more reproducible.

### A note on persistence

Some ESPS utilities maintain settings between invocations when run on a normal
interactive system. Since the examples above remove Docker containers after
every invocation this kind of persistence will not occur.

### Running interactively

The bash shell is provided in the `esps:ubuntu64` image, and you can start
an interactive session inside the container like this:

```bash
# Start a shell inside the container
docker run --rm -it -v /path/to/datadir:/data public.ecr.aws/ucblx/esps:ubuntu64 /bin/bash

# Run a series of commands within the container here.
...

# Exit the container
exit
```

See the Docker documentation for more on running interactive sessions.

## Running with Singularity

Running the ESPS utilities with Singularity is similar to running with
Docker, but a little simpler since Singularity automatically allows access
to the local filesystem.

Also, Docker images are referenced by tag only, whereas Singularity images
are identified by the path to the `.sif` file.

### Listing the available ESPS utilities

```bash
singularity run ./esps_i386_alpine.sif ls /usr/local/bin
```

In the example above the `.sif` file is in the current directory '`.`'.

### Getting documentation for the ESPS utilities

```bash
singularity run ./esps_i386_alpine.sif man get_f0
```

### Processing files with the ESPS utilities

The local filesystem is accessible to the container, so no mapping is
required, and files are accessed with the same path as on the local system:

```bash
singularity run ./esps_i386_alpine.sif get_f0  /path/to/infile.wav /path/to/outfile.f0
```
