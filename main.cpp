#include "logo_detect.h"
#include <QApplication>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    logo_detect w;
    cv::waitKey(0);
    w.show();

    return a.exec();
}
