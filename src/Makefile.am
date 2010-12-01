if SHARED
shareddir = lib
shared_PROGRAMS = libztexting.so
libztexting_so_SOURCES = zstring.cc
libztexting_so_CXXFLAGS = $(SHARED_CXXFLAGS)
libztexting_so_LDFLAGS = $(SHARED_LDFLAGS)
endif

if STATIC
lib_LIBRARIES = libztexting.a
libztexting_a_SOURCES = zstring.cc
endif
