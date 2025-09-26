# Try to find GLFW with pkg-config first (works well on Linux and macOS)
find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
    pkg_check_modules(GLFW QUIET glfw3)
endif()

# If pkg-config didn't find GLFW or we're not using pkg-config, try CMake's find_package
if(NOT GLFW_FOUND)
    find_package(glfw3 QUIET)
    if(glfw3_FOUND)
        set(GLFW_FOUND TRUE)
    else()
        # Try with capitalized name as some CMake configs use this
        find_package(GLFW3 QUIET)
        if(GLFW3_FOUND)
            set(GLFW_FOUND TRUE)
        endif()
    endif()
endif()

# Last resort - try to find GLFW directly
if(NOT GLFW_FOUND)
    find_path(GLFW_INCLUDE_DIR NAMES GLFW/glfw3.h
    PATHS
    ${CMAKE_SOURCE_DIR}/third_party/glfw/include
    $ENV{GLFW_DIR}/include
    $ENV{PROGRAMFILES}/GLFW/include
    "C:/Program Files/GLFW/include"
    /usr/include
    /usr/local/include
    /opt/local/include
    /sw/include
  )

    find_library(GLFW_LIBRARY NAMES glfw glfw3 glfw3dll
    PATHS
    ${CMAKE_SOURCE_DIR}/third_party/glfw/lib
    $ENV{GLFW_DIR}/lib
    $ENV{PROGRAMFILES}/GLFW/lib
    "C:/Program Files/GLFW/lib"
    /usr/lib64
    /usr/lib
    /usr/local/lib64
    /usr/local/lib
    /opt/local/lib
    /sw/lib
  )

    if(GLFW_INCLUDE_DIR AND GLFW_LIBRARY)
        set(GLFW_FOUND TRUE)
        set(GLFW_INCLUDE_DIRS ${GLFW_INCLUDE_DIR})
        set(GLFW_LIBRARIES ${GLFW_LIBRARY})
    endif()
endif()

if(NOT GLFW_FOUND)
    message(WARNING "GLFW not found - rendering functionality may be limited")
else()
    message(STATUS "Found GLFW: ${GLFW_LIBRARIES}")
endif()

# Add source files
target_sources(VelmVT PRIVATE dummy.cpp)

# Include GLAD
target_include_directories(VelmVT PRIVATE ${CMAKE_SOURCE_DIR}/third_party/glad/include)

# Link GLFW if found
if(GLFW_FOUND)
    if(TARGET glfw)
        # If GLFW is available as a CMake target
        target_link_libraries(VelmVT PRIVATE glfw)
    else()
        # Otherwise link to the found library and include directories
        target_include_directories(VelmVT PRIVATE ${GLFW_INCLUDE_DIRS})
        target_link_libraries(VelmVT PRIVATE ${GLFW_LIBRARIES})
    endif()
endif()
