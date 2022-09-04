#ifndef CALCULATORMANAGER_H
#define CALCULATORMANAGER_H

#include <QObject>
#include <QStack>

enum EnOperator{
    EN_NONE = 0,
    EN_PLUS,    // 加 x plus y
    EN_MINUS,   // 减 x minus y
    EN_TIMES,   // 乘 x times y
    EN_OVER,    // 除 x over y
    EN_MOD,     // 求余 x modulo/modulus y
    EN_ROOT     // 求根 take the nth root of x
};

class CalculatorManager : public QObject
{
    Q_OBJECT
public:
    CalculatorManager();
    ~CalculatorManager();

    void inputNumber(int iNum);
    void inputPoint();
    void inputOperator(EnOperator enOperator);
    void clickedEqual();

    void reset();

private:
    EnOperator m_enOperator;
    double m_dInput;
    bool m_bDecimal;
    int m_iCount;
    QString m_strInput;

    QStack<EnOperator> m_stackOp;
    QStack<double> m_stackNum;

    bool bOpPri(EnOperator enOp1, EnOperator enOp2);
    bool compute(double num1, double num2, EnOperator enOpTop, double &dResult);

signals:
    void sig_show(QString);
    void sig_showResult(QString);
    void sig_error(QString);
};

#endif // CALCULATORMANAGER_H
