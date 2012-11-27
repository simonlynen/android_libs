RPC_PROTO = rpc.proto
RPC_PB_H  = rpc.pb.h
RPC_PB_C  = rpc.pb.cc

noinst_LTLIBRARIES = libcasrpcpbapi.la

libcasrpcpbapi_la_SOURCES = $(RPC_PB_C)
BUILT_SOURCES             = $(RPC_PB_C)

$(RPC_PB_C): $(RPC_PROTO)
	$(PROTOC) $^ --cpp_out=.

CLEANFILES = $(RPC_PB_H) $(RPC_PB_C)
