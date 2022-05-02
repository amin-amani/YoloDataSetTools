

#include <QtTest>
//#include "
#include "YoloLabel.h"
// add necessary includes here
class FrameToPlateTest : public QObject
{
    Q_OBJECT

public:
    FrameToPlateTest();
    ~FrameToPlateTest();

private slots:
    void DoTest();

};

FrameToPlateTest::FrameToPlateTest()
{

}

FrameToPlateTest::~FrameToPlateTest()
{

}

void FrameToPlateTest::DoTest()
{
    YoloLabel a;
    QString line="33 0.287891 0.363889 0.008594 0.018056";
    QString result= a.TranslateLine(line,2560,1440,666,505,184,40);
    qDebug()<<result;
    QVERIFY2(result=="33 0.385875 0.475005 0.119569 0.650016","invalid ans");
}


QTEST_APPLESS_MAIN(FrameToPlateTest)

#include "tst_FrameToPlate.moc"
