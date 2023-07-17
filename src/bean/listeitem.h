#ifndef UUIDLISTEITEM_H
#define UUIDLISTEITEM_H

#include "uuiditem.h"

using namespace std;

class ListeItem : public UuidItem {
    Q_OBJECT
    Q_PROPERTY(QString uri READ getUri CONSTANT)
    Q_PROPERTY(QString label READ getLabel CONSTANT )
    Q_PROPERTY(QString art READ getArt CONSTANT )
    Q_PROPERTY(QString additionalData READ getData  CONSTANT )

public:
    explicit ListeItem(QObject *parent = 0);

      /**
     * @brief getNom
     * @return
     */
    QString getLabel() const { return label;}
    void setLabel(const QString v) { label = v;}

    /**
     * @brief
     * @return
     */
    QString getArt() const { return art;}
    void setArt(const QString v) { art = v;}

    /**
     * @brief getUri
     * @return
     */
    QString getUri() const {return uri;}
    void setUri(const QString v) {uri=v;}

    /**
     * @brief getData
     * @return
     */
    QString getData() const { return data;}
    void setData( QString v) { data = v;}



protected :
    qint64 uuid;    // identifiant unique, auto incrementation

    QString label;  // titre / nom de l'item
    QString art;    // chemin optionnel vers la pochette / icone
    QString uri; // chemin optionnel vers la resource

    QString data;   // donné additionnelle

};

typedef QList<ListeItem *> UuidListeItemListe;


#endif // UUIDLISTEITEM_H
