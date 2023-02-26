#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QListWidget>
#include<QKeyEvent>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("FuthkEditor"); //软件标题显示这个
    this->setWindowIcon(QIcon("../QtNeoCha/pic/icon.png")); //设置窗口图标

    setCentralWidget(central);

    m_ImageList->setViewMode(QListWidget::IconMode);//显示模式
    m_ImageList->setIconSize(QSize(100, 100));//设置图片大小
    m_ImageList->setResizeMode(QListView::Adjust);//适应布局调整
    m_ImageList->setMovement(QListView::Static);//不能移
    m_ImageList->setSelectionMode(QListView::NoSelection);

    //cursor
    QListWidgetItem* imageItem = new QListWidgetItem;
    imageItem->setIcon(QIcon("../QtNeoCha/pic/cursor.jpg"));
    m_ImageList->addItem(imageItem);

    setFocusPolicy(Qt::StrongFocus);//按下tab才能focus on
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
//    //ctrl系列
//    if(Qt::Key_Space == event->key()){
//        isSpace=!isSpace;
//        return;
//    }
    //空格意味着大小写切换
    if(Qt::Key_Space == event->key()){
        isSpace=!isSpace;
        return;
    }
    //删除
    if(Qt::Key_Backspace == event->key()){
        int numOfItem=m_ImageList->count();
        if(numOfItem<=1)return;
        QListWidgetItem *item = m_ImageList->takeItem(numOfItem-2);//选中最后一个的地址
        delete item;
        if(true==seqIsNumber.back()){//是数字就删两个
            item = m_ImageList->takeItem(numOfItem-3);
            delete item;
        }
        seqIsNumber.pop_back();
        return;
    } else if(Qt::Key_Delete == event->key()){//清空文本
        int numOfItem=m_ImageList->count();
        for(int i=0; i<numOfItem; i++){
            QListWidgetItem *item = m_ImageList->takeItem(0);//选中第一个的地址
            delete item;
        }
        seqIsNumber.clear();
        displayCursor();//需要重画光标
        return;
    }

    //普通输入
    char ch;
    QString str;
    if ('1' <= event->key() && '9' >= event->key()) {
        displayChar("sn");
        ch='a'-'0'-1+event->key();
        str+=ch;
        isSpace=false;//以防数字打出大写字母
    } else if ('0' == event->key()) {
        displayChar("sn");
        ch='z';
        str+=ch;
        isSpace=false;//以防数字打出大写字母
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
    } else if ('?' == event->key()) {//打出 ？ 和 。
        displayChar("sq");
        str+="s1";
    } else if ('\'' == event->key()) {
        str+="su";
    } else if (';' == event->key()) {
        str+="sd";
    } else {
        return; //防止加入不显示的字符所导致的删除时删除不显示字符这一bug
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
    QListWidgetItem *item = m_ImageList->takeItem(numOfItem-1);//选中光标
    delete item;

    QListWidgetItem *imageItem = new QListWidgetItem;
    QString picName;
    if(isSpace) {
        picName="../QtNeoCha/pic/upper/"+s+".jpg";//空格意味着大小写切换,upper
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
