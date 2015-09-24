#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fnLoadAllQA();
    fnDisplayCurrentQA(0,'1');
    intCurrentQA=0;
    intMarksGained=0;
}

void MainWindow::fnLoadAllQA(){
    QFile data(":/new/generalqa/qatxt.txt");
    if (data.open(QFile::ReadOnly)) {
        QTextStream in(&data);
        intTotalQAS = in.readLine().toInt();
        objqa = new clsqadetails[intTotalQAS];
        for(int i=0;i<intTotalQAS;i++){
            objqa[i].strQuestion = in.readLine();
            objqa[i].strAns1 = in.readLine();
            objqa[i].strAns2 = in.readLine();
            objqa[i].intDefaultAns = in.readLine().toInt();
            objqa[i].intSelectedAns = 0;
            objqa[i].blnAnswered = false;
        }
        data.close();
    }
}

void MainWindow::fnDisplayCurrentQA(int intIndex, char chr)
{
    switch (chr) {
    case '1':
        ui->cmdPrevious->setEnabled(false);
        break;
    case '2':
        ui->cmdPrevious->setEnabled(true);
        break;
    case 'L':
        ui->cmdNext->setEnabled(true);
        ui->optgroup->setVisible(true);
        break;
    case 'R':
        ui->cmdNext->setEnabled(false);
        ui->optgroup->setVisible(false);
        QString str;
        str = str.sprintf("%d out of %d",intMarksGained,intTotalQAS);
        ui->lblQuestion->setText(str);

        if(intTotalQAS/2 <=intMarksGained){
            ui->lblIndividualResultImage->setPixmap(QPixmap (":/new/images/thumbup.png"));

        }else{
            ui->lblIndividualResultImage->setPixmap(QPixmap (":/new/images/thumbdown.png"));
        }

        return;
        break;
    }
    QString strTemp;
    strTemp.sprintf("%d/%d) %s",intIndex+1, intTotalQAS,objqa[intIndex].strQuestion.toStdString().c_str());
    ui->lblQuestion->setText(strTemp);
    ui->lblAns1->setText(objqa[intIndex].strAns1);
    ui->lblAns2->setText(objqa[intIndex].strAns2);

    if(objqa[intIndex].blnAnswered){
        ui->lblAns1->setEnabled(false);
        ui->lblAns2->setEnabled(false);
        if(objqa[intIndex].intSelectedAns == objqa[intIndex].intDefaultAns){
            ui->lblIndividualResultImage->setPixmap(QPixmap (":/new/images/correct.png"));
        }else{
            ui->lblIndividualResultImage->setPixmap(QPixmap (":/new/images/wrong.png"));
        }
        ui->cmdNext->setEnabled(true);
        if(objqa[intIndex].intDefaultAns==1){
            ui->lblAns1->setChecked(true);
        }else{
            ui->lblAns2->setChecked(true);
        }
    }else{
        ui->lblAns1->setEnabled(true);
        ui->lblAns2->setEnabled(true);
        ui->lblIndividualResultImage->clear();
        ui->optgroup->setEnabled(true);
        ui->lblAns1->setAutoExclusive(false);
        ui->lblAns1->setChecked(false);
        ui->lblAns1->setAutoExclusive(true);
        ui->lblAns2->setAutoExclusive(false);
        ui->lblAns2->setChecked(false);
        ui->lblAns2->setAutoExclusive(true);
        ui->cmdNext->setEnabled(false);
    }
}

MainWindow::~MainWindow()
{
    delete[] objqa;
    delete ui;
}

void MainWindow::on_cmdNext_clicked()
{
    intCurrentQA+=1;
    if(intCurrentQA==1){
        fnDisplayCurrentQA(intCurrentQA,'2'); //second question
    }else if(intCurrentQA==intTotalQAS){
        fnDisplayCurrentQA(intCurrentQA,'R'); //result. after last question
    }
    else{
        fnDisplayCurrentQA(intCurrentQA,'X');
    }
}

void MainWindow::on_cmdPrevious_clicked()
{
    intCurrentQA-=1;
    if(intCurrentQA==0){
        fnDisplayCurrentQA(intCurrentQA,'1');
    } else if(intCurrentQA==intTotalQAS-1){
        fnDisplayCurrentQA(intCurrentQA,'L'); //last question
    }
    else{
        fnDisplayCurrentQA(intCurrentQA,'X');
    }
}

void MainWindow::fnOnAnswerSelected(int intIndex){
    ui->cmdNext->setEnabled(true);
    objqa[intIndex].blnAnswered = true;
    objqa[intIndex].intSelectedAns = ui->lblAns1->isChecked()? 1 : 2;
    if(objqa[intIndex].intSelectedAns == objqa[intIndex].intDefaultAns){
        ui->lblIndividualResultImage->setPixmap(QPixmap (":/new/images/correct.png"));
        intMarksGained+=1;
    }else{
        ui->lblIndividualResultImage->setPixmap(QPixmap (":/new/images/wrong.png"));
    }
    ui->lblAns1->setEnabled(false);
    ui->lblAns2->setEnabled(false);
}

void MainWindow::on_lblAns1_clicked()
{
    fnOnAnswerSelected(intCurrentQA);
}

void MainWindow::on_lblAns2_clicked()
{
    fnOnAnswerSelected(intCurrentQA);
}
