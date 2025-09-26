file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS *.cpp)

add_executable(${PROJECT_NAME}_tests.exe ${TEST_SOURCES})

target_link_libraries(${PROJECT_NAME}_tests.exe PRIVATE ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME}_tests.exe PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
