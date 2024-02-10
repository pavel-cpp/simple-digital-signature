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
        hash-calculator/hash_calculator.cpp
        io-tools/io_tools.cpp
        testing/testing.h
        key-sing-manager/key_sign_manager.cpp
)
