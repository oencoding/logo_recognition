#include "mainwindow.h"
#include <QApplication>
#include <opencv/cv.h>
#include "opencv2/highgui/highgui.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.LogoDetection("chupa.jpg","chupa_chups-gigante08.jpg");
    w.GetListOfFiles("C:\\Users\\Natalia\\Desktop\\mnt\\DataSet_pic\\reference", "C:\\Users\\Natalia\\Desktop\\mnt\\DataSet_pic");
    cv::waitKey(0);
    w.show();

    return a.exec();
}
