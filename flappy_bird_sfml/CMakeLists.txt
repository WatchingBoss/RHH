cmake_minimum_required (VERSION 3.6)

project (flappy)

set( CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)

find_package(OpenGL REQUIRED)

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic")
endif()

if(WIN32)
  set (THIRD_PART_LIBS "D:/Documents/libs/third_part_libs")
else()
  set (THIRD_PART_LIBS "/media/ubu/data/Documents/libs/third_part_libs")
endif()

# Including headers of third part libraries
include_directories (${THIRD_PART_LIBS})

# SFML
set( SFML_DIR "${THIRD_PART_LIBS}/SFML/lib/cmake/SFML" )
set( SFML_STATIC_LIBRARIES TRUE )
find_package(SFML COMPONENTS network audio graphics window system REQUIRED)
if(SFML_FOUND)
set( SFML_LINKS "sfml-graphics" )
endif()

file(GLOB PROJECT_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB PROJECT_HEADERS ${PROJECT_SOURCE_DIR}/inc/*.hpp)

source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Headers" FILES ${PROJECT_HEADERS})

add_executable ( ${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS} )
target_link_libraries ( ${PROJECT_NAME} ${SFML_LINKS} )
