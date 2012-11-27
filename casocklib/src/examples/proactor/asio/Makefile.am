SUBDIRS = ftp

SRCS_CLIENT = client.cc
SRCS_SERVER = server.cc

LIB_UTIL    = $(top_srcdir)/src/casock/util/libcasutil.la
LIB_CLIENT  = $(top_srcdir)/src/casock/proactor/asio/client/libcasproasioclient.la
LIB_SERVER  = $(top_srcdir)/src/casock/proactor/asio/server/libcasproasioserver.la

bin_PROGRAMS = client server

server_SOURCES  = $(SRCS_SERVER)
server_LDADD    = $(LIB_SERVER) $(LIB_UTIL)
server_LDFLAGS  = -static

client_SOURCES  = $(SRCS_CLIENT)
client_LDADD    = $(LIB_CLIENT) $(LIB_UTIL)
client_LDFLAGS  = -static
