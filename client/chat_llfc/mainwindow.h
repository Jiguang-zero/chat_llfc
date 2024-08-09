#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/******************************************************************************
 *
 * @file       mainwindow.h
 * @brief      Main Window
 *
 * @author     Jiguang Zearo
 * @date       2024/08/07
 * @history
 *****************************************************************************/

#include "login_dialog.h"
#include "register_dialog.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void SlotSwitchRegister();

private:
    Ui::MainWindow *ui;
    LoginDialog * _loginDialog;
    RegisterDialog * _registerDialog;
};
#endif // MAINWINDOW_H
