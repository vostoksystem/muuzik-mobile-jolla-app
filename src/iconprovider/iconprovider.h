/*
 * With an icon provider you can load an icon (png) from qrc or local resources,
 * in a specific colour with just an id string
 *
 * Install :
 * Copy the src/iconprovider to the root of your src project's directory
 * Add the pri file to your pro file
 *
 * Usage :
 * You can use the iconProvider in Qt or qml
 *
 * For qml, register the service into your main :
 * QScopedPointer<QQuickView> view(SailfishApp::createView());
 * IconProvider::init(view.data(),"MyProvider");
 *
 * assuming you created a file sdcard under resource img,You can then access image with url like this :
 * image://MyProvider/img/sdcard
 *
 * For QT , create a new instance or just use the default one with getInstance
 * id would then be : "img/sdcard"
 *
 * Path format :
 * path can be absolute
 * if start by "~", set againt home directory
 * if relative :  on sailfish resolve to the root of the project, for other QT project, relative to current
 * working directory
 *
 * Qrc resources have priority over local resources
 *
 * Check the sample code
 */

#ifndef ICONPROVIDER_H
#define ICONPROVIDER_H

#include <QObject>
#include <QQuickImageProvider>
#include <QQuickView>

class IconProvider : public QQuickImageProvider {

public:
    /**
     * @brief return a default iconprovider instance. Only look into qrc
     * @return
     */
    static IconProvider& getInstance();

    /**
     * @brief create a new icon provider
     * @param path ; path to more local img. Note qrc has priority over local resources
     */
    IconProvider(const QString &path = "" );

    /**
     * @brief register a new icon provider as "name" into the view for use with qml
     * @param view : pointer to the view
     * @param name : name under whom iconprovider can be used into qml
     * @param path : additionnal path to img resources ; will still look under qrc first
     */
    static void init(const QQuickView *view, const QString &name, const QString &path = "");

    /**
     * @brief Return an icon for id in the form <path> or <path>?<color> ; color optionnal
     * @param id : id string for the icon, full alias path for qrc, relative path for direct img (without .png)
     * @param size : size of current pixmat
     * @param requestedSize ; can be width/height 0 for no resize
     * @return pixmap for "id", might be empty if id not found
     */
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);

private :

    QString path;
};


#endif // ICONPROVIDER_H
