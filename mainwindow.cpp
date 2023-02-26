#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QListWidget>
#include<QKeyEvent>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("FuthkEditor"); //���������ʾ���
    this->setWindowIcon(QIcon(":/new/pic/icon.png")); //���ô���ͼ��

    setCentralWidget(central);

    m_ImageList->setViewMode(QListWidget::IconMode);//��ʾģʽ
    m_ImageList->setIconSize(QSize(100, 100));//����ͼƬ��С
    m_ImageList->setResizeMode(QListView::Adjust);//��Ӧ���ֵ���
    m_ImageList->setMovement(QListView::Static);//������
    m_ImageList->setSelectionMode(QListView::NoSelection);//����ѡ

    //cursor
    QListWidgetItem* imageItem = new QListWidgetItem;
    imageItem->setIcon(QIcon(":/new/pic/cursor.jpg"));
    m_ImageList->addItem(imageItem);

    setFocusPolicy(Qt::StrongFocus);//����tab����focus on
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::keyPressEvent(QKeyEvent *event) {
    //ctrlϵ��
    if(event ->matches(QKeySequence::Save)){//ctrl s
        QScreen *screen_test = QGuiApplication::primaryScreen();
        QPixmap pixmap_test = screen_test->grabWindow(this->m_ImageList->winId(),0,0,30,-1);// x,y
        //ע��gitignore
        pixmap_test.save(QCoreApplication::applicationDirPath() + "/../../QtNeoCha/1.jpg");

        return;
    }/////////////////////////////////////////////////////////////////////////////////////////////////
    //�ո���ζ�Ŵ�Сд�л�
    if(Qt::Key_Space == event->key()){
        isSpace=!isSpace;
        return;
    }
    //ɾ��
    if(Qt::Key_Backspace == event->key()){
        int numOfItem=m_ImageList->count();
        if(numOfItem<=1)return;
        for(int i=0; i<charLength.back(); i++){
            QListWidgetItem *item = m_ImageList->takeItem(numOfItem-2-i);//ѡ�����һ���ĵ�ַ
            delete item;
        }
        charLength.pop_back();
        return;
    } else if(Qt::Key_Delete == event->key()){//����ı�
        int numOfItem=m_ImageList->count();
        for(int i=0; i<numOfItem; i++){
            QListWidgetItem *item = m_ImageList->takeItem(0);//ѡ�е�һ���ĵ�ַ
            delete item;
        }
        charLength.clear();
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
//        isSpace=false;//�Է����ִ����д��ĸ  //���ã���Ϊ�ȴ����sn.jpg��Ȼ���Сд��Ȼ�����ĸ
    } else if ('0' == event->key()) {
        displayChar("sn");
        ch='z';
        str+=ch;
//        isSpace=false;//�Է����ִ����д��ĸ
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
        charLength.push_back(2);
    else // һ�����ȵ�
        charLength.push_back(1);
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
        picName=":/new/pic/upper/"+s+".jpg";//�ո���ζ�Ŵ�Сд�л�,upper
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
    //		//������ʾ������
    //		m_ImageList->resize(frameGeometry().size());

    //������ʾ��������,����Ч�����Ǻܺ� //�����һ�㿴����
    QSize sz=geometry().size();
    sz.setHeight(sz.height()-50);
    m_ImageList->resize(sz);

    //        //������ʾ������������ʾЧ��Ҳ�ܺ�
    //        m_ImageList->resize(ui->centralwidget->size()); //ѹ�����У����
}
 
MainWindow::~MainWindow()
{
    delete ui;
}
