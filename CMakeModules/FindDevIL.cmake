FIND_PATH(DEVIL_INCLUDE_DIR IL)

FIND_LIBRARY(DEVIL_LIBRARY NAMES IL DevIL)
IF(NOT DEVIL_LIBRARY)
    MESSAGE(SEND_ERROR "DevIL not found")
ENDIF(NOT DEVIL_LIBRARY)

IF(DEVIL_INCLUDE_DIR AND DEVIL_LIBRARY)
   SET(DEVIL_FOUND TRUE)
ENDIF(DEVIL_INCLUDE_DIR AND DEVIL_LIBRARY)

IF(DEVIL_FOUND)
   IF (NOT DevIL_FIND_QUIETLY)
      MESSAGE(STATUS "Found DevIL: ${DEVIL_LIBRARY}")
   ENDIF (NOT DevIL_FIND_QUIETLY)
ELSE(DEVIL_FOUND)
   IF (DevIL_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "Could not find DevIL")
   ENDIF (DevIL_FIND_REQUIRED)
ENDIF(DEVIL_FOUND)