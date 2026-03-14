# cppx

A Cargo-inspired CLI tool for quickly creating and managing modern C++ projects.

## Requirements

- C++20 compiler (GCC 12+ or Clang 15+)
- CMake 3.20+
- Ninja (optional, used automatically if available)
- clang-format (optional, for `cppx fmt`)
- clang-tidy (optional, for `cppx lint`)

## Building cppx

```bash
cmake -S . -B build
cmake --build build
```

## Usage

```bash
cppx new hello      # Create a new project in hello/
cppx init           # Initialize a project in the current directory

cd hello
cppx build          # Configure and build
cppx run            # Build and run the executable
cppx test           # Build and run tests
cppx fmt            # Format source code with clang-format
cppx lint           # Lint source code with clang-tidy
cppx clean          # Remove the build directory
```

## Generated project structure

```
project_name/
├── cppx.toml
├── CMakeLists.txt
├── README.md
├── .gitignore
├── .clang-format
├── src/
│   └── main.cpp
├── include/
│   └── project_name/
├── tests/
│   └── test_main.cpp
└── docs/
    └── overview.md
```

## Dependencies

Fetched automatically via CMake FetchContent:

- [CLI11](https://github.com/CLIUtils/CLI11) - command line parsing
- [toml++](https://github.com/marzer/tomlplusplus) - TOML manifest parsing
