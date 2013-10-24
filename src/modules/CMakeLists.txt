cmake_minimum_required(VERSION 2.6)
option(BUILD_MODULES "Build the modules" ON)

if(BUILD_MODULES)
    option(MOD_PHYSICS "Build the physics module" ON)

    if(MOD_PHYSICS)
        project(SGM-Physics)

        find_package(Chipmunk REQUIRED)
        include_directories(${CHIPMUNK_INCLUDE_DIR})

        file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES physics/*.c)
        add_library(${PROJECT_NAME} MODULE ${${PROJECT_NAME}_SOURCES})
        target_link_libraries(${PROJECT_NAME} ${CHIPMUNK_LIBRARY})
        set_target_properties(${PROJECT_NAME} PROPERTIES ENABLE_EXPORTS ON)

        install(TARGETS ${PROJECT_NAME} DESTINATION lib)
    endif()
endif(BUILD_MODULES)
