SRCS = RPCServerProxy.cc RPCSocketServerImpl.cc RPCSocketServerFactoryImpl.cc RPCSocketSession.cc RPCServerCommunicator.cc

LIBS = $(top_srcdir)/src/casock/proactor/asio/server/libcasproasioserver.la \
       $(top_srcdir)/src/casock/rpc/asio/protobuf/base/libcasrpcaiopbbase.la \
       $(top_srcdir)/src/casock/rpc/protobuf/server/libcasrpcpbserver.la

noinst_LTLIBRARIES = libcasrpcaiopbserver.la

libcasrpcaiopbserver_la_SOURCES = $(SRCS)
libcasrpcaiopbserver_la_LIBADD  = $(LIBS)
