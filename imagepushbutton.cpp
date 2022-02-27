#include "imagepushbutton.h"

#include <QPushButton>
#include <QDebug>
#include <QPropertyAnimation>

ImagePushButton::ImagePushButton(QString normalImg, QString pressImg)
{
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;

    // 按钮和图片一样大，不要把图片传太大
    QPixmap pix;
    if( pix.load(normalImgPath) == false) {
        qDebug() << "图片加载失败";
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    this->setStyleSheet("QPushButton{border:0px;}"); //设置按钮样式

}

void ImagePushButton::zoomDown()
{
    // 动画：时间，起始位置，终止位置，弹跳效果
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

void ImagePushButton::zoomUp()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

void ImagePushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressImgPath == ""){
        return QPushButton::mousePressEvent(e);
    }

    QPixmap pix;
    if( pix.load(this->pressImgPath) == false) {
        qDebug() << "图片加载失败";
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    this->setStyleSheet("QPushButton{border:0px;}");

    return QPushButton::mousePressEvent(e);
}

void ImagePushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressImgPath == "")
        return QPushButton::mouseReleaseEvent(e);

    QPixmap pix;
    if( pix.load(this->normalImgPath) == false) {
        qDebug() << "图片加载失败";
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    this->setStyleSheet("QPushButton{border:0px;}");

    return QPushButton::mouseReleaseEvent(e);
}
