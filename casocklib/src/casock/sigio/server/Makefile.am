SRCS = SocketServer.cc  SockAcceptorHandler.cc

LIB_BASE = $(top_srcdir)/src/casock/sigio/base/libcassiobase.la

lib_LTLIBRARIES             = libcassioserver.la
libcassioserver_la_SOURCES  = $(SRCS)
libcassioserver_la_LIBADD   = $(LIB_BASE)
