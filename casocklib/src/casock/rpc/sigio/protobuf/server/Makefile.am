SRCS = RPCServerProxy.cc RPCAcceptorHandler.cc \
       RPCReaderHandler.cc RPCServerCommunicator.cc

LIBS = $(top_srcdir)/src/casock/sigio/server/libcassioserver.la \
			 $(top_srcdir)/src/casock/rpc/sigio/protobuf/base/libcasrpcsiopbbase.la \
       $(top_srcdir)/src/casock/rpc/protobuf/server/libcasrpcpbserver.la

noinst_LTLIBRARIES = libcasrpcsiopbserver.la

libcasrpcsiopbserver_la_SOURCES  = $(SRCS)
libcasrpcsiopbserver_la_LIBADD   = $(LIBS)
