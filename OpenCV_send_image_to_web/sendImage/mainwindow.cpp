#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "opencv2/opencv.hpp"

using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_websocketServer = new WebSocketServer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    VideoCapture cap;
    cap.open(0, CAP_DSHOW);

    Mat frame;

    while (cv::waitKey(1))
    {
        if (!cap.read(frame))
        {
            qDebug() << "No frames grabbed!\n";
            break;
        }

        cv::flip(frame, frame, 1);   // 左右镜像

        std::vector<uchar> buf;
        cvMatToJPG(frame, buf);

        QByteArray jpgData = QByteArray::fromRawData(reinterpret_cast<const char*>(buf.data()), buf.size());

        emit m_websocketServer->sendBinaryMessage(jpgData);
    }
}


void MainWindow::cvMatToJPG(const cv::Mat &input, std::vector<uchar>& buf)
{
    // jpeg编码
    std::vector<int> params;
    params.resize(3, 0);
    params[0] = cv::IMWRITE_JPEG_QUALITY;
    params[1] = 90;     // 压缩率

    cv::imencode(".jpg", input, buf, params);
}


