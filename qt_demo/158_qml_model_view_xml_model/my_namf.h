#ifndef _MY_NAMF_H_
#define _MY_NAMF_H_
#include <QQmlNetworkAccessManagerFactory>
#include "QtNetwork/QNetworkAccessManager"

class MyNAMFactory : public QQmlNetworkAccessManagerFactory
{
public:
    virtual QNetworkAccessManager *create(QObject *parent);
};
#endif 