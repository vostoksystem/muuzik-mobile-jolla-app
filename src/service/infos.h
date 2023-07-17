#ifndef INFOSSERVICE_H
#define INFOSSERVICE_H

#include <QObject>


class infosService : public QObject {
    Q_OBJECT


public:
    static infosService& getInstance();


private :
    explicit infosService(QObject *parent = 0);

signals:

public slots:
};

#endif // INFOSSERVICE_H
