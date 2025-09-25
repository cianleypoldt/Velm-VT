#add_library(VlemVT "")
add_subdirectory(core)
add_subdirectory(io)
add_subdirectory(processing)
add_subdirectory(render)

# Export include path for installation
target_include_directories(VlemVT PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
