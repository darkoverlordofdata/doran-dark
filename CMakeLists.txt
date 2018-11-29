cmake_minimum_required ( VERSION 3.1 )
#########################################################################################
#
#   Library: Dark.Framework
#
#########################################################################################
project ( dark VERSION 0.1.0 )

# Includes: 
list ( APPEND INCLUDE .lib/dark/include )
list ( APPEND INCLUDE .lib/dark/vendor/tgc )


# C Sources:
list ( APPEND CSOURCE .lib/dark/vendor/tgc/tgc.c )
list ( APPEND CSOURCE .lib/dark/src/gc.c )
list ( APPEND CSOURCE .lib/dark/src/string.c )
list ( APPEND CSOURCE .lib/dark/src/Comparable.c )
list ( APPEND CSOURCE .lib/dark/src/DObject.c )
list ( APPEND CSOURCE .lib/dark/src/collections/Hashmap.c )
list ( APPEND CSOURCE .lib/dark/src/collections/List.c )
list ( APPEND CSOURCE .lib/dark/src/collections/Vector.c )
list ( APPEND CSOURCE .lib/dark/src/io/FileSystem.c )
list ( APPEND CSOURCE .lib/dark/src/io/File.c )
list ( APPEND CSOURCE .lib/dark/src/types/Boolean.c )
list ( APPEND CSOURCE .lib/dark/src/types/Number.c )
list ( APPEND CSOURCE .lib/dark/src/types/Char.c )
list ( APPEND CSOURCE .lib/dark/src/types/Double.c )
list ( APPEND CSOURCE .lib/dark/src/types/Float.c )
list ( APPEND CSOURCE .lib/dark/src/types/Integer.c )
list ( APPEND CSOURCE .lib/dark/src/types/Long.c )
list ( APPEND CSOURCE .lib/dark/src/types/Short.c )
list ( APPEND CSOURCE .lib/dark/src/types/String.c )
list ( APPEND CSOURCE .lib/dark/src/types/StringBuilder.c )

# Vala Sources:

# Vapis:
list ( APPEND VAPI .lib/dark/src/dark.vapi )

# Vapidir:

## Export to the parent scope:
set ( DARK true PARENT_SCOPE )
set ( INCLUDES "${INCLUDES}; ${INCLUDE}" PARENT_SCOPE )
set ( C_SOURCES "${C_SOURCES};${CSOURCE}" PARENT_SCOPE )

set ( CUSTOM_VAPIS "${CUSTOM_VAPIS};${VAPI}" PARENT_SCOPE )



