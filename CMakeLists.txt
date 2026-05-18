cmake_minimum_required(VERSION 3.20)

project(lab_6)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
    main.cpp
)

set(HEADERS
    containers/Container.h
    containers/Set.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Wno-write-strings
    -Wno-overloaded-virtual
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${PROJECT_NAME} PRIVATE -g)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -O2)
endif()
