SRCS_CLIENT = ftpclient.cc FTPClientSockReaderHandler.cc
SRCS_SERVER = ftpserver.cc FTPServerSockAcceptorHandler.cc FTPServerSockReaderHandler.cc

LIB_UTIL    = $(top_srcdir)/src/casock/util/libcasutil.la
LIB_CLIENT  = $(top_srcdir)/src/casock/sigio/client/libcassioclient.la
LIB_SERVER  = $(top_srcdir)/src/casock/sigio/server/libcassioserver.la

bin_PROGRAMS = ftpclient ftpserver

ftpclient_SOURCES  = $(SRCS_CLIENT)
ftpclient_LDADD    = $(LIB_CLIENT) $(LIB_UTIL)
ftpclient_LDFLAGS  = -static

ftpserver_SOURCES  = $(SRCS_SERVER)
ftpserver_LDADD    = $(LIB_SERVER) $(LIB_UTIL)
ftpserver_LDFLAGS  = -static
