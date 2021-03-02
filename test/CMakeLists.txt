file(GLOB TEST_SRC_FILES "*.cpp")

add_executable(test ${TEST_SRC_FILES} catch/catch_amalgamated.cpp)
target_include_directories(test PUBLIC catch)