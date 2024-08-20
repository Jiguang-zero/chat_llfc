#ifndef HTTP_MANAGER_H
#define HTTP_MANAGER_H

/******************************************************************************
 *
 * @file       http_manager.h
 * @brief      http manager
 *
 * @author     Jiguang Zearo
 * @date       2024/08/08
 * @history
 *****************************************************************************/

#include "utils/singleton.h"
#include "global.h"

#include <QString>
#include <QUrl>
#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>

// CRTP
class HttpManager : public QObject, public Singleton<HttpManager>,
                    public std::enable_shared_from_this<HttpManager>
{
    Q_OBJECT

private:
    friend class Singleton<HttpManager>; // 基类需要构造函数
    HttpManager();
    QNetworkAccessManager _manager;

public:
    // 智能指针需要析构 公有
    ~HttpManager();

    void PostHttpRequest(QUrl url, QJsonObject json, ReqId req_id, Modules mod);

private slots:
    void slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);

signals:
    void sig_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);
    void sig_reg_mod_finish(ReqId id, QString res, ErrorCodes err);
};

#endif // HTTP_MANAGER_H
