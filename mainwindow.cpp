#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QListWidget>
#include<QKeyEvent>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("FuthkEditor"); //���������ʾ���
    this->setWindowIcon(QIcon("../QtNeoCha/pic/icon.png")); //���ô���ͼ��

    setCentralWidget(central);

    m_ImageList->setViewMode(QListWidget::IconMode);//��ʾģʽ
    m_ImageList->setIconSize(QSize(100, 100));//����ͼƬ��С
    m_ImageList->setResizeMode(QListView::Adjust);//��Ӧ���ֵ���
    m_ImageList->setMovement(QListView::Static);//������
    m_ImageList->setSelectionMode(QListView::NoSelection);

    //cursor
    QListWidgetItem* imageItem = new QListWidgetItem;
    imageItem->setIcon(QIcon("../QtNeoCha/pic/cursor.jpg"));
    m_ImageList->addItem(imageItem);

    setFocusPolicy(Qt::StrongFocus);//����tab����focus on
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
//    //ctrlϵ��
//    if(Qt::Key_Space == event->key()){
//        isSpace=!isSpace;
//        return;
//    }
    //�ո���ζ�Ŵ�Сд�л�
    if(Qt::Key_Space == event->key()){
        isSpace=!isSpace;
        return;
    }
    //ɾ��
    if(Qt::Key_Backspace == event->key()){
        int numOfItem=m_ImageList->count();
        if(numOfItem<=1)return;
        QListWidgetItem *item = m_ImageList->takeItem(numOfItem-2);//ѡ�����һ���ĵ�ַ
        delete item;
        if(true==seqIsNumber.back()){//�����־�ɾ����
            item = m_ImageList->takeItem(numOfItem-3);
            delete item;
        }
        seqIsNumber.pop_back();
        return;
    } else if(Qt::Key_Delete == event->key()){//����ı�
        int numOfItem=m_ImageList->count();
        for(int i=0; i<numOfItem; i++){
            QListWidgetItem *item = m_ImageList->takeItem(0);//ѡ�е�һ���ĵ�ַ
            delete item;
        }
        seqIsNumber.clear();
        displayCursor();//��Ҫ�ػ����
        return;
    }

    //��ͨ����
    char ch;
    QString str;
    if ('1' <= event->key() && '9' >= event->key()) {
        displayChar("sn");
        ch='a'-'0'-1+event->key();
        str+=ch;
        isSpace=false;//�Է����ִ����д��ĸ
    } else if ('0' == event->key()) {
        displayChar("sn");
        ch='z';
        str+=ch;
        isSpace=false;//�Է����ִ����д��ĸ
    } else if (event->key() >= 'A' && event->key() <= 'Z') {
        ch=event->key();
        str+=ch;
    } else if ('[' == event->key() || '(' == event->key() || '{' == event->key()) {
        str+="sl";
    } else if (']' == event->key() || ')' == event->key() || '}' == event->key()) {
        str+="sr";
    } else if ('.' == event->key()) {
        str+="s1";
    } else if ('!' == event->key()) {
        str+="s2";
    } else if ('^' == event->key()) {
        str+="s3";
    } else if (',' == event->key()) {
        str+="s0";
    } else if ('?' == event->key()) {//��� �� �� ��
        displayChar("sq");
        str+="s1";
    } else if ('\'' == event->key()) {
        str+="su";
    } else if (';' == event->key()) {
        str+="sd";
    } else {
        return; //��ֹ���벻��ʾ���ַ������µ�ɾ��ʱɾ������ʾ�ַ���һbug
    }

    if (('0' <= event->key() && '9' >= event->key()) ||'?' == event->key())
        seqIsNumber.push_back(true);
    else
        seqIsNumber.push_back(false);
    displayChar(str);
}

void MainWindow::displayChar(const QString& s){
    //cursor off
    int numOfItem=m_ImageList->count();
    QListWidgetItem *item = m_ImageList->takeItem(numOfItem-1);//ѡ�й��
    delete item;

    QListWidgetItem *imageItem = new QListWidgetItem;
    QString picName;
    if(isSpace) {
        picName="../QtNeoCha/pic/upper/"+s+".jpg";//�ո���ζ�Ŵ�Сд�л�,upper
        isSpace=false;
    } else
        picName="../QtNeoCha/pic/lower/"+s+".jpg";//lower
    imageItem->setIcon(QIcon(picName));
    m_ImageList->addItem(imageItem);

    displayCursor();
}
void MainWindow::displayCursor(){
    //cursor on
    QListWidgetItem *imageItem = new QListWidgetItem;
    imageItem->setIcon(QIcon("../QtNeoCha/pic/cursor.jpg"));
    m_ImageList->addItem(imageItem);
}
 
MainWindow::~MainWindow()
{
    delete ui;
}
