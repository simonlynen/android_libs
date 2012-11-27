SRCS = RPCClientProxy.cc RPCChannel.cc \
			 RPCReaderHandler.cc RPCClientCommunicator.cc

LIBS = $(top_srcdir)/src/casock/sigio/client/libcassioclient.la \
			 $(top_srcdir)/src/casock/rpc/sigio/protobuf/base/libcasrpcsiopbbase.la \
			 $(top_srcdir)/src/casock/rpc/protobuf/client/libcasrpcpbclient.la

noinst_LTLIBRARIES = libcasrpcsiopbclient.la

libcasrpcsiopbclient_la_SOURCES  = $(SRCS)
libcasrpcsiopbclient_la_LIBADD   = $(LIBS)
