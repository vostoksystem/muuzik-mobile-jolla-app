#ifndef ALBUMSTAT_H
#define ALBUMSTAT_H

#include <QObject>
#include "uuiditem.h"

class AlbumStat : public UuidItem {
    Q_OBJECT
    Q_DISABLE_COPY(AlbumStat)

    Q_PROPERTY(QString chemin READ getChemin CONSTANT  )
    Q_PROPERTY(quint64 duree READ getDuree  CONSTANT )
    Q_PROPERTY(quint64 pistes READ getPistes  CONSTANT )
    Q_PROPERTY(QString artiste READ getArtiste CONSTANT  )
    Q_PROPERTY(QString album READ getAlbum CONSTANT  )
    Q_PROPERTY(quint64 annee READ getAnnee CONSTANT  )

public:
    explicit AlbumStat(QObject *parent = 0);
    virtual ~AlbumStat();

    void setDuree(const quint64 v) {duree=v;}
    quint64 getDuree() const {return duree;}

    void setChemin(const QString & v) {chemin=v;}
    QString getChemin() const {return chemin;}

    void setPistes(const quint64 v) {pistes=v;}
    quint64 getPistes() const {return pistes;}

    void setArtiste(const QString & v) {artiste=v;}
    QString getArtiste() const {return artiste;}

    void setAlbum(const QString & v) {album=v;}
    QString getAlbum() const {return album;}

    /**
     * @since 2.4
     */
    void setAnnee(const quint64 v) {annee=v;}
    quint64 getAnnee() const { return annee;}


private :
    QString chemin; // uri (virtuel) vers l'album
    quint64 duree; // durée totale en seconde
    quint64 pistes;  // nombre de titre dans cet album

    QString artiste;
    QString album;
    quint64 annee;
};

#endif // ALBUMSTAT_H
