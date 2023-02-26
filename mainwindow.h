#ifndef MAINWINDOW_H
#define MAINWINDOW_H
 
#include <QMainWindow>
#include <QListWidget>
namespace Ui {
class MainWindow;
}
 
class MainWindow : public QMainWindow
{
    Q_OBJECT
 
public:
    void setSize(){m_ImageList->resize(this->size());}
    void keyPressEvent(QKeyEvent *event);

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    void displayChar(const QString& s);
    void displayCursor();

    bool isSpace=false;
    QVector<bool> seqIsNumber;
    QWidget* central = new QWidget; //后面将listWidget加入mainWindow中
    QListWidget *m_ImageList = new QListWidget(central);

    Ui::MainWindow *ui;
};
 
#endif // MAINWINDOW_H
