#ifndef IMAGEPUSHBUTTON_H
#define IMAGEPUSHBUTTON_H

#include <QWidget>
#include <QString>
#include <QPushButton>

class ImagePushButton : public QPushButton
{
    Q_OBJECT

private:
    QString normalImgPath; // button背景图片
    QString pressImgPath;  // 按下之后的背景图片

public:
//    explicit ImagePushButton(QWidget *parent = nullptr);

    ImagePushButton(QString normalImg, QString pressImg = "");

    // 图片上跳和下跳
    void zoomUp(void);
    void zoomDown(void);

    // 按下使用另一张图片，谈起使用原图片
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:

};

#endif // IMAGEPUSHBUTTON_H
