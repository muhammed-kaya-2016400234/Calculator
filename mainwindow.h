#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    std::vector<QString> calc;             //stores text of buttons clicked
    int mode=0;                             //default mode is zero(decimal)
private slots:

     void multi();
     void clr();
     void hex();
     void dec();
     void equ();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
