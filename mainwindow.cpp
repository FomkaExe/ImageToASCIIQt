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
    QObject::connect(ui->edgetracingCheckbox, SIGNAL(stateChanged(int)), this, SLOT(uncheckOther()));
    QObject::connect(ui->greyscaleCheckbox, SIGNAL(stateChanged(int)), this, SLOT(uncheckOther()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    ui->graphicsView->fitInView(m_scene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void MainWindow::startClicked()
{
    if (ui->edgetracingCheckbox->isChecked()) {
        errmsg->showMessage("Not working right now, sorry! Check again later");
//        m_image->edgetracingAlgo();
//        ui->textBrowser->setPlainText(m_image->getASCII());
    } else if (ui->greyscaleCheckbox->isChecked()) {
        m_image->greyscaleAlgo();
        qDebug() << m_image->getASCII();
        ui->textBrowser->setPlainText(m_image->getASCII());
        ui->textBrowser->show();
    } else {
        errmsg->showMessage("Choose the drawing algorithm");
    }
}

void MainWindow::openClicked()
{
    const char filter[] = "Image Files (*.png *.jpg *.jpeg *.bmp);;All files(*.*)";
    QString name = QFileDialog::getOpenFileName(this,
                                                tr("Open Image"),
                                                "/home",
                                                tr(filter));
    if (name.isNull()) {
        return;
    }
    m_image->setFilename(name);
    m_image->setImage(QImage(name));
    m_scene->clear();
    m_scene->addPixmap(QPixmap::fromImage(m_image->getImage()));
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
