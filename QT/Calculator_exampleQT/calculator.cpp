#include "calculator.h"
#include "button.h"

#include <QGridLayout>
#include <QLineEdit>
#include <QtMath>

Calculator::Calculator(QWidget *parent)
    : QWidget(parent), sumInMemory(0.0), sumSoFar(0.0)
    , factorSoFar(0.0), waitingForOperand(true), check(true)
{
    equation = new QLineEdit("0");
    result_line = new QLineEdit("= 0");

    equation->setReadOnly(true);
    equation->setAlignment(Qt::AlignRight);
    equation->setMaxLength(15);
    QFont font = equation->font();
    font.setPointSize(font.pointSize() + 6);
    equation->setFont(font);

    result_line->setReadOnly(true);
    result_line->setAlignment(Qt::AlignRight);
    result_line->setMaxLength(15);
    QFont res_font = result_line->font();
    res_font.setPointSize(res_font.pointSize() + 16);
    result_line->setFont(res_font);

    for(int i = 0; i < NumDigitButtons; ++i)
    { digitButtons[i] = createButton(QString::number(i), &Calculator::digitClicked); }

    Button *pointButton = createButton(tr("."), &Calculator::pointClicked);
    Button *changeSignButton = createButton(tr("\302\261"), &Calculator::changeSignClicked);

    Button *backspaceButton = createButton(tr("Backspace"), &Calculator::backspaceClicked);
    Button *clearButton = createButton(tr("Clear"), &Calculator::clear);
    Button *clearAllButton = createButton(tr("Clear All"), &Calculator::clearAll);

    Button *clearMemoryButton = createButton(tr("MC"), &Calculator::clearMemory);
    Button *readMemoryButton = createButton(tr("MR"), &Calculator::readMemory);
    Button *setMemoryButton = createButton(tr("MS"), &Calculator::setMemory);
    Button *addToMemoryButton = createButton(tr("M+"), &Calculator::addToMemory);

    Button *divisionButton = createButton(tr("\303\267"), &Calculator::multiplicativeOperatorClicked);
    Button *timesButton = createButton(tr("\303\227"), &Calculator::multiplicativeOperatorClicked);
    Button *minusButton = createButton(tr("-"), &Calculator::additiveOperatorClicked);
    Button *plusButton = createButton(tr("+"), &Calculator::additiveOperatorClicked);

    Button *squareRootButton = createButton(tr("Sqrt"), &Calculator::unaryOperatorClicked);
    Button *powerButton = createButton(tr("x\302\262"), &Calculator::unaryOperatorClicked);
    Button *reciprocalButton = createButton(tr("1/x"), &Calculator::unaryOperatorClicked);
    Button *equalButton = createButton(tr("="), &Calculator::equalClicked);

    QGridLayout * mainLayout = new QGridLayout;

    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(equation, 0,0,1,6);
    mainLayout->addWidget(result_line, 1,0,1,6);
    mainLayout->addWidget(backspaceButton, 2,0,1,2);
    mainLayout->addWidget(clearButton, 2,2,1,2);
    mainLayout->addWidget(clearAllButton, 2,4,1,2);

    mainLayout->addWidget(clearMemoryButton, 3, 0);
    mainLayout->addWidget(readMemoryButton, 4, 0);
    mainLayout->addWidget(setMemoryButton, 5, 0);
    mainLayout->addWidget(addToMemoryButton, 6, 0);

    for( int i = 1; i < NumDigitButtons; ++i)
    {
        int row = ((9-i) / 3) + 3;
        int column = ((i - 1) % 3) + 1;
        mainLayout->addWidget(digitButtons[i], row,column);
    }

    mainLayout->addWidget(digitButtons[0], 6, 2);
    mainLayout->addWidget(pointButton, 6, 1);
    mainLayout->addWidget(changeSignButton, 6, 3);

    mainLayout->addWidget(divisionButton, 3, 4);
    mainLayout->addWidget(timesButton, 4, 4);
    mainLayout->addWidget(minusButton, 5, 4);
    mainLayout->addWidget(plusButton, 6, 4);

    mainLayout->addWidget(squareRootButton, 3, 5);
    mainLayout->addWidget(powerButton, 4, 5);
    mainLayout->addWidget(reciprocalButton, 5, 5);
    mainLayout->addWidget(equalButton, 6, 5);
    setLayout(mainLayout);

    setWindowTitle("Calculator");
}


bool Calculator::getCheck() const
{
    return check;
}

void Calculator::setCheck(bool c)
{
    check = c;
}

void Calculator::digitClicked()
{
    Button *clickedButton= qobject_cast<Button *>(sender());
    int digitValue = clickedButton->text().toInt();
    if( equation->text() == "0" && digitValue == 0.0 )
        return;

    if  (waitingForOperand) {
        equation->clear();
        waitingForOperand = false;
    }

    equation->setText(equation->text() + QString::number(digitValue));

}

void Calculator::unaryOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = equation->text().toDouble();
    double result = 0.0;

    if (clickedOperator == tr("Sqrt")) {
        if (operand < 0.0){
            abortOperation();
            return;
        }
        result = std::sqrt(operand);
        equation->setText("Square of " + equation->text());
    } else if (clickedOperator == tr("x\302\262")) {
        result = std::pow(operand, 2.0);  
        equation->setText("Power of " + equation->text());
    } else if (clickedOperator == tr("1/x")) {
        if (operand == 0.0) {
            abortOperation();
            return;
        }
        result = 1.0 / operand;
        equation->setText("1 / " + equation->text());
    }
    result_line->setText("= " + QString::number(result));
    waitingForOperand = true;
}

