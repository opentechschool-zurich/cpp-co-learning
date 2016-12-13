# This module finds an installed Mlpack package.
#
# It sets the following variables:
#  Mlpack_FOUND              - Set to false, or undefined, if lemon isn't found.
#  Mlpack_INCLUDE_DIR        - Mlpack include directory.
#  Mlpack_LIBRARIES          - Mlpack library files
FIND_PATH(Mlpack_INCLUDE_DIR mlpack/core.hpp PATHS /usr/include /usr/local/include ${CMAKE_INCLUDE_PATH} ${CMAKE_PREFIX_PATH}/include $ENV{Mlpack_ROOT}/include ENV CPLUS_INCLUDE_PATH)
FIND_LIBRARY(Mlpack_LIBRARIES
  NAMES mlpack
  PATHS $ENV{Mlpack_ROOT}/src/impex $ENV{Mlpack_ROOT}/lib ENV LD_LIBRARY_PATH ENV LIBRARY_PATH
)

GET_FILENAME_COMPONENT(Mlpack_LIBRARY_PATH ${Mlpack_LIBRARIES} PATH)
SET( Mlpack_LIBRARY_DIR ${Mlpack_LIBRARY_PATH} CACHE PATH "Path to Mlpack library.")

# handle the QUIETLY and REQUIRED arguments and set Mlpack_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Mlpack DEFAULT_MSG Mlpack_LIBRARIES Mlpack_INCLUDE_DIR)

MARK_AS_ADVANCED( Mlpack_INCLUDE_DIR Mlpack_LIBRARIES Mlpack_LIBRARY_DIR )
