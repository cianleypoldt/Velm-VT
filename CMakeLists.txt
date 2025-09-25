cmake_minimum_required(VERSION 3.15)
project(VlemVT LANGUAGES CXX)

# -----------------------------
# C++ standard
# -----------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------
# Enable compile_commands.json generation
# -----------------------------
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -----------------------------
# Include directories
# -----------------------------
include_directories(
    third_party/glad/include
    third_party/glm
    third_party/imgui
    third_party/spdlog/include
    third_party/nlohmann_json/include
)

# -----------------------------
# System libraries
# -----------------------------
find_package(PkgConfig REQUIRED)

# GLFW
pkg_check_modules(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
link_directories(${GLFW_LIBRARY_DIRS})

# HDF5
pkg_check_modules(HDF5 REQUIRED hdf5)
include_directories(${HDF5_INCLUDE_DIRS})
link_directories(${HDF5_LIBRARY_DIRS})

# -----------------------------
# Gather source files
# -----------------------------
file(GLOB_RECURSE VLEMVT_SOURCES CONFIGURE_DEPENDS src/*.cpp)
set(GLAD_SRC ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glad/src/glad.c)

# -----------------------------
# Create library
# -----------------------------
add_library(${PROJECT_NAME} STATIC ${VLEMVT_SOURCES} ${GLAD_SRC})
target_link_libraries(${PROJECT_NAME}
    ${GLFW_LIBRARIES}
    ${HDF5_LIBRARIES}
)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)

# -----------------------------
# Enable testing
# -----------------------------
include(CTest)
enable_testing()

# -----------------------------
# GoogleTest (system-installed)
# -----------------------------
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# -----------------------------
# Add test executable
# -----------------------------
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS tests/*.cpp)
add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES})
target_link_libraries(${PROJECT_NAME}_tests PRIVATE ${PROJECT_NAME} GTest::GTest GTest::Main)

# -----------------------------
# Register tests
# -----------------------------
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_tests)
