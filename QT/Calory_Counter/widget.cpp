#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // Init values
    m_person.SetWeight(ui->weightSpinBox->value());
    m_time = ui->timeSpinBox->value();
    m_speed = ui->speedSpinBox->value();

    // Connections
    connect( ui->weightSpinBox, &QDoubleSpinBox::valueChanged,
            this, &Widget::WeightChanged);
    connect( ui->timeSpinBox, &QDoubleSpinBox::valueChanged,
            this, &Widget::TimeChamged);
    connect( ui->speedSpinBox, &QDoubleSpinBox::valueChanged,
            this, &Widget::SpeedChanged);

    // Update calory count
    connect( this, &Widget::CaloryCountChanged, [=](){
        ui->caloryNumberLabel->setText(QString::number(m_calory_count));
    });

    CalculateCalories();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::CalculateCalories()
{
    m_calory_count = ( (0.0215 * (m_speed * m_speed * m_speed)) - (0.0175 * ( m_speed * m_speed))
                      + (0.8710 * m_speed) + 1.4577) * m_person.weight() * m_time;
    emit CaloryCountChanged();
}

void Widget::WeightChanged(double weight)
{
    m_person.SetWeight(weight);
    CalculateCalories();
}

void Widget::TimeChamged(double time)
{
    m_time = time;
    CalculateCalories();
}

void Widget::SpeedChanged(double speed)
{
    m_speed = speed;
    CalculateCalories();
}
