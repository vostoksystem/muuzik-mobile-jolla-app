#ifndef TESTJSON_H
#define TESTJSON_H

#include <QObject>

class TestJson : public QObject
{
    Q_OBJECT
public:
    explicit TestJson(QObject *parent = 0);


    static void doTest(const QString vurl );

private :
    static QString readFile(const QString &filename);

signals:

public slots:
};

#endif // TESTJSON_H
