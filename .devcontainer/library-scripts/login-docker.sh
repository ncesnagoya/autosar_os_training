#!/bin/bash

set -eu

## variavles
docker_user_name=mitsu48

# You need access token for docker login using Docker CLI 
docker login -u ${docker_user_name}
