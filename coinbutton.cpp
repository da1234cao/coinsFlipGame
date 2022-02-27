#include "coinbutton.h"

#include <QDebug>

CoinButton::CoinButton(QString btnImg)
{
    QPixmap pix;
    if(pix.load(btnImg) == false){
        qDebug() << "图片加载失败：" << btnImg;
        return;
    }

    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(QIcon(pix));
    this->setIconSize(QSize(pix.width(),pix.height()));

    // 初始化定时器
    this->timer1 = new QTimer(this);
    this->timer2 = new QTimer(this);

    connect(timer1,&QTimer::timeout,this,[=](){
        QString imgPath = QString(":/res/image/Coin000%1.png").arg(this->min++);
        QPixmap pix;
        pix.load(imgPath);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(QIcon(pix));
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(this->min == this->max + 1){
            this->min = 1;
            timer1->stop();
        }
    });

    connect(timer2,&QTimer::timeout,this,[=](){
        QString imgPath = QString(":/res/image/Coin000%1.png").arg(this->max--);
        QPixmap pix;
        pix.load(imgPath);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(QIcon(pix));
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(this->max == this->min - 1){
            this->max = 8;
            timer2->stop();
        }
    });

}


void CoinButton::changeFlag()
{
    // 正面，则翻转成反面
    if(this->flag == 1){
        this->timer1->start(30);
        this->flag = false;
    }else {
        this->timer2->start(30);
        this->flag = true;
    }
}

void CoinButton::mousePressEvent(QMouseEvent *e)
{
    // 屏蔽按下功能
    if(this->disableBtn == true)
        return;
    QPushButton::mousePressEvent(e);
}
