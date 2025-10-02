#!/usr/bin/env bash
set -euo pipefail

BUILD_DIR="${BUILD_DIR:-build-debug}"
GENERATOR="${GENERATOR:-}"
JOBS="${JOBS:-$(nproc 2>/dev/null || sysctl -n hw.ncpu)}"

cmake -S . -B "$BUILD_DIR" \
  -DCMAKE_BUILD_TYPE=Debug \
  -DWARPFRAME_BUILD_TESTS=ON \
  -DWARPFRAME_BUILD_BENCH=ON \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  ${GENERATOR:+-G "$GENERATOR"}

cmake --build "$BUILD_DIR" -j "${JOBS}"

echo "Running ./warpframe ..."
exec "$BUILD_DIR/warpframe"
