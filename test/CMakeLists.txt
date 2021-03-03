file(GLOB_RECURSE TEST_SRC_FILES "*.cpp")

add_executable(test ${TEST_SRC_FILES} ${SRC_FILES})
target_include_directories(test PUBLIC catch)