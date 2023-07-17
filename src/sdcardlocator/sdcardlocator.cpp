#include "sdcardlocator.h"
#include <QDebug>

SdcardLocator::SdcardLocator(QObject *parent) : QObject(parent),
    location(""),type(""){
    SdcardLocator::checkSdcard();
}

/**
 * @brief instance (singleton) for the service
 * @return
 */
SdcardLocator& SdcardLocator::getInstance() {
    static SdcardLocator instance;
    return instance;
}

/**
 * @brief register the service into the context so it can be used in qml
 * @param context
 * @param name : register service on this name, SdcardLocator instead if null
 */
void SdcardLocator::init(QQmlContext *context, QString name) {
    context->setContextProperty(name,&SdcardLocator::getInstance());
}

/**
  * @brief check if url is  on the sdcard.
  * @param url
  * @return false if not or no sdcard
  * @since 1.4
  */
bool SdcardLocator::isOnSdcard(const QString &url) {
    if( isPresent() == false || url.length() == 0) {
        return false;
    }

    if(url.startsWith(location)) {
        return true;
    }

    if(url.startsWith("file:/" + location)) {
        return true;
    }

    return false;
}

/**
 * @brief check for a sdcard
 */
void SdcardLocator::checkSdcard() {
    FILE *fichier;
    char ligne[1024];

    fichier = popen("df -T", "r");
    if (fichier == NULL) {
        return;
    }

    while (fgets(ligne, 1024, fichier) != NULL) {
        QString chaine = QString::fromUtf8(ligne);
        QStringList liste = chaine.split(QRegExp("\\s+"));

        if( liste.length()>=6 && liste.at(6).indexOf("/media/sdcard/")==0) {
            type = liste.at(1);
            location = liste.at(6);
            break;
        }

        // fix sur l'update 2.2.0.29
        //@since 1.2
        if( liste.length()>=6 && liste.at(6).indexOf("/run/media/nemo/")==0) {
            type = liste.at(1);
            location = liste.at(6);
            break;
        }

        // fix sur l'update 2.2.0.29
        //@since 1.2
        if( liste.length()>=6 && liste.at(6).indexOf("/opt/alien/run/media/nemo")==0) {
            type = liste.at(1);
            location = liste.at(6);
            break;
        }
    }

    pclose(fichier);
}

/*
 * ok, solution is unreliable because if sdcard is empty
 * the check is false, so back to scanning thought df
QString SdcardLocator::checkSdcard() {

    QDir rep("/media/sdcard");
    if(rep.exists() == false || rep.isReadable() == false) {
        return QString::null;
    }

    rep.setFilter(QDir::Dirs|QDir::NoDotAndDotDot|QDir::Readable);
    QStringList l = rep.entryList();
    foreach ( QString f, l) {
        QDir d(rep.absoluteFilePath(f));
        d.setFilter(QDir::Dirs|QDir::Files|QDir::NoDotAndDotDot|QDir::Readable);

        if(d.entryList().length()>0) {
            return( d.canonicalPath());
        }
    }


    return QString::null;
}
 */
