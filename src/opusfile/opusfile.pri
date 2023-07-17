HEADERS +=  $$PWD/internal.h \
			$$PWD/opusfile.h

SOURCES +=  $$PWD/internal.c \
			$$PWD/opusfile.c \
			$$PWD/info.c \
			$$PWD/http.c \
			$$PWD/stream.c

			
  
LIBS += -logg -lopus
  
