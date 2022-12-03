#!/bin/bash
#
# build docker image for vscode devcontainer.

set -eu

## variavles
docker_registry=ncesnagoya
docker_image_name=autosar_os_training
variant=debian-11

# build and push docker iamge.
docker build . \
    -f Dockerfile \
    -t ${docker_registry}/${docker_image_name}:0-${variant} \
    --build-arg VARIANT=${variant}
