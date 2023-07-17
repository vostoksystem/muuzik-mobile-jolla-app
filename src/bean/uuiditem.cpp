#include "uuiditem.h"

static qint64 uuid_def = 1;

UuidItem::UuidItem(QObject *parent) : QObject(parent) {
    uuid=uuid_def;
    uuid_def++;
}
