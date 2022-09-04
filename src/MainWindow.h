#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class CalculatorManager;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initUI();
    void initConnect();

private:
    Ui::MainWindow *ui;

    CalculatorManager *cal;

    QString m_strInput;

public slots:
    void slot_show(QString strText);
    void slot_showResult(QString strText);
    void slot_error(QString strText);

private slots:
    void slot_btnReset_clicked();

    void slot_btnNum1_clicked();
    void slot_btnNum2_clicked();
    void slot_btnNum3_clicked();
    void slot_btnNum4_clicked();
    void slot_btnNum5_clicked();
    void slot_btnNum6_clicked();
    void slot_btnNum7_clicked();
    void slot_btnNum8_clicked();
    void slot_btnNum9_clicked();
    void slot_btnNum0_clicked();

    void slot_btnPoint_clicked();

    void slot_btnOperaPlus_clicked();
    void slot_btnOperaSub_clicked();
    void slot_btnOperaMul_clicked();
    void slot_btnOperaDiv_clicked();
    void slot_btnOperaMod_clicked();
    void slot_btnOperaRoot_clicked();

    void slot_btnOperaEqu_clicked();

};
#endif // MAINWINDOW_H
