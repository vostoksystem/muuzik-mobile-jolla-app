#include "plsmanager.h"
#include <QTextStream>
#include <QDir>
#include <QFile>
#include <qregularexpression.h>
#include <QHash>
#include <QDebug>

#include "../metadataservice.h"

#include "../../virtualfiles/VFservice.h"

plsManager::plsManager(QObject *parent) : QObject(parent) {
}

/**
 * @brief Write data into 'disk'
 * @param list list of title
 * @param path full absolute path to the playlist,if exit, override
 * @return true if list writen
 */
bool plsManager::marshaller(const QList<MetaData *> list ,const QString &path ) {

    QFile f(path);
    if( f.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {

        QTextStream stream(&f);

        stream << "[playlist]" << "\n";
        stream << "NumberOfEntries=" << list.length() << "\n";

        int i=1;
        foreach (MetaData *s, list) {
            stream << "File" << i << "=file://" << VFI.getPathFromVUrl(s->getChemin()) << "\n";
            stream << "Title" << i << "=" << s->getTitre() << "\n";
            stream << "Length" << i << "=" << s->getDuree() << "\n";
            i++;
        }
        stream  << endl;

        f.close();

        return true;
    }

    return false;
}

/**
 * @brief Read playlist and return a title list
 * @param path full absolute path too the playlist
 * @return the list, NULL on error
 */
Pls *plsManager::unmarshaller(const QString &path ) {

    Pls *pls = new Pls();
    pls->setPath(path);
    pls->setType(Pls::PlsType::PLS);
    pls->setNom(VFI.getName(path));

    QHash<QString,QString> hash;

    QFile f(path);
    if( f.open(QIODevice::ReadOnly)) {
        QTextStream in(&f);
        while(!in.atEnd()) {
            QStringList l = in.readLine().split('=');
            if(l.length()<2) {
                continue;
            }
            hash.insert(l.at(0),l.at(1));
        }

        f.close();
    }

    // parse les valeurs
    quint64 nb=1; // failsafe à 512

    while( hash.contains(QString("File"+QString::number((nb))) ) && nb < 512 ) {
        try {
            QString p = hash.value(QString("File"+ QString::number((nb)) ));
            QString u = VFI.getVUrl( p.remove("file://") );
            if(VFI.exist(u)) {

                quint64 t = hash.value(QString("Length"+QString::number((nb)) )).toInt();
                pls->ajouterUrl(u,t);
            }
        }catch( const std::exception & e ) {
        }
        nb++;
    }

    return pls;
}
