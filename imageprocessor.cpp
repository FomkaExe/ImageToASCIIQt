#include "imageprocessor.h"

#include <QFile>
#include <QDebug>

ImageProcessor::ImageProcessor()
    : m_filename(QString())
    , m_ASCII(QString())
    , m_lowres_ASCII(QString())
{
    m_image = new QImage();
}

ImageProcessor::~ImageProcessor()
{
    delete m_image;
}

const QString ImageProcessor::getFilename()
{
    return m_filename;
}

void ImageProcessor::setFilename(QString filename)
{
    m_filename = filename;
}

const QImage ImageProcessor::getImage()
{
    return *m_image;
}


void ImageProcessor::setImage(QImage image)
{
    *m_image = image;
}

const QString ImageProcessor::getASCII()
{
    return m_ASCII;
}

const QString ImageProcessor::getLowresASCII()
{
    return m_lowres_ASCII;
}

void ImageProcessor::clearASCII()
{
    m_ASCII = QString();
    m_lowres_ASCII = QString();
}

void ImageProcessor::greyscaleAlgo(bool lowres, int width, int height)
{
    QImage temp = *m_image;
    temp = temp.convertToFormat(QImage::Format_Grayscale8);
    if (lowres) {
        temp = temp.scaled(width/2, height/2);
        for (int i = 0; i < temp.height(); ++i) {
            for (int j = 0; j < temp.width(); ++j) {
                if (qGray(temp.pixel(j, i)) < 32) {
                    m_lowres_ASCII += "@@@";
                } else if (qGray(temp.pixel(j, i)) < 64) {
                    m_lowres_ASCII += "888";
                } else if (qGray(temp.pixel(j, i)) < 96) {
                    m_lowres_ASCII += "000";
                } else if (qGray(temp.pixel(j, i)) < 128) {
                    m_lowres_ASCII += "ooo";
                } else if (qGray(temp.pixel(j, i)) < 192) {
                    m_lowres_ASCII += ":::";
                } else if (qGray(temp.pixel(j, i)) < 224) {
                    m_lowres_ASCII += "...";
                } else {
                    m_lowres_ASCII += "   ";
                }
            }
            m_lowres_ASCII += '\n';
        }
        m_lowres_ASCII += '\n';
    } else {
        if (m_image->width() > 1000) {
            temp = temp.scaled(1000, temp.height());
        }
        if (m_image->height() > 1000) {
            temp = temp.scaled(temp.width(), 1000);
        }
//        temp = temp.scaled(temp.width(), temp.height());
        for (int i = 0; i < temp.height(); ++i) {
            for (int j = 0; j < temp.width(); ++j) {
                if (qGray(temp.pixel(j, i)) < 32) {
                    m_ASCII += "@@@";
                } else if (qGray(temp.pixel(j, i)) < 64) {
                    m_ASCII += "888";
                } else if (qGray(temp.pixel(j, i)) < 96) {
                    m_ASCII += "000";
                } else if (qGray(temp.pixel(j, i)) < 128) {
                    m_ASCII += "ooo";
                } else if (qGray(temp.pixel(j, i)) < 192) {
                    m_ASCII += ":::";
                } else if (qGray(temp.pixel(j, i)) < 224) {
                    m_ASCII += "...";
                } else {
                    m_ASCII += "   ";
                }
            }
            m_ASCII += '\n';
        }
        m_ASCII += '\n';
    }
//    if (width) {
//        QImage temp = m_image->scaled(width*0.5, height*0.5);
//        qDebug() << temp.width() << temp.height();
//        temp = temp.convertToFormat(QImage::Format_Grayscale8);
//        for (int i = 0; i < temp.height(); ++i) {
//            for (int j = 0; j < temp.width(); ++j) {
//                if (qGray(temp.pixel(j, i)) < 32) {
//                    m_lowres_ASCII += "@@@";
//                } else if (qGray(temp.pixel(j, i)) < 64) {
//                    m_lowres_ASCII += "888";
//                } else if (qGray(temp.pixel(j, i)) < 96) {
//                    m_lowres_ASCII += "000";
//                } else if (qGray(temp.pixel(j, i)) < 128) {
//                    m_lowres_ASCII += "ooo";
//                } else if (qGray(temp.pixel(j, i)) < 192) {
//                    m_lowres_ASCII += ":::";
//                } else if (qGray(temp.pixel(j, i)) < 224) {
//                    m_lowres_ASCII += "...";
//                } else {
//                    m_lowres_ASCII += "   ";
//                }
//            }
//            m_lowres_ASCII += '\n';
//        }
//        m_lowres_ASCII += '\n';
//    } else {
//        QImage temp = *m_image;
//        temp = temp.convertToFormat(QImage::Format_Grayscale8);
//        for (int i = 0; i < temp.height(); ++i) {
//            for (int j = 0; j < temp.width(); ++j) {
//                if (qGray(temp.pixel(j, i)) < 32) {
//                    m_ASCII += "@@@";
//                } else if (qGray(temp.pixel(j, i)) < 64) {
//                    m_ASCII += "888";
//                } else if (qGray(temp.pixel(j, i)) < 96) {
//                    m_ASCII += "000";
//                } else if (qGray(temp.pixel(j, i)) < 128) {
//                    m_ASCII += "ooo";
//                } else if (qGray(temp.pixel(j, i)) < 192) {
//                    m_ASCII += ":::";
//                } else if (qGray(temp.pixel(j, i)) < 224) {
//                    m_ASCII += "...";
//                } else {
//                    m_ASCII += "   ";
//                }
//            }
//            m_ASCII += '\n';
//        }
//        m_ASCII += '\n';
//    }
}

void ImageProcessor::edgetracingAlgo()
{

}
