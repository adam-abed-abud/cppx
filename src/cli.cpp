#include <cppx/generator.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

namespace cppx {

void write_file(const fs::path &path, const std::string &content) {
    std::ofstream out(path);
    out << content;
}

std::string generate_main_cpp() {
    return R"(#include <iostream>

int main() {
    std::cout << "Hello, cppx!" << std::endl;
    return 0;
}
)";
}

std::string generate_clang_format() {
    return R"(BasedOnStyle: LLVM
IndentWidth: 4
ColumnLimit: 100
)";
}

std::string generate_test_main() {
    return R"(#include <iostream>

int main() {
    std::cout << "Tests passed!" << std::endl;
    return 0;
}
)";
}

std::string generate_overview(const std::string &name) {
    return "# " + name + " Overview\n\nProject documentation goes here.\n";
}

std::string generate_readme(const std::string &name) {
    return "# " + name + "\n\nA C++ project created with cppx.\n";
}

std::string generate_gitignore() {
    return R"(build/
.cache/
compile_commands.json
CMakeUserPresets.json
)";
}

std::string generate_manifest(const std::string &name) {
    return "[project]\nname = \"" + name +
           "\"\nversion = \"0.1.0\"\ncpp_standard = \"20\"\n\n"
           "[build]\ntype = \"executable\"\n\n"
           "[tools]\nformatter = \"clang-format\"\nlinter = \"clang-tidy\"\n";
}

std::string generate_cmakelists(const std::string &name) {
    return "cmake_minimum_required(VERSION 3.20)\n"
           "project(" + name + " VERSION 0.1.0 LANGUAGES CXX)\n\n"
           "set(CMAKE_CXX_STANDARD 20)\n"
           "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n"
           "set(CMAKE_EXPORT_COMPILE_COMMANDS ON)\n\n"
           "add_executable(" + name + " src/main.cpp)\n"
           "target_compile_options(" + name + " PRIVATE -Wall -Wextra -Wpedantic)\n\n"
           "# Testing\n"
           "enable_testing()\n"
           "add_executable(tests tests/test_main.cpp)\n"
           "target_compile_options(tests PRIVATE -Wall -Wextra -Wpedantic)\n"
           "add_test(NAME tests COMMAND tests)\n";
}

void generate_project(const std::string &name) {
    fs::path root = fs::current_path() / name;

    if (fs::exists(root)) {
        std::cerr << "Error: directory '" << name << "' already exists.\n";
        return;
    }

    // Create directory structure
    fs::create_directories(root / "src");
    fs::create_directories(root / "include" / name);
    fs::create_directories(root / "tests");
    fs::create_directories(root / "docs");

    // Write project files
    write_file(root / "src" / "main.cpp", generate_main_cpp());
    write_file(root / "cppx.toml", generate_manifest(name));
    write_file(root / "CMakeLists.txt", generate_cmakelists(name));
    write_file(root / ".gitignore", generate_gitignore());
    write_file(root / ".clang-format", generate_clang_format());
    write_file(root / "README.md", generate_readme(name));
    write_file(root / "tests" / "test_main.cpp", generate_test_main());
    write_file(root / "docs" / "overview.md", generate_overview(name));

    std::cout << "Project created: " << name << "\n\n"
              << "Structure generated:\n"
              << "  src/\n"
              << "  include/\n"
              << "  tests/\n"
              << "  docs/\n\n"
              << "Ready to build.\n";
}

void init_project() {
    fs::path root = fs::current_path();
    std::string name = root.filename().string();

    if (fs::exists(root / "cppx.toml")) {
        std::cerr << "Error: cppx.toml already exists. This is already a cppx project.\n";
        return;
    }

    // Create directory structure
    fs::create_directories(root / "src");
    fs::create_directories(root / "include" / name);
    fs::create_directories(root / "tests");
    fs::create_directories(root / "docs");

    // Write project files
    write_file(root / "src" / "main.cpp", generate_main_cpp());
    write_file(root / "cppx.toml", generate_manifest(name));
    write_file(root / "CMakeLists.txt", generate_cmakelists(name));
    write_file(root / ".gitignore", generate_gitignore());
    write_file(root / ".clang-format", generate_clang_format());
    write_file(root / "README.md", generate_readme(name));
    write_file(root / "tests" / "test_main.cpp", generate_test_main());
    write_file(root / "docs" / "overview.md", generate_overview(name));

    std::cout << "Initialized cppx project: " << name << "\n\n"
              << "Structure generated:\n"
              << "  src/\n"
              << "  include/\n"
              << "  tests/\n"
              << "  docs/\n\n"
              << "Ready to build.\n";
}

} // namespace cppx
