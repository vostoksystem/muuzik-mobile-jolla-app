#ifndef RECENTSERVICE_H
#define RECENTSERVICE_H

#include <QObject>
#include <QDate>
#include <qqml.h>
#include <QQmlContext>

#include "../bean/listeitem.h"

#define RECENTSERVICE_QML_NAME "recentService"

class recentService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool enCours READ estEnCours NOTIFY enCoursChanged )
    Q_PROPERTY(QStringList liste READ getListe NOTIFY listeChanged )

public:
    static recentService& getInstance();
    static void init(QQmlContext *context, QString name = RECENTSERVICE_QML_NAME);

    typedef struct{
        QString vurl;
        qint64 timestamp;
    } Item;

    /**
     * @return vrai si un scan est en cours
     */
    Q_INVOKABLE bool estEnCours() const { return raf; }

    /**
      *  @brief rechearger la liste des albums en fonction de leurs dates de publication
      */
    Q_INVOKABLE void recharger();

    /**
     * @brief retourne la liste des albums par ordre décroissant (date)
     * @return liste des url (virtuelle)
     */
    Q_INVOKABLE const QStringList getListe();

    /**
      * @brief retroune un "vrai" nombre aleatoire \ Math.random
      * ici pour eviter de créer un nouveau service
      * @param max : valeur max
      * @return val entre 0 et max
      */
    Q_INVOKABLE quint64 random(quint64 max);

private:
    explicit recentService(QObject *parent = 0);

    bool raf; // remplissage de la db en cours

    QStringList liste; // la liste des albums classés par ordre de date

    //cache des albums
    QList<Item> cache;

    /**
     * @brief fait le rechargement : loop sur les sources(
     */
    static void doRechargement();

    /**
     * @brief boucle récursive sur les répertoires
     * @param url : url sous "base"
     * @return liste des "albums" sous "base"
     */
    static QStringList recur(const QString &vurl);

    void constuireListePublique();


signals:
    void enCoursChanged();

    // emit quand la liste a changé
    void listeChanged();

    // rechargement fait (interne)
    // liste des url BRUTE
    void rechargementFaitIntr(const QList<Item> l);

protected slots:
    // le thread a fini de recharger la liste
    // liste des url BRUTE
    void finRechargementImpl(const QList<Item> l);

public slots:
    // suppression de l'url ( et de tout les childs)
    void onRemoved(QString vurl);
    void onMoved(QString vurl, QString as);
    void onRenamed(QString vurl, QString name);
    void onDateChanged(QString vurl, quint64 timestamp);
};


#endif // RECENTSERVICE_H
