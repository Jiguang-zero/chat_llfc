#ifndef LOGIN_DIALOG_H
#define LOGIN_DIALOG_H


/******************************************************************************
 *
 * @file       login_dialog.h
 * @brief      登录页面绘画
 *
 * @author     Jiguang Zearo
 * @date       2024/08/07
 * @history
 *****************************************************************************/

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private:
    Ui::LoginDialog *ui;
};

#endif // LOGIN_DIALOG_H
