#ifndef QDOWNLOADERSERVICE_H
#define QDOWNLOADERSERVICE_H

#include <QObject>
#include <QQmlContext>
#include <QNetworkReply>
#include <QHash>
#include "qdownloader.h"

// name of the service which is available into qml
#define QDONWLOADER_QML_NAME "qdownloader"


//use this macro in your cpp to make your code simpler
#define QDOWNSERVICE QDownloaderService::getInstance()

/**
 * @brief The QDownloaderSErvice class
 * @version 1.2
 */
class QDownloaderService : public QObject {
    Q_OBJECT

    Q_PROPERTY(quint16 pending READ getPending NOTIFY pendingChanged )
    Q_PROPERTY(bool signalOnRootError READ getEmitSignalOnRootError WRITE setEmitSignalOnRootError NOTIFY emitSignalOnRootErrorChanged )

public:
    /**
     * @brief return instance of QDownloaderService service (singleton)
     * @return
     */
    static QDownloaderService & getInstance();

    /**
     * @brief this will register the service to be available into qml
     * @param context
     * @param name ; name for service (in qml), default to QDONWLOADER_QML_NAME
     */
    static void init(QQmlContext *context, const QString name = QDONWLOADER_QML_NAME);

    /**
     * @brief if to the "start" method fail, a false value is returned but not the error signal.
     * Setting this value to true will also emit the signal with the value QNetworkReply::OperationCanceledError
     * @view start
     * @param value true to also emit an error on "root" error (r/w, file exist...)
     */
    void setEmitSignalOnRootError(bool const value);


    /**
     * @brief return if the start method will emit an error signal
     * @return true if on error, the start method emit an error too
     */
    bool getEmitSignalOnRootError() { return signalOnRootError;}

    /**
     * @brief start downloading from "source" to "target" ; target should not exist
     *
     * @param source : source url
     * @param target : target file
     * @param message : for the notification, SailfishOS only, let blank for none
     * @return : true if starting downloading ( doesn't mean it will be successful
     */
    Q_INVOKABLE bool start(QString const & source, QString const & target, QString const &message = "" );

    /**
      * @brief return the number of file to donwload (including in donwload)
      * @return nb of files in/to donwload
      */
    Q_INVOKABLE quint16 getPending() const { return pending.size(); }

    /**
      * @brief check if "source" is pending i.e. is or to be donwload
      * @return true if "source" is in the list
      */
    Q_INVOKABLE bool isPending(QString const &source) { return pending.contains(source); }

signals:
    /**
     * @brief emited while downloading url
     * @param url : source url
     * @param read bytes read
     * @param total bytes
     */
    void downloading(QUrl const &url, qint64 read ,qint64 total);

    /**
     * @brief emited after finished donwloading url
     * @param url :  url of the file
     * @param target : absolute file path to the downloade resources
     */
    void success(QUrl const & url,QString const &target );

    /**
     * @brief download of url ended with error
     * @param url
     * @param status
     * @since 1.2 : ajout de target
     */
    void error(QUrl const & url, QString const &target, QNetworkReply::NetworkError status );

    /**
     * @brief all donwload done (with or without error)
     */
    void finished();

    /**
     * @brief emited when the number of files pending (to/in donwload) changed
     */
    void pendingChanged();

    /**
     * @brief emited if should emit a signal too when "start" fail
     */
    void emitSignalOnRootErrorChanged();

private:
    explicit QDownloaderService(QObject *parent = 0);

    QHash<QString,QDownloaderPtr> pending;

    bool signalOnRootError;

private slots:
    void downloadingImpl(QUrl const &url, qint64 read ,qint64 total);
    void successImpl(QUrl const & url,QString const &target );
    void errorImpl(QUrl const & url, QString const target, QNetworkReply::NetworkError status );

};

#endif // QDOWNLOADERSERVICE_H
