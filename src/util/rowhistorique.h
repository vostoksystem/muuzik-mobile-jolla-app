#ifndef ROWHISTORIQUE_H
#define ROWHISTORIQUE_H

#include <QObject>
#include <QString>
#include "../bean/uuiditem.h"

using namespace std;

class RowHistorique : public UuidItem{
    Q_OBJECT
    Q_DISABLE_COPY(RowHistorique)

    Q_PROPERTY(QString nom READ getNom  CONSTANT )
    Q_PROPERTY(QString chemin READ getChemin  CONSTANT )
    Q_PROPERTY(qint64 ouverture READ getOuverture  CONSTANT )
    Q_PROPERTY(qint64 nombre READ getNombre  CONSTANT )
    Q_PROPERTY(quint64 duree READ getDuree CONSTANT )
    Q_PROPERTY(quint64 pistes READ getPiste CONSTANT )

public:
    explicit RowHistorique(QObject *parent = 0);
    virtual ~RowHistorique();

    QString nom;
    QString chemin; // rep virtuel
    quint64 ouverture; // derniere ouverture en minute depuis epoch
    quint64 nombre; // ouvert 'nombre" fois
    quint64 duree;      // longeur en seconde
    quint64 pistes;     // nombre de pistes

    QString  getNom() const { return nom;}
    void setNom(const QString &v) {nom = v;}

    QString  getChemin() const { return chemin;}
    void setChemin(const QString &v) {chemin = v;}

    quint64 getOuverture() const {return ouverture;}
    void setOuverture(const qint64 v) {ouverture = v;}

    quint64 getNombre() const {return nombre;}
    void setNombre(const qint64 v) {nombre = v;}

    quint64 getDuree() const { return duree; }
    void setDuree(quint64 v) {duree = v;}

    quint64 getPiste() const { return pistes; }
    void setPiste(quint64 v) {pistes = v;}
};

typedef QList<RowHistorique *> RowHistoriqueListe;

#endif // ROWHISTORIQUE_H
