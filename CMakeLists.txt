cmake_minimum_required(VERSION 3.10)
project(File_Encryptor)  # Define project name first

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Common sources and headers for both executables
file(GLOB_RECURSE COMMON_SOURCES 
    "src/app/Crypto/Crypto.cpp"
    "src/app/fileHandling/*.cpp"
    "src/app/processes/*.cpp"
)

file(GLOB_RECURSE HEADERS
    "src/app/Crypto/*.hpp"
    "src/app/fileHandling/*.hpp"
    "src/app/processes/*.hpp"
)

# First executable for main.cpp
add_executable(File_Encryptor main.cpp ${COMMON_SOURCES} ${HEADERS})

# Second executable for CryptoMain.cpp
add_executable(Cryption src/app/Crypto/CryptoMain.cpp ${COMMON_SOURCES} ${HEADERS})

# Include directories for both executables
target_include_directories(File_Encryptor PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/app
    ${CMAKE_CURRENT_SOURCE_DIR}/src/app/Crypto/
    ${CMAKE_CURRENT_SOURCE_DIR}/src/app/fileHandling/
    ${CMAKE_CURRENT_SOURCE_DIR}/src/app/processes/
)

target_include_directories(Cryption PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/app
    ${CMAKE_CURRENT_SOURCE_DIR}/src/app/Crypto/
    ${CMAKE_CURRENT_SOURCE_DIR}/src/app/fileHandling/
    ${CMAKE_CURRENT_SOURCE_DIR}/src/app/processes/
)

# Compiler options for both executables
target_compile_options(File_Encryptor PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -O2
)

target_compile_options(Cryption PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -O2
)
