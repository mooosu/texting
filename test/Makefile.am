CXXFLAGS=-I../src -O0 -ggdb3 -L../src -I/usr/local/include -L/usr/local/lib
LIBS=-lscws -lpcre -lpcre++ -lboost_unit_test_framework -lyaml-cpp
if SHARED
ZTEXTING_LIB= -lztexting
endif

if STATIC
ZTEXTING_LIB= ../src/libztexting.a
endif

noinst_PROGRAMS = zstring_test ztexting_test ztexting_test2
zstring_test_SOURCES = zstring_test.cc zstrip_test.cc zscws_test.cc zutils_test.cc zstring_regexp_test.cc zpcre_test.cc zstmt_test.cc
zstring_test_CXXFLAGS= $(CXXFLAGS)
zstring_test_LDADD= $(ZTEXTING_LIB) $(LIBS)


ztexting_test_SOURCES = ztexting_test.cc
ztexting_test_CXXFLAGS= $(CXXFLAGS)
ztexting_test_LDADD= $(ZTEXTING_LIB) $(LIBS)

ztexting_test2_SOURCES = ztexting_test2.cc
ztexting_test2_CXXFLAGS= $(CXXFLAGS)
ztexting_test2_LDADD= $(ZTEXTING_LIB) $(LIBS)
