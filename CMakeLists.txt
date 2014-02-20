
project(LIBALTAR C)
cmake_minimum_required(VERSION 2.8)

set(LIBALTAR_VERSION_MAJOR 1)
set(LIBALTAR_VERSION_MINOR 0)

set(PACKAGE_NAME libaltar)
set(PACKAGE_VERSION "${LIBALTAR_VERSION_MAJOR}.${LIBALTAR_VERSION_MINOR}")
set(PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")
set(PACKAGE_BUGREPORT "http://github.com/acolyte-sf/libaltar/issues")

set(LIBALTAR_HEADERS_DIR "${PROJECT_SOURCE_DIR}/include")
set(LIBALTAR_SRC_DIR "${PROJECT_SOURCE_DIR}/src")

if("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
  add_definitions(-Wall -Wextra -pedantic)
endif()

include_directories("${LIBALTAR_HEADERS_DIR}")

add_subdirectory("${LIBALTAR_HEADERS_DIR}")
add_subdirectory("${LIBALTAR_SRC_DIR}")

add_library(libaltar ${LIBALTAR_SRC_FILES} ${LIBALTAR_HEADER_FILES})

