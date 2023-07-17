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

#ifndef VFSERVICE_H
#define VFSERVICE_H

#include <QObject>
#include <QString>
#include <QQmlContext>
#include "VFInfo.h"
#include "vfstat.h"
#include <QFileInfo>
#include <QDir>
#include <qqml.h>

using namespace std;

#define VFSERVICE_QML_NAME "VFService"

#define VFI VFService::getInstance()

/**
 * @brief The VFService class is a service, compatible with qt/wml and give you access
 * to different file operations into the virtual file system
 *
 * In order to use the service, you MUST register it into the main application with
 * the init method
 *
 * vfs : virtual file system, e.i. uri is relative to the vfs, NOT the OS partition,
 * unix like format, MUST start with "/" (ak the root of the virtual file system)
 *
 * @version 1.7
 * @author levreau.jerome@vostoksystem.eu
 */
class VFService : public QObject {
    Q_OBJECT

public:

    // how to order result
    // you can access enum from the qml object VFEnum ; note VFOrder and VFType shre the same numeric value
    enum VFOrder { ALPHA,   // alphabetic order ; for recursive op you might consider URI instead
                   DATE,    // newer first ; directory still first alphabetic order
                   SIZE,    // smallest first ; directory still first alphabetic order
                   URI,     // order by their uri (alpha ascending) ; for non recursive op same a ALPHA
                   NONE     // don't order result
                 };
    Q_ENUM(VFOrder)

    // what to look for
    // you can access enum from the qml object VFEnum ; note VFOrder and VFType shre the same numeric value
    enum VFType { BOTH,     // both directories and files
                  DIR,      // only directories, current directory
                  FILE,     // Only files, current directory
                  RECURSIVE // ALL files, scan recursively

                };
    Q_ENUM(VFType)

    static const QString FILTERNONE; // "";
    static const QString FILTERAUDIO; // "\\.(mp3|ogg|flac|m4a|m4b|wav|aif|aiff|opus)$";
    static const QString FILTERVIDEO; // "\\.(mkv[avi|mp4|m4v|mpg|mov|3gp)$";
    static const QString FILTERIMAGE; // "\\.(jpg|jpeg|png|gif)$";
    static const QString FILTERTEXT; // "\\.(txt|text)$";
    static const QString FILTERDOCUMENT; // "\\.(txt|text|doc|docx|xls|pps|ppsx|odt|ods|odp|pdf)$";
    static const QString FILTERPDF; // "\\.(pdf)$";

    /**
     * @brief instance (singleton) for the service
     * @return
     */
    static VFService& getInstance();

    /**
     * @brief register the service into the context so it can be used in qml
     * @param context
     * @param name : register service on this name, default to VFSERVICE_QML_NAME
     */
    static void init(QQmlContext *context, QString name=VFSERVICE_QML_NAME);

    /*************************************************************
    * Sources: this is the list of directory, into the "real" system
    * that're going to be conbined and act as "root" for the virtual file system
    * default is root of the user's directory
    *
    * NOTA : if a source collide with an already regired one (parent / child directory),
    * it's discarded
    *************************************************************/

    /**
     * @brief add a new source location (absolute path, directory)
     * @param src : path to the directory
     * @return true if successfully added (exit)
     */
    bool addSource(const QString &path);

    /**
     * @brief remove a source from the system
     * @param path to the directory (absolute path)
     */
    void removeSource(const QString &path);

    /**
     * @brief replace all sources with a new list
     * @param paths
     * @return true if all source set, else false
     */
    bool setSources(const QList<QString> &paths);

    /**
     * @brief return the current list of sources
     * @return
     */
    QList<QString> getSources() const {return srcs;}

    /**
     * @brief return true if path as source
     * @param path
     * @return
     */
    bool SourceExist(const QString & path);

    /*************************************************************
     * control
    *************************************************************/

    /**
     * @brief define if hidden files and dir (start with a dot ) must by listed, default to false
     * This parameter apply only to "get", "countDirectories", "countFiles" methods
     * @param val : true, include in "get" else skipped
     */
    Q_INVOKABLE void setHidden(bool val);

    /**
     * @brief if hidden files are taking into account
     * @return
     */
    Q_INVOKABLE bool getHidden() const {return hidden;}


    /*************************************************************
     * base op
    *************************************************************/

    /**
     * @brief check if resource exist AND is readable
     * @param vurl
     * @return true if exist
     */
    Q_INVOKABLE bool exist(const QString &vurl);

    /**
     * @brief check if can write into directory or override / create file
     * @param vurl
     * @return
     */
    Q_INVOKABLE bool isWritable(const QString &vurl);

    /**
     * @brief check if uri is a valid directory
     * @param uri
     * @return
     */
    Q_INVOKABLE bool isDirectory(const QString &vurl);

    /**
     * @brief check if uri is a valid file
     * @param vurl
     * @return
     */
    Q_INVOKABLE bool isFile(const QString &vurl);

