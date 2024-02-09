cmake_minimum_required(VERSION 3.27)
project(digital-signature)

set(CMAKE_CXX_STANDARD 17)

file(GLOB HEADER_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} */)
foreach(HEADER_DIR ${HEADER_DIRS})
    file(GLOB_RECURSE HEADERS ${HEADER_DIR}/*.h)
    if(HEADERS)
        include_directories(${HEADER_DIR})
    endif()
endforeach()


add_executable(
        ${PROJECT_NAME}
        main.cpp
        file-hasher/file_hasher.cpp
        file-reader/file_reader.cpp
        cryptographic-hash/cryptographic_hash.cpp
        cryptographic-provider/cryptographic_provider.cpp
        file-hash-calculator/file_hash_calculator.cpp
        file-hash-calculator/file_hash_calculator.h
        file-hash-calculator/file_hash_calculator.cpp
)
