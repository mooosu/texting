bin_PROGRAMS = zstring_test
zstring_test_SOURCES = zstring_test.cc
zstring_test_CXXFLAGS= -I../src -O0 -ggdb3 -L../src

if SHARED
ZTEXTING_LIB= -lztexting
endif

if STATIC
ZTEXTING_LIB= ../src/libztexting.a
endif
zstring_test_LDADD=-lboost_unit_test_framework $(ZTEXTING_LIB)
