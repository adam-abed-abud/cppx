#include <cppx/toolchain.hpp>
#include <cstdlib>
#include <iostream>

namespace cppx {

bool has_tool(const std::string &name) {
    // "which <tool> > /dev/null 2>&1" returns 0 if found, non-zero if not.
    // We redirect output so nothing prints to the terminal.
    std::string cmd = "which " + name + " > /dev/null 2>&1";
    return std::system(cmd.c_str()) == 0;
}

void require_tool(const std::string &name) {
    if (!has_tool(name)) {
        std::cerr << "Error: '" << name << "' not found. Please install it.\n";
        std::exit(1);
    }
}

std::string cmake_generator_flag() {
    if (has_tool("ninja")) {
        return " -G Ninja";
    }
    return "";
}

} // namespace cppx
