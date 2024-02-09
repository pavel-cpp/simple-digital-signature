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
        file-hasher/file_hasher.h
        file-reader/file_reader.cpp
        file-reader/file_reader.h
        cryptographic-hash/cryptographic_hash.cpp
        cryptographic-hash/cryptographic_hash.h
        cryptographic-provider/cryptographic_provider.cpp
)
