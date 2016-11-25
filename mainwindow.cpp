#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

#define StartSize 40

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SIZE=20;
    effectiveSize=SIZE * 40 + StartSize;
    resize(680/15*SIZE,680/15*SIZE);    //设置窗口大小
    for(int i=0;i<MAXSIZE;i++)
    {\
        vector<int> temp(MAXSIZE,0);
        a.push_back(temp);
    }
    //memset(a,0,SIZE*SIZE*sizeof(int));
    player=0;

}

MainWindow::~MainWindow()
{
    delete ui;
}



//paintEvent是一个虚函数槽，子类可以对父类的paintEvent进行重写。
//当调用update(),repaint()的时候，paintEvent()会被调用。
//另外，当界面有任何改变的时候,paintEvent也会被调用。
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    int i, j;
    //画棋盘
    for (i = 0; i < SIZE + 1; i++)
    {
        p.drawLine(StartSize, StartSize + i * 40, SIZE*40+StartSize, StartSize + i * 40);
        p.drawLine(StartSize + i * 40, StartSize, StartSize + i * 40, SIZE*40+StartSize);
    }


    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            if (a[i][j] == 1)  //玩家1放的棋子
            {
                brush.setColor(Qt::black);
                p.setBrush(brush);
                p.drawEllipse(QPoint((i+1)*40+20, (j+1)*40+20), 15, 15);  //画棋子
            }
            else if (a[i][j] == 2)   //玩家2放的棋子
            {
                brush.setColor(Qt::white);
                p.setBrush(brush);
                p.drawEllipse(QPoint((i+1)*40+20, (j+1)*40+20), 15, 15);
            }
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    int x, y;
    if(e->x() >= StartSize && e->x() < effectiveSize && e->y() >= StartSize && e->y() < effectiveSize)
    {
        x = (e->x() - StartSize) / 40;
        y = (e->y() - StartSize) / 40;
        if (!a[x][y])
        {
            a[x][y] = player++ % 2 + 1;  //player++来改变玩家
        }
        if(isWin(x, y))
        {
            update();
            //setEnabled(false);  //棋盘不能被选取
            effectiveSize=0;
            if(player%2==1) QMessageBox::information(this, "游戏结束", "黑子玩家赢！", QMessageBox::Ok);
            else QMessageBox::information(this, "游戏结束", " 白子玩家赢！", QMessageBox::Ok);
        }
    }
    update();
}

int MainWindow::isWin(int x, int y)
{
     return case1(x, y) || case2(x, y) || case3(x, y) || case4(x ,y);
}


//从(x,y)坐标开始往 左右，连续5颗颜色相同
bool MainWindow::case1(int x, int y)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        if(y - i >= 0 &&
           y + 4 - i <= 0xF &&
           a[x][y - i] == a[x][y + 1 - i] &&
           a[x][y - i] == a[x][y + 2 - i] &&
           a[x][y - i] == a[x][y + 3 - i] &&
           a[x][y - i] == a[x][y + 4 - i])
        return 1;
    }
    return 0;
}


//从(x,y)坐标开始往 上下，连续5颗颜色相同
bool MainWindow::case2(int x, int y)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        if(x - i >= 0 &&
           x + 4 - i <= 0xF &&
           a[x - i][y] == a[x + 1 - i][y] &&
           a[x - i][y] == a[x + 2 - i][y] &&
           a[x - i][y] == a[x + 3 - i][y] &&
           a[x - i][y] == a[x + 4 - i][y])
           return 1;
    }
    return 0;
}


//从(x,y)坐标开始往 左上右下，连续5颗颜色相同
bool MainWindow::case3(int x, int y)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        if(x - i >= 0 &&
           y - i >= 0 &&
           x + 4 - i <= 0xF &&
           y + 4 - i <= 0xF &&
           a[x - i][y - i] == a[x + 1 - i][y + 1 - i] &&
           a[x - i][y - i] == a[x + 2 - i][y + 2 - i] &&
           a[x - i][y - i] == a[x + 3 - i][y + 3 - i] &&
           a[x - i][y - i] == a[x + 4 - i][y + 4 - i])
           return 1;
    }
    return 0;
}


//从(x,y)坐标开始往 左下右上，连续5颗颜色相同
bool MainWindow::case4(int x, int y)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        if(x + i <= 0xF &&
           y - i >= 0 &&
           x - 4 + i >= 0 &&
           y + 4 - i <= 0xF &&
           a[x + i][y - i] == a[x - 1 + i][y + 1 - i] &&
           a[x + i][y - i] == a[x - 2 + i][y + 2 - i] &&
           a[x + i][y - i] == a[x - 3 + i][y + 3 - i] &&
           a[x + i][y - i] == a[x - 4 + i][y + 4 - i])
           return 1;
    }
    return 0;
}

void MainWindow::on_action_triggered()
{
    effectiveSize=SIZE * 40 + StartSize;
    resize(680/15*SIZE,680/15*SIZE);    //设置窗口大小
   // memset(a,0,SIZE*SIZE*sizeof(int));
    for(int i=0;i<MAXSIZE;i++)
        for(int j=0;j<MAXSIZE;j++)
            a[i][j]=0;
    player=0;
    update();
}

void MainWindow::on_action20_20_triggered()
{
    SIZE=15;
    effectiveSize=SIZE * 40 + StartSize;
    resize(680/15*SIZE,680/15*SIZE);    //设置窗口大小
   // memset(a,0,SIZE*SIZE*sizeof(int));
    for(int i=0;i<MAXSIZE;i++)
        for(int j=0;j<MAXSIZE;j++)
            a[i][j]=0;
    player=0;
    update();
}

void MainWindow::on_action30_30_triggered()
{
    SIZE=20;
    effectiveSize=SIZE * 40 + StartSize;
    resize(680/15*SIZE,680/15*SIZE);    //设置窗口大小
   // memset(a,0,SIZE*SIZE*sizeof(int));
    for(int i=0;i<MAXSIZE;i++)
        for(int j=0;j<MAXSIZE;j++)
            a[i][j]=0;
    player=0;
    update();
}

void MainWindow::on_action50_50_triggered()
{
    SIZE=25;
    effectiveSize=SIZE * 40 + StartSize;
    resize(680/15*SIZE,680/15*SIZE);    //设置窗口大小
   // memset(a,0,SIZE*SIZE*sizeof(int));
    for(int i=0;i<MAXSIZE;i++)
        for(int j=0;j<MAXSIZE;j++)
            a[i][j]=0;
    player=0;
    update();
}

void MainWindow::on_action_5_triggered()
{
    QMessageBox::information(this, "关于五子棋游戏！", "田建超开发测试！", QMessageBox::Ok);
}
