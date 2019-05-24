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
                          QString actualParam );   //设置参数(前面是形参,后面是实参)
    QString getUrl() const;
    QString getParameter() const;
    void
    addParameter( QString formalParam,
                  QString actualParam );   //添加参数(前面是形参,后面是实参)

    void connect( const QObject *receiver,
                   const char *member ) const;   //绑定槽函数(网络请求完成时触发槽函数)

    void disconnect() const;  //解除connect绑定
    void disconnect( const QObject *receiver,
                     const char *member ) const;  //解除connect绑定

    void post() const;   //利用POST方式发送请求

    static QString getReply(
        QNetworkReply
            * );   //获取回应信息(QString),这是static函数,可以不创建对象直接用
private:
    QString                Url;         //网络ip地址
    QString                parameter;   //发送的参数
    QNetworkAccessManager *manage;
};

#endif   // LINK_H
