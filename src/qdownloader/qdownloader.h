#ifndef QDOWNLOADER_H
#define QDOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QStringList>

class QDownloaderService;

/**
 * @brief this object can be used to download asynchronously a remote file to a local location.
 * This class is intented to be used for a single call only
 *
 * On success, "target" is availbalbe else all tempory data is removed
 *
 * @see qdownloaderservice
 * @version 1.1
 * @author levreau.jerome@vostoksystem.eu
 */
class QDownloader : public QObject {
    Q_OBJECT

    friend class QNetworkAccessManager;
    friend class QDownloaderService;

public:
    explicit QDownloader(QObject *parent = 0);
    virtual ~QDownloader();

    /**
     * @brief start downloading from "source" to "target" ; target should not exist
     * this method will fail if the object is downloading. So even you can reuse it, it's not recommended
     *
     * @param source : source url
     * @param target : target file
     * @param message : for the notification, SailfishOS only, let blank for none
     * @return : true if starting downloading ( doesn't mean it will be successful
     */
    bool start(QString const & source, QString const & target, QString const &message = "" );

    /**
     * @brief return the source url as QString
     * don't call this method if "start" failed
     *
     * @return the "url"  for "source" as set in "start"
     */
    const QUrl &getUrl() const {return url; }

    /**
     * @brief return the target file name / path.
     * don't call this method if "start" failed or donwload was unsuccessful
     *
     * @return the file generated from "target" as set in "start"
     */
    const QFile &getFile() const {return file;}

signals:
    /**
     * @brief emited while downloading
     * @param url : source url
     * @param read bytes read
     * @param total bytes
     */
    void downloading(QUrl const &url, qint64 read ,qint64 total);

    /**
     * @brief emited after finished donwloading
     * @param url :  url of the file
     * @param target : absolute file path to the downloade resources
     */
    void success(QUrl const & url,QString const &target );

    /**
     * @brief download ended with error
     * @param url
     * @param target
     * @param status
     * @since 1.1 : added target param
     */
    void error(QUrl const & url, QString const &target, QNetworkReply::NetworkError status );

private:
    QNetworkAccessManager *manager;
    QNetworkReply *reply;

    QString notification;

protected :
    QUrl url;
    QFile file;

private slots:
    void onDownloadProgress(qint64 bytesRead,qint64 bytesTotal);
    void onFinished(QNetworkReply* reply);
    void onReadyRead();
    void onReplyFinished();
};
typedef QSharedPointer<QDownloader> QDownloaderPtr;

#endif // QDOWNLOADER_H
