noinst_PROGRAMS = zstring_test
zstring_test_SOURCES = zstring_test.cc zstrip_test.cc zscws_test.cc zutils_test.cc zstring_regexp_test.cc zpcre_test.cc zstmt_test.cc
zstring_test_CXXFLAGS= -I../src -O0 -ggdb3 -L../src -I/usr/local/include -L/usr/local/lib

LIBS=-lscws -lpcre -lpcre++ -lboost_unit_test_framework -lyaml-cpp

if SHARED
ZTEXTING_LIB= -lztexting
endif

if STATIC
ZTEXTING_LIB= ../src/libztexting.a
endif
zstring_test_LDADD= $(ZTEXTING_LIB) $(LIBS)

