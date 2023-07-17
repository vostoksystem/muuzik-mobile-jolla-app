#ifndef RESULTITEM_H
#define RESULTITEM_H

#include <QObject>
#include "uuiditem.h"
#include "../virtualfiles/VFInfo.h"

using namespace std;

class ResultItem : public UuidItem {
    Q_OBJECT

    Q_PROPERTY(QString vurl READ getVUrl CONSTANT)
    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(VFInfo::VFType type READ getType CONSTANT)

public:
    explicit ResultItem(QObject *parent = 0);

    QString getName() const {return name;}
    QString getVUrl() const {return vurl;}
    VFInfo::VFType getType() const {return type;}

    bool isDirectory() { return type == VFInfo::VFType::DIRECTORY; }

    void setVurl(const QString &v) {vurl = v;}
    void setName(const QString &v) {name = v;}
    void setType(const  VFInfo::VFType  &v) {type = v;}

private:
    QString name;
    QString vurl;
    VFInfo::VFType type;

};

typedef QList<ResultItem *> ResultItemListe;


#endif // RESULTITEM_H
