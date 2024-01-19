#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>

class ImageProcessor;
class QGraphicsScene;
class QTextBrowser;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void resizeEvent(QResizeEvent* event);

public slots:
    void startClicked();
    void fullscreenClicked();
    void openClicked();
    void saveClicked();
    void aboutQtClicked();

private:
    Ui::MainWindow *ui;
    ImageProcessor *m_image;
    QGraphicsScene *m_scene;
    QTextBrowser *m_textbrowser;
};
#endif // MAINWINDOW_H
