

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
    void TranslateTest();
    void RectISChildTest();
    void SortObjectsByPlateTest();

};
//================================================================================================
FrameToPlateTest::FrameToPlateTest()
{

}

FrameToPlateTest::~FrameToPlateTest()
{

}
//================================================================================================
void FrameToPlateTest::TranslateTest()
{
    YoloLabel a;
    QString line="33 0.287891 0.363889 0.008594 0.018056";
    QString result= a.TranslateLine(line,2560,1440,666,505,184,40);
    qDebug()<<result;
    QVERIFY2(result=="33 0.385875 0.475005 0.119569 0.650016","invalid ans");
}
//================================================================================================
void FrameToPlateTest::RectISChildTest()
{
  YoloLabel a;
  QRect parent(10,10,100,100);
  QRect child(20,20,10,10);
bool res=a.RectIsChild(parent,child);
QVERIFY2(res==true,"rect child test fail");


child.setX(20);
child.setY(20);
child.setWidth(100);
child.setHeight(100);
res=a.RectIsChild(parent,child);
QVERIFY2(res==false,"rect child test fail");


child.setX(20);
child.setY(20);
child.setWidth(10);
child.setHeight(90);
res=a.RectIsChild(parent,child);
QVERIFY2(res==false,"rect child test fail");

child.setX(20);
child.setY(20);
child.setWidth(90);
child.setHeight(10);
res=a.RectIsChild(parent,child);
QVERIFY2(res==false,"rect child test fail");
}
//================================================================================================
void FrameToPlateTest::SortObjectsByPlateTest()
{
    YoloLabel a;
  QString content=
    "43 0.760742 0.466435 0.0843099 0.0393519\n"
    "5 0.113607 0.894097 0.0094401 0.0260417\n"
    "3 0.770182 0.465278 0.00683594 0.0219907\n"
    "5 0.789063 0.466435 0.00683594 0.0185185\n"
    "6 0.76237 0.466435 0.00846354 0.0231481\n"
    "6 0.797201 0.465278 0.00683594 0.0190972\n"
    "6 0.738607 0.46875 0.00911458 0.0243056\n"
    "9 0.778971 0.464699 0.00878906 0.0219907\n"
    "9 0.730469 0.468171 0.0078125 0.021412\n"
    "24 0.750326 0.468171 0.014974 0.0196759\n"
    "42 0.792643 0.452546 0.0146484 0.00694444\n"
    "43 0.0895182 0.891204 0.0986328 0.0445602\n"
    "1 0.09375 0.894676 0.0078125 0.025463\n"
    "3 0.10319 0.894097 0.00846354 0.0266204\n"
    "3 0.0651042 0.894097 0.00813802 0.0248843\n"
    "3 0.0556641 0.894097 0.00878906 0.0248843\n"
    "5 0.134766 0.896991 0.00813802 0.0225694\n"
    "7 0.125326 0.898148 0.00911458 0.0243056\n"
    "15 0.0800781 0.894676 0.0130208 0.0243056\n"
    "42 0.129232 0.882523 0.016276 0.00868056\n";


  QString ans=    "3 0.770182 0.465278 0.00683594 0.0219907"
                  "5 0.789063 0.466435 0.00683594 0.0185185"
                  "6 0.76237 0.466435 0.00846354 0.0231481"
                  "6 0.797201 0.465278 0.00683594 0.0190972"
                  "6 0.738607 0.46875 0.00911458 0.0243056"
                  "9 0.778971 0.464699 0.00878906 0.0219907"
                  "9 0.730469 0.468171 0.0078125 0.021412"
                  "24 0.750326 0.468171 0.014974 0.0196759"
                  "42 0.792643 0.452546 0.0146484 0.00694444";

    QString result= a.GetLablesInsidePlate("43 0.760742 0.466435 0.0843099 0.0393519",3072,1728,content);
    QVERIFY2(result==ans,"invalid ans");
}
//================================================================================================
QTEST_APPLESS_MAIN(FrameToPlateTest)

#include "tst_FrameToPlate.moc"
