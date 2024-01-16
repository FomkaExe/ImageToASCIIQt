#include "imageprocessor.h"

#include <QFile>
#include <QDebug>

ImageProcessor::ImageProcessor()
    : m_filename(QString())
    , m_ASCII(QString())
{
    m_image = new QImage();
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

void ImageProcessor::setImage(QImage image)
{
    *m_image = image;
}

QString ImageProcessor::getASCII()
{
    return m_ASCII;
}

void ImageProcessor::greyscaleAlgo()
{
    for (int i = 0; i < m_image->height(); ++i) {
        for (int j = 0; j < m_image->width(); ++j) {
            qDebug() << "test";
            if (qGray(m_image->pixel(j, i)) < 32) {
                m_ASCII += "@";
            } else if (qGray(m_image->pixel(j, i)) < 64){
                m_ASCII += "8";
            } else if (qGray(m_image->pixel(j, i)) < 96){
                m_ASCII += "0";
            } else if (qGray(m_image->pixel(j, i)) < 128){
                m_ASCII += "o";
            } else if (qGray(m_image->pixel(j, i)) < 192){
                m_ASCII += ":";
            } else if (qGray(m_image->pixel(j, i)) < 224){
                m_ASCII += ".";
            } else {
                m_ASCII += " ";
            }
        }
        m_ASCII += '\n';
    }
    m_ASCII += '\n';
}

void ImageProcessor::edgetracingAlgo()
{

}
