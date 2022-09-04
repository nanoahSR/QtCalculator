#include "CalculatorManager.h"
#include <QObject>
#include <QDebug>
/**
 * 界面类传入数字存在内存中，待点击“+”“-”“*”“/”和“=”按钮后，进行计算。
 *
 * 原理：
 * 利用两个栈实现加减乘除运算，
 * 第一个栈存数字
 * 第二个栈存运算符。存入运算符时要与栈顶元素判断优先级。乘除优先级高于加减。
 * 栈顶元素优先级高于输入运算符时，先运算栈顶运算符，存入结果后再存入输入的运算符。
 *
 * 计算：
 * 运算符栈的栈顶元素、数字栈的两个元素进行运算。【注意，这里要注意栈push/pop的顺序】
 *
 */
// TODO: 1. 括号
// TOOD: 2. 幂运算....

CalculatorManager::CalculatorManager()
    : m_enOperator(EN_NONE)
    , m_dInput(0)
    , m_bDecimal(false)
    , m_iCount(0)
    , m_strInput("")
{
    m_stackNum.clear();
    m_stackOp.clear();
}

CalculatorManager::~CalculatorManager()
{

}

/**
 * @brief CalculatorManager::inputNumber：输入数字
 * @param iNum
 */
void CalculatorManager::inputNumber(int iNum)
{
    // 判断是不是小数
    if (!m_bDecimal)
        m_dInput = m_dInput * 10 + iNum;
    else
    {
        m_iCount ++;
        int i = m_iCount;
        double dNum = static_cast<double>(iNum);
        while (i--)
        {
            dNum = dNum*1.0 / 10;
        }
        m_dInput = m_dInput + dNum;
    }
    m_strInput.append(QString::number(iNum));
    emit sig_show(m_strInput);
}

/**
 * @brief CalculatorManager::inputPoint: 点击小数点
 */
void CalculatorManager::inputPoint()
{
    // 防止重复输入
    if (m_bDecimal)
    {
        emit sig_show("INPUT ERROR!");
        reset();
    }
    else {
        m_bDecimal = true;
        m_strInput.append(".");
        emit sig_show(m_strInput);
    }
}

/**
 * @brief CalculatorManager::inputOperator： 输入运算符
 * @param enOperator
 */
void CalculatorManager::inputOperator(EnOperator enOperator)
{
    switch(enOperator)
    {
    case EN_PLUS: m_strInput.append(" + "); break;
    case EN_MINUS: m_strInput.append(" - "); break;
    case EN_TIMES: m_strInput.append(" x "); break;
    case EN_OVER: m_strInput.append(" ÷ "); break;
    case EN_MOD: m_strInput.append(" mod "); break;
    case EN_ROOT: m_strInput.append(" yroot "); break;
    case EN_NONE:
    default: break;
    }
    emit sig_show(m_strInput);

    m_stackNum.push(m_dInput);
    // 复位
    m_dInput = 0;
    m_bDecimal = false;
    m_iCount = 0;

    if (true == m_stackOp.empty())
    {
        m_stackOp.push(enOperator);
    }
    else
    {
        EnOperator enOpTop = m_stackOp.top();
        int iPri = bOpPri(enOpTop, enOperator);
        if (iPri)
        {
            double num1 = m_stackNum.top();
            m_stackNum.pop();
            double num2 = m_stackNum.top();
            m_stackNum.pop();
            double dResult = 0.0;
            if(!compute(num1, num2, enOpTop, dResult))
            {
                reset();
                return ;
            }
            m_stackNum.push(dResult);
            m_stackOp.pop();
            m_stackOp.push(enOperator);
        }
        else
        {
            m_stackOp.push(enOperator);
        }
    }
}

/**
 * @brief CalculatorManager::clickedEqual: 点击=
 */
void CalculatorManager::clickedEqual()
{
    m_strInput.append(" =");
    emit sig_show(m_strInput);

    m_stackNum.push(m_dInput);

    while (!m_stackOp.empty())
    {
        EnOperator enOp = m_stackOp.top();
        m_stackOp.pop();
        double num1 = m_stackNum.top();
        m_stackNum.pop();
        double num2 = m_stackNum.top();
        m_stackNum.pop();
        double dResult = 0.0;
        if(!compute(num1, num2, enOp, dResult))
        {
            reset();
            return ;
        }
        m_stackNum.push(dResult);
    }

    double dResult = m_stackNum.top();
    emit sig_showResult(QString::number(dResult));

    reset();
}

void CalculatorManager::reset()
{
    m_enOperator = EN_NONE;
    m_dInput = 0;
    m_bDecimal = false;
    m_iCount = 0;

    m_stackOp.clear();
    m_stackNum.clear();

    m_strInput = "";
}

/**
 * @brief CalculatorManager::bOpPri
 * @param enOp1
 * @param enOp2
 * @return false: enOp1 <= enOp2; true: enOp1 > enOp2
 */
bool CalculatorManager::bOpPri(EnOperator enOp1, EnOperator enOp2)
{
    if(EN_NONE == enOp1)
    {
        if(EN_NONE == enOp2) {
            return true;
        } else {
            return false;
        }
    }

    if(EN_NONE == enOp2)
    {
        return true;
    }

    if(EN_PLUS == enOp1 || EN_MINUS == enOp1)
    {
        if(EN_TIMES == enOp2 || EN_OVER == enOp2 || EN_MOD == enOp2 || EN_ROOT == enOp2)
            return false;
        else
            return true;
    }

    if(EN_TIMES == enOp1 || EN_OVER == enOp1 || EN_MOD == enOp1 || EN_ROOT == enOp1)
    {
        if(EN_PLUS == enOp2 || EN_MINUS == enOp2)
            return true;
        else
            return false;
    }
    return true;
}

/**
 * @brief CalculatorManager::compute 计算，
 *          根据栈[先进后出]的特性，num1后进先出，是运算符后面的数字。num2先进后出，是运算符前面的数字。
 * @param num1
 * @param num2
 * @param enOpTop
 * @return
 */
bool CalculatorManager::compute(double num1, double num2, EnOperator enOpTop, double& dResult)
{
    switch(enOpTop)
    {
    case EN_PLUS:
    {
        dResult = num2 + num1;
        break;
    }
    case EN_MINUS:
    {
        dResult = num2 - num1;
                break;
    }
    case EN_TIMES:
    {
        dResult = num2 * num1;
                break;
    }
    case EN_OVER:
    {
        if (num1 == 0) {
            emit sig_error("ERROR");
            return false;
        } else {
            dResult = num2 * 1.0 / num1;
            break;
        }
    }
    case EN_MOD:
    {
        if (num1 == 0) {
            emit sig_error("ERROR");
            return false;
        } else {
            dResult = fmod(num2, num1);
            break;
        }
    }
    case EN_ROOT:
    {
        if (num1 == 0) {
            emit sig_error("ERROR");
            return false;
        } else {
            dResult = pow(num2*1.0, 1.0/num1);
            qDebug() << num2 << num1 << dResult;
            break;
        }
    }
    case EN_NONE:
    default:
        return false;
    }
    return true;
}
