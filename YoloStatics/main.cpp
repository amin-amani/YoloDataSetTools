#include <QtCore>
#include <QFile>
//================================================================================
QStringList GetDatatLabelFiles(QString path)
{
    QStringList result;
    QStringList filters={".txt"};
    QDirIterator directoryIterator(path, QDirIterator::Subdirectories);
    while (directoryIterator.hasNext())
    {
        QString fname= directoryIterator.next();
        if(fname.contains("/."))
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

        QString line=file.readLine();
        if(!file.canReadLine())break;
        result.append(line.split(" ")[0].toUInt());


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
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if(argc<2){
        PrintHelpMenu();

        return 0;
    }
    qDebug()<<"input path:"<<argv[1];
    QVector<int> labels;
    QStringList labelFiles=GetDatatLabelFiles(argv[1]);
    for(int i=0;i<labelFiles.count();i++)
    {

     labels.append( GetClassCount(labelFiles[i]));
    }
    QStringList classNames= GetClassNames(QString(argv[1])+"/classes.txt");
    int min = *std::min_element(labels.begin(), labels.end());
    int max = *std::max_element(labels.begin(), labels.end());

    for(int i=min;i<=max;i++)
    {
        qDebug()<<""<<i<<" "<<classNames[i]<<" = "<<labels.count(i) << " " << labels.count(i)*100 /labels.length()<<"%";


    }
    return  0;
    return a.exec();
}
