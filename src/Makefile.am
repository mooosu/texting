SOURCES=zstring.cc zstrip.cc unicode.cc zscws.cc zutils.cc
if SHARED
shareddir = lib
shared_PROGRAMS = libztexting.so
libztexting_so_SOURCES = $(SOURCES)
libztexting_so_CXXFLAGS = $(SHARED_CXXFLAGS)
libztexting_so_LDFLAGS = $(SHARED_LDFLAGS)
libztexting_so_LDADD=-lpcre -lpcre++ -lscws
endif

if STATIC
lib_LIBRARIES = libztexting.a
libztexting_a_SOURCES = $(SOURCES)
libztexting_a_CXXFLAGS= -O0 -ggdb3 -lpcre -lpcre++
endif
