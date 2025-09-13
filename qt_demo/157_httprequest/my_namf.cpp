#include "my_namf.h"
#include <QtNetwork/QNetworkDiskCache>
#include <QtCore/QStandardPaths>

QNetworkAccessManager *MyNAMFactory::create(QObject *parent)
{
    QNetworkAccessManager *nam = new QNetworkAccessManager(parent);
    QNetworkDiskCache* diskCache = new QNetworkDiskCache(nam);

    QString cachePath = QStandardPaths::displayName(QStandardPaths::CacheLocation);

    qDebug() << "cache path:" << cachePath;

    diskCache->setCacheDirectory(cachePath);
    diskCache->setMaximumCacheSize(100 * 1024 * 1024);   // 这里设置的缓存大小为 100 MB

    nam->setCache(diskCache);
    return nam;
}