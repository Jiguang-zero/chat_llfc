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
}

MainWindow::~MainWindow()
{
    delete ui;
}
