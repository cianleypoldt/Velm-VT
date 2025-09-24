cmake_minimum_required(VERSION 3.15)
project(VelmVT LANGUAGES CXX)

# -----------------------------
# C++ standard
# -----------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------
# Header-only / local dependencies
# -----------------------------
# GLAD
set(GLAD_SRC ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glad/src/glad.c)

# Include directories for header-only libraries
include_directories(
    third_party/glad/include
    third_party/glm
    third_party/imgui
    third_party/spdlog/include
    third_party/nlohmann_json/include
)

# -----------------------------
# System libraries via Pacman / package manager
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

# VTK (system-installed)
# Set VTK_DIR if needed, e.g., /usr/lib/cmake/vtk-9.1
# On Arch/Manjaro, you can check the path with: pacman -Ql vtk | grep CMake
# find_package(VTK REQUIRED COMPONENTS
#     vtkCommonCore
#     vtkRenderingCore
#     vtkFiltersCore
# )

# include(${VTK_USE_FILE})

# -----------------------------
# Gather source files
# -----------------------------
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# -----------------------------
# Create executable
# -----------------------------
add_executable(${PROJECT_NAME} ${SOURCES} ${GLAD_SRC})

# -----------------------------
# Link libraries
# -----------------------------
target_link_libraries(${PROJECT_NAME}
    ${GLFW_LIBRARIES}
    ${HDF5_LIBRARIES}
    # ${VTK_LIBRARIES}
)

# -----------------------------
# Compiler options
# -----------------------------
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
