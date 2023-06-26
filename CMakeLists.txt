cmake_minimum_required(VERSION 3.22)
set(SG_PROJECT_NAME "Shooter Game")
set(SG_BINARY_NAME "shooter_game")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
add_definitions(-DSFML_STATIC)

project(${SG_PROJECT_NAME})

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_SHARED_LIBS OFF)
set(BUILD_CURL_EXE OFF)

function(fetch_library library_name repo_url git_tag)
    FetchContent_Declare(
    ${library_name}
    GIT_REPOSITORY ${repo_url}
    GIT_TAG ${git_tag}
    GIT_PROGRESS TRUE
    USES_TERMINAL_DOWNLOAD TRUE
   )
   FetchContent_MakeAvailable(${library_name})
endfunction(fetch_library)

fetch_library(SFML https://github.com/SFML/SFML.git 2.5.1)
fetch_library(TGUI https://github.com/texus/TGUI.git 0.9)
fetch_library(FMT https://github.com/fmtlib/fmt.git a0b8a92e3d1532361c2f7feb63babc5c18d00ef2)
fetch_library(BOX2D https://github.com/erincatto/box2d.git 411acc32eb6d4f2e96fc70ddbdf01fe5f9b16230)
fetch_library(SQLITECPP https://github.com/SRombauts/SQLiteCpp.git 4cb0bf68b75b2f8b749ec5dc77f152f8aa62ec0e)

# set(IMGUI_DIR ${INCLUDE_DIR}/imgui)
# fetch_library(IMGUISFML https://github.com/SFML/imgui-sfml.git 15753d56403a7aeb1cae12fd930cfb1d2eac5e74)
find_package(Boost REQUIRED)
find_package(CURL REQUIRED)

add_subdirectory(include)

file(GLOB_RECURSE CPP_FILES "${SOURCE_DIR}/*.cpp")
add_executable(${SG_BINARY_NAME} ${CPP_FILES})

add_dependencies(${SG_BINARY_NAME} sfml-system)
add_dependencies(${SG_BINARY_NAME} sfml-graphics)
add_dependencies(${SG_BINARY_NAME} sfml-window)
add_dependencies(${SG_BINARY_NAME} sfml-audio)
add_dependencies(${SG_BINARY_NAME} sfml-network)
add_dependencies(${SG_BINARY_NAME} tgui)
add_dependencies(${SG_BINARY_NAME} fmt)
add_dependencies(${SG_BINARY_NAME} clip)
add_dependencies(${SG_BINARY_NAME} box2d)
add_dependencies(${SG_BINARY_NAME} glad)
add_dependencies(${SG_BINARY_NAME} glfw)
add_dependencies(${SG_BINARY_NAME} imgui)
add_dependencies(${SG_BINARY_NAME} sajson)
add_dependencies(${SG_BINARY_NAME} SQLiteCpp)

include_directories(${SG_BINARY_NAME} PRIVATE ${Boost_INCLUDE_DIR})
include_directories(${SG_BINARY_NAME} PRIVATE ${CURL_SOURCE_DIR}/include)
target_include_directories(${SG_BINARY_NAME} PRIVATE ${INCLUDE_DIR})
target_link_libraries(${SG_BINARY_NAME} sfml-graphics sfml-system sfml-audio sfml-window sfml-network)
target_link_libraries(${SG_BINARY_NAME} tgui)
target_link_libraries(${SG_BINARY_NAME} fmt)
target_link_libraries(${SG_BINARY_NAME} clip)
target_link_libraries(${SG_BINARY_NAME} box2d)
target_link_libraries(${SG_BINARY_NAME} curl)
target_link_libraries(${SG_BINARY_NAME} SQLiteCpp)
