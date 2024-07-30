#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "person.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void CalculateCalories();
    void WeightChanged(double weight);
    void TimeChamged(double time);
    void SpeedChanged(double speed);

signals:
    void CaloryCountChanged();

private:
    Ui::Widget *ui;
    Person m_person;
    double m_time;
    double m_speed;
    double m_calory_count;
};
#endif // WIDGET_H
