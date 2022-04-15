#include <QtCore>
#include <QFile>
#include <QDir>
//================================================================================
QStringList GetDataSetLabelFiles(QString path)
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
    qDebug()<<"help : you can create new label files with removing some class names from current label files";
    qDebug()<<"to print result based on class names put classes.txt inside path";
    qDebug()<<"Usage: YoloClassSplitter /path/to/labels classname1 classname2";

}
//================================================================================
QStringList GetIndexFromClassName(int argc, char *argv[],QStringList classNames)
{

    QStringList result;
    for(int i=2;i<argc;i++)
    {
//        qDebug()<<"class: "<<argv[i]<<" "<< classNames.indexOf(QString(argv[i]));
    result.append(QString::number( classNames.indexOf(QString(argv[i]))));
    }
    return result;

}

void SplitLabelFile(QString fileName,QString destinationPath,QStringList indexList)
{
    QFile file(fileName);
    QFile outfile (destinationPath);
    if(!file.open(QFile::ReadOnly))return ;
    while(true)
    {

        QString classnum=file.readLine().split(' ')[0];
        if(indexList.indexOf(classnum)<0)
        {

        }
      qDebug()<<"cs:"<<classnum<<indexList.indexOf(classnum);

        if(!file.canReadLine())break;



    }
    file.close();
}
//================================================================================

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if(argc<2){
        PrintHelpMenu();

        return 0;
    }
    qDebug()<<"input path:"<<argv[1];
    QStringList classNames= GetClassNames(QString(argv[1])+"/classes.txt");
    QStringList indexList= GetIndexFromClassName(argc,argv,classNames);
    QDir dir;
    dir.mkdir( QString(argv[1])+"/out");
    QStringList labelFiles=GetDataSetLabelFiles(argv[1]);
    SplitLabelFile(labelFiles[0],QString(argv[1])+"/out",indexList);

    return  0;
    return a.exec();
}
