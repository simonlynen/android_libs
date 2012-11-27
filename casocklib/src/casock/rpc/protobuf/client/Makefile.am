SRCS = RPCClientProxy.cc RPCCallHandlerImpl.cc RPCCallHandlerFactoryImpl.cc RPCCallHash.cc RPCRequestBuilder.cc RPCCallTimeoutHandler.cc RPCCallResponseReceiver.cc

LIBS = $(top_srcdir)/src/casock/rpc/protobuf/api/libcasrpcpbapi.la \
			 $(top_srcdir)/src/casock/rpc/protobuf/base/libcasrpcpbbase.la

noinst_LTLIBRARIES = libcasrpcpbclient.la

libcasrpcpbclient_la_SOURCES  = $(SRCS)
libcasrpcpbclient_la_LIBADD   = $(LIBS)
