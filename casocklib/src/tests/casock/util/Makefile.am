SRCS_LOCKABLE	= test_Lockable.cc

LIB_UTIL      = $(top_srcdir)/src/casock/util/libcasutil.la

check_PROGRAMS = test_Lockable

test_Lockable_SOURCES	= $(SRCS_LOCKABLE)
test_Lockable_LDADD  	= $(LIB_UTIL)

TESTS  = $(check_PROGRAMS)
