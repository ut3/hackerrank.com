#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([hackerrank], [1], [rick.ramstetter@gmail.tld])
AM_INIT_AUTOMAKE

AC_CONFIG_HEADERS([config.h])

CXXFLAGS="$CXXFLAGS -std=c++14"
# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdint.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_UINT16_T
AC_TYPE_INT16_T
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([strerror])

AC_CONFIG_FILES(m4_esyscmd([find .  -type f -iname 'Makefile.am' -print | sed -e 's:Makefile\.am:Makefile:' -e 's:^./::' | sort]))
AC_OUTPUT
