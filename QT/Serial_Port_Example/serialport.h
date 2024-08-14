#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void receiveMessage();
    void on_connectButton_clicked();
    void on_sendButton_clicked();
    void on_disconnectButton_clicked();
    void on_refreshButton_clicked();
    void on_clearButton_clicked();

private:
    Ui::Widget *ui;
    QSerialPort serialPort;
    QSerialPortInfo info;
    QString buffer;
    QString code;
    int codeSize;
};
#endif // SERIALPORT_H
