ESPS Docker containers
======================

The `/docker` directory contains build instructions for creating Docker
images that contain the ESPS utilities. Two Dockerfiles are provided that
build:

   - An [Alpine Linux](https://alpinelinux.org/)-based image for the
     [i386 architecture](https://hub.docker.com/u/i386).
     [[Dockerfile.i386_alpine](Dockerfile.i386_alpine)]

   - An [Ubuntu Linux](https://ubuntu.com)-based image for the
     amd64 architecture. [[Dockerfile.ubuntu64](Dockerfile.ubuntu64)]

Both Dockerfiles produce the same set of utilities and documentation
files. The alpine image is smaller than the ubuntu image and runs the
utilities with native 32-bit support. On the 64-bit ubuntu image 32-bit
support is provided by the libc6-i386 package.

# Building the alpine image

To build either image, first `cd` to the directory containing the Dockerfiles,
then:

```bash
# Build alpine image.
docker build --tag esps:i386_alpine --file Dockerfile.i386_alpine .

# Build ubuntu image.
docker build --tag esps:ubuntu64 --file Dockerfile.ubuntu64 .
```

# Pushing images to a registry

The ESPS Docker images are [shared publicly](https://gallery.ecr.aws/w5x7g6y7/esps)
in the [AWS ECR](https://aws.amazon.com/ecr/). To push an image
to the registry with the [AWS CLI](https://docs.aws.amazon.com/cli/) you must
first create an [IAM user](https://aws.amazon.com/iam/) that has permission to
update the registry and store the user's credentials in the
[CLI's `credentials` file](https://docs.aws.amazon.com/cli/latest/userguide/cli-configure-files.html).

In the examples below the [UC Berkeley Linguistics repository](https://gallery.ecr.aws/w5x7g6y7/esps)
is shown, and you may substitute your own. To push a built image:

```bash
# First specify the IAM user credentials to use by specifying the appropriate
# `[section]` of the credentials file.
export AWS_PROFILE=[iam_user]

# Store a token for Docker to use (valid 12 hours).
aws ecr-public get-login-password --region us-east-1 | docker login --username AWS --password-stdin public.ecr.aws/w5x7g6y7

# Tag and push alpine image.
docker tag esps:i386_alpine public.ecr.aws/w5x7g6y7/esps:i386_alpine
docker push public.ecr.aws/w5x7g6y7/esps:i386_alpine

# Tag and push ubuntu image.
docker tag esps:ubuntu64 public.ecr.aws/w5x7g6y7/esps:ubuntu64
docker push public.ecr.aws/w5x7g6y7/esps:ubuntu64
```
