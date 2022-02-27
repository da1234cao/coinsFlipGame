#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <coinbutton.h>
#include <QLabel>

class PlayScene : public QMainWindow
{
    Q_OBJECT

private:
    CoinButton *coinBtn[4][4]; // 记录所有按钮
    int levelIndex; // 记录挂卡编号
    int gameArray[4][4]; // 记录关卡地图
    bool isWin = true; // 是否胜利标志
    QLabel *winLabel=nullptr; // 胜利lable

public:
//    explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int index);
    void prepare(void);
    void paintEvent(QPaintEvent *event);

    void readMap(void); // 读取地图
    void coinsDisplay(void); // 根据地图，显示金币
    bool checkWin(void); // 检查是否胜利
    void disableAllBtn(void); // 禁用所有按钮的点击功能
    void displayWinLabel(void); // 显示胜利图片

signals:
    void playScenceBack(void);

};

#endif // PLAYSCENE_H
