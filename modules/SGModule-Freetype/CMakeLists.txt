PROJECT(SGModule-Freetype)

INCLUDE_DIRECTORIES(../include /usr/include/freetype2)
ADD_LIBRARY(SGModule-Freetype MODULE main load)
TARGET_LINK_LIBRARIES(SGModule-Freetype freetype)
SET_TARGET_PROPERTIES(SGModule-Freetype PROPERTIES ENABLE_EXPORTS ON)
