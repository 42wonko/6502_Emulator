cmake_minimum_required(VERSION 3.14)
project(my_project)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  hello_test
  src/hello_test.cpp
)
target_link_libraries(
  hello_test
  GTest::gtest_main
)

set(SOURCES_EMU6502
	src/cpu_6502_main.cpp
	src/cpu_6502.cpp
	src/memory.cpp
)

set(SOURCES_EMU6502_TEST
	src/cpu_6502_main_test.cpp
	src/cpu_6502_arithmetic_test.cpp
	src/cpu_6502_logic_test.cpp
	src/cpu_6502_branch_test.cpp
	src/cpu_6502_memory_test.cpp
	src/cpu_6502.cpp
	src/memory.cpp
)

set(HADERS_EMU6502_TEST
	src/cpu_6502_main_test.h
	src/cpu_6502_arithmetic_test.h
	src/cpu_6502_logic_test.h
	src/cpu_6502_branch_test.h
	src/cpu_6502_memory_test.h
	src/cpu_6502.h
	src/memory.h
)

set(HEADERS_EMU6502
	src/cpu_6502.h
	arc/memory.h
)

add_executable(
	cpu_6502_emu ${SOURCES_EMU6502}
)

add_executable(
	cpu_6502_emu_test ${SOURCES_EMU6502_TEST}
)

target_link_libraries(
	cpu_6502_emu_test
	GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)

