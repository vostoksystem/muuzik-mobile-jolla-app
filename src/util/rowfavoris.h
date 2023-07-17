#ifndef ROWFAVORIS_H
#define ROWFAVORIS_H

#include <QObject>
#include "../bean/uuiditem.h"

class RowFavoris: public UuidItem {
    Q_OBJECT
    Q_DISABLE_COPY(RowFavoris)

    Q_PROPERTY(QString nom READ getNom  CONSTANT )
    Q_PROPERTY(QString chemin READ getChemin  CONSTANT )
    Q_PROPERTY(quint64 creation READ getCreation CONSTANT )
    Q_PROPERTY(quint64 duree READ getDuree CONSTANT )
    Q_PROPERTY(quint64 pistes READ getPiste CONSTANT )

public:
   explicit RowFavoris(QObject *parent = 0);
    virtual ~RowFavoris();

    QString nom;
    QString chemin;     // rep virtuel
    quint64 creation;       // date d'ajout
    quint64 duree;      // longeur en seconde
    quint64 pistes;     // nombre de pistes

    QString  getNom() const { return nom;}
    void setNom(const QString &v) {nom = v;}

    QString  getChemin() const { return chemin;}
    void setChemin(const QString &v) {chemin = v;}

    quint64 getCreation() { return creation; }
    void setCreation(quint64 v) {creation = v;}

    quint64 getDuree() const { return duree; }
    void setDuree(quint64 v) {duree = v;}

    quint64 getPiste() const { return pistes; }
    void setPiste(quint64 v) {pistes = v;}
};

typedef QList<RowFavoris *> RowFavorisListe;

#endif // ROWFAVORIS_H
