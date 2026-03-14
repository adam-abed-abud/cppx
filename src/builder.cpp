#include <cppx/builder.hpp>
#include <cppx/toolchain.hpp>
#include <cstdlib>
#include <filesystem>
#include <iostream>

#include <toml++/toml.hpp>

namespace fs = std::filesystem;

namespace cppx {

static void require_project() {
    if (!fs::exists("cppx.toml")) {
        std::cerr << "Error: cppx.toml not found. Are you in a cppx project?\n";
        std::exit(1);
    }
}

void build_project() {
    require_project();
    require_tool("cmake");

    std::string generator = cmake_generator_flag();

    std::cout << "Configuring...\n";
    int rc = std::system(("cmake -S . -B build" + generator).c_str());
    if (rc != 0) {
        std::cerr << "Configuration failed.\n";
        std::exit(1);
    }

    std::cout << "Building...\n";
    rc = std::system("cmake --build build");
    if (rc != 0) {
        std::cerr << "Build failed.\n";
        std::exit(1);
    }

    std::cout << "Build complete.\n";
}

void run_project() {
    require_project();

    // Read project name from manifest to find the executable
    auto tbl = toml::parse_file("cppx.toml");
    std::string name = tbl["project"]["name"].value_or<std::string>("unknown");

    fs::path exe = fs::path("build") / name;
    if (!fs::exists(exe)) {
        std::cerr << "Error: executable not found at " << exe << "\n";
        std::exit(1);
    }

    std::cout << "Running " << name << "...\n\n";
    std::system(exe.string().c_str());
}

void test_project() {
    require_tool("ctest");
    build_project();

    std::cout << "Running tests...\n";
    int rc = std::system("ctest --test-dir build --output-on-failure");
    if (rc != 0) {
        std::cerr << "Tests failed.\n";
        std::exit(1);
    }
}

void fmt_project() {
    require_project();
    require_tool("clang-format");

    std::cout << "Formatting...\n";
    int rc = std::system(
        "find src include tests -name '*.cpp' -o -name '*.hpp' "
        "| xargs clang-format -i");
    if (rc != 0) {
        std::cerr << "Formatting failed.\n";
        std::exit(1);
    }

    std::cout << "Formatting complete.\n";
}

void lint_project() {
    require_project();
    require_tool("clang-tidy");

    // Build first so compile_commands.json exists
    build_project();

    std::cout << "Linting...\n";
    int rc = std::system(
        "find src tests -name '*.cpp' "
        "| xargs clang-tidy -p build");
    if (rc != 0) {
        std::cerr << "Linting found issues.\n";
        std::exit(1);
    }

    std::cout << "Linting complete.\n";
}

void clean_project() {
    require_project();

    if (fs::exists("build")) {
        fs::remove_all("build");
        std::cout << "Build directory removed.\n";
    } else {
        std::cout << "Nothing to clean.\n";
    }
}

} // namespace cppx
