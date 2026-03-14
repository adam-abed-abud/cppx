cmake_minimum_required(VERSION 3.20)
project(cppx VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
      cli11
      GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
      GIT_TAG v2.6.2
)

FetchContent_Declare(
      tomlplusplus
      GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
      GIT_TAG        v3.4.0
)

FetchContent_MakeAvailable(cli11 tomlplusplus)

add_executable(cppx
      src/main.cpp
      src/cli.cpp
      src/builder.cpp
      src/toolchain.cpp
)

target_include_directories(cppx PRIVATE
      ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(cppx PRIVATE
      CLI11::CLI11
      tomlplusplus::tomlplusplus
)

target_compile_options(cppx PRIVATE
      -Wall -Wextra -Wpedantic
)

