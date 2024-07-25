#include "widget.h"
#include "./ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_submitButton_clicked()
{
    qDebug() << ui->firstNameLineEdit->text() + " " + ui->lastNameLineEdit->text() + ":  " + ui->subtitleTextEdit->toPlainText();
}

