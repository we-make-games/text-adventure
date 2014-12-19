cmake_minimum_required(VERSION 2.8)
set(EXE_NAME adventure)

if(NOT DEFINED CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Build type")
endif()

project(${EXE_NAME})

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)


find_package(CXX11 REQUIRED)
set(CMAKE_CXX_FLAGS "${CXX11_FLAGS} ${CMAKE_CXX_FLAGS}")


find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
set(ADVENTURE_LIBRARIES ${SDL2_LIBRARY} ${SDL2_MIXER_LIBRARIES} ${SDL2_TTF_LIBRARIES})

find_package(TinyXML REQUIRED)
include_directories(${TINYXML_INCLUDE_DIR})
list(APPEND ADVENTURE_LIBRARIES ${TINYXML_LIBRARIES} )

add_subdirectory(source)

if (CMAKE_VERSION VERSION_GREATER 2.8.5)
  include(FeatureSummary)
  feature_summary(WHAT ALL)
endif ()
