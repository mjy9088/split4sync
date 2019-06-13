PROJECT ( split4sync )
ADD_EXECUTABLE( s4s main.c )
SET ( CMAKE_INSTALL_PREFIX /usr/local )
INSTALL ( TARGETS s4s DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/ )

enable_testing()
add_test( NAME test1 COMMAND python test/test.py 1 )