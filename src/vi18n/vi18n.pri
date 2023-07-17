HEADERS +=  $$PWD/vi18n.h

SOURCES +=   $$PWD/vi18n.cpp
  
OTHER_FILES +=  $$PWD/i18n/*.properties

i18n.files = $$PWD/i18n
i18n.path = /usr/share/$${TARGET}
INSTALLS += i18n
