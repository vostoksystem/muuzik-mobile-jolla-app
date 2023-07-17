#ifndef APP_H
#define APP_H

#include <QObject>
#include <qqml.h>
#include <QRegularExpression>

#include <nemonotifications-qt5/notification.h>

using namespace std;

#ifndef RETOURLIGNE
#define RETOURLIGNE "&#10;"
#endif

#ifndef ESPACE
#define ESPACE "%20"
#endif

typedef QList<QString *> QStringPtrListe;
typedef QList<QString > QStringListe;

/**
 * @brief The App class
 */
class App  {

public :
    static const long BUFFER = 2048;
    static const uint TEMPSMAX = 900;
    static const long MINIMUM = 1024;

    static const QString IMG_REPERTOIRE;
    static const QString IMG_AUDIO;
    static const QString IMG_ALBUM;
    static const QString IMG_TITRE;
    static const QString IMG_FAV;
    static const QString IMG_HISTORIQUE;
    static const QString IMG_DEFAULT;

    static const QRegularExpression REG_fichierimage;
    static const QRegularExpression REG_fichiercover;
    static const QRegularExpression REG_fichieraudio;
    static const QRegularExpression REG_fichierpourart;

    /**
     * @brief tailleHumaine
     * @param v
     * @return
     */
    static QString tailleHumaine(const long v);

    /**
     * @brief retourne une chaine sous la forme xx:xx:xx
     * @param v
     * @return
     */
    static QString tempsHumaine(const long v);

    /**
     * @brief recherche un icone/miniature pour un repertoire
     * NOTA : va rechercher la miniature du premier fichier audio trouvé
     * @param v url physique du rep (pas virtuelle)
     * @return uri vers l'image
     */
    //  static QString getPochetteDepuisRep(const QString &v);

    /**
     * @brief recherche un icone/miniature pour un repertoire
     * NOTA : va rechercher la miniature du premier fichier audio trouvé
     * @param v url VIRTUELLE du rep (pas physique)
     * @return uri vers l'image
     */
    //  static QString getMiniaturePourRepVirtuel(const QString &v);

    /**
     * @brief recherche une miniature pour un fichier audio
     * @param v url physique du fichier (pas virtuelle)
     * @return
     */
    //   static QString getMiniaturePourAudio(const QString &v);

    /**
     * @brief cherche une miniature dans le rep PHYSIQUE
     * @param v
     * @return
     */
    //   static QString getMiniatureDansRep(const QString &v);

    /**
     * @brief la notification ou null
     * @param id
     * @return
     */
    static Notification *trouverNotification(quint32 id);



};

#endif // APP_H