    /**
     * @brief check if uri at root of vfs
     * @param vurl
     * @return true if root, esle false
     */
    Q_INVOKABLE bool isRoot(const QString &vurl);

    /**
     * @brief check if "parent" is a parent directory of "vurl" (direct or indirect)
     * NOTA : can also be used with regular url/path
     * @param parent vurl to check against
     * @param vurl
     * @return true if vurl "child" of parent
     */
    Q_INVOKABLE bool isParent(const QString &parent, const QString &vurl);

    /**
     * @brief return the parent for an vurl (until root e.i. "/")
     * @param vurl
     * @return parent vurl or "/" if already root
     */
    Q_INVOKABLE QString getParentVUrl(const QString &vurl);

    /**
      * @brief check if vurl is a direct child of root
      * @param vurl
      * @return true if more parent or false if already child of root
      * @since 1.4
      */
    Q_INVOKABLE bool hasParent(const QString &vurl);

    /**
     * @brief create an vurl from an ABSOLUTE file path
     * @param path, doesn't need to exist
     * @return
     */
    Q_INVOKABLE QString getVUrl(const QString &path);

    /**
     * @brief return corresponding source i.e. the mount point into the vfs for this uri
     * into the system file system
     * @param vurl
     * @return the source path or QString::null
     */
    Q_INVOKABLE QString getSourceFromVUrl(const QString &vurl);

    /**
     * @brief return the absolute path to the uri
     * @param vurl must exist and be readable
     * @return either the absolute path or QString::null
     */
    Q_INVOKABLE  QString getPathFromVUrl(const QString &vurl);

	    /**
     * @brief instead of returning the first valid path from vurl, return an
	 * array of all existing (usefull for rep)
     * @param vurl must exist and be readable
     * @return either the absolute path or QString::null
	 * @since 1.7
     */
    Q_INVOKABLE  QStringList getPathSFromVUrl(const QString &vurl);
	
    /**
     * @brief return corresponding source i.e. the mount point into the vfs for this absolute
     * file path
     * @param path : an absolute path (NOT vurl)
     * @return the source path or QString::null
     */
    Q_INVOKABLE QString getSourceFromPath(const QString &path);

    /**
     * @brief return the name of a file/rep (including extention) from an url or path
     * @param url can be virtual, abolute or relative, exist or not
     * @return
     */
    Q_INVOKABLE  QString getFileName(const QString &url);

    /**
     * @brief this method strip path and file extension from an url or path
     * @param url can be virtual, abolute or relative, exist or not
     * @return
     */
    Q_INVOKABLE QString getName(const QString &url);

    /**
      * @brief convenience method to build a proper vurl
      * @param parent vurl
      * @param child
      * @return well formated vurl
      * @since 1.4
      */
    Q_INVOKABLE QString mkVUrl(const QString &parent, const QString &child);

    /*************************************************************
     * read files info
    *************************************************************/

    /**
     * @brief return information for this vurl (path into the vfs
     * @param vurl
     * @return information or null if don't exist
     */
    Q_INVOKABLE  VFInfo *getInfo(const QString &vurl);

    /**
     * @brief return information / convert but from a qfileinfo
     * @param f
     * @return
     */
    VFInfo *getInfo(QFileInfo &f);

    /*************************************************************/

    /**
     * @brief start scanning for files/directories from this uri
     * This is a asynchronious operation, list will be available from signal listAvailable
     *
     * filter is a regexp apply to files name ONLY, never to directory (purpose is to be a file type extension) even if type = VFType::DIR
     * filter is allways case insensitive
     * nota : non readable file and directory got skipped
     *
     * @param vurl : source for file
     * @param filter : optionnal regular expression for file name (extension) ; see FILTERAUDIO for example
     * @param type : what to look for
     * @param order : ordering to apply on the list (directory will still be listed first alpha)
     * @return a batch id to identify this scan on the signal callback
     */
    Q_INVOKABLE  quint64 get(const QString &vurl, const QString &filter = FILTERNONE, VFType type = VFType::BOTH, VFOrder order = VFOrder::ALPHA);

    /**
     * @brief this is a synchronous - blocking function - of "get"
     * @param vurl
     * @param filter
     * @param type
     * @param order
     * @return may be empty but never null
     */
    QList<VFInfo *> getSynch(const QString &vurl, const QString &filter = FILTERNONE, VFType type = VFType::BOTH, VFOrder order = VFOrder::ALPHA);

    /*************************************************************
     * stat
    *************************************************************/

    /**
     * @brief return the number of directory (one level down/ current directoy) from this uri (to a directory !)
     * only count readable entries
     * @param filter : optional filter
     * @param vurl
     * @return
     */
    Q_INVOKABLE  quint16 countDirectories(const QString &vurl,const QString &filter = FILTERNONE);

    /**
     * @brief return the number files into this directory
     * only count readable entries
     * @param vurl
     * @param filter : optional filter
     * @return
     */
    Q_INVOKABLE  quint16 countFiles(const QString &vurl,const QString &filter = FILTERNONE);

