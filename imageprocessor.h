#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QImage>
#include <QObject>

class ImageProcessor : public QImage
{
public:
    ImageProcessor();
    QString getFilename();
    void setFilename(QString filename);
    QImage getImage();
    QImage getUnredactedImage();
    void setImage(QImage image);
    QString getASCII();
    void clearASCII();

public slots:
    void greyscaleAlgo();
    void edgetracingAlgo();

private:
    QImage *m_image;
    QImage *m_unredacted_image;
    QString m_filename;
    QString m_ASCII;
};

#endif // IMAGEPROCESSOR_H
