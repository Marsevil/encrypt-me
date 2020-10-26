cmake_minimum_required(VERSION 3.0)
project(encrypt-me)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)

set(SRCS
	main.cpp
)

set(HDRS

)

add_executable(main ${HDRS} ${SRCS})

target_compile_options(main PUBLIC "-Wall")
