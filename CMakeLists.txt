cmake_minimum_required(VERSION 3.26)
set(SG_PROJECT_NAME "Shooter Game")
set(SG_BINARY_NAME "shooter_game")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(${SG_PROJECT_NAME})

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)

function(fetch_library library_name repo_url git_tag)
    FetchContent_Declare(
    ${library_name}
    GIT_REPOSITORY ${repo_url}
    GIT_TAG ${git_tag}
   )
   FetchContent_MakeAvailable(${library_name})
endfunction(fetch_library)

fetch_library(SFML https://github.com/SFML/SFML.git 2.5.1)
fetch_library(TGUI https://github.com/texus/TGUI.git 0.9)
fetch_library(FMT https://github.com/fmtlib/fmt.git a0b8a92e3d1532361c2f7feb63babc5c18d00ef2)

set(CLIP_EXAMPLES OFF CACHE BOOL "Compile clip examples")
set(CLIP_TESTS OFF CACHE BOOL "Compile clip tests")
add_subdirectory(include)

file(GLOB_RECURSE CPP_FILES "${SOURCE_DIR}/*.cpp")
add_executable(${SG_BINARY_NAME} ${CPP_FILES})

target_include_directories(${SG_BINARY_NAME} PRIVATE ${INCLUDE_DIR})
target_link_libraries(${SG_BINARY_NAME} sfml-graphics sfml-system sfml-audio sfml-window sfml-network)
target_link_libraries(${SG_BINARY_NAME} tgui)
target_link_libraries(${SG_BINARY_NAME} fmt)
target_link_libraries(${SG_BINARY_NAME} clip)
