#include "qdownloaderservice.h"
#include <QtQml>
#include <QMetaType>
#include <QQmlEngine>


/**
 * @brief QDownloaderService::QDownloaderService
 * @param parent
 */
QDownloaderService::QDownloaderService(QObject *parent) : QObject(parent), signalOnRootError(false) {
}

/**
 * @brief return singleton instance
 * @return QDownloaderService instance
 */
QDownloaderService& QDownloaderService::getInstance() {
    static QDownloaderService instance;
    return instance;
}

/**
 * @brief this will register the service to be available into qml
 * @param context
 * @param name ; name for service (in qml), default to QDONWLOADER_QML_NAME
 */
void QDownloaderService::init(QQmlContext *context, const QString name) {
#ifdef QT_DEBUG
    qDebug() << "QDownloader, registering qml service as : " << name;
#endif

    context->setContextProperty(name, &QDownloaderService::getInstance());
    qmlRegisterUncreatableType<QNetworkReply>("org.vostok.qdownloader", 1, 0, "QDownloader", "");
}

/**
 * @brief if to the "start" method fail, a false value is returned but not the error signal.
 * Setting this value to true will also emit the signal with the value QNetworkReply::OperationCanceledError
 * @view start
 * @param value true to also emit an error on "root" error (r/w, file exist...)
 */
void QDownloaderService::setEmitSignalOnRootError(bool const value) {
    if( value == signalOnRootError) {
        return;
    }

    signalOnRootError = value;
    emit emitSignalOnRootErrorChanged();
}

/**
 * @brief start downloading from "source" to "target" ; target should not exist
 *
 * @param source : source url
 * @param target : target file
 * @param message : for the notification, SailfishOS only, let blank for none
 * @return : true if starting downloading ( doesn't mean it will be successful
 */
bool QDownloaderService::start(QString const & source, QString const & target, QString const &message ) {
#ifdef QT_DEBUG
    qDebug() << "QDownloaderService ; start for : " << source << "  as : \"" << target << "\"";
#endif

    // check if already pending for donwload
    if( pending.contains(source) ) {
        return false;
    }

    QSharedPointer<QDownloader> d( new QDownloader(), &QDownloader::deleteLater);
    if(d.data()->start(source,target,message) == false) {
        d.clear();
        if( signalOnRootError ) {
            emit error(QUrl(source), target, QNetworkReply::OperationCanceledError);
        }

        return false;
    }

    connect(d.data(), SIGNAL(downloading(QUrl,qint64,qint64)),this, SLOT(downloadingImpl(QUrl,qint64,qint64)));
    connect(d.data(), SIGNAL(success(QUrl,QString)), this, SLOT(successImpl(QUrl,QString)));
    connect(d.data(), SIGNAL(error(QUrl,QString,QNetworkReply::NetworkError)), this, SLOT(errorImpl(QUrl,QString,QNetworkReply::NetworkError)));

    pending.insert(source, d);
    emit pendingChanged();

    return true;
}

/**
 * @brief QDownloaderService::downloadingImpl
 * @param url
 * @param read
 * @param total
 */
void QDownloaderService::downloadingImpl(QUrl const &url, qint64 read ,qint64 total) {
    emit downloading(url,read,total);
}

/**
 * @brief QDownloaderService::successImpl
 * @param url
 * @param target
 */
void QDownloaderService::successImpl(QUrl const & url,QString const &target ) {
#ifdef QT_DEBUG
    qDebug() << "QDownloaderService ; success : " << url;
#endif

    pending.remove(url.toString());
    emit success(url, target);
    emit pendingChanged();
}

/**
 * @brief QDownloaderService::errorImpl
 * @param url
 * @param status
 */
void QDownloaderService::errorImpl(QUrl const & url, const QString target, QNetworkReply::NetworkError status ) {
#ifdef QT_DEBUG
    qDebug() << "QDownloaderService ERROR : " << url;
#endif

    pending.remove(url.toString());
    emit error(url, target, status);
    emit pendingChanged();
}
