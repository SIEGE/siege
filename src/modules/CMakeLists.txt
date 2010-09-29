CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

OPTION(BUILD_MODULES "Build the modules" ON)

IF(BUILD_MODULES)
    ADD_CUSTOM_TARGET(modules)

    IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
    SET(SG_FNAME_DEBUG ".debug")
    ELSE(CMAKE_BUILD_TYPE STREQUAL "Debug")
    SET(SG_FNAME_DEBUG)
    ENDIF(CMAKE_BUILD_TYPE STREQUAL "Debug")
    SET(SG_FNAME_PREFIX "SGModule-")

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

    SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/modules)
    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/modules)

    ADD_SUBDIRECTORY(SGModule-Chipmunk)
    ADD_SUBDIRECTORY(SGModule-DevIL)
    ADD_SUBDIRECTORY(SGModule-Freetype)
    ADD_SUBDIRECTORY(SGModule-GLFW)
    ADD_SUBDIRECTORY(SGModule-OpenAL)
    ADD_SUBDIRECTORY(SGModule-OpenGL)
    ADD_SUBDIRECTORY(SGModule-SDL)
    ADD_SUBDIRECTORY(SGModule-SndFile)
ENDIF(BUILD_MODULES)
