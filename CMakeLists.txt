CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(SG_VERSION_MAJOR "0")
SET(SG_VERSION_MINOR "1")
SET(SG_VERSION_PATCH "20")

#ADD_DEFINITIONS(
#    "-DSG_VERSION_MAJOR=${SG_VERSION_MAJOR}"
#    "-DSG_VERSION_MINOR=${SG_VERSION_MINOR}
#    "-DSG_VERSION_PATCH=${SG_VERSION_PATCH}"
#    )

IF(${CMAKE_SOURCE_DIR} MATCHES ${CMAKE_BINARY_DIR})
    MESSAGE(FATAL_ERROR "In-source builds are not supported. Please delete the CMakeCache.txt file and the CMakeFiles directory and try building out-of-source:\n\tmkdir build && cd build && cmake ..")
ENDIF(${CMAKE_SOURCE_DIR} MATCHES ${CMAKE_BINARY_DIR})

MACRO(CONFIGURE_FILES srcDir destDir)
    MAKE_DIRECTORY(${destDir})

    FILE(GLOB files RELATIVE ${srcDir} ${srcDir}/*)
    FOREACH(file ${files})
        SET(srcPath ${srcDir}/${file})
        SET(destPath ${destDir}/${file})

        IF(NOT IS_DIRECTORY ${srcPath})
            CONFIGURE_FILE(${srcPath} ${destPath} COPYONLY)
        ELSE(NOT IS_DIRECTORY ${srcPath})
            CONFIGURE_FILES(${srcPath} ${destPath})
        ENDIF(NOT IS_DIRECTORY ${srcPath})
    ENDFOREACH(file)
ENDMACRO(CONFIGURE_FILES)

MACRO(INSTALL_DIR srcDir destDir)
    FILE(GLOB files RELATIVE ${srcDir} ${srcDir}/*)
    FOREACH(file ${files})
        SET(srcPath ${srcDir}/${file})
        SET(destPath ${destDir}/${file})

        IF(NOT IS_DIRECTORY ${srcPath})
            INSTALL(FILES "${srcPath}" DESTINATION "${destDir}")
        ELSE(NOT IS_DIRECTORY ${srcPath})
            INSTALL_DIR("${srcPath}" "${destPath}")
        ENDIF(NOT IS_DIRECTORY ${srcPath})
    ENDFOREACH(file)
ENDMACRO(INSTALL_DIR)

#IF(CYGWIN) # should we have a separate target for cygwin?
    #SET(OS cygwin)
IF(WIN32) # also true when on cygwin
    SET(OS windows)
ELSEIF(APPLE)
    SET(OS darwin)
ELSEIF(UNIX) # note: has to be last as UNIX is true for APPLE and CYGWIN
    SET(OS linux)
ELSE(WIN32)
    SET(OS unknown)
    MESSAGE(WARNING "Unknown platform!")
ENDIF(WIN32)
SET(ARCH ${CMAKE_SYSTEM_PROCESSOR})

CONFIGURE_FILES("${CMAKE_SOURCE_DIR}/data" "${CMAKE_BINARY_DIR}/data")
INSTALL_DIR("${CMAKE_SOURCE_DIR}/data" data)
INSTALL_DIR("${CMAKE_SOURCE_DIR}/include" include)

INCLUDE(InstallRequiredSystemLibraries)

PROJECT(SIEGE)

#SET(CPACK_PACKAGE_NAME "SIEGE")
SET(CPACK_PACKAGE_VENDOR "SIEGE development team")
SET(CPACK_PACKAGE_VERSION_MAJOR ${SG_VERSION_MAJOR})
SET(CPACK_PACKAGE_VERSION_MINOR ${SG_VERSION_MINOR})
SET(CPACK_PACKAGE_VERSION_PATCH ${SG_VERSION_PATCH})
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Simple Interplatform Entity Game Engine")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README.txt")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING.txt")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "libSIEGE")
SET(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "libSIEGE")
SET(CPACK_SOURCE_IGNORE_FILES "build;.git;.gitignore")

SET(CPACK_INSTALL_CMAKE_PROJECTS "${CMAKE_BINARY_DIR};SIEGE;ALL;/")

INCLUDE(CPack)

ADD_SUBDIRECTORY(src)
