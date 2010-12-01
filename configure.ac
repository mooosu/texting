AC_INIT([ztexting], [1.0], [ztexting@hellom2.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CXX
AC_PROG_RANLIB
AC_CONFIG_FILES([
                 Makefile
                 src/Makefile
                 test/Makefile
                 ])

# Pre-defined macro to set opt build mode. Run with --disable-shared option to turn off optimization.
FB_ENABLE_DEFAULT_OPT_BUILD

# Predefined macro to set static library mode. Run with --disable-static option to turn off static lib mode.

FB_ENABLE_DEFAULT_STATIC
AX_BOOST_BASE([1.4])
AX_BOOST_UNIT_TEST_FRAMEWORK



AC_OUTPUT

