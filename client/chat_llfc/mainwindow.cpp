#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _loginDialog = new LoginDialog(this);
    setCentralWidget(_loginDialog);
    // _loginDialog->show();

    // 创建和注册消息链接
    connect(_loginDialog, &LoginDialog::switchRegister, this, &MainWindow::SlotSwitchRegister);
    _registerDialog = new RegisterDialog(this);
    _registerDialog->hide();

    _loginDialog->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    _registerDialog->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SlotSwitchRegister()
{
    setCentralWidget(_registerDialog);
    _loginDialog->hide();
    _registerDialog->show();
}
