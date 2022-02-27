#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "imagepushbutton.h"
#include "chooselevelscene.h"
#include "globalvar.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    void paintEvent(QPaintEvent *event);

private:
    Ui::MainScene *ui;
    void prepare();
    ChooseLevelScene *chooseScene = nullptr;
};
#endif // MAINSCENE_H
