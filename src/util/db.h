#ifndef DB_H
#define DB_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>

using namespace std;

/**
 * @brief The DB class
 * @version 1.2
 */
class DB : public QObject {
    Q_OBJECT

public:
    static DB& getInstance();
    ~DB();

    /**
     * @brief s'assure que la db est ouverte
     * @return false si pb
     */
    bool open();

    /**
     * @brief true si la db est ouverte
     * @return false si non
     */
    bool isOpen();

    /**
     * @brief createStatement
     * @param str
     * @return
     */
    QSqlQuery *createStatement(const QString &str);

    /**
     * @brief createQuery
     * @return
     */
    QSqlQuery createQuery();

    /**
     * @brief sanitized
     * @param str
     * @return sanitized str
     * @since 1.2
     */
    QString sanitized(const QString str);

    /**
     * @brief transaction
     */
    bool transaction();

    /**
     * @brief commit
     */
    bool commit();

    /*
     * @brief rollback
     */
    bool rollback();

private :
    explicit DB(QObject *parent = 0);

    QSqlDatabase db;

protected :
    /**
     * @brief getDb
     * @return
     */
    QSqlDatabase getDb() { return db;}

signals:

public slots:
};

#endif // DB_H
