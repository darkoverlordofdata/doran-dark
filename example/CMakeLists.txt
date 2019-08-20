cmake_minimum_required ( VERSION 3.1 )
###################################################################################
#
#   Build example
#
###################################################################################
project ( example VERSION 0.0.1 )

#
set ( VERSION 0.0.1 )
set ( RELEASE_NAME example )

#
# enable features
#
include ( CMakeToolsHelpers OPTIONAL )

#
#   libraries - sources & packages
#
add_subdirectory ( .lib/dark )
if (EXISTS ${CMAKE_SOURCE_DIR}/data AND NOT DEFINED ZEROG )
    add_subdirectory (data)
    list ( APPEND RESOURCES ${resources_gresource_xml_C_FILE} )
endif ()

#
#   application source
#

list ( APPEND C_SOURCES src/Boot.c )
list ( APPEND C_SOURCES src/main.c )
list ( APPEND C_SOURCES src/stb.c )
#
#   application includes
#
set ( INCLUDES "${INCLUDES};/home/darkoverlordofdata/Documents/GitHub/daran-dark/include" )
set ( INCLUDES "${INCLUDES};./include" )
set ( INCLUDES "${INCLUDES};./vendor" )


#
#   compiler options
#
# Libs: 
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lglfw3" )
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lglew32" )
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lfreetype" )
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lopengl32" )
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lm" )
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lBlocksRuntime" )
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lgc" )

set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fblocks" )

set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w -std=c11 -O3" )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -std=c++17 -O3" )


# definitions 

# links folders 

include_directories(AFTER ${INCLUDES})

#
#   compile ccode & link executable
#
add_executable ( ${PROJECT_NAME} ${C_SOURCES} ${RESOURCES} )
add_custom_command(TARGET ${PROJECT_NAME} 
                   POST_BUILD COMMAND 
                   ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> .. )
target_link_libraries ( ${PROJECT_NAME} glfw3 glew32 freetype opengl32 m BlocksRuntime gc  )
install (TARGETS ${PROJECT_NAME} RUNTIME DESTINATION . )

include (CPack)

# (generated from template: c. Do not modify. )
