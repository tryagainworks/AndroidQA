#ifndef CLSQADETAILS_H
#define CLSQADETAILS_H
#include <QString>

class clsqadetails
{
public:
    clsqadetails();
    QString strQuestion;
    QString strAns1;
    QString strAns2;
    int intDefaultAns;
    int intSelectedAns;
    bool blnAnswered;
};

#endif // CLSQADETAILS_H
