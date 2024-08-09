#include "register_dialog.h"
#include "ui_register_dialog.h"
#include "global.h"
#include "http_manager.h"

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    ui->password_edit->setEchoMode(QLineEdit::Password);
    ui->conrim_edit->setEchoMode(QLineEdit::Password);
    ui->error_message->setProperty("state", "normal");
    repolish(ui->error_message);
    connect(HttpManager::GetInstance().get(), &HttpManager::sig_reg_mod_finish,
            this, &RegisterDialog::slot_reg_mod_finish);

    initHttpHandlers();
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_get_code_button_clicked()
{
    auto email = ui->email_label->text();
    static const QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    auto regexMatch = regex.match(email);
    bool match = regexMatch.hasMatch();

    if (match) {
        // 发送验证码
    } else {
        showErrorMessage(tr("邮箱地址不正确"), false);
    }

}

void RegisterDialog::slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err)
{
    if (err != ErrorCodes::SUCCESS) {
        showErrorMessage(tr("网络请求错误"), false);
        return;
    }

    // parse json
    QJsonDocument jsonDox = QJsonDocument::fromJson(res.toUtf8());
    if (jsonDox.isNull()) {
        showErrorMessage(tr("json 解析失败"), false);
        return;
    }
    if (!jsonDox.isObject()) {
        showErrorMessage(tr("json 解析失败"), false);
        return;
    }

    _handlers[id](jsonDox.object());

    return;
}

void RegisterDialog::showErrorMessage(QString str, bool b_ok)
{
    ui->error_message->setProperty("state", b_ok ? "normal" : "err");
    ui->error_message->setText(str);

    repolish(ui->error_message);
}

void RegisterDialog::initHttpHandlers()
{
    _handlers.insert(ReqId::ID_GET_VARIFY_CODE, [this](const QJsonObject& jsonObj) {
        int error = jsonObj["error"].toInt();
        if (error != ErrorCodes::SUCCESS) {
            showErrorMessage(tr("参数错误"), false);
            return;
        }

        auto email = jsonObj["email"].toString();
        showErrorMessage(tr("验证码已经发送到邮箱，注意查收"), true);
        qDebug() << "email is " << email;
    });
}

