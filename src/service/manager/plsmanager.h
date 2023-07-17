#ifndef PLSMANAGER_H
#define PLSMANAGER_H

#include <QObject>
#include <QList>
#include <QString>

#include "../../bean/MetaData.h"
#include "../../bean/pls.h"

// lit / ecrit des playlist au format pls
class plsManager : public QObject {
    Q_OBJECT

public:
    explicit plsManager(QObject *parent = 0);

    /**
     * @brief Write data into 'disk'
     * @param list list of title
     * @param full absolute path to the playlist,if exit, override
     * @return true if list writen
     */
    static bool marshaller(const QList<MetaData *> list ,const QString &path );


    /**
     * @brief Read playlist and return a title list
     * @param full absolute path too the playlist
     * @return the list ; might be empty
     */
    static Pls *unmarshaller(const QString &source );
};

#endif // PLSMANAGER_H
