#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>

class QPushButton;
class ImageProcessor;
class QGraphicsScene;
class QErrorMessage;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
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
    void uncheckOther();
    void aboutQtClicked();

private:
    Ui::MainWindow *ui;
    ImageProcessor *m_image;
    QGraphicsScene *m_scene;
    QErrorMessage *errmsg;
};
#endif // MAINWINDOW_H
