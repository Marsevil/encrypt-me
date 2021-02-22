cmake_minimum_required(VERSION 3.0)
project(lyoko)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)

set(SRCS
	lyoko/sources/main.cpp
	lyoko/sources/ConfigReader.cpp
	lyoko/sources/CommandView.cpp
)

set(HDRS
	lyoko/sources/ConfigReader.hpp
	lyoko/sources/CommandView.hpp
)

add_executable(lyoko ${HDRS} ${SRCS})

set_property(TARGET lyoko PROPERTY CXX_STANDARD 17)
target_compile_options(lyoko PUBLIC "-Wall")

target_include_directories(lyoko PUBLIC "include" BEFORE)
add_subdirectory("includes/lib_encrypt-me")

target_link_libraries(lyoko encrypt-me)
