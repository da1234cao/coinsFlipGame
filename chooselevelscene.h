#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>

#include "globalvar.h"
#include "playscene.h"

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT

private:
    PlayScene *play = nullptr;

public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void prepare();

signals:
    // 自定义信号，用于返回主场景
    void chooseScenceBack(void);
};

#endif // CHOOSELEVELSCENE_H
