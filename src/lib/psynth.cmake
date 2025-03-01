target_link_libraries(${LF_MAIN_TARGET} PRIVATE pulse-simple)
target_link_libraries(${LF_MAIN_TARGET} PRIVATE m)
target_link_libraries(${LF_MAIN_TARGET} PRIVATE curses)
target_link_libraries(${LF_MAIN_TARGET} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../../external/kissfft/libkissfft-float.a)
target_include_directories(${LF_MAIN_TARGET} PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(${LF_MAIN_TARGET} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../../external/kissfft)

target_sources(${LF_MAIN_TARGET} PRIVATE 
  ${CMAKE_CURRENT_LIST_DIR}/freq.c
  ${CMAKE_CURRENT_LIST_DIR}/buffer.c 
  ${CMAKE_CURRENT_LIST_DIR}/midi.c
  )