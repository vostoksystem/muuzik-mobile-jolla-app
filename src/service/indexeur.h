#ifndef INDEXEURSERVICE_H
#define INDEXEURSERVICE_H

#include <QObject>
#include <qqml.h>
#include <QQmlContext>
#include "../util/daoindexeur.h"

#define INDEXEURSERVICE_QML_NAME "IndexeurService"

#define INDEXEUR_DATE "indexeur/date"
#define INDEXEUR_DATE_DEF 0

#define INDEXEUR_THRESHOLD_REFRESH 50

/**
 * @brief The indexeurService class
 */
class IndexeurService : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool enCours READ estEnCours NOTIFY enCoursChanged )
    Q_PROPERTY(bool dbok  READ getDbok NOTIFY dbOkChanged )

public:
    static IndexeurService& getInstance();
    static void init(QQmlContext *context, QString name = INDEXEURSERVICE_QML_NAME);

    /**
      * reinit la base de donne
      */
    Q_INVOKABLE void recharger();

    /**
     * @return vrai si un scan est en cours
     */
    Q_INVOKABLE bool estEnCours() const {
        return enCours;
    }

    /**
     * @return vrai si la db est initialisé
     */
    Q_INVOKABLE bool getDbok() const {
        return dbok;
    }

    /**
     * @brief teste si doit faire une mise à jour de la db
     * // si oui, enchaine sur un rechargement
     * @return
     */
    void verifierMiseaJour();

protected :
    void setEncours(bool v);

private:
    explicit IndexeurService(QObject *parent = 0);

    bool enCours; // remplissage de la db en cours
    bool dbok; // true si la db a été init

    static const QRegularExpression REG_fichieraudio;

    // fonction lié au thread pour le rechargement
    static void doRechargement();

    // scanne récursivement les reps et met à jour la db
    static void recurRechargement(const QString &vurl);

    // fait le test
    static void doVerifierMiseAJour();

    // recup dans les rep et retourne la date la plus récente
    static quint64 recurMiseAJour(const QString &vurl);


signals:
    void enCoursChanged();
    void dbOkChanged();

    // rechargement fait (interne)
    void rechargementFaitIntr();

    // la verification de l'etat de la db est faite
    void miseAJoursFaiteIntr(quint64 timestamp);

protected slots:

    void finVerifierMiseAJourImpl(quint64 timestamp);
    void finRechargementImpl();

public slots:
    // suppression de l'url ( et de tout les childs)
    void onRemoved(QString vurl);
    void onMoved(QString vurl, QString as);
    void onRenamed(QString vurl, QString name);
};

#endif // INDEXEURSERVICE_H
