#include <CLI/CLI.hpp>
#include <cppx/builder.hpp>
#include <cppx/generator.hpp>
#include <iostream>
#include <string>

int main(int argc, char **argv) {

    CLI::App app{"cppx - A fast C++ project starter."};
    app.require_subcommand(1);

    // "cppx new <name>"
    auto *new_cmd = app.add_subcommand("new", "Create a new C++ project");
    std::string project_name;
    new_cmd->add_option("name", project_name, "Project name")->required();

    // "cppx init"
    auto *init_cmd = app.add_subcommand("init", "Initialize a cppx project in the current directory");

    // "cppx build"
    auto *build_cmd = app.add_subcommand("build", "Build the project");

    // "cppx run"
    auto *run_cmd = app.add_subcommand("run", "Build and run the project");

    // "cppx test"
    auto *test_cmd = app.add_subcommand("test", "Run tests");

    // "cppx fmt"
    auto *fmt_cmd = app.add_subcommand("fmt", "Format source code");

    // "cppx lint"
    auto *lint_cmd = app.add_subcommand("lint", "Lint source code");

    // "cppx clean"
    auto *clean_cmd = app.add_subcommand("clean", "Remove build artifacts");

    CLI11_PARSE(app, argc, argv);

    // Dispatch
    if (new_cmd->parsed()) {
        cppx::generate_project(project_name);
    } else if (init_cmd->parsed()) {
        cppx::init_project();
    } else if (build_cmd->parsed()) {
        cppx::build_project();
    } else if (run_cmd->parsed()) {
        cppx::build_project();
        cppx::run_project();
    } else if (test_cmd->parsed()) {
        cppx::test_project();
    } else if (fmt_cmd->parsed()) {
        cppx::fmt_project();
    } else if (lint_cmd->parsed()) {
        cppx::lint_project();
    } else if (clean_cmd->parsed()) {
        cppx::clean_project();
    }

    return 0;
}
