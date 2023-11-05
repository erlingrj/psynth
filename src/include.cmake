target_link_libraries(${LF_MAIN_TARGET} PRIVATE pulse-simple)
target_link_libraries(${LF_MAIN_TARGET}  ${CMAKE_CURRENT_SOURCE_DIR}/libkissfft-float.a)
target_sources(${LF_MAIN_TARGET} PRIVATE freq.c buffer.c midi.c)