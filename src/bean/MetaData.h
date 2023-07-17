#ifndef METADATA_H
#define METADATA_H

#include <QObject>
#include <QMediaContent>
#include "uuiditem.h"

class MetaData : public UuidItem {
    Q_OBJECT
    Q_DISABLE_COPY(MetaData)

    Q_PROPERTY(qint64 annee READ getAnnee  CONSTANT )
    Q_PROPERTY(qint64 duree READ getDuree  CONSTANT )
    Q_PROPERTY(QString titre READ getTitre  CONSTANT )
    Q_PROPERTY(QString album READ getAlbum  CONSTANT )
    Q_PROPERTY(QString artiste READ getArtiste CONSTANT  )
    Q_PROPERTY(QString chemin READ getChemin CONSTANT  )

private:
    QString titre;
    QString album;
    QString artiste;
    QString chemin; // uri (virtuel) vers le media

    qint64 annee;
    qint64 duree; // en seconde


public:
    explicit MetaData(QObject *parent = 0);
    virtual ~MetaData();

    void setTitre(const QString & v) {titre=v;}
    QString getTitre() const {return titre;}

    void setAlbum(const QString & v) {album=v;}
    QString getAlbum() const {return album;}

    void setArtiste(const QString & v) {artiste=v;}
    QString getArtiste() const {return artiste;}

    void setAnnee(const qint64 v) {annee=v;}
    qint64 getAnnee() const {return annee;}

    void setDuree(const qint64 v) {duree=v;}
    qint64 getDuree() const {return duree;}

    void setChemin(const QString & v) {chemin=v;}
    QString getChemin() const {return chemin;}

    /**
     * @brief calcule la duree de la liste en secondes
     * @param l
     * @return
     */
    static qint64 dureeListe(const QList<MetaData *> *);

    /**
     * @brief chaine representant cette duree
     * @return
     */
    static QString dureeString(const qint64);

    /**
     * @brief versMediaContent
     * @return
     */
    static QList<QMediaContent> versMediaContent(QList<MetaData *> *);
    static QMediaContent versMediaContent(MetaData *);

    /**
     * @brief fait une copy de l'objet
     * @param t
     * @return
     */
    static MetaData *copy(MetaData *obj);

    /**
     * @brief cree un nouveau titre depuis une url PHYSIQUE vers le media
     * @return
     */
    static MetaData *depuisUrl(const QString & );

    /**
     * @brief cree une liste de titre depuis une liste d'url canonique
     * @param l
     * @return
     */
    static QList<MetaData *> *depuisUrl(const QList<QString> & l);
};

typedef QList<MetaData *> *MetaDataList;


#endif // METADATA_H
