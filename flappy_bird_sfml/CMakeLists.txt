cmake_minimum_required (VERSION 3.6)

project (flappy)

# Specify compile configuration
set( CMAKE_BUILD_TYPE Debug )

# Required libraries
find_package(OpenGL REQUIRED)

# Compiler flags
if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic")
endif()

# Including third part libraries' headers
## Set path to variable
if(WIN32)
  set (THIRD_PART_LIBS "D:/Documents/libs/third_part_libs")
else()
  set (THIRD_PART_LIBS "/media/ubu/data/Documents/libs/third_part_libs")
endif()
## Include
include_directories (${THIRD_PART_LIBS})

# SFML
if(MSVC)
## Set path to SFMLconfig.cmake file
set( SFML_DIR "${THIRD_PART_LIBS}/SFML/lib/cmake/SFML" )
## Winodws - static library, Linux - dynamic library
set( SFML_STATIC_LIBRARIES TRUE	)
endif()
## Add SFML required components
find_package(SFML 2 COMPONENTS network audio graphics window system REQUIRED)
if(SFML_FOUND)
set( SFML_LINKS	"sfml-graphics"	"sfml-window" "sfml-system")
endif()

# Groups
file(GLOB PROJECT_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB PROJECT_HEADERS ${PROJECT_SOURCE_DIR}/inc/*.hpp ${PROJECT_SOURCE_DIR}/inc/*.h)
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Headers" FILES ${PROJECT_HEADERS})

# Compile and link
add_executable ( ${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS} )
## Specify standard
set_property( TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17 )

target_link_libraries ( ${PROJECT_NAME} ${SFML_LINKS} )

# Copy media FILES
if(MSVC)
file( COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/	DESTINATION	${CMAKE_CURRENT_BINARY_DIR}/../res)
endif()
