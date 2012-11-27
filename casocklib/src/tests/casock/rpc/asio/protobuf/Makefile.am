CXXTSRCS_TEST1  = test1_cxx.cc
CXXSRCS_TEST2		= test2_cxx.cc

CXXTSRCS        = $(CXXTSRCS_TEST1) $(CXXSRCS_TEST2)

SRCS_TEST1      = $(CXXTSRCS_TEST1)
SRCS_TEST2			= $(CXXSRCS_TEST2) Test2Manager.cc Test2ClientThread.cc Test2ResponseHandlerImpl.cc Test2ShutdownResponseHandlerImpl.cc

LIB_UTIL      = $(top_srcdir)/src/casock/util/libcasutil.la
LIB_RPCCLIENT = $(top_srcdir)/src/casock/rpc/asio/protobuf/client/libcasrpcaiopbclient.la
LIB_RPCSERVER = $(top_srcdir)/src/casock/rpc/asio/protobuf/server/libcasrpcaiopbserver.la
#LIB_PROTOBUF  = @LIB_PROTOBUF_PATH@/libprotobuf.a
LIB_RPCTEST1  = $(top_srcdir)/src/tests/casock/rpc/protobuf/api/libcasrpcpbtapi.la

AM_CPPFLAGS = -DUSE_UT_CXXTEST

check_PROGRAMS    = test1_cxx test2_cxx

test1_cxx_SOURCES = $(SRCS_TEST1)
test1_cxx_LDADD   = $(LIB_RPCCLIENT) $(LIB_RPCSERVER) $(LIB_UTIL) $(LIB_RPCTEST1)# $(LIB_PROTOBUF)
test1_cxx_LDFLAGS = -static

test2_cxx_SOURCES = $(SRCS_TEST2)
test2_cxx_LDADD   = $(LIB_RPCCLIENT) $(LIB_RPCSERVER) $(LIB_UTIL) $(LIB_RPCTEST1)# $(LIB_PROTOBUF)
test2_cxx_LDFLAGS = -static

TESTS	= $(check_PROGRAMS)

%_cxx.cc: %_cxx.h
	$(CXXTESTGEN) $(CXXTFLAGS) $< -o $@

CLEANFILES = $(CXXTSRCS)
