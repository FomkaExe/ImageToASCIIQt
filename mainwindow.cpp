#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imageprocessor.h"

#include <QFileDialog>
#include <QObject>
#include <QAction>
#include <QDebug>
#include <QPixmap>
#include <QErrorMessage>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_image = new ImageProcessor();
    m_scene = new QGraphicsScene();
    errmsg = new QErrorMessage(this);

    ui->graphicsView->setScene(m_scene);

    QObject::connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openClicked()));
    QObject::connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveClicked()));
    QObject::connect(ui->startButton, SIGNAL(clicked()), this, SLOT(startClicked()));
    QObject::connect(ui->fullscreenButton, SIGNAL(clicked()), this, SLOT(fullscreenClicked()));
    QObject::connect(ui->edgetracingCheckbox, SIGNAL(stateChanged(int)), this, SLOT(uncheckOther()));
    QObject::connect(ui->greyscaleCheckbox, SIGNAL(stateChanged(int)), this, SLOT(uncheckOther()));
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
    if (ui->edgetracingCheckbox->isChecked()) {
        errmsg->showMessage("Not working right now, sorry! Check again later");
//        m_image->edgetracingAlgo();
//        ui->textBrowser->setPlainText(m_image->getASCII());
    } else if (ui->greyscaleCheckbox->isChecked()) {
        qDebug() << ui->textBrowser->width() << ui->textBrowser->height();
        qDebug() << m_image->getImage().width() << m_image->getImage().height();
        QFont font("Consolas");
        QFontMetrics metrics(font);
        m_image->scaleImage(ui->textBrowser->width(),
                            ui->textBrowser->height(),
                            metrics.horizontalAdvance("@"),
                            metrics.height());
        qDebug() << m_image->getImage().width() << m_image->getImage().height();
        m_image->greyscaleAlgo();
//        qDebug() << mf.horizontalAdvance("@") << mf.height();
        ui->textBrowser->setFont(font);
        ui->textBrowser->zoomOut(9);
        ui->textBrowser->setText(m_image->getASCII());
    } else {
        errmsg->showMessage("Choose the drawing algorithm");
    }
}

void MainWindow::fullscreenClicked()
{

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
    m_image->setFilename(name);
    m_image->setImage(QImage(name));
    m_scene->clear();
    ui->textBrowser->clear();
    m_scene->addPixmap(QPixmap::fromImage(m_image->getUnredactedImage()));
    ui->graphicsView->fitInView(m_scene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void MainWindow::saveClicked()
{
    if (m_image->getASCII().isEmpty()) {
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
    file.write(m_image->getASCII().toUtf8()); // will it work?????????????????
}

void MainWindow::uncheckOther()
{
    if (sender() == ui->edgetracingCheckbox && ui->edgetracingCheckbox->isChecked()) {
        ui->greyscaleCheckbox->setChecked(false);
    }
    if (sender() == ui->greyscaleCheckbox && ui->greyscaleCheckbox->isChecked()) {
        ui->edgetracingCheckbox->setChecked(false);
    }
}
