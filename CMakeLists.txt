cmake_minimum_required(VERSION 3.22)
set(SG_PROJECT_NAME "Shooter Game")
set(SG_BINARY_NAME "shooter_game")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(${SG_PROJECT_NAME})


add_definitions(-DSFML_STATIC)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "Detected compiler: GCC")
    add_compile_options(-fPIC -g)
    elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(STATUS "Detected compiler: Clang")
    add_compile_options(-fPIC -g)
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message(STATUS "Detected compiler: MSVC")
    add_compile_options("/MD" "/Z7" "/EHsc")
else ()
    message(WARNING "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}")
endif ()



include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_SHARED_LIBS OFF)
set(BUILD_CURL_EXE OFF)
set(IMGUI_SFML_FIND_SFML OFF)
set(THOR_SHARED_LIBS OFF)
set(IMGUI_DIR ${INCLUDE_DIR}/thirdparty/imgui)
set(SFML_STATIC_LIBRARIES TRUE)
set(TGUI_BUILD_GUI_BUILDER FALSE)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/mods DESTINATION ${CMAKE_BINARY_DIR})
set(BUILD_SHARED_LIBS OFF)
set(SFEX_USE_UPDATE_BASED_INPUT_HANDLING ON)
set(BUILD_TESTS OFF)

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
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system audio)

fetch_library(TGUI https://github.com/texus/TGUI.git 0.9)
fetch_library(FMT https://github.com/fmtlib/fmt.git a0b8a92e3d1532361c2f7feb63babc5c18d00ef2)
fetch_library(IMGUISFML https://github.com/SFML/imgui-sfml.git 15753d56403a7aeb1cae12fd930cfb1d2eac5e74)
fetch_library(SFEX https://github.com/DolphyWind/SFML-Extended b69732972b21b8ae8f55b0b8a842d49e91e5dc67)

if(WIN32)
    find_package(CURL CONFIG REQUIRED)
else()
    find_package(CURL REQUIRED)
endif(WIN32)

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
add_dependencies(${SG_BINARY_NAME} ImGui-SFML)
add_dependencies(${SG_BINARY_NAME} SFEX)

include_directories(${SG_BINARY_NAME} PRIVATE ${Boost_INCLUDE_DIR})
include_directories(${SG_BINARY_NAME} PRIVATE ${CURL_SOURCE_DIR}/include)
target_include_directories(${SG_BINARY_NAME} PRIVATE ${INCLUDE_DIR})
target_link_libraries(${SG_BINARY_NAME} sfml-graphics sfml-system sfml-audio sfml-window sfml-network)
target_link_libraries(${SG_BINARY_NAME} tgui)
target_link_libraries(${SG_BINARY_NAME} fmt)
target_link_libraries(${SG_BINARY_NAME} clip)
target_link_libraries(${SG_BINARY_NAME} CURL::libcurl)
target_link_libraries(${SG_BINARY_NAME} ImGui-SFML)
target_link_libraries(${SG_BINARY_NAME} SFEX)
target_link_libraries(${SG_BINARY_NAME} "${CMAKE_SOURCE_DIR}/lib/liblua.a")

# Os-Specific Linking
if(WIN32)
elseif(APPLE)
elseif(UNIX)
target_link_libraries(${SG_BINARY_NAME} X11)
else()
endif(WIN32)

