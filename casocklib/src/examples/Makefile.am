SUBDIRS = rpc ftp proactor

SRCS_CLIENT = client.cc ClientSockReaderHandler.cc
SRCS_SERVER = server.cc ServerSockAcceptorHandler.cc ServerSockReaderHandler.cc

LIB_UTIL    = $(top_srcdir)/src/casock/util/libcasutil.la
LIB_CLIENT  = $(top_srcdir)/src/casock/sigio/client/libcassioclient.la
LIB_SERVER  = $(top_srcdir)/src/casock/sigio/server/libcassioserver.la

bin_PROGRAMS = client server

client_SOURCES  = $(SRCS_CLIENT)
client_LDADD    = $(LIB_CLIENT) $(LIB_UTIL)
client_LDFLAGS  = -static

server_SOURCES  = $(SRCS_SERVER)
server_LDADD    = $(LIB_SERVER) $(LIB_UTIL)
server_LDFLAGS  = -static
