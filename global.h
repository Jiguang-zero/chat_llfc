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

#include "Qstyle"

/**
 * @brief repolish refresh qss
 */
extern std::function<void(QWidget*)> repolish;

#endif // GLOBAL_H
