#!/usr/bin/env bash
set -euo pipefail

CLANG_FORMAT="${CLANG_FORMAT:-clang-format}"
if ! command -v "$CLANG_FORMAT" >/dev/null 2>&1; then
  echo "clang-format not found, skipping." >&2
  exit 0
fi

# Adjust globs if you add more extensions/dirs
mapfile -t FILES < <(git ls-files '*.hpp' '*.h' '*.cpp' '*.c' 2>/dev/null || true)
if [[ "${#FILES[@]}" -eq 0 ]]; then
  echo "No C/C++ files found."
  exit 0
fi

echo "Formatting ${#FILES[@]} files..."
"$CLANG_FORMAT" -i "${FILES[@]}"
echo "Done."
