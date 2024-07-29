#include "widget.h"
#include "./ui_widget.h"
#include <QDebug>
#include <cstdlib>
#include <ctime>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //  Setup the seed

    std::srand(std::time(nullptr));

    // Generate answer number

    answer_number = rand() % 10 + 1;

    // Disable the restart button

    ui->restartButton->setDisabled(true);

    // Clear the text

    ui->resultLabel->setText("");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_guessButton_clicked()
{
    guess_number = ui->guessSpinBox->value();
    qDebug() << "User guessed:  " << QString::number(guess_number);

    // Guess Control

    if( guess_number == answer_number)
    {
        // Congrats message

        ui->resultLabel->setText("Congratulations, the number is " + QString::number(guess_number));

        // Button actions

        ui->guessButton->setDisabled(true);
        ui->restartButton->setDisabled(false);
    }
    else
    {
        //  Caompare

        if( guess_number > answer_number )
        {
            ui->resultLabel->setText("Number is lower than that");
        }
        else if(guess_number < answer_number )
        {
            ui->resultLabel->setText("Number is higher than that");
        }
    }



}


void Widget::on_restartButton_clicked()
{
    // Reset

    ui->guessButton->setDisabled(false);

    ui->restartButton->setDisabled(true);

    ui->guessSpinBox->setValue(1);

    answer_number = rand() % 10 + 1;

    ui->resultLabel->setText("");
}

