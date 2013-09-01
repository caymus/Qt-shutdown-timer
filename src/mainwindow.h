#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTimer>
#include <QDesktopServices>
#include <QProcess>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QTimer *countdown;
    QWidget *centralWidget;

protected slots:
    void timeOut();

private:
    Ui::MainWindow *ui;
    int startMilliseconds;


private slots:
    void on_btStart_clicked();
    void on_btStop_clicked();
};

#endif // MAINWINDOW_H
