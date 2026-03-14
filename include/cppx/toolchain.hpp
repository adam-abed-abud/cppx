#pragma once

#include <string>

namespace cppx {

// Returns true if the given command is found on PATH
bool has_tool(const std::string &name);

// Checks that required tools exist, exits with error if not
void require_tool(const std::string &name);

// Returns "-G Ninja" if ninja is available, empty string otherwise
std::string cmake_generator_flag();

} // namespace cppx
