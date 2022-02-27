#include "chooselevelscene.h"

#include <QIcon>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QPainter>
#include <QDebug>
#include <QLabel>

#include "imagepushbutton.h"
#include "playscene.h"

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    this->prepare();
}

void ChooseLevelScene::prepare()
{
    // 窗口设置
    this->setFixedSize(WIDTH,HEIGH);
    this->setWindowIcon(QIcon(":/res/image/Coin0001.png"));
    this->setWindowTitle("选择关卡");

    // 创建菜单栏
    QMenuBar *bar = this->menuBar();
    setMenuBar(bar);
    QMenu *optionMenu = bar->addMenu("选项");
    QAction *exitMenu =optionMenu->addAction("退出");

    connect(exitMenu,&QAction::triggered,this,[=](){
        this->close();
    });

    // 返回按钮
    ImagePushButton *backButton = new ImagePushButton(":/res/image/BackButton.png",":/res/image/BackButtonSelected.png");
    backButton->setParent(this);
    backButton->move(this->width()-backButton->width(),this->height()-backButton->height());

    connect(backButton,&ImagePushButton::clicked,this,[=](){
        emit this->chooseScenceBack();
    });

    // 创建选择关卡按钮
    for(int i=0; i<20; i++){
        ImagePushButton *menuBtn = new ImagePushButton(":/res/image/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(i%4*60+40, i/4*60+150);

        connect(menuBtn,&ImagePushButton::clicked,this,[=](){
            // 点击按钮，创建游戏关卡
            this->hide();
            this->play = new PlayScene(i+1);
            play->show();

            //游戏场景初始位置，为chooseLevelScene位置
            play->setGeometry(this->geometry());

            // 接受从游戏关卡发送的信号
            // (这部分代码，放在外层不行，接收不到信号。原因应该是放在外层，这个代码会顺序执行过，但执行的时候，play还没有被menuBtn点击创建出来。)
            connect(play,&PlayScene::playScenceBack,this,[=](){
                // 从游戏场景返回时，chooseLevelScene位置为游戏场景位置
                this->setGeometry(play->geometry());

                play->hide();
                this->show();
                delete play;
                play = nullptr;
            });
        });


        //menuBtn->setText(QString::number(i+1)); // 不规则图片，添加文本，非常难看
        // 在按钮上叠加一层label
        QLabel *label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(i%4*60+40, i/4*60+150);
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
//        connect(label,&QLabel::) // label没有鼠标点击相关的信号，不能用信号-串-信号的方式。
        label->setAttribute(Qt::WA_TransparentForMouseEvents); // 属性设置成鼠标穿透，这样label不挡着按钮了

    }
}

void ChooseLevelScene::paintEvent(QPaintEvent *event)
{
    // 背景加载
    QPainter painter(this);
    QPixmap pix;
    if( pix.load(":/res/image/OtherSceneBg.png") == false) {
        qDebug() << "图片加载失败";
        return;
    }
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/image/Title.png");
//    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix);
}
