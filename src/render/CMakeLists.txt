target_sources(VlemVT PRIVATE
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

target_include_directories(VlemVT PRIVATE
    ${PROJECT_SOURCE_DIR}/third_party/glad/include
    ${GLFW_INCLUDE_DIRS}
)

target_link_libraries(VlemVT PRIVATE glad ${GLFW_LIBRARIES})
