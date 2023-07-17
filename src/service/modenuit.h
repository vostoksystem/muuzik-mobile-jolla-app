#ifndef MODENUIT_H
#define MODENUIT_H

#include <QObject>
#include <QTimer>
#include <qqml.h>
#include <QQmlContext>

#include "lecteur.h"
#include "pulse/volumeProxy.h"

#include <nemonotifications-qt5/notification.h>

#define NUITSERVICE_QML_NAME "modeNuitService"

using namespace std;

class modeNuitService : public QObject {
    friend class Notification;

    Q_OBJECT
    Q_PROPERTY(bool actif READ getActif NOTIFY actifChanged )
    Q_PROPERTY(bool possible READ getPossible CONSTANT )
    Q_PROPERTY(quint64 tempsFinal READ getTempsFinale WRITE setTempsFinal NOTIFY tempsChanged )
    Q_PROPERTY(bool reductionVolume READ getReductionVolume WRITE setReductionVolume NOTIFY reductionVolumeChanged )
    Q_PROPERTY(quint32 volumeFinal READ getVolumeFinal WRITE setVolumeFinal NOTIFY volumeFinalChanged )

public:
    static  modeNuitService& getInstance();
    static void init(QQmlContext *context, QString name = NUITSERVICE_QML_NAME);

    // true si mode nuit possible (connection dbus active...)
    bool getPossible() const {return volume->isOk();}

    // true si le mode nuit est en cours
    bool getActif() const {return actif;}

    void setTempsFinal(quint64 const v);
    quint64 getTempsFinale() const {return tempsFinal;}

    void setReductionVolume(bool const v);
    bool getReductionVolume() const {return reductionVolume;}

    Q_INVOKABLE void setVolumeFinal(quint32 const v);
    quint32 getVolumeFinal() const {return volumeFinal;}

    /**
      *@brief active le mode nuit (si possible)
      */
    Q_INVOKABLE void demarrer();

    /**
      * @brief arrete le mode nuit
      */
    Q_INVOKABLE void arreter();

    /**
      * @brief temps restant avant arret, en seconde
      * @return le temps en secondes
      */
    Q_INVOKABLE quint32 tempRestant();

private:
    explicit modeNuitService(QObject *parent = 0);
    ~modeNuitService();

    lecteurService *lecteur;
    VolumeProxy *volume;

    bool actif; // true si le mode nuit est en cours

    quint64 tempsFinal;

    bool reductionVolume;
    quint32 volumeFinal;
    // doit garder un cache du volume actuel pour eviter les boucles initvolume/volumeChanged
    quint32 volumeActuel;

    QTimer tduree;
    QTimer tvolume;

    quint64 backduree;

    void initTimerVolume();

signals:
    void actifChanged();
    void tempsChanged();
    void reductionVolumeChanged();
    void volumeFinalChanged();

private slots:
    void changementPlaylist();
    void changementEtat(bool s);

    void finTemps();
    void finVolume();

    void changementCurrentStep(quint32 v);
};

#endif // MODENUIT_H
