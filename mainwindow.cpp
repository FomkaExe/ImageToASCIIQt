#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imageprocessor.h"

#include <QFileDialog>
#include <QObject>
#include <QPixmap>
#include <QErrorMessage>
#include <QMessageBox>
#include <QStandardPaths>


MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    m_image = new ImageProcessor();
    m_scene = new QGraphicsScene();
    m_textbrowser = new QTextBrowser();

    this->setWindowTitle("Image to ASCII converter");

    ui->graphicsView->setScene(m_scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QObject::connect(ui->actionOpen, SIGNAL(triggered()),
                     this, SLOT(openClicked()));
    QObject::connect(ui->actionSave, SIGNAL(triggered()),
                     this, SLOT(saveClicked()));
    QObject::connect(ui->actionAbout_Qt, SIGNAL(triggered()),
                     this, SLOT(aboutQtClicked()));
    QObject::connect(ui->startButton, SIGNAL(clicked()),
                     this, SLOT(startClicked()));
    QObject::connect(ui->fullscreenButton, SIGNAL(clicked()),
                     this, SLOT(fullscreenClicked()));
}

MainWindow::~MainWindow() {
    delete m_image;
    delete m_scene;
    delete m_textbrowser;
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    ui->graphicsView->fitInView(m_scene->itemsBoundingRect(),
                                Qt::KeepAspectRatio);
}

void MainWindow::startClicked() {
    if (!m_image->getLowresASCII().isNull()) {
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

void MainWindow::fullscreenClicked() {
    QFont font("Consolas");
    m_textbrowser->setFont(font);
    if (m_image->getASCII().isNull()) {
        m_image->greyscaleAlgo(false);
    }
    m_textbrowser->zoomOut(9);
    m_textbrowser->setText(m_image->getASCII());
    m_textbrowser->showMaximized();
}

void MainWindow::openClicked() {
    const char filter[] =
            "Image Files (*.png *.jpg *.jpeg *.bmp *.webp);;All files(*.*)";

    QString downloadDir =
    QStandardPaths::standardLocations(QStandardPaths::DownloadLocation).last();

    QString name =
    QFileDialog::getOpenFileName(this,
                                 tr("Open Image"),
                                 downloadDir,
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
    ui->graphicsView->fitInView(m_scene->itemsBoundingRect(),
                                Qt::KeepAspectRatio);
}

void MainWindow::saveClicked() {
    if (m_image->getLowresASCII().isEmpty()) {
        QErrorMessage msg(this);
        msg.showMessage("Error! No ASCII generated");
        msg.exec();
        return;
    }

    QString saveDir =
    QStandardPaths::standardLocations(QStandardPaths::DownloadLocation).last();

    const char filter[] = "All files(*.*)";
    QString filename = QFileDialog::getSaveFileName(this,
                                                tr("Save file"),
                                                saveDir,
                                                tr(filter));

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        QErrorMessage msg(this);
        msg.showMessage("Error writing to file, try again");
        msg.exec();
        return;
    }
    file.write(m_image->getLowresASCII().toUtf8());
}

void MainWindow::aboutQtClicked() {
    QMessageBox::aboutQt(this);
}
