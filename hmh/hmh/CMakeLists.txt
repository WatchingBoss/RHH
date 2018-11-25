# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("like_handmadehero")

include_directories( ${PROJECT_SOURCE_DIR}/inc )

file ( GLOB PROJ_SRCS ${PROJECT_SOURCE_DIR}/src/*.cpp )
file( GLOB PROJ_INCS ${PROJECT_SOURCE_DIR}/inc/*.h )

source_group( "Source" FILES {PROJ_SRCS} )
source_group( "Header" FILES {PROJ_INCS} )

if( MSVC )
add_executable( ${PROJECT_NAME} WIN32 ${PROJ_SRCS} ${PROJ_INCS} )
endif( MSVC )
