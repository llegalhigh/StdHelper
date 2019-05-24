#ifndef LINK_H
#define LINK_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>


class Link : public QObject {
    Q_OBJECT

public:
    explicit Link( QString Url = "", QString parameter = "" );
    ~Link();

    void setUrl( QString Url );
    void
            setParameter( QString formalParam,
                          QString actualParam );   //���ò���(ǰ�����β�,������ʵ��)
    QString getUrl() const;
    QString getParameter() const;
    void
    addParameter( QString formalParam,
                  QString actualParam );   //��Ӳ���(ǰ�����β�,������ʵ��)

    void connect( const QObject *receiver,
                   const char *member ) const;   //�󶨲ۺ���(�����������ʱ�����ۺ���)

    void disconnect() const;  //���connect��
    void disconnect( const QObject *receiver,
                     const char *member ) const;  //���connect��

    void post() const;   //����POST��ʽ��������

    static QString getReply(
        QNetworkReply
            * );   //��ȡ��Ӧ��Ϣ(QString),����static����,���Բ���������ֱ����
private:
    QString                Url;         //����ip��ַ
    QString                parameter;   //���͵Ĳ���
    QNetworkAccessManager *manage;
};

#endif   // LINK_H
