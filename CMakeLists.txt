cmake_minimum_required ( VERSION 3.1 )
#########################################################################################
#
#   Library: Microsoft.Xna.Framework
#
#########################################################################################
project ( dark VERSION 0.1.0 )


list ( APPEND CSOURCE .lib/dark/src/string.c )
list ( APPEND CSOURCE .lib/dark/src/Comparable.c )
list ( APPEND CSOURCE .lib/dark/src/DObject.c )
list ( APPEND CSOURCE .lib/dark/src/collections/Hashmap.c )
list ( APPEND CSOURCE .lib/dark/src/collections/List.c )
list ( APPEND CSOURCE .lib/dark/src/collections/Vector.c )
list ( APPEND CSOURCE .lib/dark/src/types/Number.c )
list ( APPEND CSOURCE .lib/dark/src/types/Long.c )

list ( APPEND VAPI .lib/dark/vapis/dark.vapi )

## Export to the parent scope:

set ( C_SOURCES "${C_SOURCES};${CSOURCE}" PARENT_SCOPE )
set ( INCLUDES "${INCLUDES}; ${CMAKE_SOURCE_DIR}/.lib/dark/include" PARENT_SCOPE )
set ( CUSTOM_VAPIS "${CUSTOM_VAPIS};${VAPI}" PARENT_SCOPE )
