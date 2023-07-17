#include "iconprovider.h"
#include <QPainter>
#include <QDebug>
#include <sailfishapp.h>
#include <QDir>

/**
 * @brief return a default iconprovider instance. Only look into qrc
 * @return
 */
IconProvider& IconProvider::getInstance() {
    static IconProvider instance;
    return instance;
}

/**
 * @brief create a new icon provider
 * @param path ; path to more local img. Note local has priority over qrc resources
 */
IconProvider::IconProvider(const QString &path ) : QQuickImageProvider(QQuickImageProvider::Pixmap) {

    if(path.length()==0) {
        return;
    }

    this->path=path;

    if(path.at(0) == '~') {
        this->path.replace("~", QDir::homePath());
        return;
    }

    // I would go for simple test on "/" but because of windoze, must check if dir exist instead
    QDir dir(path);
    if(dir.exists()) {
        return;
    }

    // relative
#ifdef LIBSAILFISHAPP_SAILFISHAPP_H
    this->path = SailfishApp::pathTo(path).toString(QUrl::RemoveScheme);
#else
    QDir tmp(QDir::currentPath());
    this->path=QDir::cleanPath(tmp.absoluteFilePath(path));
#endif
}

/**
 * @brief Return an icon for id in the form <path> or <path>?<color> ; color optionnal
 * @param id : id string for the icon, full alias path for qrc, relative path for direct img (without .png)
 * @param size : size of current pixmat
 * @param requestedSize ; can be width/height 0 for no resize
 * @return pixmap for "id", might be empty if id not found
 */
QPixmap IconProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) {
    QStringList parts = id.split('?');

    QPixmap img(":/" + parts.at(0) );

    if(img.isNull() && (path.length() !=0)) {
        QDir dir(this->path);
        img.load(dir.absoluteFilePath(parts.at(0) + ".png"));
    }

    if(img.isNull()) {
        return img;
    }

    if(size){
        *size  = img.size();
    }

    if(parts.length() > 1 && QColor::isValidColor(parts.at(1))) {
        QPainter painter(&img);
        painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
        painter.fillRect(img.rect(), parts.at(1));
        painter.end();
    }

    if(requestedSize.width() > 0 && requestedSize.height() > 0) {
        return img.scaled(requestedSize.width(), requestedSize.height(), Qt::IgnoreAspectRatio);
    }

    return img;
}

/**
 * @brief register a new icon provider as "name" into the view for use with qml
 * @param view : pointer to the view
 * @param name : name under whom iconprovider can be used into qml
 * @param path : additionnal path to img resources ; will still look under qrc first
 */
void IconProvider::init(const QQuickView *view, const QString &name, const QString &path) {
    view->engine()->addImageProvider(name.toLatin1(), new IconProvider(path));
}

