# CMakeList.txt : CMake project for CommandPattern, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.30.0)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("CommandPattern")

# Add source to this project's executable.
add_executable (CommandPattern "CommandPattern.cpp" "CommandPattern.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CommandPattern PROPERTY CXX_STANDARD 20)
endif()

include(FetchContent)

set(CMAKE_TLS_VERIFY OFF)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

FetchContent_Declare(
    raylib
    URL "https://github.com/raysan5/raylib/archive/refs/tags/6.0.tar.gz"
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(raylib)
file(REMOVE_RECURSE ${raylib_SOURCE_DIR}/examples)
file(REMOVE_RECURSE ${raylib_SOURCE_DIR}/projects)

# TODO: Add tests and install targets if needed.
target_link_libraries(CommandPattern
raylib)