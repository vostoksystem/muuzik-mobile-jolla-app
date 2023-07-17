#ifndef ROWINDEXEUR_H
#define ROWINDEXEUR_H

#include <QObject>
#include <QString>

using namespace std;

class RowIndexeur : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(RowIndexeur)
    Q_PROPERTY(QString nom READ getNom CONSTANT )
    Q_PROPERTY(QString chemin READ getChemin CONSTANT )
    Q_PROPERTY(QString motscles READ getMotsCles CONSTANT )
    Q_PROPERTY(qint64 format READ getFormat CONSTANT )

public:
    explicit RowIndexeur(QObject *parent = 0);
    virtual ~RowIndexeur();

    QString nom;
    QString chemin;
    QString motscles;
    quint64 format;

    QString  getNom() const {return nom;}
    void setNom(const QString &v) {nom = v;}

    QString  getChemin() const {return chemin;}
    void setChemin(const QString &v) {chemin = v;}

    QString getMotsCles () const {return motscles;}
    void setMotsCles(const QString &v) {motscles = v;}

    quint64 getFormat() const {return format;}
    void setFormat(const qint64 v) {format = v;}
};

typedef QList<RowIndexeur *> RowIndexeurListe;


#endif // ROWINDEXEUR_H
