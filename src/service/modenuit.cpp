#include "modenuit.h"
#include "mpris/mpris.h"
#include <QDebug>
#include "../app.h"

#include "pulse/volumeProxy.h"
#include "lecteur.h"

#include "../vi18n/vi18n.h"

#include <nemonotifications-qt5/notification.h>

/**
 * @brief modeNuitService::modeNuitService
 * @param parent
 */
modeNuitService::modeNuitService(QObject *parent) : QObject(parent),
    actif(false),
    tempsFinal(3600),reductionVolume(true),volumeFinal(0),volumeActuel(0)
{

    lecteur = &lecteurService::getInstance();
    connect(lecteur,SIGNAL(listeChanged()),this, SLOT(changementPlaylist()));
    connect(lecteur,SIGNAL(etatChanged(bool)),this, SLOT(changementEtat(bool)));

    volume = &VolumeProxy::getInstance();
    connect(volume,SIGNAL(currentStepChanged(quint32)),this, SLOT(changementCurrentStep(quint32)));

    volumeFinal = volume->getCurrentStep();
    volumeActuel = volumeFinal;

    connect(&tduree, SIGNAL(timeout()), this, SLOT(finTemps()));
    connect(&tvolume, SIGNAL(timeout()), this, SLOT(finVolume()));
}

/**
 * @brief modeNuitService::~modeNuitService
 */
modeNuitService::~modeNuitService() {

}

/**
 * @brief modeNuitService::getInstance
 * @return
 */
modeNuitService& modeNuitService::getInstance() {
    static modeNuitService instance;
    return instance;
}

/**
 * @brief modeNuitService::init
 * @param context
 * @param name
 */
void modeNuitService::init(QQmlContext *context,QString name) {
    context->setContextProperty(name, &modeNuitService::getInstance());
}

/**
 * @brief modeNuitService::setTemps
 * @param v
 */
void modeNuitService::setTempsFinal(quint64 const v) {
    tempsFinal=v;
    backduree=tempsFinal *1000;
    emit tempsChanged();
}

/**
 * @brief modeNuitService::setReductionVolume
 * @param v
 */
void modeNuitService::setReductionVolume(bool const v) {

    reductionVolume=v;
    emit reductionVolumeChanged();
}

/**
 * @brief modeNuitService::setVolume
 * @param v
 */
void modeNuitService::setVolumeFinal(const quint32 v) {

    if(v>=volume->getCurrentStep()) {
        return;
    }

    volumeFinal=v;
    emit volumeFinalChanged();
}

/**
  *@brief active le mode nuit (si possible)
  */
void modeNuitService::demarrer() {

    if(actif) {
        return;
    }

    actif=true;
    emit actifChanged();

    if(lecteur->getEtat()==false) {
        // le callback s'occupera de lancer les timers
        lecteur->lire();
    } else {
        tduree.setInterval(backduree);
        tduree.start();

        initTimerVolume();
    }

    Notification n;
    n.setPreviewBody(VI18N.get( "nuit.demarrer" ).arg(App::tempsHumaine(tempsFinal)));
    n.setHintValue("x-nemo-icon", "image://theme/icon-s-timer");
    n.publish();
}

/**
  * @brief arrete le mode nuit
  */
void modeNuitService::arreter() {

    if(actif==false) {
        return;
    }

    tduree.stop();
    tvolume.stop();
    backduree = tempsFinal*1000;
    actif=false;
    emit actifChanged();

    Notification n;
    n.setPreviewBody(VI18N.get( "nuit.arrete" ));
    n.setHintValue("x-nemo-icon", "image://theme/icon-s-message");
    n.publish();

    lecteur->stopper();
}

/**
  * @brief temps restant avant arret, en seconde
  * @return le temps en secondes
  */
quint32 modeNuitService::tempRestant() {
    return (tduree.remainingTime() > 0 ? tduree.remainingTime() : backduree) / 1000;
}

/**
 * @brief modeNuitService::changementPlaylist
 */
void modeNuitService::changementPlaylist() {

    quint64 t = lecteur->getDureeTotale();
    if(t==0) {
        // si en cours : arrete
        if(actif) {
            arreter();
        }

        tempsFinal=0;
        emit tempsChanged();
        return;
    }

    // @FIX ? on est à la seconde pres ?
    if( tempsFinal > 0 && tempsFinal <= t) {
        // a deja defini un temps utilisateur, skip
        return;
    }

    // def le temp ou clamp
    tempsFinal = t;
    emit tempsChanged();

    if(actif==false) {
        return;
    }

    if(lecteur->getEtat()) {
        // en lecture, verif si pas trop long
        quint64 v = tduree.remainingTime();

        if(v> tempsFinal*1000) {
            // liste a été réduite...
            tduree.stop();
            tduree.setInterval(tempsFinal*1000);
            tduree.start();
            initTimerVolume();
        }

        return;
    }

    // en pause
    // clamp la dure de timeout
    backduree = tempsFinal*1000 > backduree ? backduree : tempsFinal*1000;
}

/**
 * @brief modeNuitService::changementEtat
 * @param s
 */
void modeNuitService::changementEtat(bool s) {

    if(actif==false) {
        return;
    }

    // passe en lecture
    if(s) {
        tduree.setInterval(backduree);
        tduree.start();

        initTimerVolume();
        return;
    }

    // mettre en pause : arreter les timers
    backduree = tduree.remainingTime();
    tduree.stop();
    tvolume.stop();
}

/**
 * @brief signal du timer de temps
 */
void modeNuitService::finTemps() {

    arreter();
}

/**
 * @brief signal du timer de volume
 */
void modeNuitService::finVolume() {

    quint32 cv = volume->getCurrentStep();

    if( cv<= volumeFinal) {
        // fin, on ne touche plus au volume
        // on laisse le tduree s'occuper de stopper la lecture : eviter les croisements start/stop
        return;
    }

    if(tduree.isActive()==false) {
        return;
    }

    volume->setCurrentStep(cv-1);

    // NOTA : pas la peine, changementCurrentStep s'en charge
    // initTimerVolume();
}

/**
 * @brief modeNuitService::initTimerVolume
 */
void modeNuitService::initTimerVolume() {
    if(actif==false) {
        return;
    }

    if(reductionVolume==false) {
        return;
    }

    tvolume.stop();

    if(tduree.isActive()==false) {
        return;
    }

    qint32 d =  volume->getCurrentStep() - volumeFinal;
    if(d<0) {
        return;
    }

    quint64 v = tduree.remainingTime();
    tvolume.setInterval(v/(d+1));
    tvolume.start();
}

/**
 * @brief modeNuitService::changementCurrentStep
 * @param v
 */
void modeNuitService::changementCurrentStep(quint32 v) {
    if(actif==false) {
        return;
    }

    initTimerVolume();
}
