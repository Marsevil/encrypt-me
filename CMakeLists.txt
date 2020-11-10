cmake_minimum_required(VERSION 3.0)
project(encrypt-me)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)

set(SRCS
	sources/main.cpp
	sources/Cryptor.cpp
)

set(HDRS
	sources/Cryptor.hpp
)

add_executable(main ${HDRS} ${SRCS})

set_property(TARGET main PROPERTY CXX_STANDARD 17)
target_compile_options(main PUBLIC "-Wall")
