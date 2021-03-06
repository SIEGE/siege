CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
OPTION(BUILD_EXAMPLES "Build the examples" ON)
OPTION(INSTALL_EXAMPLES "Install examples and data" OFF)

MACRO(EXAMPLE name)
    STRING(TOLOWER ${name} sname)

    PROJECT(Example-${name} C)
    ADD_DEPENDENCIES(examples ${PROJECT_NAME})

    ADD_EXECUTABLE(${PROJECT_NAME} ${sname})
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} SIEGE.static ${AUX_LIBRARIES})

    IF(INSTALL_EXAMPLES)
        INSTALL(TARGETS ${PROJECT_NAME} DESTINATION bin)
    ENDIF(INSTALL_EXAMPLES)
ENDMACRO(EXAMPLE)

IF(BUILD_EXAMPLES)
    ADD_CUSTOM_TARGET(examples)

    EXAMPLE(AStar)
    EXAMPLE(Audio)
    EXAMPLE(Coldet)
    EXAMPLE(Draw)
    EXAMPLE(Emitter)
    EXAMPLE(GetOpt)
    EXAMPLE(Gradient)
    EXAMPLE(Minimal)
    EXAMPLE(Sprite)
    EXAMPLE(Text)
    EXAMPLE(Physics)
    EXAMPLE(Pyramid)
    EXAMPLE(Shadow)
    EXAMPLE(Demo)
    EXAMPLE(Surface)
    EXAMPLE(Thread)
    EXAMPLE(Directory)
    EXAMPLE(Set)
    EXAMPLE(Atlas)
    EXAMPLE(Timer)
ENDIF(BUILD_EXAMPLES)
