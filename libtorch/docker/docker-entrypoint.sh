#!/usr/bin/env bash
set -Eeo pipefail

cmake -B build -D CMAKE_BUILD_TYPE=Release \
      -D CMAKE_PREFIX_PATH=/opt/conda/lib/python${PYTHON_VERSION}/site-packages/torch/share/cmake/Torch/ \
      -D CREATE_SCRIPTMODULES=ON


cmake --build build --target basics
cd build/tutorials/basics
exec bash
