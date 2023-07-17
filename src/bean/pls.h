#ifndef PLS_H
#define PLS_H

#include <QObject>
#include "uuiditem.h"

class Pls : public UuidItem {
    Q_OBJECT
    Q_DISABLE_COPY(Pls)

    Q_PROPERTY(QString nom READ getNom CONSTANT )
    Q_PROPERTY(QString path READ getPath CONSTANT )
    Q_PROPERTY(PlsType type READ getType CONSTANT )
    Q_PROPERTY(QList<QString> liste READ getListe CONSTANT )
    Q_PROPERTY(quint64 taille READ getTaille CONSTANT )
    Q_PROPERTY(quint64 duree READ getDuree CONSTANT )

public:
    explicit Pls(QObject *parent = 0);

    enum PlsType {
        PLS,
        M3U
    };
    Q_ENUM(PlsType)

    /**
     * @brief getNom
     * @return
     */
    QString getNom() const { return nom;}
    void setNom(const QString v) { nom = v;}

    /**
     * @brief getPath
     * @return
     */
    QString getPath() const { return path;}
    void setPath(const QString v) { path = v;}

    /**
     * @brief getType
     * @return
     */
    PlsType getType() const { return type;}
    void setType(const PlsType v) { type = v;}

    /**
     * @brief getTaille
     * @return
     */
    quint64 getTaille() { return liste.length(); }

    /**
     * @brief getDuree
     * @return
     */
    quint64 getDuree() { return duree; }

    /**
     * @brief getListe
     * @return
     */
    QList<QString> getListe() { return liste; }

    /**
     * @brief ajoute un nouveau media à la liste
     * @param url
     * @param duree
     */
    void ajouterUrl(const QString &vurl, quint64 timestamp);

    /**
     * @brief efface les info pistes
     */
    void resetUrl();

    /**
     * @brief copy
     * @param obj
     * @return
     */
    static Pls *copy(Pls *obj);

private :
    QString nom;
    QString path;
    PlsType type;

    quint64 duree;

    QList<QString> liste;
};

#endif // PLS_H
