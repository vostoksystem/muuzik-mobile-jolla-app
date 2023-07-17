#include "infos.h"

/**
 * @brief infosService::infosService
 * @param parent
 */
infosService::infosService(QObject *parent) : QObject(parent) {

}

/**
 * @brief infosService::getInstance
 * @return
 */
infosService& infosService::getInstance() {
    static infosService instance;
    return instance;
}

//http://ws.audioscrobbler.com/2.0/?method=artist.search&artist=pink%20floyd&api_key=edb5727ffe1a4ac4c0aca7c4d068aa16&format=json
//http://ws.audioscrobbler.com/2.0/?method=artist.getinfo&artist=pink%20floyd&api_key=edb5727ffe1a4ac4c0aca7c4d068aa16&format=json
//http://ws.audioscrobbler.com/2.0/?method=album.getinfo&api_key=edb5727ffe1a4ac4c0aca7c4d068aa16&artist=pink%20floyd&album=atom%20heart%20mother&format=json

