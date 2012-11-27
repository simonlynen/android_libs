#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.60)
AC_INIT(casocklib, 0.01, leandro.costa@gmail.com)
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADER([config.h])
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB
AC_PROG_LIBTOOL

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lprotobuf':
AC_CHECK_LIB([protobuf], [main])
# FIXME: Replace `main' with a function in `-lpthread':
AC_CHECK_LIB([pthread], [main])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([arpa/inet.h fcntl.h netdb.h netinet/in.h stdlib.h string.h strings.h sys/ioctl.h sys/socket.h sys/time.h unistd.h sys/syscall.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_HEADER_TIME
AC_STRUCT_TM

# Checks for library functions.
AC_TYPE_SIGNAL
AC_FUNC_STRFTIME
AC_CHECK_FUNCS([alarm bzero gethostbyname gettimeofday localtime_r memset select socket strerror])


# Default directories

DIR_PROTOBUF=/usr/local/protobuf-2.3.0
#DIR_PROTOBUF=/usr/local/protobuf-2.2.0a
DIR_PROTOBUF_LIB_DEFAULT=$DIR_PROTOBUF/lib
DIR_PROTOBUF_INC_DEFAULT=$DIR_PROTOBUF/include

DIR_BOOST=/usr/local/boost_1_42_0
DIR_BOOST_LIB_DEFAULT=$DIR_BOOST/lib
DIR_BOOST_INC_DEFAULT=$DIR_BOOST/include

DIR_GFLAGS=/usr/local/gflags-1.3
DIR_GFLAGS_LIB_DEFAULT=$DIR_GFLAGS/lib
DIR_GFLAGS_INC_DEFAULT=$DIR_GFLAGS/include

DIR_GLOG=/usr/local/glog-0.3.0
DIR_GLOG_LIB_DEFAULT=$DIR_GLOG/lib
DIR_GLOG_INC_DEFAULT=$DIR_GLOG/include

DIR_GTEST=/usr/local/gtest-1.5.0
DIR_GTEST_LIB_DEFAULT=$DIR_GTEST/lib
DIR_GTEST_INC_DEFAULT=$DIR_GTEST/include

DIR_GMOCK=/usr/local/gmock-1.5.0
DIR_GMOCK_LIB_DEFAULT=$DIR_GMOCK/lib
DIR_GMOCK_INC_DEFAULT=$DIR_GMOCK/include


# Tools

# CxxTest (cxxtest.tigris.org)
AC_PATH_PROG([CXXTESTGEN], [cxxtestgen.pl], [cxxtestgen.pl], [/usr/local/cxxtest-3.10.1/cxxtest/cxxtestgen.pl])

DIR_CXXTEST_INC_DEFAULT='/usr/local/cxxtest-3.10.1/cxxtest'
#DIR_CXXTEST_INC_DEFAULT='/usr/include'

# CxxTest code generator flags:
CXXTFLAGS='--error-printer'

#   protoc: Google Protocol Buffers (http://code.google.com/p/protobuf)
AC_PATH_PROG([PROTOC], [protoc], [protoc], [$DIR_PROTOBUF/bin])


# Includes and compiler directives

INCLUDES='-I$(top_srcdir)/src'
#CPPFLAGS='-g -Wall -O -Wno-write-strings -Weffc++ -D_REENTRANT -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC'
#CPPFLAGS='-g -Wall -O -Wno-write-strings -D_REENTRANT -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC'
#CPPFLAGS='-g -O -Wno-write-strings -D_REENTRANT -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC'
CPPFLAGS='-g -Wall -O -Wno-write-strings -D_REENTRANT'
CFLAGS=
CXXFLAGS=


dnl **************************************************************************
dnl Check for the presence of cxxtest headers
dnl **************************************************************************

AC_ARG_WITH(cxxtest-includes,
            AC_HELP_STRING([--with-cxxtest-includes=DIR],
                           [Specify location of cxxtest headers]),
                           [CPPFLAGS="$CPPFLAGS -I$withval"],
                           [CPPFLAGS="$CPPFLAGS -I${DIR_CXXTEST_INC_DEFAULT}"])

dnl **************************************************************************
dnl Check for presence of Google Protocol Buffers libraries and headers
dnl **************************************************************************

AC_ARG_WITH(protobuf-includes,
            AC_HELP_STRING([--with-protobuf-includes=DIR],
                           [Specify location of Google Protocol Buffers headers]),
                           [INCLUDES="$INCLUDES -I$withval"],
                            [INCLUDES="$INCLUDES -I${DIR_PROTOBUF_INC_DEFAULT}"])

AC_ARG_WITH(protobuf-libs,
            AC_HELP_STRING([--with-protobuf-libs=DIR],
                           [Specify location of Google Protocol Buffers libs]),
                           [LIB_PROTOBUF_PATH="$withval"],
                           [LIB_PROTOBUF_PATH="${DIR_PROTOBUF_LIB_DEFAULT}"])

LIBS="$LIBS -L${LIB_PROTOBUF_PATH} -lprotobuf"


dnl **************************************************************************
dnl Check for presence of Boost libraries and headers
dnl **************************************************************************

AC_ARG_WITH(boost-includes,
            AC_HELP_STRING([--with-boost-includes=DIR],
                           [Specify location of Boost headers]),
                           [INCLUDES="$INCLUDES -I$withval"],
                            [INCLUDES="$INCLUDES -I${DIR_BOOST_INC_DEFAULT}"])

AC_ARG_WITH(boost-libs,
            AC_HELP_STRING([--with-boost-libs=DIR],
                           [Specify location of Boost libs]),
                           [LIB_BOOST_PATH="$withval"],
                           [LIB_BOOST_PATH="${DIR_BOOST_LIB_DEFAULT}"])


dnl **************************************************************************
dnl Check for presence of google-gflags libraries and headers
dnl **************************************************************************

AC_ARG_WITH(gflags-includes,
            AC_HELP_STRING([--with-gflags-includes=DIR],
                           [Specify location of google-gflags headers]),
                           [INCLUDES="$INCLUDES -I$withval"],
                            [INCLUDES="$INCLUDES -I${DIR_GFLAGS_INC_DEFAULT}"])

AC_ARG_WITH(gflags-libs,
            AC_HELP_STRING([--with-gflags-libs=DIR],
                           [Specify location of google-gflags libs]),
                           [LIB_GFLAGS_PATH="$withval"],
                           [LIB_GFLAGS_PATH="${DIR_GFLAGS_LIB_DEFAULT}"])

LIBS="$LIBS -L${LIB_GFLAGS_PATH} -lgflags"


dnl **************************************************************************
dnl Check for presence of google-glog libraries and headers
dnl **************************************************************************

AC_ARG_WITH(glog-includes,
            AC_HELP_STRING([--with-glog-includes=DIR],
                           [Specify location of google-glog headers]),
                           [INCLUDES="$INCLUDES -I$withval"],
                            [INCLUDES="$INCLUDES -I${DIR_GLOG_INC_DEFAULT}"])

AC_ARG_WITH(glog-libs,
            AC_HELP_STRING([--with-glog-libs=DIR],
                           [Specify location of google-glog libs]),
                           [LIB_GLOG_PATH="$withval"],
                           [LIB_GLOG_PATH="${DIR_GLOG_LIB_DEFAULT}"])

LIBS="$LIBS -L${LIB_GLOG_PATH} -lglog"


dnl **************************************************************************
dnl Check for presence of Google C++ Testing Framework libraries and headers
dnl **************************************************************************

AC_ARG_WITH(gtest-includes,
            AC_HELP_STRING([--with-gtest-includes=DIR],
                           [Specify location of Boost headers]),
                           [INCLUDES="$INCLUDES -I$withval"],
                            [INCLUDES="$INCLUDES -I${DIR_GTEST_INC_DEFAULT}"])

AC_ARG_WITH(gtest-libs,
            AC_HELP_STRING([--with-gtest-libs=DIR],
                           [Specify location of Boost libs]),
                           [LIB_GTEST_PATH="$withval"],
                           [LIB_GTEST_PATH="${DIR_GTEST_LIB_DEFAULT}"])

LIBS="$LIBS -L${LIB_GTEST_PATH} -lgtest"

dnl **************************************************************************
dnl Check for presence of Google C++ Mocking Framework libraries and headers
dnl **************************************************************************

AC_ARG_WITH(gmock-includes,
            AC_HELP_STRING([--with-gmock-includes=DIR],
                           [Specify location of Boost headers]),
                           [INCLUDES="$INCLUDES -I$withval"],
                            [INCLUDES="$INCLUDES -I${DIR_GMOCK_INC_DEFAULT}"])

AC_ARG_WITH(gmock-libs,
            AC_HELP_STRING([--with-gmock-libs=DIR],
                           [Specify location of Boost libs]),
                           [LIB_GMOCK_PATH="$withval"],
                           [LIB_GMOCK_PATH="${DIR_GMOCK_LIB_DEFAULT}"])

LIBS="$LIBS -L${LIB_GMOCK_PATH} -lgmock"


AC_SUBST(LIB_PROTOBUF_PATH)
AC_SUBST(LIB_BOOST_PATH)
AC_SUBST(LIB_GFLAGS_PATH)
AC_SUBST(LIB_GLOG_PATH)
AC_SUBST(LIB_GTEST_PATH)
AC_SUBST(LIB_GMOCK_PATH)
AC_SUBST(INCLUDES)
AC_SUBST(CXXTFLAGS)

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/casock/Makefile
                 src/casock/proactor/Makefile
                 src/casock/proactor/asio/Makefile
                 src/casock/proactor/asio/base/Makefile
                 src/casock/proactor/asio/client/Makefile
                 src/casock/proactor/asio/server/Makefile
                 src/casock/rpc/Makefile
                 src/casock/rpc/asio/Makefile
                 src/casock/rpc/asio/protobuf/Makefile
                 src/casock/rpc/asio/protobuf/base/Makefile
                 src/casock/rpc/asio/protobuf/client/Makefile
                 src/casock/rpc/asio/protobuf/server/Makefile
                 src/casock/rpc/protobuf/Makefile
                 src/casock/rpc/protobuf/api/Makefile
                 src/casock/rpc/protobuf/base/Makefile
                 src/casock/rpc/protobuf/client/Makefile
                 src/casock/rpc/protobuf/server/Makefile
                 src/casock/rpc/sigio/Makefile
                 src/casock/rpc/sigio/protobuf/Makefile
                 src/casock/rpc/sigio/protobuf/base/Makefile
                 src/casock/rpc/sigio/protobuf/client/Makefile
                 src/casock/rpc/sigio/protobuf/server/Makefile
                 src/casock/sigio/Makefile
                 src/casock/sigio/base/Makefile
                 src/casock/sigio/client/Makefile
                 src/casock/sigio/server/Makefile
                 src/casock/util/Makefile
                 src/examples/Makefile
                 src/examples/ftp/Makefile
                 src/examples/proactor/Makefile
                 src/examples/proactor/asio/Makefile
                 src/examples/proactor/asio/ftp/Makefile
                 src/examples/rpc/Makefile
                 src/examples/rpc/asio/Makefile
                 src/examples/rpc/protobuf/Makefile
                 src/examples/rpc/protobuf/api/Makefile
                 src/examples/rpc/sigio/Makefile
                 src/tests/Makefile
                 src/tests/casock/Makefile
                 src/tests/casock/proactor/Makefile
                 src/tests/casock/proactor/asio/Makefile
                 src/tests/casock/rpc/Makefile
                 src/tests/casock/rpc/asio/Makefile
                 src/tests/casock/rpc/asio/protobuf/Makefile
                 src/tests/casock/rpc/protobuf/Makefile
                 src/tests/casock/rpc/protobuf/api/Makefile
                 src/tests/casock/rpc/protobuf/base/Makefile
                 src/tests/casock/rpc/protobuf/client/Makefile
                 src/tests/casock/util/Makefile
                 src/tests/casock/util/util/Makefile])
AC_OUTPUT