    /**
     * @brief check if a vurl match  a filter
     * @param vurl
     * @param filter; ex FILTERAUDIO, etc...
     * @return true if match, else false
     * @since 1.4
     */

    Q_INVOKABLE bool VurlMatch(const QString &vurl,const QString &filter);

    /**
     * @brief return statistic from a directory, recursively. If vurl refer to a file
     * just convert a vfinfo into vfstat
     * @param vurl : base url
     * @param filter : filter to apply on file, never on directory
     * @return a batch_id, data will be available on signal statAvailable
     */
    Q_INVOKABLE quint64 getStat(const QString &vurl, const QString &filter  = FILTERNONE);

    /**
     * @brief return statistic from a directory, recursively. If vurl refer to a file
     * just convert a vfinfo into vfstat
     * @param vurl : base url
     * @param filter : filter to apply on file, never on directory
     * @return stat for vurl; if vurl not found, return an empty class
     */
    Q_INVOKABLE VFStat *getStatSynch(const QString &vurl, const QString &filter  = FILTERNONE);


    /*************************************************************
     * action
    *************************************************************/

    /**
     * @brief remove files from this uri  ; delete directory RECURSIVELY
     * this method also delete hidden files and directories
     * NOTA : even if return false, some files may have been deleted
     * (some shadowed file in ro mode only other not)
     * @param vurl
     * @return true if file(s) removed, else false (likely r/w denied )
     */
    Q_INVOKABLE bool remove(const QString &vurl);

    /**
     * @brief move uri (files or directory) into a new location
     * each files / directory are moved into the same "source",
     * no files will be moved between different physical location (e.i. files
     * on a sdcard stay in the sdcard)
     * destination directories will be automatically created
     * @param vurl : source
     * @param into : the new location, i.e the target PARENT directory (virtual too)
     * @return true if file/directory moved, else false (r/w issues, target exist)
     */
    Q_INVOKABLE bool move(const QString &vurl, const QString &into);

    /**
     * @brief rename file at "uri" as "name"
     * NOTA : if return false, no file got renamed on any locaiton
     * @param vurl to the source file ; must exist
     * @param name new name
     * @return true if successfully renamed else false (r/w error, name already exist..)
     */
    Q_INVOKABLE bool rename(const QString &vurl, const QString &name);

    /**
     * @brief change date for file or directory at vurl
     * NOTA : date will be changed on any source and action is not recursive
     * @param vurl : source file
     * @param timestamp : new date on the for of a timestamp (mill sec since 1970)
     * @return : true if successfull + emit dateChanged
     */
    Q_INVOKABLE bool date(const QString &vurl,const quint64 timestamp);

private:
    explicit VFService(QObject *parent = 0);

    QList<QString > srcs; // sources for "root" directory into the vf system

    bool hidden;
    QDir::Filters _filter;
    QDir::Filters _filter_d;
    QDir::Filters _filter_f;

    /**
     * @brief getInfo_imp
     * @param f
     * @return
     */
    VFInfo *getInfo_imp(QFileInfo &f);

    /**
     * @brief qtconcurrent worker
     * @param vurl
     * @param filter
     * @param type
     */
    static void doGet(quint64 id, const QString &vurl, const QString &filter, VFType type, VFOrder order);

    /**
     * @brief worker ; return the list
     * @param base
     * @param vurl
     * @param exp
     * @return
     */
    QList<VFInfo *> doGetScan(QString &base, QString vurl, QRegularExpression *exp, VFType type );

    /**
     * @brief qtconcurrent worker
     * @param vurl
     * @param filter
     */
    static void doStat(quint64 id, const QString &vurl, const QString &filter);

    /**
     * @brief doStatScan
     * @param stat
     * @param base
     * @param vurl
     * @param exp
     * @return
     */
    void doStatScan(VFStat *stat, QString &base, QString vurl, QRegularExpression *exp);


    /**
     * @brief escape "'()space
     * @param val
     * @return
     * @since 1.4
     */
    static QString sanitize(QString val);

signals :
    /**
     * @brief list available to user
     * @param batch
     * @param vurl for the search
     * @param list, the list for the search batchId ; never null
     */
    void listAvailable(quint64 batchId, QString vurl, QVariantList list);

    /**
     * @brief statAvailable
     * @param batchId
     * @param vurl
     * @param stat
     */
    void statAvailable(quint64 batchId, QVariant stat);

    /**
     * @brief emited when successfuly removed uri
     * @param uri
     */
    void removed(QString vurl);

    /**
     * @brief emited when a move was performed
     * @param vurl original uri
     * @param as : vurl into is new location
     */
    void moved(QString vurl, QString as);

    /**
     * @brief emited when a rename was performed
     * @param vurl with original name
     * @param name the new name
     */
    void renamed(QString vurl, QString name);

    /**
     * @brief date of vurl as been modified
     * @param vurl
     * @param timestamp
     */
    void dateChanged(QString vurl, quint64 timestamp);
};

#endif // VFSERVICE_H
