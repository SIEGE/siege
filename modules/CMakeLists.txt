CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

project(SIEGEModules)
IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
  SET(SG_FNAME_DEBUG ".debug")
ELSE(CMAKE_BUILD_TYPE STREQUAL "Debug")
  SET(SG_FNAME_DEBUG)
ENDIF(CMAKE_BUILD_TYPE STREQUAL "Debug")
SET(SG_FNAME_PREFIX "SGModule-")

include_directories(include)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules/")

#if(CYGWIN) # should we have a separate target for cygwin?
#  set(OS cygwin)
if(WIN32) # also true when on cygwin
  set(OS windows)
elseif(APPLE)
  set(OS darwin)
elseif(UNIX) # note: has to be last as UNIX is true for APPLE and CYGWIN
  set(OS linux)
else(WIN32)
  set(OS unknown)
  message(WARNING "Unknown platform!")
endif(WIN32)
set(ARCH ${CMAKE_SYSTEM_PROCESSOR})

set(BIN_DIR ${OS}-${ARCH})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${BIN_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${BIN_DIR})

add_subdirectory(SGModule-Chipmunk)
add_subdirectory(SGModule-DevIL)
add_subdirectory(SGModule-Freetype)
if(WIN32) # fails on unix -- broken lib
  add_subdirectory(SGModule-GLFW)
endif(WIN32)
add_subdirectory(SGModule-OpenAL)
add_subdirectory(SGModule-OpenGL)
add_subdirectory(SGModule-SDL)
add_subdirectory(SGModule-SndFile)
