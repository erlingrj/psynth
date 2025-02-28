cmake_minimum_required(VERSION 3.22)

if(NOT DEFINED ENV{FP_SDK_PATH})
  message(FATAL_ERROR "FP_SDK_PATH environment variable not set!")
endif()

include($ENV{FP_SDK_PATH}/cmake/riscv-toolchain.cmake)
include($ENV{FP_SDK_PATH}/cmake/fp-app.cmake)

project(tacl)

set(TARGET_NAME fp-tacl)
file(GLOB SOURCES "*.c")
message(STATUS "SOURCES: ${SOURCES}") 
add_executable(${TARGET_NAME} ${SOURCES})
add_subdirectory($ENV{FP_SDK_PATH} BINARY_DIR)
target_link_libraries(${TARGET_NAME} PRIVATE fp-sdk)

fp_add_outputs(${TARGET_NAME})