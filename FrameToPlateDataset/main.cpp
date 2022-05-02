#include <QtCore>
#include <QFile>
#include "YoloLabel.h"
#include <opencv4/opencv2/opencv.hpp>
//================================================================================
QStringList GetDataSetLabelFiles(QString path)
{
    QStringList result;
    QStringList filters={".txt"};
    QDirIterator directoryIterator(path, QDirIterator::Subdirectories);
    while (directoryIterator.hasNext())
    {
        QString fname= directoryIterator.next();
        if(fname.contains("/.") || fname.contains("classes.txt"))
            continue;

        for(int i=0;i<filters.count();i++)
        {

            if(fname.endsWith(filters[i]))
            {

                result.append(fname);


                break;
            }

        }
    }
    return result;
}
//================================================================================

QVector<int> GetClassCount(QString fileName)
{
    QVector<int> result;
    QFile file(fileName);

    if(!file.open(QFile::ReadOnly))return result;
    while(true)
    {

        QString line=file.readLine().trimmed();
        result.append(line.split(" ")[0].toUInt());
        if(!file.canReadLine())break;


    }
    file.close();
    return  result;
}
//================================================================================

QStringList GetPlatePosition(QString fileName)
{
    QStringList result;
    QFile file(fileName);

    if(!file.open(QFile::ReadOnly))return result;
    while(true)
    {

        QString line=file.readLine().trimmed();
        if(line.split(" ")[0].toUInt()==43)
        {
            result.append(line);

        }
        if(!file.canReadLine())break;


    }
    file.close();
    return  result;
}
//================================================================================

QStringList GetClassNames(QString fileName)
{
    QStringList result;
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly))return result;
    while(true)
    {

        QString line=file.readLine();
        result.append(line.trimmed());
        if(!file.canReadLine())break;



    }
    file.close();
    return result;

}
//================================================================================
void PrintHelpMenu()
{
    qDebug()<<"help :";
    qDebug()<<"to print result based on class names put classes.txt inside path";
    qDebug()<<"Usage: YoloDatasetTools /path/to/labels";

}
//================================================================================

cv::Mat CropRectFromImage(cv::Mat image,QRect location)
{

    cv::Rect roi(location.x(), location.y(), location.width(), location.height());
    return  image(roi);

}
//================================================================================
QString GetNameFromPath(QString fileName)
{
    QStringList parts=fileName.split("/");

    return parts[parts.length()-1];
}
//================================================================================
QString GetImageFileNameFromLabelFileName(QString labelFileName)
{
    QString imageFilename= labelFileName;
    imageFilename.replace(".txt",".jpg");
    imageFilename.replace(".txt",".png");
    imageFilename.replace(".txt",".bmp");
    return imageFilename;
}
//================================================================================

int main(int argc, char *argv[])
{
    // QCoreApplication a(argc, argv);
  QVector<int> labels;
     QDir dir;

    if(argc<2){
        PrintHelpMenu();

        return 0;
    }

    QString outputPath=argv[1];
    outputPath+="/ocr/";
    dir.mkdir(outputPath);
    qDebug()<<"input path:"<<argv[1];

    QStringList labelFiles=GetDataSetLabelFiles(argv[1]);


    for(int i=0;i<labelFiles.count();i++)
    {

        QString labelFileName=  labelFiles[i];
        QStringList plateList=  GetPlatePosition(labelFileName);
        QString imageFilename=GetImageFileNameFromLabelFileName(labelFileName);
        cv::Mat img=cv::imread(imageFilename.toStdString());

              int number=0;
        for(int j=0;j<plateList.length();j++)
        {
    YoloLabel lab;
            QRect r= lab.GetImageLocation(plateList[j],img.cols,img.rows);
            cv::Mat plate= CropRectFromImage(img,r);

            cv::imwrite((outputPath+GetNameFromPath(imageFilename)+"_"+QString::number(number)+".png").toStdString(),plate);
            lab.CreateTranslatedOCR(plateList[j],labelFileName,outputPath+GetNameFromPath(imageFilename)+"_"+QString::number(number++)+".txt",img.cols,img.rows,r.x(),r.y(),r.width(),r.height());
//            QList<int> lst;
//            lst.append(43);
//            lab.RemoveLabelsFromYoloLabelAndTranslate(labelFileName,outputPath+GetNameFromPath(imageFilename)+"_"+QString::number(number++)+".txt",lst,img.cols,img.rows,r.x(),r.y(),r.width(),r.height());


        }





    }


    return  0;

}
