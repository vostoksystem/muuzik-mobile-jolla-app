#ifndef VFSTAT_H
#define VFSTAT_H

#include <QObject>

using namespace std;

class VFService;

/**
 * @brief The this class hold information for the stat method
 * @since 1.6
 */
class VFStat : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString vurl READ getVUrl CONSTANT)
    Q_PROPERTY(QString filter READ getFilter CONSTANT)
    Q_PROPERTY(quint64 dirCount READ getDirCount CONSTANT)
    Q_PROPERTY(quint64 fileCount READ getFileCount CONSTANT)
    Q_PROPERTY(quint64 fileSize READ getFileSize CONSTANT)

    friend class VFService;

public:
    explicit VFStat(QObject *parent = 0);

    /**
     * @brief base vurl
     * @return
     */
    QString getVUrl() const { return vurl; }

    /**
     * @brief file filter used, default to none ("")
     * @return
     */
    QString getFilter() const { return filter; }

    /**
     * @brief number of directories (including sub)
     * @return
     */
    quint64 getDirCount() const { return dirCount; }

    /**
     * @brief number of files, including sub directories
     * @note : if a same vurl exist in different absolute file path, file is counted twice
     * @return
     */
    quint64 getFileCount() const { return fileCount; }

    /**
     * @brief total size in byte
     * @note : if same vurl exist in different absolute file path, file is counted twice
     * @return
     */
    quint64 getFileSize() const { return fileSize; }


protected:
    QString vurl;
    QString filter;
    quint64 dirCount;
    quint64 fileCount;
    quint64 fileSize;   

private:
    Q_DISABLE_COPY(VFStat)

};

#endif // VFSTAT_H