void Calculator::additiveOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    if (!clickedButton)
        return;
    QString clickedOperator = clickedButton->text();
    double operand = equation->text().toDouble();

    pendingAdditiveOperator = clickedOperator;

    if (!pendingMultiplicativeOperator.isEmpty()) {

        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        equation->setText(QString::number(operand));
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }

    if (!pendingAdditiveOperator.isEmpty()) {

        if(!calculate(operand, pendingAdditiveOperator)) {
            abortOperation();
            return;
        }
        if (pendingAdditiveOperator == tr("+"))
            equation->setText(QString::number(operand) + " + ");
        else
            equation->setText(QString::number(operand) + " - ");
        result_line->setText(QString::number(sumSoFar));
    } else {
        sumSoFar = operand;
    }


    waitingForOperand = true;
}

void Calculator::multiplicativeOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    if (!clickedButton)
        return;
    QString clickedOperator = clickedButton->text();
    double operand = equation->text().toDouble();
    if (!Calculator::getCheck())
        pendingMultiplicativeOperator = clickedOperator;

    if (!pendingMultiplicativeOperator.isEmpty()) {

        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
            }
        if(pendingMultiplicativeOperator == tr("\303\227"))
            equation->setText(QString::number(operand) + " x ");
        else
            equation->setText(QString::number(operand) + " / ");
        result_line->setText(QString::number(factorSoFar));
    } else {
        factorSoFar = operand;
    }

    if (Calculator::getCheck())
        pendingMultiplicativeOperator = clickedOperator;
        Calculator::setCheck(false);

    waitingForOperand = true;
}

void Calculator::equalClicked()
{
    double operand = equation->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {

        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        operand = factorSoFar;
        pendingMultiplicativeOperator.clear();
    }

    if (!pendingAdditiveOperator.isEmpty()) {

        if (!calculate(operand, pendingAdditiveOperator)) {
            abortOperation();
            return;
        }
        pendingAdditiveOperator.clear();
    } else {
        sumSoFar = operand;
    }

    result_line->setText("= " + QString::number(sumSoFar));
    waitingForOperand = true;
}

void Calculator::pointClicked()
{
    if (waitingForOperand)
        equation->setText("0");
    if (!equation->text().contains("."))
        equation->setText(equation->text() + tr("."));
    waitingForOperand = false;
}

void Calculator::changeSignClicked()
{
    QString text = equation->text();
    double value = text.toDouble();

    if (value > 0.0) {
        text.prepend(tr("-"));
    } else if (value < 0.0) {
        text.remove(0, 1);
    }
    equation->setText(text);
}

void Calculator::backspaceClicked()
{
    if (waitingForOperand)
        return;

    QString text = equation->text();
    text.chop(1);
    if ( text.isEmpty()) {
        text = "0";
        waitingForOperand = true;
    }
    equation->setText(text);
}

void Calculator::clear()
{
    if (waitingForOperand)
        return;

    equation->setText("0");
    result_line->setText("= 0");
    Calculator::setCheck(true);
    waitingForOperand = true;
}

void Calculator::clearAll()
{
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    pendingAdditiveOperator.clear();
    pendingMultiplicativeOperator.clear();
    equation->setText("0");
    result_line->setText("= 0");
    Calculator::setCheck(true);
    waitingForOperand = true;
}

void Calculator::clearMemory()
{
    sumInMemory = 0.0;
}

void Calculator::readMemory()
{
    result_line->setText(QString::number(sumInMemory));
    waitingForOperand = true;
}

void Calculator::setMemory()
{
    equalClicked();
    sumInMemory = result_line->text().toDouble();
}

void Calculator::addToMemory()
{
    equalClicked();
    sumInMemory += result_line->text().toDouble();
}

template<typename PointerToMemberFunction>
Button *Calculator::createButton(const QString &text, const PointerToMemberFunction & member)
{
    Button *button = new Button(text);
    connect(button, &Button::clicked, this, member);
    return button;
}

void Calculator::abortOperation()
{
    clearAll();
    equation->setText(tr("####"));
    result_line->setText(tr("####"));
}

bool Calculator::calculate(double rightOperand, const QString &pendingOperator)
{
    if (pendingOperator == tr("+")) {
        equation->setText(QString::number(sumSoFar) + " + " + QString::number(rightOperand));
        sumSoFar += rightOperand;
    } else if (pendingOperator == tr("-")) {
        equation->setText(QString::number(sumSoFar) + " - " + QString::number(rightOperand));
        sumSoFar -= rightOperand;
    } else if (pendingOperator == tr("\303\227")) {
        equation->setText(QString::number(factorSoFar) + " x " + QString::number(rightOperand));
        factorSoFar *= rightOperand;
    } else if (pendingOperator == tr("\303\267")) {
        if (rightOperand == 0.0)
            return false;
        equation->setText(QString::number(factorSoFar) + " / " + QString::number(rightOperand));
        factorSoFar /= rightOperand;
    }
    return true;
}
