#include "mainwindow.h"
#include <QApplication>
 
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setAutoFillBackground(true);
    w.setPalette(QPalette(QColor(Qt::black)));
    w.setSize();//程序最开始时生效一次，调整至和mainwindow一致大小  徐修改
    w.show();
 
    return a.exec();
}
