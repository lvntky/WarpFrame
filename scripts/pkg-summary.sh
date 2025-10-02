#!/usr/bin/env bash
set -euo pipefail

echo "CMake: $(cmake --version 2>/dev/null | head -n1 || echo 'n/a')"
echo "C++:   $(${CXX:-c++} --version 2>/dev/null | head -n1 || echo 'n/a')"
echo "clang-format: $(clang-format --version 2>/dev/null || echo 'n/a')"
echo "clang-tidy:   $(clang-tidy --version 2>/dev/null || echo 'n/a')"
echo "nproc:        $(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 'n/a')"
