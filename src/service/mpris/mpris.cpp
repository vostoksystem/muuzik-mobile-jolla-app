#include "mpris.h"

Mpris::Mpris( QObject *parent): QDBusAbstractAdaptor(parent) {

    uri.append("file");
    mime.append("audio/mp3");
    mime.append("audio/ogg");
    mime.append("audio/flac");
    mime.append("audio/wav");
    mime.append("audio/mp4");
}

/**
 * @brief Mpris::Raise
 */
void Mpris::Raise(){
}

/**
 * @brief Mpris::Quit
 */
void Mpris::Quit(){
}
