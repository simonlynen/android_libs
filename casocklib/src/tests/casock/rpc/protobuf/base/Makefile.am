SRCS_RPC_PROXY = test_RPCProxy.cc

LIB_UTIL    = $(top_srcdir)/src/casock/util/libcasutil.la
LIB_RPCBASE	= $(top_srcdir)/src/casock/rpc/protobuf/base/libcasrpcpbbase.la

AM_CPPFLAGS = -DUSE_UT_GTEST

check_PROGRAMS = test_RPCProxy

test_RPCProxy_SOURCES = $(SRCS_RPC_PROXY)
test_RPCProxy_LDADD		= $(LIB_RPCBASE) $(LIB_UTIL)
test_RPCProxy_LDFLAGS = -static

TESTS	= $(check_PROGRAMS)
