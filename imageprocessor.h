#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QImage>

class ImageProcessor : public QImage {
public:
    ImageProcessor();
    ~ImageProcessor();

    const QString getFilename();
    void setFilename(const QString& filename);
    const QImage getImage();
    void setImage(const QImage& image);
    const QString getASCII();
    const QString getLowresASCII();
    void clearASCII();

public slots:
    void greyscaleAlgo(bool lowres, int width = 0, int height = 0);

private:
    QImage *m_image;
    QString m_filename;
    QString m_ASCII;
    QString m_lowres_ASCII;
};

#endif // IMAGEPROCESSOR_H
