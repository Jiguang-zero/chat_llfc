#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _loginDialog = new LoginDialog();
    setCentralWidget(_loginDialog);
    _loginDialog->show();

    // 创建和注册消息链接
    connect(_loginDialog, &LoginDialog::switchRegister, this, &MainWindow::SlotSwitchRegister);
    _registerDialog = new RegisterDialog();
}

MainWindow::~MainWindow()
{
    delete ui;
    if (_loginDialog) {
        delete _loginDialog;
        _loginDialog = nullptr;
    }
    if (_registerDialog) {
        delete _registerDialog;
        _registerDialog = nullptr;
    }
}

void MainWindow::SlotSwitchRegister()
{
    setCentralWidget(_registerDialog);
    _loginDialog->hide();
    _registerDialog->show();
}
