CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules/")
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/include")

SET(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
SET(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")

find_package(Threads REQUIRED)
find_package(DL)

find_package(SDL REQUIRED)

include_directories("${SDL_INCLUDE_DIR}")

IF(UNIX)
    SET(AUX_INCLUDES "")
    SET(AUX_LIBRARIES "${DL_LIBRARY}" "m" "rt" ${CMAKE_THREAD_LIBS_INIT})
ELSE(UNIX)
    SET(AUX_INCLUDES "")
    SET(AUX_LIBRARIES "")
ENDIF(UNIX)

SET(AUX_LIBRARIES ${AUX_LIBRARIES} "${SDL_LIBRARY}")

MACRO(SHARED_STATIC name dir ext)
    PROJECT(${name})

    FILE(GLOB_RECURSE ${name}_SOURCES ${dir}/*.${ext})
    ADD_LIBRARY(${name} SHARED ${${name}_SOURCES})
    ADD_LIBRARY(${name}.static STATIC ${${name}_SOURCES})

    TARGET_LINK_LIBRARIES(${name}        ${AUX_LIBRARIES} ${ARGN})
    TARGET_LINK_LIBRARIES(${name}.static ${AUX_LIBRARIES} ${ARGN})

    SET_TARGET_PROPERTIES(${name} ${name}.static PROPERTIES OUTPUT_NAME ${name}
                                                            ENABLE_EXPORTS ON
                                                            VERSION "${SG_VERSION_MAJOR}.${SG_VERSION_MINOR}.${SG_VERSION_PATCH}")

    INSTALL(TARGETS ${name} DESTINATION lib)
    INSTALL(TARGETS ${name}.static DESTINATION lib)
ENDMACRO(SHARED_STATIC)

OPTION(BUILD_MONOLITHIC "Build the monolithic SIEGE build" ON)
OPTION(BUILD_SPLIT "Build the separated SIEGE build" OFF)

ADD_SUBDIRECTORY(siege)
ADD_SUBDIRECTORY(examples)
ADD_SUBDIRECTORY(modules)
