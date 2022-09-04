#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QPushButton>

#include "calculator/CalculatorManager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , cal(new CalculatorManager())
{
    ui->setupUi(this);
    setWindowTitle(QObject::tr("计算器"));

    initUI();
    initConnect();
}

MainWindow::~MainWindow()
{
    if (nullptr != cal)
    {
        delete cal;
        cal = nullptr;
    }

    delete ui;
}

void MainWindow::initUI()
{

}

void MainWindow::initConnect()
{
    connect(cal, SIGNAL(sig_show(QString)), this, SLOT(slot_show(QString)));
    connect(cal, SIGNAL(sig_showResult(QString)), this, SLOT(slot_showResult(QString)));
    connect(cal, SIGNAL(sig_error(QString)), this, SLOT(slot_error(QString)));

    connect(ui->btnReset, SIGNAL(clicked()), this, SLOT(slot_btnReset_clicked()));

    connect(ui->btnNum1, SIGNAL(clicked()), this, SLOT(slot_btnNum1_clicked()));
    connect(ui->btnNum2, SIGNAL(clicked()), this, SLOT(slot_btnNum2_clicked()));
    connect(ui->btnNum3, SIGNAL(clicked()), this, SLOT(slot_btnNum3_clicked()));
    connect(ui->btnNum4, SIGNAL(clicked()), this, SLOT(slot_btnNum4_clicked()));
    connect(ui->btnNum5, SIGNAL(clicked()), this, SLOT(slot_btnNum5_clicked()));
    connect(ui->btnNum6, SIGNAL(clicked()), this, SLOT(slot_btnNum6_clicked()));
    connect(ui->btnNum7, SIGNAL(clicked()), this, SLOT(slot_btnNum7_clicked()));
    connect(ui->btnNum8, SIGNAL(clicked()), this, SLOT(slot_btnNum8_clicked()));
    connect(ui->btnNum9, SIGNAL(clicked()), this, SLOT(slot_btnNum9_clicked()));
    connect(ui->btnNum0, SIGNAL(clicked()), this, SLOT(slot_btnNum0_clicked()));

    connect(ui->btnPoint, SIGNAL(clicked()), this, SLOT(slot_btnPoint_clicked()));

    connect(ui->btnOperaPlus, SIGNAL(clicked()), this, SLOT(slot_btnOperaPlus_clicked()));
    connect(ui->btnOperaSub, SIGNAL(clicked()), this, SLOT(slot_btnOperaSub_clicked()));
    connect(ui->btnOperaMul, SIGNAL(clicked()), this, SLOT(slot_btnOperaMul_clicked()));
    connect(ui->btnOperaDiv, SIGNAL(clicked()), this, SLOT(slot_btnOperaDiv_clicked()));
    connect(ui->btnMod, SIGNAL(clicked()), this, SLOT(slot_btnOperaMod_clicked()));
    connect(ui->btnRoot, SIGNAL(clicked()), this, SLOT(slot_btnOperaRoot_clicked()));


    connect(ui->btnOperaEqu, SIGNAL(clicked()), this, SLOT(slot_btnOperaEqu_clicked()));
}

void MainWindow::slot_show(QString strText)
{
    if ("" == strText)
    {
        ui->textBrowser->clear();
    }
    else
        ui->textBrowser->setText(strText);
}

void MainWindow::slot_showResult(QString strText)
{
    ui->textBrowser->append(strText);
}

void MainWindow::slot_error(QString strText)
{
    ui->textBrowser->setText(strText);
}

void MainWindow::slot_btnReset_clicked()
{
    cal->reset();
    ui->textBrowser->clear();
}

void MainWindow::slot_btnNum1_clicked()
{
    cal->inputNumber(1);
}

void MainWindow::slot_btnNum2_clicked()
{
    cal->inputNumber(2);
}

void MainWindow::slot_btnNum3_clicked()
{
    cal->inputNumber(3);
}

void MainWindow::slot_btnNum4_clicked()
{
    cal->inputNumber(4);
}

void MainWindow::slot_btnNum5_clicked()
{
    cal->inputNumber(5);
}

void MainWindow::slot_btnNum6_clicked()
{
    cal->inputNumber(6);
}

void MainWindow::slot_btnNum7_clicked()
{
    cal->inputNumber(7);
}

void MainWindow::slot_btnNum8_clicked()
{
    cal->inputNumber(8);
}

void MainWindow::slot_btnNum9_clicked()
{
    cal->inputNumber(9);
}

void MainWindow::slot_btnNum0_clicked()
{
    cal->inputNumber(0);
}

void MainWindow::slot_btnPoint_clicked()
{
    cal->inputPoint();
}

void MainWindow::slot_btnOperaPlus_clicked()
{
    ui->textBrowser->clear();
    cal->inputOperator(EN_PLUS);
}

void MainWindow::slot_btnOperaSub_clicked()
{
    cal->inputOperator(EN_MINUS);
}

void MainWindow::slot_btnOperaMul_clicked()
{
    cal->inputOperator(EN_TIMES);
}

void MainWindow::slot_btnOperaDiv_clicked()
{
    cal->inputOperator(EN_OVER);
}

void MainWindow::slot_btnOperaMod_clicked()
{
    cal->inputOperator(EN_MOD);
}

void MainWindow::slot_btnOperaRoot_clicked()
{
    cal->inputOperator(EN_ROOT);
}

void MainWindow::slot_btnOperaEqu_clicked()
{
    cal->clickedEqual();
}

