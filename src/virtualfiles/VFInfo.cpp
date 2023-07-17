#include "VFInfo.h"
#include <QtQml>
#include <QMetaType>
#include <QQmlEngine>

static quint64 uuid_glb = 1;

VFInfo::VFInfo(QObject *parent) : QObject(parent){
    uuid= uuid_glb;
    uuid_glb++;
}

/**
 * @brief copy obj into a new object
 * @param obj
 * @return
 */
VFInfo *VFInfo::copy(VFInfo *obj) {
    VFInfo *v = new VFInfo();

    v->vurl = obj->vurl;
    v->source = obj->source;
    v->name = obj->name;
    v->timestamp = obj->timestamp;
    v->size = obj->size;
    v->grouppid = obj->grouppid;
    v->userid = obj->userid;

    return v;
}

/*************************************************************/
//void VFInfo::init() {
//    qmlRegisterType<VFInfo>("VFInfo", 1, 0, "VFInfo");
//    qmlRegisterUncreatableType<VFInfo::VFType>("VFType", 1, 0, "VFType","");
//}

/*************************************************************/
bool VFInfo::orderByName(VFInfo *a, VFInfo *b) {
    if(a->type != b->type) {
        // got a dir an a file, dir first
        return a->type ==VFInfo::DIRECTORY;
    }

    return a->name.compare(b->name) <0;
}

bool VFInfo::orderBySize(VFInfo *a, VFInfo *b) {
    if(a->type == VFInfo::DIRECTORY || b->type == VFInfo::DIRECTORY) {
        return orderByName(a,b);
    }

    return a->size < b->size;
}

bool VFInfo::orderByDate(VFInfo *a, VFInfo *b) {
    if(a->type == VFInfo::DIRECTORY || b->type == VFInfo::DIRECTORY) {
        return orderByName(a,b);
    }
    return b->timestamp < a->timestamp;
}

bool VFInfo::orderByUri(VFInfo *a, VFInfo *b) {
    return a->vurl.compare(b->vurl) <0;
}

