#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <vector>

#define MAXSIZE 50

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private slots:
    void on_action_triggered();

    void on_action20_20_triggered();

    void on_action30_30_triggered();

    void on_action50_50_triggered();

    void on_action_5_triggered();

private:
    Ui::MainWindow *ui;
    vector<vector<int>> a;             //该格子是否放棋子
    int effectiveSize;   //鼠标有效操作范围
    int isWin(int, int);
    bool case1(int, int);
    bool case2(int, int);
    bool case3(int, int);
    bool case4(int, int);
    int player;
    int SIZE;           //棋盘尺寸
};

#endif // MAINWINDOW_H
