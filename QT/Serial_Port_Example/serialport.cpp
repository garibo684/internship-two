#include "serialport.h"
#include "ui_serialport.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // Disable maximizing
    setFixedSize(width(), height());

    // Adding title for widget
    QWidget::setWindowTitle("Serial Port Example");

    // Ports
    QList<QSerialPortInfo> ports = info.availablePorts();
    QList<QString> stringPorts;
    for(int i = 0 ; i < ports.size() ; i++){
        stringPorts.append(ports.at(i).portName());
    }
    ui->portComboBox->addItems(stringPorts);

    // Baud Rate Ratios
    QList<qint32> baudRates = info.standardBaudRates(); // What baudrates does my computer support ?
    QList<QString> stringBaudRates;
    for(int i = 0 ; i < baudRates.size() ; i++){
        stringBaudRates.append(QString::number(baudRates.at(i)));
    }
    ui->baudComboBox->addItems(stringBaudRates);

    // Data Bits
    ui->dataBitComboBox->addItem("5");
    ui->dataBitComboBox->addItem("6");
    ui->dataBitComboBox->addItem("7");
    ui->dataBitComboBox->addItem("8");

    // Stop Bits
    ui->stopBitComboBox->addItem("1 Bit");
    ui->stopBitComboBox->addItem("1,5 Bits");
    ui->stopBitComboBox->addItem("2 Bits");

    // Parities
    ui->parityComboBox->addItem("No Parity");
    ui->parityComboBox->addItem("Even Parity");
    ui->parityComboBox->addItem("Odd Parity");
    ui->parityComboBox->addItem("Mark Parity");
    ui->parityComboBox->addItem("Space Parity");

    //Flow Controls
    ui->flowComboBox->addItem("No Flow Control");
    ui->flowComboBox->addItem("Hardware Flow Control");
    ui->flowComboBox->addItem("Software Flow Control");

    ui->baudComboBox->setCurrentIndex(12);
    ui->baudComboBox->setCurrentText(ui->baudComboBox->itemText(ui->baudComboBox->currentIndex()));

    ui->dataBitComboBox->setCurrentIndex(3);
    ui->dataBitComboBox->setCurrentText(ui->dataBitComboBox->itemText(ui->dataBitComboBox->currentIndex()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::receiveMessage()
{
    QByteArray dataBA = serialPort.readAll();
    QString data(dataBA);
    buffer.append(data);
    int index = buffer.indexOf(code);
    if(index != -1){
        QString message = buffer.mid(0,index);
        ui->messageBox->setTextColor(Qt::blue); // Receieved message's color is blue.
        ui->messageBox->append(message);
        buffer.remove(0,index+codeSize);
    }

}

void Widget::on_connectButton_clicked()
{

    QString portName = ui->portComboBox->currentText();
    serialPort.setPortName(portName);

    serialPort.open(QIODevice::ReadWrite);

    if(!serialPort.isOpen()){
        ui->messageBox->setTextColor(Qt::red);
        ui->messageBox->append("!!!! Something went Wrong !!!!");
    }
    else {
        ui->messageBox->setTextColor(Qt::darkGreen);
        ui->messageBox->append("---- Connected to " + serialPort.portName() + " ----");

        QString stringbaudRate = ui->baudComboBox->currentText();
        int intbaudRate = stringbaudRate.toInt();
        serialPort.setBaudRate(intbaudRate);

        QString dataBits = ui->dataBitComboBox->currentText();
        if(dataBits == "5 Bits") {
           serialPort.setDataBits(QSerialPort::Data5);
        }
        else if((dataBits == "6 Bits")) {
           serialPort.setDataBits(QSerialPort::Data6);
        }
        else if(dataBits == "7 Bits") {
           serialPort.setDataBits(QSerialPort::Data7);
        }
        else if(dataBits == "8 Bits"){
           serialPort.setDataBits(QSerialPort::Data8);
        }

        QString stopBits = ui->stopBitComboBox->currentText();
        if(stopBits == "1 Bit") {
         serialPort.setStopBits(QSerialPort::OneStop);
        }
        else if(stopBits == "1,5 Bits") {
         serialPort.setStopBits(QSerialPort::OneAndHalfStop);
        }
        else if(stopBits == "2 Bits") {
         serialPort.setStopBits(QSerialPort::TwoStop);
        }

        QString parity = ui->parityComboBox->currentText();
        if(parity == "No Parity"){
          serialPort.setParity(QSerialPort::NoParity);
        }
        else if(parity == "Even Parity"){
          serialPort.setParity(QSerialPort::EvenParity);
        }
        else if(parity == "Odd Parity"){
          serialPort.setParity(QSerialPort::OddParity);
        }
        else if(parity == "Mark Parity"){
          serialPort.setParity(QSerialPort::MarkParity);
        }
        else if(parity == "Space Parity") {
            serialPort.setParity(QSerialPort::SpaceParity);
        }


        QString flowControl = ui->flowComboBox->currentText();
        if(flowControl == "No Flow Control") {
          serialPort.setFlowControl(QSerialPort::NoFlowControl);
        }
        else if(flowControl == "Hardware Flow Control") {
          serialPort.setFlowControl(QSerialPort::HardwareControl);
        }
        else if(flowControl == "Software Flow Control") {
          serialPort.setFlowControl(QSerialPort::SoftwareControl);
        }

        code = ui->codeLineEdit->text();
        codeSize = code.size();

        connect(&serialPort,SIGNAL(readyRead()),this,SLOT(receiveMessage()));
    }
}

void Widget::on_sendButton_clicked()
{
    QString message = ui->sendLineEdit->text();
    ui->messageBox->setTextColor(Qt::darkGreen); // Color of message to send is green.
    ui->messageBox->append(message);
    serialPort.write(message.toUtf8());
}


// Button of Disconnect
void Widget::on_disconnectButton_clicked()
{
    serialPort.close();
    if(!serialPort.isOpen()){
        ui->messageBox->setTextColor(Qt::darkRed);
        ui->messageBox->append("---- Disconnected from " + serialPort.portName() + " ----");
    }

}

// Button of Refresh Ports
void Widget::on_refreshButton_clicked()
{
    ui->portComboBox->clear();
    QList<QSerialPortInfo> ports = info.availablePorts();
    QList<QString> stringPorts;
    for(int i = 0 ; i < ports.size() ; i++){
        stringPorts.append(ports.at(i).portName());
    }
    ui->portComboBox->addItems(stringPorts);
}

// Button of Clear
void Widget::on_clearButton_clicked()
{
    ui->messageBox->clear();
}




