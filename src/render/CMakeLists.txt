find_package(glfw3 REQUIRED)
target_sources(${PROJECT_NAME} PRIVATE dummy.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
