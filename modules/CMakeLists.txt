CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

project(SIEGEModules)
#SET(CMAKE_BUILD_TYPE Debug)
include_directories(include)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules/")

set(CPU_64BIT 0)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(CPU_64BIT 1)
endif(CMAKE_SIZEOF_VOID_P EQUAL 8)

if(WIN32) #also true when on cygwin
  if(CPU_64BIT)
    set(BIN_DIR win64)
  else(CPU_64BIT)
    set(BIN_DIR win32)
  endif(CPU_64BIT)
elseif(APPLE)
  message(SEND_ERROR "TODO")
  set(BIN_DIR apple)

#elseif(CYGWIN) #should we have a separate target for cygwin?

elseif(UNIX) #note: has to be last as UNIX is true for APPLE and CYGWIN
  if(CPU_64BIT)
    set(BIN_DIR amd64)
  else(CPU_64BIT)
    set(BIN_DIR i386)
  endif(CPU_64BIT)
else(WIN32)
  message(FATAL_ERROR "Unknown platform!")
endif(WIN32)

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
