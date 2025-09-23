cmake_minimum_required(VERSION 3.15)
project(Zenoa LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -flto -DNDEBUG")

# Find GLM
find_package(glm REQUIRED)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Recursively gather all .cpp files in src/
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link GLM and OpenGL
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        glm::glm
        OpenGL::GL
)

# Include directories if needed (not required for GLM if using targets)
# target_include_directories(${PROJECT_NAME} PRIVATE src)

# Optionally set warnings and other compile options
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
