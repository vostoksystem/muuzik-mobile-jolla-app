/*
  Copyright (C) 2016 Jerome levreau / vostoksystem.
  Contact: contact <contact@vostoksytem.eu>
  All rights reserved.

  Apache 2.0 Licence

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  */

#ifndef VFINFO_H
#define VFINFO_H

#include <QObject>

using namespace std;

class VFService;

/**
 * @brief The VFInfo class hold information about a resource into the virtual tree
 * @version 1.0
 * @author levreau.jerome@vostoksystem.eu
 */
class VFInfo : public QObject {
    Q_OBJECT

    Q_PROPERTY(quint64 uuid READ getUuid CONSTANT)
    Q_PROPERTY(QString vurl READ getVUrl CONSTANT)
    Q_PROPERTY(QString source READ getSource CONSTANT)
    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(QString filename READ getFilename CONSTANT)
    Q_PROPERTY(VFType type READ getType CONSTANT)

    Q_PROPERTY(quint16 grouppid READ getGroupId CONSTANT)
    Q_PROPERTY(quint16 userid READ getUserId CONSTANT)
    Q_PROPERTY(quint64 timestamp READ getTimestamp CONSTANT)
    Q_PROPERTY(quint64 size READ getSize CONSTANT)

    friend class VFService;

public :
    explicit VFInfo(QObject *parent = 0);
    // ~VFInfo();

    enum VFType {
        DIRECTORY,
        FILE
    };
    Q_ENUM(VFType)

    /**
     * @brief unique id for this object - not linked to uri or absolut path -
     * so two identical obj - event when using "copy" - will have different uuid
     * @return
     */
    quint64 getUuid() const {return uuid;}

    /**
     * @brief url to the resource into the virtual tree (name included)
     * @param v
     */
    QString getVUrl() const {return vurl;}

    /**
     * @brief path to the "mounting" point of uri, into the real system
     * so source+uri = absolutePath
     * with obfuscate resources, one source is used arbitrary
     * @param v
     */
    QString getSource() const {return source;}

    /**
     * @brief the type of resource
     * @param t
     */
    VFInfo::VFType getType() const {return type;}

    /**
     * @brief return the name of the file strip from path an extension
     * @param v
     */
    QString getName() const {return name;}

    /**
     * @brief get the name of the file, without path but with type extension
     * @return
     */
    QString getFilename() const {return filename;}

    /**
     * @brief setGroupId
     * @param v
     */
    quint16 getGroupId() const {return grouppid;}

    /**
     * @brief setUserId
     * @param v
     */
    quint16 getUserId() const {return userid;}

    /**
     * @brief creation date
     * @param v
     */
    quint64 getTimestamp() const {return timestamp;}

    /**
     * @brief setSize
     * @param v
     */
    quint64 getSize() const {return size;}

    /**
     * @brief check if this is a directory
     * @return
     */
    bool isDirectory() { return type == DIRECTORY; }

    /**
     * @brief check if this is a file
     * @return
     */
    bool isFile() { return type == FILE; }

    /**
     * @brief copy obj into a new object
     * NOTA : only copy data, no signal nor property
     * @param obj
     * @return
     */
    static VFInfo *copy(VFInfo *obj);

protected:
    quint64 uuid;       // unique id

    QString vurl;       // path to the resource into the virtual tree (name included)
    QString source;     // path to the "mounting" point of uri, into the real system
    QString name;       // readable name (no extension)
    QString filename;    // plain file name (with extension)
    VFType type;        // type of resource

    quint16 grouppid;   // groupid on the system (owner)
    quint16 userid;     // user id on the system (owner)
    quint64 timestamp;  // creation date
    quint64 size;       // size in bytes

//    void setVurl(const QString & v) {vurl=v;}
//    void setName(const QString & v) {name=v;}
//    void setFilename(const QString & v) {name=v;}
//    void setType(const VFInfo::VFType t) {type = t;}

//    void setSize(const quint64 v) {size=v;}
//    void setTimestamp(const quint64 v) {timestamp=v;}
//    void setUserId(const quint16 v) {userid=v;}
//    void setGroupId(const quint16 v) {grouppid=v;}


    static bool orderByName(VFInfo *a, VFInfo *b);

    static bool orderBySize(VFInfo *a, VFInfo *b);

    static bool orderByDate(VFInfo *a, VFInfo *b);

    static bool orderByUri(VFInfo *a, VFInfo *b);

private:
    Q_DISABLE_COPY(VFInfo)

};
typedef QList<VFInfo *> VFInfoList;

#endif // VFINFO_H
