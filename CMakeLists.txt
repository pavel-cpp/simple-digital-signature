cmake_minimum_required(VERSION 3.27)
project(digital-signature)

set(CMAKE_CXX_STANDARD 17)

include_directories(./)


add_executable(
        ${PROJECT_NAME}
        main.cpp
        io-tools/io_tools.cpp
        cryptographic/hash/hash.cpp
        cryptographic/provider/provider.cpp
        file-hash-calculator/file_hash_calculator.cpp
        file-hash-calculator/file_hash_calculator.h
        file-hash-calculator/file_hash_calculator.cpp
        io-tools/io_tools.cpp
        io-tools/io_tools.h
        cryptographic/cryptographic.h
)
