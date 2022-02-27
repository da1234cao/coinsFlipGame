#include "playscene.h"
#include "globalvar.h"
#include "imagepushbutton.h"
#include "coinbutton.h"
#include "dataconfig.h"

#include <QDebug>
#include <QPainter>
#include <QLabel>
#include <QPropertyAnimation>

//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}

PlayScene::PlayScene(int index)
{
    this->levelIndex = index;
    this->prepare();
    this->readMap();
    this->coinsDisplay();
}

void PlayScene::prepare()
{
    // 设置窗口
    this->setFixedSize(WIDTH,HEIGH);
    this->setWindowIcon(QIcon(":/res/image/Coin0001.png"));
    const QString title = QString("翻金币-关卡%1").arg(this->levelIndex);
    this->setWindowTitle(title);

    // 返回按钮：返回到关卡选择页面
    ImagePushButton *backButton = new ImagePushButton(":/res/image/BackButton.png",":/res/image/BackButtonSelected.png");
    backButton->setParent(this);
    backButton->move(this->width()-backButton->width(),this->height()-backButton->height());

    connect(backButton,&ImagePushButton::clicked,this,[=](){
        emit this->playScenceBack();
    });

    // 胜利的label，先隐藏在上面（所有的ui创建，都在构造函数中完成）
    this->winLabel = new QLabel;
    winLabel->setParent(this);
    QPixmap pix;
    pix.load(":/res/image/LevelCompletedDialogBg.png");
    winLabel->setGeometry(QRect(0,0,pix.width(),pix.height()));
    winLabel->setPixmap(pix);
    winLabel->move((this->width()-pix.width())*0.5,-pix.height());
}

void PlayScene::readMap()
{
    dataConfig allMap; // 每次构造所有关卡的地图。这样写很烂。但是可以省略读取文件操作。
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            this->gameArray[i][j] = allMap.mData[this->levelIndex][i][j];
        }
    }
}

void PlayScene::coinsDisplay()
{
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            // 设置金币或者银币路径
            QString coinPath;
            if(this->gameArray[i][j] == 1)
                coinPath = ":/res/image/Coin0001.png";
            else
                coinPath = ":/res/image/Coin0008.png";

            QLabel *label = new QLabel;
            QPixmap pix = QPixmap(":/res/image/BoardNode.png");
            label->setGeometry(QRect(0,0,pix.width(),pix.height()));
            label->setPixmap(pix);
            label->setParent(this);
            label->move(i*pix.width()+40, j*pix.height()+150);

            CoinButton *coin = new CoinButton(coinPath);
            coin->setParent(this);
            coin->move(i*pix.width()+40+2, j*pix.height()+150+2);

            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j];

            // 保存金币指针
            coinBtn[i][j] = coin;

            // 点击金币:进行翻转；更新关卡地图；
            connect(coin,&CoinButton::clicked,this,[=](){
                coin->changeFlag();
                this->gameArray[i][j] = this->gameArray[i][j] == 0 ? 1 : 0;

                // 翻转周围金币
                if(coin->posX + 1 <= 3){// 翻转右侧金币
                    int i = coin->posX + 1;
                    int j = coin->posY;
                    coinBtn[i][j]->changeFlag();
                    this->gameArray[i][j] = this->gameArray[i][j] == 0 ? 1 : 0;
                }
                if(coin->posX - 1 >= 0){// 翻转左侧金币
                    int i = coin->posX - 1;
                    int j = coin->posY;
                    coinBtn[i][j]->changeFlag();
                    this->gameArray[i][j] = this->gameArray[i][j] == 0 ? 1 : 0;
                }
                if(coin->posY + 1 <= 3){// 翻转下侧金币
                    int i = coin->posX;
                    int j = coin->posY + 1;
                    coinBtn[i][j]->changeFlag();
                    this->gameArray[i][j] = this->gameArray[i][j] == 0 ? 1 : 0;
                }
                if(coin->posY - 1 >= 0){// 翻转上侧金币
                    int i = coin->posX;
                    int j = coin->posY - 1;
                    coinBtn[i][j]->changeFlag();
                    this->gameArray[i][j] = this->gameArray[i][j] == 0 ? 1 : 0;
                }

                if(this->checkWin() == true){ // 胜利后：禁用所有金币按钮，弹出胜利label
                    qDebug() << "We Win";
                    this->disableAllBtn();
                    this->displayWinLabel();
                }

            });
        }
    }
}


bool PlayScene::checkWin()
{
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(this->gameArray[i][j] == 1)
                this->isWin = true;
            else {
                this->isWin = false;
                goto ans;
    //            break 2;
            }
        }
    }
ans:
    return this->isWin;
}


void PlayScene::disableAllBtn()
{
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            this->coinBtn[i][j]->disableBtn = true;
        }
    }
}


void PlayScene::displayWinLabel()
{
    QPropertyAnimation *animation = new QPropertyAnimation(winLabel,"geometry",winLabel); // 动画绑定到button的“geomerty”属性上
    animation->setDuration(1000); // 动画时长
    animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height())); // 起始位置
    animation->setEndValue(QRect(winLabel->x(),winLabel->y()+130,winLabel->width(),winLabel->height())); // 终止位置
    animation->setEasingCurve(QEasingCurve::OutBounce); // 缓和曲线
    animation->start();
}


void PlayScene::paintEvent(QPaintEvent *event)
{
    // 背景加载
    QPainter painter(this);
    QPixmap pix;
    if( pix.load(":/res/image/PlayLevelSceneBg.png") == false) {
        qDebug() << "图片加载失败";
        return;
    }
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/image/Title.png");
    pix = pix.scaled(pix.width()*0.8,pix.height()*0.8);
    painter.drawPixmap(20,20,pix);
}
