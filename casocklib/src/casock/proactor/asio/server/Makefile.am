SRCS = SocketServer.cc SocketSession.cc

LIB_BASE = $(top_srcdir)/src/casock/proactor/asio/base/libcasproasiobase.la

lib_LTLIBRARIES                 = libcasproasioserver.la
libcasproasioserver_la_SOURCES  = $(SRCS)
libcasproasioserver_la_LIBADD   = $(LIB_BASE)
