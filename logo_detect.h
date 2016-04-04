#ifndef LOGO_DETECT_H
#define LOGO_DETECT_H

#include <QMainWindow>
#include <QString>
#include <QDir>
#include <QStringList>

#include "opencv2/highgui/highgui.hpp"

using namespace cv;

namespace Ui {
class logo_detect;
}

class logo_detect : public QMainWindow
{
    Q_OBJECT

public:
    explicit logo_detect(QWidget *parent = 0);
    ~logo_detect();
    QDir logo_dir;
    QDir img_dir;
    Mat LogoDetection(const std::string& logo_filename, const std::string& img_filename);
    QStringList GetListOfFiles(QDir dir);
    QString BtClick();

private slots:
    void on_logo_dir_bt_clicked();

    void on_img_dir_bt_clicked();

    void on_pushButton_clicked();

private:
    Ui::logo_detect *ui;
};

#endif // LOGO_DETECT_H
