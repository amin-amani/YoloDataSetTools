#include <QtCore>
#include <QFile>
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
bool LabelExistInFile(QString fileName,int label)
{

    QFile file(fileName);
    if(!file.open(QFile::ReadOnly))return false;
    while(true)
    {

        QString line=file.readLine().trimmed();
        if(line.split(" ")[0].toUInt()==label)
        {
                file.close();
                return true;
        }
        if(!file.canReadLine())break;
    }
    file.close();
    return  false;
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

int  GetLabelNumber(QString label,QString labelListFileName)
{
    int result=-1;

    QFile file(labelListFileName);
    if(!file.open(QFile::ReadOnly))return result;
    int i=0;
    while(true)
    {

        QString line=file.readLine().trimmed();
        if(line==label)result=i;
        i++;
        if(!file.canReadLine())break;



    }
    file.close();
    return result;


}
//================================================================================


//================================================================================
void PrintHelpMenu()
{
    qDebug()<<"help :";
    qDebug()<<"to print result based on class names put classes.txt inside path";
    qDebug()<<"Usage: YoloDatasetTools /path/to/labels anylabel ";

}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if(argc<3){
        PrintHelpMenu();
        return 0;
    }

    qDebug()<<"input path:"<<argv[1];
    qDebug()<<"label to search:"<<argv[2]<<" number:"<<GetLabelNumber(argv[2],QString(argv[1])+"/classes.txt");
    int inputLabelNumber =GetLabelNumber(argv[2],QString(argv[1])+"/classes.txt");
    if(inputLabelNumber<0){qDebug()<<"wrong label name please check again!";return 0;}
    QVector<int> labels;

    QStringList labelFiles=GetDataSetLabelFiles(argv[1]);


    for(int i=0;i<labelFiles.count();i++)
    {
        if(LabelExistInFile(labelFiles[i],inputLabelNumber))
        {
            qDebug()<<labelFiles[i];
        }
    }

    return  0;
    return a.exec();
}
