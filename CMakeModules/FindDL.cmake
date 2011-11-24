FIND_PATH(DL_INCLUDE_DIR dlfcn.h)

FIND_LIBRARY(DL_LIBRARY NAMES dl)
#IF(NOT DL_LIBRARY AND (NOT UNIX AND NOT WIN32))
#    MESSAGE(SEND_ERROR "libDL not found")
#ENDIF(NOT DL_LIBRARY AND (NOT UNIX AND NOT WIN32))

IF(DL_INCLUDE_DIR)
	IF(DL_LIBRARY)
		SET(DL_FOUND TRUE)
	ELSEIF(UNIX OR WIN32)
		SET(DL_FOUND TRUE)
		SET(DL_LIBRARY "c") # just a "no-op" linkage...
	ENDIF(DL_LIBRARY)
ENDIF(DL_INCLUDE_DIR)

IF(DL_FOUND)
   IF (NOT DL_FIND_QUIETLY)
      MESSAGE(STATUS "Found DL: ${DL_LIBRARY}")
   ENDIF (NOT DL_FIND_QUIETLY)
ELSE(DL_FOUND)
   IF (DL_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "Could not find DL")
   ENDIF (DL_FIND_REQUIRED)
ENDIF(DL_FOUND)
