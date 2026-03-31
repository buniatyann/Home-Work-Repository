# my_make

A GNU Make clone built from scratch in C++20.

This project reimplements the core functionality of GNU Make as a learning exercise and portfolio piece. It follows a clean pipeline architecture: **CLI → Lexer → Parser → AST → Evaluator → Dependency Graph → Executor**.

## Building

Requires CMake 3.20+ and a C++20 compiler (GCC 12+, Clang 15+).

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)
```

The binary is at `build/src/my_make`.

## Usage

```bash
# Use default Makefile in current directory
./my_make

# Specify a target
./my_make clean

# Specify a makefile
./my_make -f build.mk

# Dry run (print commands without executing)
./my_make -n

# Override a variable
./my_make CC=clang

# Always rebuild everything
./my_make -B

# Keep going on errors
./my_make -k

# Silent mode
./my_make -s

# Change directory before running
./my_make -C path/to/project
```

## Supported Features

### Core
- Targets, prerequisites, and tab-indented recipes
- Multiple targets per rule
- Inline recipes (`all: ; echo done`)
- Comments (`#`) and escaped hashes (`\#`)
- Line continuations (`\`)
- Auto-detection of `GNUmakefile`, `makefile`, `Makefile`

### Variables
- Recursive (`=`), simple (`:=`), append (`+=`), conditional (`?=`) assignment
- Command-line variable overrides (`VAR=value`)
- Origin-based precedence (command-line > override > file > environment > default)
- Automatic variables: `$@`, `$<`, `$^`, `$*`

### Rules
- Explicit rules with dependency tracking
- Pattern rules (`%.o: %.c`)
- Double-colon rules (`target::`)
- Order-only prerequisites (`target: normal | order-only`)

### Special Targets
- `.PHONY` — always rebuild regardless of timestamps

### Recipe Prefixes
- `@` — silent (don't print the command)
- `-` — ignore errors
- `+` — run even in dry-run mode

### Build Behavior
- Timestamp-based incremental rebuilds
- Dependency graph with cycle detection
- Dry-run mode (`-n`)
- Always-make mode (`-B`)
- Keep-going mode (`-k`)

## Roadmap

| Phase | Status | Features |
|-------|--------|----------|
| 1 — Foundation | Done | Lexer, parser, rules, graph, executor, CLI |
| 2 — Variables | Planned | `$(VAR)` expansion, automatic variables in recipes |
| 3 — Pattern Rules | Planned | Implicit rule search, built-in rules, VPATH |
| 4 — Functions | Planned | `$(wildcard)`, `$(patsubst)`, `$(shell)`, `$(foreach)`, `$(call)`, `$(eval)` |
| 5 — Conditionals | Planned | `ifeq`/`ifdef`, `include`, `export`, `override` |
| 6 — Parallel | Planned | `-j N` parallel execution, recursive make |

## Architecture

```
src/
├── cli/          Command-line argument parsing
├── lexer/        Line continuations, comment stripping, classification
├── parser/       Makefile syntax → AST nodes
├── ast/          Data structures (Rule, VariableAssignment, etc.)
├── variables/    Scoped variable table with origin precedence
├── rules/        Explicit and pattern rule storage
├── graph/        DAG construction, cycle detection, topological sort
├── executor/     Timestamp checks, recipe execution via /bin/sh
├── errors/       GNU make-compatible error formatting
└── main.cpp      Pipeline wiring
```

The project builds as a static library (`my_make_lib`) plus an executable, so all internals are unit-testable.

## Running Tests

```bash
# Run directly
./build/tests/my_make_tests

# Or via CTest
cd build && ctest --output-on-failure
```

