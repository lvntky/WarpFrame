#!/usr/bin/env bash
set -euo pipefail

BUILD_DIR="${BUILD_DIR:-build-debug}"
if [[ ! -d "$BUILD_DIR" ]]; then
  echo "No $BUILD_DIR. Run scripts/dev.sh first or set BUILD_DIR." >&2
  exit 1
fi

ctest --test-dir "$BUILD_DIR" --output-on-failure
