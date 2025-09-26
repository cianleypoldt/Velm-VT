
target_sources(VelmVT PRIVATE dummy.cpp)
target_include_directories(VelmVT PRIVATE ${CMAKE_SOURCE_DIR}/third_party/glad/include)
target_link_libraries(VelmVT PRIVATE glfw)
