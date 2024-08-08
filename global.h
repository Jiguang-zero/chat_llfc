#ifndef GLOBAL_H
#define GLOBAL_H

/******************************************************************************
 *
 * @file       global.h
 * @brief      Global Configs
 *
 * @author     Jiguang Zearo
 * @date       2024/08/08
 * @history
 *****************************************************************************/

#include <QWidget>
#include <functional>
#include <QRegularExpression>
#include <QByteArray>
#include <QNetworkReply>

#include "Qstyle"

/**
 * @brief repolish refresh qss
 */
extern std::function<void(QWidget*)> repolish;

enum ReqId {
    ID_GET_VARIFY_CODE = 1001, // VERIFY
    ID_REGISTER_USER = 1002, // REGISTER
};

enum Modules {
    REGISTER_MOD = 0,
};

enum ErrorCodes {
    SUCCESS,
    ERR_JSON = 1, // json parsed failed
    ERR_NETWORK = 2, // NETWORK error
};

#endif // GLOBAL_H
