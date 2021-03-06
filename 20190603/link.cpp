#include "link.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>

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
