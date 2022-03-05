cmake_minimum_required(VERSION 3.14)
project(sd-shell)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/command/cat_command.cpp"
              "${CMAKE_CURRENT_SOURCE_DIR}/src/command/command_factory.cpp"
              "${CMAKE_CURRENT_SOURCE_DIR}/src/command/echo_command.cpp"
              "${CMAKE_CURRENT_SOURCE_DIR}/src/command/exit_command.cpp"
              "${CMAKE_CURRENT_SOURCE_DIR}/src/command/external_command.cpp"
              "${CMAKE_CURRENT_SOURCE_DIR}/src/command/pwd_command.cpp"
              "${CMAKE_CURRENT_SOURCE_DIR}/src/command/wc_command.cpp"
              "${CMAKE_CURRENT_SOURCE_DIR}/src/expander/expander.cpp"
              "${CMAKE_CURRENT_SOURCE_DIR}/src/parser/parser.cpp"
              "${CMAKE_CURRENT_SOURCE_DIR}/src/runner/runner.cpp"
              "${CMAKE_CURRENT_SOURCE_DIR}/src/tokenizer/tokenizer.cpp")
set(TEST_SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/test/catch/catch_amalgamated.cpp"
                   "${CMAKE_CURRENT_SOURCE_DIR}/test/command_test.cpp"
                   "${CMAKE_CURRENT_SOURCE_DIR}/test/expander_test.cpp"
                   "${CMAKE_CURRENT_SOURCE_DIR}/test/main.cpp"
                   "${CMAKE_CURRENT_SOURCE_DIR}/test/tokenizer_test.cpp")

add_subdirectory(src)
add_subdirectory(test)