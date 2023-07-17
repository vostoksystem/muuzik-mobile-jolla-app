#ifndef TRACK_H
#define TRACK_H

#include <QObject>

class Track : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Track)

public:
    explicit Track(QObject *parent = 0);

    void setVurl(const QString &v) {vurl = v;}
    QString getVurl() const { return vurl; }

    void setTimestamp(quint64 v) { timestamp = v; }
    quint64 getTimestamp() { return timestamp; }

private:
    QString vurl;
    qint64 timestamp;


};

#endif // TRACK_H
