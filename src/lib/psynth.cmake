target_link_libraries(${LF_MAIN_TARGET} PRIVATE m)
target_link_libraries(${LF_MAIN_TARGET} PRIVATE curses)
target_link_libraries(${LF_MAIN_TARGET} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../../external/kissfft/libkissfft-float.a)
target_include_directories(${LF_MAIN_TARGET} PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(${LF_MAIN_TARGET} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../../external/kissfft)

# Update CMAKE_MODULE_PATH to include the directory where the FindSDL2.cmake file is located
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

# Find the SDL2 library using FindSDL2.cmake
find_package(SDL2 REQUIRED)

message(STATUS "SDL2_INCLUDE_DIR: ${SDL2_INCLUDE_DIR}")
message(STATUS "SDL2_LIBRARY: ${SDL2_LIBRARY}")

target_link_libraries(${LF_MAIN_TARGET} PUBLIC ${SDL2_LIBRARY})
target_include_directories(${LF_MAIN_TARGET} PUBLIC ${SDL2_INCLUDE_DIR})


target_sources(${LF_MAIN_TARGET} PRIVATE 
  ${CMAKE_CURRENT_LIST_DIR}/freq.c
  ${CMAKE_CURRENT_LIST_DIR}/buffer.c 
  ${CMAKE_CURRENT_LIST_DIR}/midi.c
  )