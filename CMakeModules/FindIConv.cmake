FIND_PATH(ICONV_INCLUDE_DIR iconv.h)

FIND_LIBRARY(ICONV_LIBRARY NAMES iconv)
IF(NOT ICONV_LIBRARY AND NOT UNIX)
    MESSAGE(SEND_ERROR "IConv not found")
ENDIF(NOT ICONV_LIBRARY AND NOT UNIX)

IF(ICONV_INCLUDE_DIR)
	IF(ICONV_LIBRARY)
		SET(ICONV_FOUND TRUE)
	ELSEIF(UNIX)
		SET(ICONV_FOUND TRUE)
		SET(ICONV_LIBRARY "c") # just a "no-op" linkage...
	ENDIF(ICONV_LIBRARY)
ENDIF(ICONV_INCLUDE_DIR)

IF(ICONV_FOUND)
   IF (NOT IConv_FIND_QUIETLY)
      MESSAGE(STATUS "Found IConv: ${ICONV_LIBRARY}")
   ENDIF (NOT IConv_FIND_QUIETLY)
ELSE(ICONV_FOUND)
   IF (IConv_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "Could not find IConv")
   ENDIF (IConv_FIND_REQUIRED)
ENDIF(ICONV_FOUND)
