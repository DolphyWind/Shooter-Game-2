cmake_minimum_required(VERSION 3.26)
set(SG_PROJECT_NAME "Shooter Game")
set(SG_BINARY_NAME "shooter_game")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

project(${SG_PROJECT_NAME})

file(GLOB_RECURSE CPP_FILES "${SOURCE_DIR}/*.cpp")
add_executable(${SG_BINARY_NAME} ${CPP_FILES})

# Fetch and configure SFML
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        2.5.1
)
FetchContent_MakeAvailable(SFML)

# Fetch and configure SFML dependencies
FetchContent_GetProperties(SFML)
if(NOT SFML_POPULATED)
    FetchContent_Populate(SFML)
    add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR})
endif()


target_include_directories(${SG_BINARY_NAME} PRIVATE ${INCLUDE_DIR})
target_include_directories(${SG_BINARY_NAME} PRIVATE ${SOURCE_DIR})

target_link_libraries(${SG_BINARY_NAME} PRIVATE sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
# target_link_libraries(${SG_BINARY_NAME} PRIVATE tgui)
# target_link_libraries(${SG_BINARY_NAME} PRIVATE ${Boost_LIBRARIES})
# target_link_libraries(${SG_BINARY_NAME} PRIVATE thor)
# target_link_libraries(${SG_BINARY_NAME} PRIVATE fmt::fmt)