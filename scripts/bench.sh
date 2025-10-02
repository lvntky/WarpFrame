#!/usr/bin/env bash
set -euo pipefail

BUILD_DIR="${BUILD_DIR:-build-release}"
if [[ ! -x "$BUILD_DIR/warpframe_bench" ]]; then
  echo "Building benches in $BUILD_DIR ..."
  "${BASH_SOURCE%/*}/release.sh" >/dev/null
fi

exec "$BUILD_DIR/warpframe_bench"
