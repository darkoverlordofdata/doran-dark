cmake_minimum_required ( VERSION 3.1 )
#########################################################################################
#
#   Library: Dark.Framework
#
#########################################################################################
project ( dark VERSION 0.1.0 )

# Includes: 
list ( APPEND INCLUDE .lib/dark/include )
list ( APPEND INCLUDE .lib/dark/src/vendor )


# C Sources:
list ( APPEND CSOURCE .lib/dark/src/runtime/hashmap.c )
list ( APPEND CSOURCE .lib/dark/src/runtime/runtime.c )
list ( APPEND CSOURCE .lib/dark/src/runtime/objc-cache.c )
list ( APPEND CSOURCE .lib/dark/src/runtime/objc-class.c )
list ( APPEND CSOURCE .lib/dark/src/core.c )
list ( APPEND CSOURCE .lib/dark/src/string.c )
list ( APPEND CSOURCE .lib/dark/src/printf.c )
list ( APPEND CSOURCE .lib/dark/src/DSClass.c )
list ( APPEND CSOURCE .lib/dark/src/DSObject.c )
list ( APPEND CSOURCE .lib/dark/src/DSComparable.c )
# list ( APPEND CSOURCE .lib/dark/src/collections/DSCollection.c )
list ( APPEND CSOURCE .lib/dark/src/collections/DSArray.c )
list ( APPEND CSOURCE .lib/dark/src/collections/DSHashmap.c )
list ( APPEND CSOURCE .lib/dark/src/collections/DSList.c )

# list ( APPEND CSOURCE .lib/dark/src/io/DSFileSystem.c )
# list ( APPEND CSOURCE .lib/dark/src/io/DSFile.c )

list ( APPEND CSOURCE .lib/dark/src/types/DSBoolean.c )
list ( APPEND CSOURCE .lib/dark/src/types/DSNumber.c )
list ( APPEND CSOURCE .lib/dark/src/types/DSChar.c )
list ( APPEND CSOURCE .lib/dark/src/types/DSDouble.c )
list ( APPEND CSOURCE .lib/dark/src/types/DSFloat.c )
list ( APPEND CSOURCE .lib/dark/src/types/DSInteger.c )
list ( APPEND CSOURCE .lib/dark/src/types/DSLong.c )
list ( APPEND CSOURCE .lib/dark/src/types/DSShort.c )
list ( APPEND CSOURCE .lib/dark/src/types/DSString.c )
list ( APPEND CSOURCE .lib/dark/src/types/DSStringBuilder.c )
list ( APPEND CSOURCE .lib/dark/src/Functional/Either.c )
list ( APPEND CSOURCE .lib/dark/src/Functional/Option.c )
list ( APPEND CSOURCE .lib/dark/src/Functional/Maybe.c )

# Vala Sources:

# Vapis:
list ( APPEND VAPI .lib/dark/src/dark.vapi )

# Vapidir:

## Export to the parent scope:
set ( DARK true PARENT_SCOPE )
set ( INCLUDES "${INCLUDES}; ${INCLUDE}" PARENT_SCOPE )
set ( C_SOURCES "${C_SOURCES};${CSOURCE}" PARENT_SCOPE )
set ( DEPS_LIBRARIES "${DEPS_LIBRARIES};-lgc" PARENT_SCOPE)

set ( CUSTOM_VAPIS "${CUSTOM_VAPIS};${VAPI}" PARENT_SCOPE )



