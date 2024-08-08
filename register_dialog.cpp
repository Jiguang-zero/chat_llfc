#include "register_dialog.h"
#include "ui_register_dialog.h"
#include "global.h"

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    ui->password_edit->setEchoMode(QLineEdit::Password);
    ui->conrim_edit->setEchoMode(QLineEdit::Password);
    ui->error_message->setProperty("state", "normal");
    repolish(ui->error_message);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_get_code_button_clicked()
{
    auto email = ui->email_label->text();
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch();

    if (match) {
        // 发送验证码
    } else {
        showErrorMessage(tr("邮箱地址不正确"), false);
    }

}

void RegisterDialog::showErrorMessage(QString str, bool b_ok)
{
    ui->error_message->setProperty("state", b_ok ? "normal" : "err");
    ui->error_message->setText(str);

    repolish(ui->error_message);
}

