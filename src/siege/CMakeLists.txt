CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
OPTION(BUILD_SIEGE "Build the SIEGE library" ON)

IF(BUILD_SIEGE)
    IF(BUILD_MONOLITHIC)
        SHARED_STATIC(SIEGE . c)
    ENDIF(BUILD_MONOLITHIC)

    IF(BUILD_SPLIT)
        SHARED_STATIC(SG-Util util c)
        SHARED_STATIC(SG-Modules modules c)

        SHARED_STATIC(SG-AI ai c SG-Util)
        SHARED_STATIC(SG-Audio audio c SG-Util)
        SHARED_STATIC(SG-Graphics graphics c SG-Util)
        SHARED_STATIC(SG-Input input c)
        SHARED_STATIC(SG-Physics physics c SG-Graphics)

        SHARED_STATIC(SG-Core core c SG-Util SG-Graphics SG-Physics)
    ENDIF(BUILD_SPLIT)
ENDIF(BUILD_SIEGE)
