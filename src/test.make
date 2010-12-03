
CFLAGS=`pcre-config --cflags` `pcre++-config --cflags`
LIBS=-lscws `pcre-config --libs` `pcre++-config --libs`

cws_all:unicode.o zstrip.o zutils.o zscws.o zpcre.o zstring.o main.o
	g++  unicode.o zstrip.o zutils.o zscws.o zpcre.o zstring.o main.o -o cws_all ${LIBS}

unicode.o:unicode.cc unicode.h
	g++ -c unicode.cc ${CFLAGS}

zstrip.o:zstrip.cc zstrip.h
	g++ -c zstrip.cc ${CFLAGS}

zutils.o:zutils.cc zutils.h
	g++ -c zutils.cc ${CFLAGS}

zscws.o:zscws.cc zscws.h
	g++ -c zscws.cc ${CFLAGS}

zpcre.o:zpcre.cc zpcre.h
	g++ -c zpcre.cc  ${CFLAGS}

zstring.o:zstring.cc zstring.h
	g++ -c zstring.cc ${CFLAGS}

main.o:main.cc
	g++ -c main.cc ${CFLAGS}

clean:
	rm -f *.o
	rm -f cws_all
