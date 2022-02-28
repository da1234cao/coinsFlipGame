#include "mainscene.h"
#include "ui_mainscene.h"

#include <QPainter>
#include <QPushButton>
#include <QTimer>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    prepare(); // 初始化设置

}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::prepare()
{
    // 设置窗口
    this->setFixedSize(WIDTH,HEIGH);
    this->setWindowIcon(QIcon(":/res/image/Coin0001.png")); // ubuntu中，显示图标的位置是，打开应用栏中的
    this->setWindowTitle("翻金币游戏");

    // 退出按钮-功能
    connect(ui->actionQuit,&QAction::triggered,this,&MainScene::close);

    // 实例化关卡选择界面
    chooseScene = new ChooseLevelScene;

    // 开始按钮:按钮动画抖动;延时进入选择观察界面;
    ImagePushButton *startBtn = new ImagePushButton(":/res/image/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(QPoint(this->width()*0.5 - startBtn->width()*0.5, this->height()*0.7));
    connect(startBtn,&ImagePushButton::clicked,this,[=](){
        startBtn->zoomDown();
        startBtn->zoomUp();

        QTimer::singleShot(400,this,[=](){
            chooseScene->setGeometry(this->geometry());// 设置chooseScene场景位置
            this->hide();
            chooseScene->show();
        });
    });

    //接受关卡选择界面信号；
    connect(chooseScene,&ChooseLevelScene::chooseScenceBack,this,[=](){
        this->setGeometry(chooseScene->geometry()); // 返回mainscene位置，和chooseScene位置相同
        chooseScene->hide();
        this->show();
    });


}


void MainScene::paintEvent(QPaintEvent *event)
{
    // 通过paintEvent，绘制背景图片
    // 由于窗口大小固定，可以放心绘制
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/image/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/image/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5); // 图片有点大，缩小点
    painter.drawPixmap(10,30,pix);
}
