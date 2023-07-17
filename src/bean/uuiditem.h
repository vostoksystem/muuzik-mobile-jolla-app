#ifndef UUIDITEM_H
#define UUIDITEM_H

#include <QObject>

class UuidItem : public QObject {
    Q_OBJECT
    Q_PROPERTY(qint64 uuid READ getUuid  CONSTANT )

public:
    explicit UuidItem(QObject *parent = 0);

    /**
     * @brief getUuid ; final / ro
     * @return
     */
    qint64 getUuid() const { return uuid;}

protected :
    qint64 uuid;    // identifiant unique, auto incrementation
};

#endif // UUIDITEM_H
