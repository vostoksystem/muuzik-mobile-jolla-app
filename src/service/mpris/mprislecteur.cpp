#include "mprislecteur.h"
#include "../pulse/volumeProxy.h"

MprisLecteur::MprisLecteur(lecteurService *s): QDBusAbstractAdaptor(s),service(s),taille(0) {
    connect(s,SIGNAL(titreChanged(MetaData*)),this, SLOT(changementTitre(MetaData*)));
    connect(s,SIGNAL(listeChanged()),this, SLOT(changementPlaylist()));
    connect(s,SIGNAL(modeChanged()),this, SLOT(changementMode()));
    connect(s,SIGNAL(etatChanged(bool)),this, SLOT(changementEtat(bool)));
}

/**
 * @brief MprisLecteur::Next
 */
void  MprisLecteur::Next(){
    qDebug() << "!!! MprisLecteur::Next";

    service->suivant();
}

/**
 * @brief MprisLecteur::Previous
 */
void MprisLecteur:: Previous(){
    qDebug() << "!!! MprisLecteur::Previous";

    service->precedent();
}

/**
 * @brief MprisLecteur::Pause
 */
void  MprisLecteur::Pause(){
    qDebug() << "!!! MprisLecteur::Pause";

    if( service->getEtat()==false) {
        return;
    }

    service->lire();
}

/**
 * @brief MprisLecteur::PlayPause
 */
void  MprisLecteur::PlayPause(){
    qDebug() << "!!! MprisLecteur::PlayPause";

    service->lire();
}

/**
 * @brief MprisLecteur::Stop
 */
void  MprisLecteur::Stop(){
    qDebug() << "!!! MprisLecteur::Stop";

    service->stopper();
}

/**
 * @brief MprisLecteur::Play
 */
void  MprisLecteur::Play(){
    qDebug() << "!!! MprisLecteur::Play";
    if( service->getEtat() == true) {
        return;
    }

    service->lire();
}

/**
 * @brief MprisLecteur::Seek
 * @param offset
 */
void MprisLecteur::Seek(qlonglong offset) {
    service->avancer(offset/1000);
}

void MprisLecteur::SetPosition(const QDBusObjectPath &TrackId, qlonglong Position) {

}

void  MprisLecteur::OpenUri(QString uri){

}

/**
 * @brief MprisLecteur::getPlaybackStatus
 * @return
 */
QString MprisLecteur::getPlaybackStatus() {
    if (service->getEtat()==true) {
        return "Playing";
    }

    if(service->getTaille()==0) {
        return "Stopped";
    }

    return "Paused";
}

/**
 * @brief MprisLecteur::getLoopStatus
 * @return
 */
QString MprisLecteur::getLoopStatus() {
    if(service->getBoucle()) {
        return "Playlist";
    }
    return "None";
}

/**
 * @brief MprisLecteur::setLoopStatus
 * @param v
 */
void  MprisLecteur::setLoopStatus(QString v) {
    if( v.compare("None",Qt::CaseInsensitive)==0 && service->getBoucle()==true) {
        service->switchBoucle();
        return;
    }

    if(service->getAleatoire()==false) {
        service->switchBoucle();
    }
}

/**
 * @brief MprisLecteur::getShuffle
 * @return
 */
bool MprisLecteur::getShuffle() {
    return service->getAleatoire();
}

void MprisLecteur::setShuffle(bool v) {
    if(service->getAleatoire() == v) {
        return;
    }

    service->switchAleatoire();
}

/**
 * @brief MprisLecteur::getPosition
 * @return
 */
qlonglong MprisLecteur::getPosition() {
    return service->getPosition()*1000;
}

/**
 * @brief MprisLecteur::getMetadata
 * @return
 */
QVariantMap MprisLecteur::getMetadata() {
    return metadata;
}

double MprisLecteur::getVolume() {
    double m = VolumeProxy::getInstance().getStepCount();
    if(m==0) {
        return 0;
    }

    double v = VolumeProxy::getInstance().getCurrentStep();

    return v/m;
}

void MprisLecteur::setVolume(double v) {
    double m = VolumeProxy::getInstance().getStepCount();
    if(m==0) {
        return ;
    }

    VolumeProxy::getInstance().setCurrentStep(v*m);
}

/**
 * @brief MprisLecteur::getCanGoNext
 * @return
 */
bool MprisLecteur::getCanGoNext() {
    return service->aSuivant();
}

/**
 * @brief MprisLecteur::getCanGoPrevious
 * @return
 */
bool MprisLecteur::getCanGoPrevious() {
    return service->aPrecedent();
}

/**
 * @brief MprisLecteur::getCanPlay
 * @return
 */
bool MprisLecteur::getCanPlay() {
    return service->getTaille()>0;
}

/**
 * @brief MprisLecteur::changementTitre
 * @param t
 */
void MprisLecteur::changementTitre(MetaData *t) {
    metadata.clear();
    if( t!=NULL) {
        metadata.insert("mpris:trackid","/org/mpris/MediaPlayer2/muuzik/"+t->getUuid());
        metadata.insert("mpris:length",t->getDuree()*1000);
        metadata.insert("mpris:artUrl","qrc:///img/son");
        metadata.insert("xesam:title",t->getTitre());
        metadata.insert("xesam:album",t->getAlbum());
        metadata.insert("xesam:artist",t->getArtiste());
        metadata.insert("xesam:contentCreated", QDate(t->getAnnee(),1,1) );
    }

    QVariantMap p;
    p.insert("Metadata", metadata);
    p.insert("CanGoNext", getCanGoNext());
    p.insert("CanGoPrevious", getCanGoPrevious());


    sendDBusProperty(p);
}

/**
 * @brief MprisLecteur::changementPlaylist
 */
void MprisLecteur::changementPlaylist() {

    QVariantMap p;

    quint64 t=service->getTaille();

    if( t!=taille) {
        taille=t;
        bool b=getCanPlay();
        p.insert("CanPlay", b);
        p.insert("CanPause", b);
        p.insert("CanSeek", b);
    }

    p.insert("CanGoNext", getCanGoNext());
    p.insert("CanGoPrevious", getCanGoPrevious());

    sendDBusProperty(p);
}

/**
 * @brief MprisLecteur::changementEtat
 * @param s
 */
void MprisLecteur::changementEtat(bool s) {
    QVariantMap p;
    p.insert("PlaybackStatus", getPlaybackStatus());
    sendDBusProperty(p);
}

/**
 * @brief MprisLecteur::changementMode
 */
void MprisLecteur::changementMode() {
    QVariantMap p;
    p.insert("Shuffle", getShuffle());
    p.insert("LoopStatus", getLoopStatus());
    sendDBusProperty(p);
}

/**
 * @brief MprisLecteur::sendDBusProperty
 * @param value
 */
void MprisLecteur::sendDBusProperty(const QVariantMap value) {
    QDBusMessage signal = QDBusMessage::createSignal(MPRIS_OBJ,FREEDESKTOP_PROPERTIES,"PropertiesChanged" );
    signal << MPRIS_PLAYER_ID;
    signal << value;
    signal << QStringList();
    QDBusConnection::sessionBus().send(signal);
}


