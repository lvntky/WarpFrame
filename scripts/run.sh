#!/usr/bin/env bash
set -euo pipefail

CANDIDATES=("build-debug/warpframe" "build-release/warpframe" "build/warpframe")
for bin in "${CANDIDATES[@]}"; do
  if [[ -x "$bin" ]]; then
    exec "$bin"
  fi
done
echo "warpframe binary not found. build first with scripts/dev.sh or scripts/release.sh" >&2
exit 1
