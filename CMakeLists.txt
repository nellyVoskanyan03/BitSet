cmake_minimum_required(VERSION 3.14)
project(BitSet)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# Add executable
add_executable(
	main
	src/main.cpp
)

set (gtest_force_shared_crt ON CACHE BOOL "MSVC defaults to shared CRT" FORCE)
add_subdirectory(test/googletest)
target_compile_definitions(
	gtest
    PUBLIC
    GTEST_LANG_CXX20
    GTEST_HAS_TR1_TUPLE=0
)

add_executable(
	tests
	test/bitsetTest.cpp
)

target_link_libraries(tests PRIVATE gtest gtest_main)