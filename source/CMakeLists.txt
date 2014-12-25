# -*-cmake-*-
include_directories(lib engine ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${EXE_NAME} 
  Game.cpp
  Helper.cpp
  Window.cpp
  )
target_link_libraries(${EXE_NAME} ${ADVENTURE_LIBRARIES})
install(TARGETS ${EXE_NAME} DESTINATION bin)
