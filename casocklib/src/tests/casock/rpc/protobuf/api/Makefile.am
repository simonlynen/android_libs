RPC_PROTO = rpc_test.proto
RPC_PB_H  = rpc_test.pb.h
RPC_PB_C  = rpc_test.pb.cc

noinst_LTLIBRARIES = libcasrpcpbtapi.la

libcasrpcpbtapi_la_SOURCES  = $(RPC_PB_C)
BUILT_SOURCES               = $(RPC_PB_C)

$(RPC_PB_C): $(RPC_PROTO)
	$(PROTOC) $^ --cpp_out=.

CLEANFILES = $(RPC_PB_H) $(RPC_PB_C)
