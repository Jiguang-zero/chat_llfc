#ifndef REGISTER_DIALOG_H
#define REGISTER_DIALOG_H

/******************************************************************************
 *
 * @file       register_dialog.h
 * @brief      Register Dialog
 *
 * @author     Jiguang Zearo
 * @date       2024/08/08
 * @history
 *****************************************************************************/

#include <QDialog>

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

private:
    Ui::RegisterDialog *ui;
};

#endif // REGISTER_DIALOG_H
