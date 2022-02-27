#ifndef COINBUTTON_H
#define COINBUTTON_H

#include <QPushButton>
#include <QTimer>

class CoinButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit CoinButton(QWidget *parent = nullptr);

    CoinButton(QString btnImg); // 传入金币or银币路径

    // 成员变量应当设置为私有
    // 写get、set方法比较麻烦，这里设置为共有;

    // 下面三个成员变量：金币位置，正(1)反(0)
    int posX=0;
    int posY=0;
    int flag = 1;

    // 币翻转动作。
    void changeFlag();
    QTimer *timer1; // 正面翻反面
    QTimer *timer2; // 反面翻正面
    int min = 1; // 记录翻转过程中图片切换步骤
    int max = 8;

    // 禁用按钮的点击功能
    bool disableBtn = false;
    void mousePressEvent(QMouseEvent *e);

signals:

};

#endif // COINBUTTON_H
