# Find the MKL libraries
#
# Options:
#
#   MKL_USE_SINGLE_DYNAMIC_LIBRARY  : use single dynamic library interface
#   MKL_USE_STATIC_LIBS             : use static libraries
#   MKL_MULTI_THREADED              : use multi-threading
#
# This module defines the following variables:
#
#   MKL_FOUND            : True mkl is found
#   MKL_INCLUDE_DIR      : unclude directory
#   MKL_LIBRARIES        : the libraries to link against.

########################################################################################################
# An option that the user can select. Can accept condition to control when option is available for user.
# Usage:
#   caffe_option(<option_variable> "doc string" <initial value or boolean expression> [IF <condition>])
function(caffe_option variable description value)
  set(__value ${value})
  set(__condition "")
  set(__varname "__value")
  foreach(arg ${ARGN})
    if(arg STREQUAL "IF" OR arg STREQUAL "if")
      set(__varname "__condition")
    else()
      list(APPEND ${__varname} ${arg})
    endif()
  endforeach()
  unset(__varname)
  if("${__condition}" STREQUAL "")
    set(__condition 2 GREATER 1)
  endif()

  if(${__condition})
    if("${__value}" MATCHES ";")
      if(${__value})
        option(${variable} "${description}" ON)
      else()
        option(${variable} "${description}" OFF)
      endif()
    elseif(DEFINED ${__value})
      if(${__value})
        option(${variable} "${description}" ON)
      else()
        option(${variable} "${description}" OFF)
      endif()
    else()
      option(${variable} "${description}" ${__value})
    endif()
  else()
    unset(${variable} CACHE)
  endif()
endfunction()

# Clears variables from list
# Usage:
#   caffe_clear_vars(<variables_list>)
macro(caffe_clear_vars)
  foreach(_var ${ARGN})
    unset(${_var})
  endforeach()
endmacro()

# ---[ Options
caffe_option(MKL_USE_SINGLE_DYNAMIC_LIBRARY "Use single dynamic library interface" ON)
caffe_option(MKL_USE_STATIC_LIBS "Use static libraries" OFF IF NOT MKL_USE_SINGLE_DYNAMIC_LIBRARY)
caffe_option(MKL_MULTI_THREADED  "Use multi-threading"   ON IF NOT MKL_USE_SINGLE_DYNAMIC_LIBRARY)

# ---[ Root folders
set(INTEL_ROOT "/opt/intel" CACHE PATH "Folder contains intel libs")
find_path(MKL_ROOT include/mkl.h PATHS $ENV{MKLROOT} ${INTEL_ROOT}/mkl
                                   DOC "Folder contains MKL")

# ---[ Find include dir
find_path(MKL_INCLUDE_DIR mkl.h PATHS ${MKL_ROOT} PATH_SUFFIXES include)
set(__looked_for MKL_INCLUDE_DIR)

# ---[ Find libraries
if(CMAKE_SIZEOF_VOID_P EQUAL 4)
  set(__path_suffixes lib lib/ia32)
else()
  set(__path_suffixes lib lib/intel64)
endif()

set(__mkl_libs "")
if(MKL_USE_SINGLE_DYNAMIC_LIBRARY)
  list(APPEND __mkl_libs rt)
else()
  if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    if(WIN32)
      list(APPEND __mkl_libs intel_c)
    else()
      list(APPEND __mkl_libs intel gf)
    endif()
  else()
    list(APPEND __mkl_libs intel_lp64 gf_lp64)
  endif()

  if(MKL_MULTI_THREADED)
    list(APPEND __mkl_libs intel_thread)
  else()
     list(APPEND __mkl_libs sequential)
  endif()

  list(APPEND __mkl_libs core cdft_core)
endif()


foreach (__lib ${__mkl_libs})
  set(__mkl_lib "mkl_${__lib}")
  string(TOUPPER ${__mkl_lib} __mkl_lib_upper)

  if(MKL_USE_STATIC_LIBS)
    set(__mkl_lib "lib${__mkl_lib}.a")
  endif()

  find_library(${__mkl_lib_upper}_LIBRARY
        NAMES ${__mkl_lib}
        PATHS ${MKL_ROOT} "${MKL_INCLUDE_DIR}/.."
        PATH_SUFFIXES ${__path_suffixes}
        DOC "The path to Intel(R) MKL ${__mkl_lib} library")
  mark_as_advanced(${__mkl_lib_upper}_LIBRARY)

  list(APPEND __looked_for ${__mkl_lib_upper}_LIBRARY)
  list(APPEND MKL_LIBRARIES ${${__mkl_lib_upper}_LIBRARY})
endforeach()


if(NOT MKL_USE_SINGLE_DYNAMIC_LIBRARY)
  if (MKL_USE_STATIC_LIBS)
    set(__iomp5_libs iomp5 libiomp5mt.lib)
  else()
    set(__iomp5_libs iomp5 libiomp5md.lib)
  endif()

  if(WIN32)
    find_path(INTEL_INCLUDE_DIR omp.h PATHS ${INTEL_ROOT} PATH_SUFFIXES include)
    list(APPEND __looked_for INTEL_INCLUDE_DIR)
  endif()

  find_library(MKL_RTL_LIBRARY ${__iomp5_libs}
     PATHS ${INTEL_RTL_ROOT} ${INTEL_ROOT}/compiler ${MKL_ROOT}/.. ${MKL_ROOT}/../compiler
     PATH_SUFFIXES ${__path_suffixes}
     DOC "Path to Path to OpenMP runtime library")

  list(APPEND __looked_for MKL_RTL_LIBRARY)
  list(APPEND MKL_LIBRARIES ${MKL_RTL_LIBRARY})
endif()


include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MKL DEFAULT_MSG ${__looked_for})

if(MKL_FOUND)
  message(STATUS "Found MKL (include: ${MKL_INCLUDE_DIR}, lib: ${MKL_LIBRARIES}")
endif()

caffe_clear_vars(__looked_for __mkl_libs __path_suffixes __lib_suffix __iomp5_libs)
