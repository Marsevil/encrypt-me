cmake_minimum_required(VERSION 3.0)
project(encrypt-me)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)

set(SRCS
	sources/main.cpp
    sources/FileCryptor.cpp
	sources/ConfigReader.cpp
	sources/DirectoryCryptor.cpp
	sources/Cryptor.cpp
	# Tests
		tests/CryptorTest.hpp
        tests/ConfigReaderTest.hpp
)

set(HDRS
    sources/FileCryptor.hpp
	sources/ConfigReader.hpp
	sources/DirectoryCryptor.hpp
	sources/Cryptor.hpp
)

add_executable(main ${HDRS} ${SRCS})

set_property(TARGET main PROPERTY CXX_STANDARD 17)
target_compile_options(main PUBLIC "-Wall")
