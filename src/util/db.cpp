#include "db.h"
#include <QDir>
#include <QStandardPaths>
#include <QSqlQuery>
#include <QSqlField>
#include <QSqlDriver>
#include <QDebug>

#define LOCALDB ".db"
#define LOCALDBNAME "muuzik2"

/**
 * @brief DB::DB
 * @param parent
 */
DB::DB(QObject *parent) : QObject(parent) {
    QDir d(QString(QStandardPaths::writableLocation(QStandardPaths::DataLocation)));
    d.mkpath(LOCALDB);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(
                QStandardPaths::writableLocation(QStandardPaths::DataLocation)+
                "/"+ LOCALDB "/"+ LOCALDBNAME);

    if(open()==false) {
        qDebug() << "error opening db";
        return;
    }

    QFile init(":/sql/init");
    if (init.open(QFile::ReadOnly)==false) {
        qDebug()<< "error reading init file";
        return;
    }

    QStringList tmp = QString::fromUtf8(init.readAll()).split(QChar(';'));
    foreach(QString s , tmp) {
        QString ss = s.trimmed();
        if(ss.length()==0) {
            continue;
        }
        QSqlQuery q;
        if(q.exec(ss) ==false) {
            qDebug()<< "can't run command : " << ss;
        }
        q.finish();
    }

    init.close();

    qDebug("db ok");
}

/**
 * @brief DB::~DB
 */
DB::~DB() {
    db.close();
}

/**
  * @brief DB::getInstance
  * @return
  */
DB& DB::getInstance() {
    static  DB instance;

    instance.open();
    return instance;
}

/**
  * @brief s'assure que la db est ouverte
  * @return false si pb
  */
bool DB::open() {
    if(db.isOpen()) {
        return true;
    }

    if(db.open()) {
        return true;
    }

    qDebug() << "Db closed and can't open it anymore";
    return false;
}

/**
 * @brief true si la db est ouverte
 * @return false si non
 */
bool DB::isOpen() {
    return db.isOpen();
}

/**
 * @brief createStatement
 * @param str
 * @return
 */
QSqlQuery *DB::createStatement(const QString &str) {
    QSqlQuery *q=new QSqlQuery(db);
    q->prepare(str);
    return q;
}

/**
 * @brief DB::createQuery
 * @return
 */
QSqlQuery DB::createQuery() {
   // QSqlQuery q(db);
    return QSqlQuery(db);
}

/**
 * @brief sanitized
 * @param str
 * @return sanitized str
 * @since 1.2
 */
QString DB::sanitized(const QString str) {
    QSqlField f;
    f.setType(QVariant::String);
    f.setValue(str);

    return db.driver()->formatValue(f);

}

/**
 * @brief transaction
 */
bool DB::transaction() {
    return db.transaction();
}

/**
 * @brief commit
 */
bool DB::commit() {
    return db.commit();
}

/*
 * @brief rollback
 */
bool DB::rollback() {
    return db.rollback();
}

