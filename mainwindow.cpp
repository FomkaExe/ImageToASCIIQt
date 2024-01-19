#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imageprocessor.h"

#include <QFileDialog>
#include <QObject>
#include <QAction>
#include <QDebug>
#include <QPixmap>
#include <QErrorMessage>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Image to ASCII converter");
    m_image = new ImageProcessor();
    m_scene = new QGraphicsScene();
    errmsg = new QErrorMessage(this);

    ui->graphicsView->setScene(m_scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QObject::connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openClicked()));
    QObject::connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveClicked()));
    QObject::connect(ui->actionAbout_Qt, SIGNAL(triggered()), this, SLOT(aboutQtClicked()));
    QObject::connect(ui->startButton, SIGNAL(clicked()), this, SLOT(startClicked()));
    QObject::connect(ui->fullscreenButton, SIGNAL(clicked()), this, SLOT(fullscreenClicked()));
}

MainWindow::~MainWindow()
{
    delete m_image;
    delete m_scene;
    delete errmsg;
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    ui->graphicsView->fitInView(m_scene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void MainWindow::startClicked()
{
    if (!m_image->getASCII().isNull()) {
        m_image->clearASCII();
    }
    QFont font("Consolas");
    m_image->greyscaleAlgo(true,
                           ui->textBrowser->width(),
                           ui->textBrowser->height());
    ui->textBrowser->setFont(font);
    ui->textBrowser->zoomOut(9);
    ui->textBrowser->setText(m_image->getLowresASCII());
}

void MainWindow::fullscreenClicked()
{
    QTextBrowser *text = new QTextBrowser();
    QFont font("Consolas");
    text->setFont(font);
    if (m_image->getASCII().isNull()) {
        m_image->greyscaleAlgo(false);
    }
    text->zoomOut(9);
    text->setText(m_image->getASCII());
    text->showMaximized();
}

void MainWindow::openClicked()
{
    const char filter[] = "Image Files (*.png *.jpg *.jpeg *.bmp);;All files(*.*)";
    QString name = QFileDialog::getOpenFileName(this,
                                                tr("Open Image"),
                                                "/home/fomka/Downloads",
                                                tr(filter));
    if (name.isNull()) {
        return;
    }
    m_image->clearASCII();
    m_image->setFilename(name);
    m_image->setImage(QImage(name));
    m_scene->clear();
    ui->textBrowser->clear();
    m_scene->addPixmap(QPixmap::fromImage(m_image->getImage()));
    ui->graphicsView->fitInView(m_scene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void MainWindow::saveClicked()
{
    if (m_image->getLowresASCII().isEmpty()) {
        errmsg->showMessage("Error! No ASCII generated");
        return;
    }
    const char filter[] = "All files(*.*)";
    QString filename = QFileDialog::getSaveFileName(this,
                                                tr("Save file"),
                                                "/home",
                                                tr(filter));

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        errmsg->showMessage("Error writing to file, try again");
        return;
    }
    file.write(m_image->getLowresASCII().toUtf8());
}

void MainWindow::aboutQtClicked()
{
    QMessageBox::aboutQt(this);
}
