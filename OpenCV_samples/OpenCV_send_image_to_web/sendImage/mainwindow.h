#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "websocketserver.h"
#include "opencv2/opencv.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:

    void cvMatToJPG(const cv::Mat &input, std::vector<uchar>& buf);

    Ui::MainWindow *ui;
    WebSocketServer* m_websocketServer;

};

#endif // MAINWINDOW_H
