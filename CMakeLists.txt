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

# Vala Sources:

# Vapis:
list ( APPEND VAPI .lib/dark/src/dark.vapi )

# Vapidir:

## Export to the parent scope:
set ( DARK true PARENT_SCOPE )
set ( INCLUDES "${INCLUDES}; ${INCLUDE}" PARENT_SCOPE )
set ( C_SOURCES "${C_SOURCES};${CSOURCE}" PARENT_SCOPE )
set ( DEPS_LIBRARIES "${DEPS_LIBRARIES};-lgc" PARENT_SCOPE)




