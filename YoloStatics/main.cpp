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
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QVector<int> labels;
    QStringList labelFiles=GetDatatLabelFiles("/home/cast/Desktop/autolabel");
    for(int i=0;i<labelFiles.count();i++)
    {

     labels.append( GetClassCount(labelFiles[i]));
    }
    int min = *std::min_element(labels.begin(), labels.end());
    int max = *std::max_element(labels.begin(), labels.end());

    for(int i=min;i<=max;i++)
    {
        qDebug()<<"count lable "<<i<<" = "<<labels.count(i) << " " << labels.count(i)*100 /labels.length()<<"%";


    }
    return  0;
    return a.exec();
}
