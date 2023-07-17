#ifndef LASTFMSERVICE_H
#define LASTFMSERVICE_H

#include <QObject>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <qqml.h>
#include <QJsonObject>

using namespace std;

#ifndef LOCALPATH
#define LOCALPATH "localpath"
#endif

#define LASTFMSERVICE_QML_NAME "LastfmService"


class lastfmService : public QObject {
    friend class QNetworkAccessManager;

    Q_OBJECT
    Q_PROPERTY(bool enCours READ estEnCours NOTIFY enCoursChanged)

public:
    static lastfmService& getInstance();

    /**
     * @brief register the service into the context so it can be used in qml
     * @param context
     * @param name : register service on this name, default to LASTFMSERVICE_QML_NAME
     */
    static void init(QQmlContext *context, QString name=LASTFMSERVICE_QML_NAME);


    /**
     * @brief status du service last.fm
     * @return vrai si un scan est en cours
     */
    Q_INVOKABLE bool estEnCours() const {
        return raf;
    }

    /**
     * @brief annule une requete (web) en cours
     */
    Q_INVOKABLE void annuler() {

    }

    /**
     * @brief retourne une bio, depuis local ou net
     * @param nom de l'artiste
     * @return si existe déjà ou vide si en attente depuis web
     */

    Q_INVOKABLE QString biographie(QString const &nom);

    /**
     * @brief retourne la liste des album de l'artiste au mbid
     * @param mbid de l'artiste
     * @return si existe déjà ou vide si en attente depuis web
     */
    Q_INVOKABLE QString topAlbum(QString const &mbid);

    /**
     * @brief efface la version locale d'une bio (et top album)
     * @param nom de de la bio
     */
    Q_INVOKABLE void effacerBio(QString const &nom);
    Q_INVOKABLE void effacerTopAlbum(QString const &mbid);


private :
    explicit lastfmService(QObject *parent = 0);

    bool raf;
    QNetworkAccessManager *manager;

    /**
   * @brief recherche une bio en local
   * @param nom
   * @return
   */
    static QString lireBio(QString const &nom);

    /**
     * @brief ecriture de la bio en cache; fait la convertion url
     * @param nom
     * @param data json sous forme de string
     */
    static void ecrireBio(QString const &nom, const QString &data);

    /**
     * @brief lireTopAlbum
     * @param mbid
     * @return
     */
    static QString lireTopAlbum(QString const &mbid);

    /**
     * @brief ecrireTopAlbum
     * @param mbid
     * @param data
     */
    static void ecrireTopAlbum(QString const &mbid, const QString &data);

    /**
     * @brief lire un fichier json / texte; fait la convertion url
     * @param url
     * @return le fichier sous forme texte
     */
    static QString lire(QString const &url);

    /**
     * @brief ecrire un fichier json/txt ; fait la convertion url
     * @param url
     * @param data
     */
    static void ecrire(QString const &url, const QString &data);

signals:
    void enCoursChanged();

    void trouveBio(QString donnee);

    void trouveTopAlbum(QString donnee);


private slots:
    /**
     * @brief reponse reseau
     * @param reply
     */
    void reponseNet(QNetworkReply *reply);
};

#endif // LASTFMSERVICE_H
