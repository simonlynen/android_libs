CXXTSRCS_RPC_CLIENT_PROXY = test_RPCClientProxy_cxx.cc
CXXTSRCS_RPC_REQUEST_BUILDER = test_RPCRequestBuilder_cxx.cc
CXXTSRCS = $(CXXTSRCS_RPC_CLIENT_PROXY) $(CXXTSRCS_RPC_REQUEST_BUILDER)

SRCS_RPC_CLIENT_PROXY_CXX = $(CXXTSRCS_RPC_CLIENT_PROXY) \
                        RPCCallHandlerMock.cc RPCCallHandlerFactoryMock.cc

SRCS_RPC_REQUEST_BUILDER = $(CXXTSRCS_RPC_REQUEST_BUILDER)

SRCS_RPC_CLIENT_PROXY  = test_RPCClientProxy.cc
SRCS_RPC_CALL_CONTROLLER  = test_RPCCallController.cc
SRCS_RPC_CALL_TIMEOUT_HANDLER  = test_RPCCallTimeoutHandler.cc
SRCS_RPC_CALL_RESPONSE_RECEIVER = test_RPCCallResponseReceiver.cc
SRCS_RPC_REQUEST_BUILDER = test_RPCRequestBuilder.cc

LIB_UTIL      = $(top_srcdir)/src/casock/util/libcasutil.la
LIB_RPCCLIENT = $(top_srcdir)/src/casock/rpc/protobuf/client/libcasrpcpbclient.la
#LIB_PROTOBUF  = @LIB_PROTOBUF_PATH@/libprotobuf.a
LIB_RPCTEST1  = $(top_srcdir)/src/tests/casock/rpc/protobuf/api/libcasrpcpbtapi.la

AM_CPPFLAGS = -DUSE_UT_CXXTEST

check_PROGRAMS = test_RPCClientProxy_cxx test_RPCRequestBuilder_cxx test_RPCClientProxy test_RPCCallController test_RPCCallTimeoutHandler \
								 test_RPCRequestBuilder \
								 test_RPCCallResponseReceiver

test_RPCClientProxy_cxx_SOURCES	= $(SRCS_RPC_CLIENT_PROXY_CXX)
test_RPCClientProxy_cxx_LDADD   = $(LIB_RPCCLIENT) $(LIB_UTIL) $(LIB_RPCTEST1)# $(LIB_PROTOBUF)
#test_RPCClientProxy_cxx_LDFLAGS = -static

test_RPCRequestBuilder_cxx_SOURCES   = $(SRCS_RPC_REQUEST_BUILDER)
test_RPCRequestBuilder_cxx_LDADD     = $(LIB_RPCCLIENT) $(LIB_UTIL) $(LIB_RPCTEST1)# $(LIB_PROTOBUF)
#test_RPCRequestBuilder_cxx_LDFLAGS   = -static

test_RPCClientProxy_SOURCES  = $(SRCS_RPC_CLIENT_PROXY)
test_RPCClientProxy_LDADD    = $(LIB_RPCCLIENT) $(LIB_UTIL)

test_RPCCallController_SOURCES  = $(SRCS_RPC_CALL_CONTROLLER)
test_RPCCallController_LDADD  	= $(LIB_RPCCLIENT) $(LIB_UTIL)

test_RPCCallTimeoutHandler_SOURCES  = $(SRCS_RPC_CALL_TIMEOUT_HANDLER)
test_RPCCallTimeoutHandler_LDADD  	= $(LIB_RPCCLIENT) $(LIB_UTIL)

test_RPCCallResponseReceiver_SOURCES  = $(SRCS_RPC_CALL_RESPONSE_RECEIVER)
test_RPCCallResponseReceiver_LDADD  	= $(LIB_RPCTEST1) $(LIB_RPCCLIENT) $(LIB_UTIL)

test_RPCRequestBuilder_SOURCES  = $(SRCS_RPC_REQUEST_BUILDER)
test_RPCRequestBuilder_LDADD  	= $(LIB_RPCTEST1) $(LIB_RPCCLIENT) $(LIB_UTIL)

TESTS  = $(check_PROGRAMS)

%_cxx.cc: %_cxx.h
	$(CXXTESTGEN) $(CXXTFLAGS) $< -o $@

CLEANFILES = $(CXXTSRCS)
