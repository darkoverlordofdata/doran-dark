cmake_minimum_required ( VERSION 3.1 )
###################################################################################
#
#   Build unit
#
###################################################################################
project ( unit VERSION 0.0.1 )

#
set ( VERSION 0.0.1 )
set ( RELEASE_NAME unit )

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

list ( APPEND C_SOURCES src/darkunit.c )
list ( APPEND C_SOURCES src/main.c )
#
#   application includes
#


#
#   compiler options
#
# Libs: 
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lm" )
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lBlocksRuntime" )

set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w -std=c99 -O3" )
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fblocks" )
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -LC:/msys64/mingw64/bin" )

# definitions 

include_directories(AFTER ${INCLUDES})

#
#   compile ccode & link executable
#
add_executable ( ${PROJECT_NAME} ${C_SOURCES} ${RESOURCES} )
add_custom_command(TARGET ${PROJECT_NAME} 
                   POST_BUILD COMMAND 
                   ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> .. )
target_link_libraries ( ${PROJECT_NAME} m BlocksRuntime  )
install (TARGETS ${PROJECT_NAME} RUNTIME DESTINATION . )

include (CPack)

# (generated from template: c. Do not modify. )
