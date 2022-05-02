#ifndef YOLOLABEL_H
#define YOLOLABEL_H

#include <QObject>
#include <QDebug>
#include <QRect>
#include <QFile>

class YoloLabel : public QObject
{
    Q_OBJECT


public:
    explicit YoloLabel(QObject *parent = nullptr);

    QString GenerateLable(int classID, float xCenter, float yCenter, float width, float height, float imageWidth, float imageHeight);
    QRect GetImageLocation(QString YoloLableLine, int imageWidth, int imageHeight);
    void RemoveLabelsFromYoloLabel(QString inputLabelFile,QString outputfile ,QList<int>labels);
    QString TranslateLine(QString YoloLableLine, int oldWidth, int oldHeight, int oldX, int oldY, int newWidth, int newHeight);
    void RemoveLabelsFromYoloLabelAndTranslate(QString inputLabelFile, QString outputfile, QList<int> labels, int oldWidth, int oldHeight, int oldX, int oldY, int newWidth, int newHeight);
    QString GetLablesInsidePlate(QString plate, uint imageWidth, uint imageHeight, QString labelFileContent);
    bool RectIsChild(QRect parent, QRect child);
    void CreateTranslatedOCR(QString plate, QString inputLabelFile, QString outputfile, int oldWidth, int oldHeight, int oldX, int oldY, int newWidth, int newHeight);
signals:

};

#endif // YOLOLABEL_H
