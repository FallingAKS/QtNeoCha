#include "mainwindow.h"
#include <QApplication>
 
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setAutoFillBackground(true);
    w.setPalette(QPalette(QColor(Qt::black)));
    w.setSize();//�����ʼʱ��Чһ�Σ���������mainwindowһ�´�С  ���޸�
    w.show();
 
    return a.exec();
}
