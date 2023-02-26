#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QListWidget>
#include<QKeyEvent>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("FuthkEditor"); //软件标题显示这个
    this->setWindowIcon(QIcon(":/new/pic/icon.png")); //设置窗口图标

    setCentralWidget(central);

    m_ImageList->setViewMode(QListWidget::IconMode);//显示模式
    m_ImageList->setIconSize(QSize(100, 100));//设置图片大小
    m_ImageList->setResizeMode(QListView::Adjust);//适应布局调整
    m_ImageList->setMovement(QListView::Static);//不能移
    m_ImageList->setSelectionMode(QListView::NoSelection);//不能选

    //cursor
    QListWidgetItem* imageItem = new QListWidgetItem;
    imageItem->setIcon(QIcon(":/new/pic/cursor.jpg"));
    m_ImageList->addItem(imageItem);

    setFocusPolicy(Qt::StrongFocus);//按下tab才能focus on
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::keyPressEvent(QKeyEvent *event) {
    //ctrl系列
    if(event ->matches(QKeySequence::Save)){//ctrl s
        QScreen *screen_test = QGuiApplication::primaryScreen();
        QPixmap pixmap_test = screen_test->grabWindow(this->m_ImageList->winId(),0,0,30,-1);// x,y
        //注意gitignore
        pixmap_test.save(QCoreApplication::applicationDirPath() + "/../../QtNeoCha/1.jpg");

        return;
    }/////////////////////////////////////////////////////////////////////////////////////////////////
    //空格意味着大小写切换
    if(Qt::Key_Space == event->key()){
        isSpace=!isSpace;
        return;
    }
    //删除
    if(Qt::Key_Backspace == event->key()){
        int numOfItem=m_ImageList->count();
        if(numOfItem<=1)return;
        for(int i=0; i<charLength.back(); i++){
            QListWidgetItem *item = m_ImageList->takeItem(numOfItem-2-i);//选中最后一个的地址
            delete item;
        }
        charLength.pop_back();
        return;
    } else if(Qt::Key_Delete == event->key()){//清空文本
        int numOfItem=m_ImageList->count();
        for(int i=0; i<numOfItem; i++){
            QListWidgetItem *item = m_ImageList->takeItem(0);//选中第一个的地址
            delete item;
        }
        charLength.clear();
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
//        isSpace=false;//以防数字打出大写字母  //不用，因为先打的是sn.jpg，然后归小写，然后打字母
    } else if ('0' == event->key()) {
        displayChar("sn");
        ch='z';
        str+=ch;
//        isSpace=false;//以防数字打出大写字母
    } else if (event->key() >= 'A' && event->key() <= 'Z') {
        ch=event->key()-'A'+'a';
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
        charLength.push_back(2);
    else // 一个长度的
        charLength.push_back(1);
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
        picName=":/new/pic/upper/"+s+".jpg";//空格意味着大小写切换,upper
        //":/new/pic/upper/a.jpg"
        isSpace=false;
    } else
        picName=":/new/pic/lower/"+s+".jpg";//lower
    imageItem->setIcon(QIcon(picName));
    m_ImageList->addItem(imageItem);

    displayCursor();
}
void MainWindow::displayCursor(){
    //cursor on
    QListWidgetItem *imageItem = new QListWidgetItem;
    imageItem->setIcon(QIcon(":/new/pic/cursor.jpg"));
    m_ImageList->addItem(imageItem);
}
void MainWindow::resizeEvent(QResizeEvent *event){
    //		//不能显示滚动条
    //		m_ImageList->resize(frameGeometry().size());

    //可以显示出滚动条,但是效果不是很好 //最底下一点看不到
    QSize sz=geometry().size();
    sz.setHeight(sz.height()-50);
    m_ImageList->resize(sz);

    //        //可以显示出滚动条，显示效果也很好
    //        m_ImageList->resize(ui->centralwidget->size()); //压根不行，这个
}
 
MainWindow::~MainWindow()
{
    delete ui;
}
