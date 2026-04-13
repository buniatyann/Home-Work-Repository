#!/usr/bin/env bash
# Bootstrap build for my_make — compiles directly with g++, no CMake.
# Usage: source make.sh     (or: bash make.sh)
# Output: ./my_make

set -e

CXX="${CXX:-g++}"
CXXFLAGS="${CXXFLAGS:--std=c++20 -O2 -Wall -Wextra}"
SRC_DIR="src"
MOD_DIR="$SRC_DIR/modules"
OUT="my_make"

SOURCES=(
    "$SRC_DIR/app/main.cpp"
    "$MOD_DIR/cli/cli.cpp"
    "$MOD_DIR/core/errors/errors.cpp"
    "$MOD_DIR/parser/lexer/lexer.cpp"
    "$MOD_DIR/parser/parser/parser.cpp"
    "$MOD_DIR/eval/variable_table.cpp"
    "$MOD_DIR/eval/expander.cpp"
    "$MOD_DIR/engine/rule_database/rule_database.cpp"
    "$MOD_DIR/engine/graph/graph.cpp"
    "$MOD_DIR/engine/execution/executor.cpp"
)

echo "Compiling $OUT with $CXX..."
"$CXX" $CXXFLAGS -I"$MOD_DIR" "${SOURCES[@]}" -o "$OUT"
echo "Built: ./$OUT"
