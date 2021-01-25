cmake_minimum_required(VERSION 3.0)
project(lib_encrypt-me)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)

set(SRCS
		sources/Controller.cpp
		sources/Applyer.cpp
		sources/CryptMan.cpp
)

set(HDRS
		sources/Controller.hpp
		sources/Tuple.hpp
		sources/Applyer.hpp
		sources/CryptMan.hpp
		sources/View.hpp
)

add_library(encrypt-me ${HDRS} ${SRCS})

set_property(TARGET encrypt-me PROPERTY CXX_STANDARD 17)
target_compile_options(encrypt-me PUBLIC "-Wall")
