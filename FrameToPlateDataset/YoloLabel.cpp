#include "YoloLabel.h"
//============================================================================================================
YoloLabel::YoloLabel(QObject *parent) : QObject(parent)
{

}
//============================================================================================================
QString YoloLabel::GenerateLable(int classID, float xCenter, float yCenter, float width, float height, float imageWidth, float imageHeight)
{
    float xc = xCenter;
    float yc = yCenter;
    float h = height;
    float w = width;
    xc /= imageWidth;
    yc /= imageHeight;
    h /= imageHeight;
    w /= imageWidth;
    return QString::number(classID)+" "+QString::number(xc)+" "+QString::number(yc)+" "+QString::number(w)+" "+QString::number(h);
}
//==================================================================================
QRect YoloLabel::GetImageLocation(QString YoloLableLine,int imageWidth,int imageHeight)
{
    QRect res(0,0,0,0);
    QStringList parts= YoloLableLine.split(" ");
    if(parts.count()<5)return res;


    float  w=parts[3].toFloat()*imageWidth;
    float  h=parts[4].toFloat()*imageHeight;

    float  xc=parts[1].toFloat()*imageWidth-w/2;
    float  yc=parts[2].toFloat()*imageHeight-h/2;
    res.setX(xc);
    res.setY(yc);
    res.setWidth(w);
    res.setHeight(h);

    return  res;

}
//==================================================================================
bool YoloLabel::RectIsChild(QRect parent,QRect child)
{

if(child.x()>parent.x() && child.y()> parent.y() &&
        child.x()+child.width()<parent.x()+parent.width() &&
        child.y()+child.height()<parent.y()+parent.height()
        )
    return true;

    return false;
}
//==================================================================================
QString YoloLabel::GetLablesInsidePlate(QString plate,uint imageWidth,uint imageHeight,QString labelFileContent)
{
    QString result;

QRect plateLocation= GetImageLocation(plate,imageWidth,imageHeight);
//qDebug()<<"plate:"<<plateLocation;
QStringList parts= labelFileContent.split("\n");
foreach (QString item, parts) {
    QRect itemLocation=GetImageLocation(item,imageWidth,imageHeight);
    if(RectIsChild(plateLocation,itemLocation))
        result.append(item+"");
 //  qDebug()<<"object"<<itemLocation;

}


    return  result;


}
//============================================================================================================

QString YoloLabel::TranslateLine(QString YoloLableLine,int oldWidth,int oldHeight,int oldX,int oldY,int newWidth,int newHeight)
{
//"33 0.287891 0.363889 0.008594 0.018056"
    QStringList parts= YoloLableLine.split(" ");
    if(parts.count()<5)return "";

    int id=parts[0].toUInt();
    float  w=parts[3].toFloat()*oldWidth;
    float  h=parts[4].toFloat()*oldHeight;
    float  xc=parts[1].toFloat()*oldWidth;
    float  yc=parts[2].toFloat()*oldHeight;
    xc-=oldX;
    yc-=oldY;

return GenerateLable(id,xc,yc,w,h,newWidth,newHeight);
}
//============================================================================================================

void YoloLabel::RemoveLabelsFromYoloLabel(QString inputLabelFile, QString outputfile, QList<int> labels)
{
    QString outputContent;
    if(!QFile::exists(inputLabelFile))return;
      qDebug()<<inputLabelFile;
    QFile inputFile(inputLabelFile);
    inputFile.open(QFile::ReadOnly);
    while(true)
    {
        QString line=inputFile.readLine();
       // qDebug()<<line;
        if(labels.indexOf(line.split(" ")[0].toUInt())<0)
        {
            outputContent.append(line);
        }
        if(!inputFile.canReadLine())break;
    }
    inputFile.close();
    QFile outputFile(outputfile);
    outputFile.open(QFile::WriteOnly);
    outputFile.write(outputContent.toLatin1());
    outputFile.close();
}
//============================================================================================================
void YoloLabel::RemoveLabelsFromYoloLabelAndTranslate(QString inputLabelFile, QString outputfile, QList<int> labels,int oldWidth,int oldHeight,int oldX,int oldY,int newWidth,int newHeight)
{
    QString outputContent;
    if(!QFile::exists(inputLabelFile))return;
      qDebug()<<inputLabelFile;
    QFile inputFile(inputLabelFile);
    inputFile.open(QFile::ReadOnly);
    while(true)
    {
        QString line=inputFile.readLine();
       // qDebug()<<line;
        if(labels.indexOf(line.split(" ")[0].toUInt())<0)
        {

            outputContent.append(TranslateLine(line,oldWidth,oldHeight,oldX,oldY,newWidth,newHeight)+"\n");
        }
        if(!inputFile.canReadLine())break;
    }
    inputFile.close();
    QFile outputFile(outputfile);
    outputFile.open(QFile::WriteOnly);
    outputFile.write(outputContent.toLatin1());
    outputFile.close();
}
//============================================================================================================
