# -----------------------------
# GoogleTest
# -----------------------------
find_package(GTest REQUIRED)

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS *.cpp)

add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES})
target_link_libraries(${PROJECT_NAME}_tests PRIVATE
    ${PROJECT_NAME}
    GTest::GTest
    GTest::Main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_tests)
