#include "link.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcess>

Link::Link( QString Url, QString parameter )
    : Url( Url ), parameter( parameter ) {
    manage = new QNetworkAccessManager();
}

Link::~Link() {
    delete manage;
}
void Link::setUrl( QString Url ) {
    this->Url = Url;
}

void Link::setParameter( QString formalParam, QString actualParam ) {
    this->parameter = ( formalParam + "=" + actualParam );
}

QString Link::getUrl() const {
    return Url;
}

QString Link::getParameter() const {
    return parameter;
}

void Link::addParameter( QString formalParam, QString actualParam ) {
    QString parameter = ( formalParam + "=" + actualParam );
    this->parameter += ( "&" + parameter );
}

void Link::connect( const QObject *receiver, const char *member ) const {
    QObject::connect( manage, SIGNAL( finished( QNetworkReply * ) ), receiver,
                      member );
}

void Link::disconnect() const
{
    manage->disconnect();
}

void Link::disconnect(const QObject *receiver, const char *member) const
{
    QObject::disconnect( manage, SIGNAL( finished( QNetworkReply * ) ), receiver,
                      member );
}

void Link::post() const {
    QByteArray      content = parameter.toUtf8();
    QNetworkRequest netReq;
    netReq.setUrl( QUrl( Url ) );
    netReq.setHeader( QNetworkRequest::ContentTypeHeader,
                      "application/x-www-form-urlencoded" );
    manage->post( netReq, content );
}

bool Link::checkNetwork() const
{
    // #Linuxָ® "ping -s 1 -c 1 IP"
    //QString cmdstr = QString("ping -s 1 -c 1 %1")
    //      .arg(ip);

    // #Windowsָ® "ping IP -n 1 -w Ӭʱ(ms)"
    QString cmdstr = QString("ping %1 -n 1 -w %2")
            .arg("111.230.183.100").arg(1000);

    QProcess cmd;
    cmd.start(cmdstr);
    cmd.waitForReadyRead(1000);
    cmd.waitForFinished(1000);

    QString response = cmd.readAll();
    if (response.indexOf("TTL") == -1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

QByteArray Link::getReply( QNetworkReply *reply ) {
    QByteArray result = reply->readAll();
    return result;
}

QJsonObject Link::jsonDecode(const QByteArray &json)
{
    QJsonDocument document = QJsonDocument::fromJson(json);
    QJsonObject object = document.object();
    return object;
}
