#!/bin/bash

set -e

docker run --rm -it -v $(pwd):/io quay.io/pypa/manylinux1_x86_64:latest bash /io/build_wheels.sh
