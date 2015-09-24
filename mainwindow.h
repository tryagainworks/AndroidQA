#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <clsqadetails.h>
#include <QMainWindow>
#include <QFile>
#include <QTextStream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    clsqadetails *objqa;
    int intTotalQAS;
    void fnLoadAllQA();
    void fnDisplayCurrentQA(int intIndex, char chr);
    int intCurrentQA;
    void fnOnAnswerSelected(int intIndex);
    int intMarksGained;
private slots:

    void on_cmdNext_clicked();

    void on_cmdPrevious_clicked();

    void on_lblAns1_clicked();

    void on_lblAns2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
