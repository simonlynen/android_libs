RPC_PROTO = rpc_hello.proto
RPC_PB_H  = rpc_hello.pb.h
RPC_PB_C  = rpc_hello.pb.cc

noinst_LTLIBRARIES = libcasrpcpbexapi.la

libcasrpcpbexapi_la_SOURCES = $(RPC_PB_C)
BUILT_SOURCES               = $(RPC_PB_C)

$(RPC_PB_C): $(RPC_PROTO)
	$(PROTOC) $^ --cpp_out=.

CLEANFILES = $(RPC_PB_H) $(RPC_PB_C)
