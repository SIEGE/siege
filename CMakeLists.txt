CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

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

PROJECT(SIEGE)

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

INCLUDE(InstallRequiredSystemLibraries)

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Simple Interplatform Entity Game Engine")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/readme.txt")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/license.txt")
SET(CPACK_PACKAGE_VENDOR "SIEGE development team")
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "1")
SET(CPACK_PACKAGE_VERSION_PATCH "7")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "libSIEGE")

INCLUDE(CPack)

ADD_SUBDIRECTORY(src)
