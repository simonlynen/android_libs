SRCS_CLIENT1 = client1.cc
SRCS_SERVER1 = server1.cc

LIB_UTIL    = $(top_srcdir)/src/casock/util/libcasutil.la
LIB_CLIENT  = $(top_srcdir)/src/casock/proactor/asio/client/libcasproasioclient.la
LIB_SERVER  = $(top_srcdir)/src/casock/proactor/asio/server/libcasproasioserver.la

bin_PROGRAMS = client1 server1

server1_SOURCES = $(SRCS_SERVER1)
server1_LDADD   = $(LIB_SERVER) $(LIB_UTIL)
server1_LDFLAGS	= -static

client1_SOURCES = $(SRCS_CLIENT1)
client1_LDADD   = $(LIB_CLIENT) $(LIB_UTIL)
client1_LDFLAGS	= -static
