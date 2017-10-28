#!/usr/bin/env bash

set -ex

OUTDIR=/io/dist

for PYBIN in opt/python/*/bin; do
    if [[ ${PYBIN} == *"26"* ]]; then
        continue
    fi

    if [[ ${PYBIN} == *"33"* ]]; then
        continue
    fi

    "${PYBIN}/pip" install -r /io/dev-requirements.txt
    "${PYBIN}/pip" wheel /io/ -w "${OUTDIR}"
done
