#include "imageprocessor.h"

#include <QFile>
#include <QDebug>

ImageProcessor::ImageProcessor()
    : m_filename(QString())
    , m_ASCII(QString())
{
    m_image = new QImage();
    m_unredacted_image = new QImage();
}

ImageProcessor::~ImageProcessor()
{
    delete m_image;
    delete m_unredacted_image;
}

QString ImageProcessor::getFilename()
{
    return m_filename;
}

void ImageProcessor::setFilename(QString filename)
{
    m_filename = filename;
}

QImage ImageProcessor::getImage()
{
    return *m_image;
}

QImage ImageProcessor::getUnredactedImage()
{
    return *m_unredacted_image;
}

void ImageProcessor::setImage(QImage image)
{
    *m_unredacted_image = image;
    *m_image = image.convertToFormat(QImage::Format_Grayscale16);
}

void ImageProcessor::scaleImage(int width, int height, int fontWidth, int fontHeight)
{
    if (m_image->width() > width) {
        *m_image = m_image->scaled(width, m_image->height());
    }
    if (m_image->height() > height) {
        *m_image = m_image->scaled(m_image->width(), height);
    }
    *m_image = m_image->scaled(width/fontWidth, height/fontHeight);
}

QString ImageProcessor::getASCII()
{
    return m_ASCII;
}

void ImageProcessor::clearASCII()
{
    m_ASCII = QString();
}

void ImageProcessor::greyscaleAlgo()
{
    for (int i = 0; i < m_image->height(); ++i) {
        for (int j = 0; j < m_image->width(); j++) {
            if (qGray(m_image->pixel(j, i)) < 32) {
                m_ASCII += "@@@";
            } else if (qGray(m_image->pixel(j, i)) < 64) {
                m_ASCII += "888";
            } else if (qGray(m_image->pixel(j, i)) < 96) {
                m_ASCII += "000";
            } else if (qGray(m_image->pixel(j, i)) < 128) {
                m_ASCII += "ooo";
            } else if (qGray(m_image->pixel(j, i)) < 192) {
                m_ASCII += ":::";
            } else if (qGray(m_image->pixel(j, i)) < 224) {
                m_ASCII += "...";
            } else {
                m_ASCII += "   ";
            }
        }
        m_ASCII += '\n';
    }
    m_ASCII += '\n';
}

void ImageProcessor::edgetracingAlgo()
{

}
