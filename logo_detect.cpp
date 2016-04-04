#include "logo_detect.h"
#include "ui_logo_detect.h"
#include <stdio.h>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/nonfree/nonfree.hpp"

#include <QFileDialog>
#include <QString>
#include <QDir>
#include <QStringList>

using namespace cv;

logo_detect::logo_detect(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::logo_detect)
{
    ui->setupUi(this);
}

logo_detect::~logo_detect()
{
    delete ui;
}

void logo_detect::on_logo_dir_bt_clicked()
{
    QString ld = this->BtClick();
    this->ui->logo_dir_le->setText(ld);
    if (!ld.isEmpty())
      this->logo_dir.setPath(ld);
}

void logo_detect::on_img_dir_bt_clicked()
{
    QString id = this->BtClick();
    this->ui->img_dir_le->setText(id);
    if (!id.isEmpty())
      this->img_dir.setPath(id);

}

void logo_detect::on_pushButton_clicked()
{
    if (!this->logo_dir.path().isEmpty() && !this->img_dir.path().isEmpty()) {
        QStringList logo_files = this->GetListOfFiles(this->logo_dir);
        QStringList img_files = this->GetListOfFiles(this->img_dir);

        std::string id = this->img_dir.path().toStdString();
        std::string ld = this->logo_dir.path().toStdString();

        for (int i = 0; i < img_files.size(); ++i) {
            for (int j = 0; j < logo_files.size(); ++j)
                this->LogoDetection(ld + "/" + logo_files.at(j).toStdString(), id + "/" + img_files.at(i).toStdString());

            std::string image_file = img_files.at(i).toStdString();
            std::cout << image_file << std::endl;
        }
    }
}

void logo_detect::LogoDetection(const std::string& logo_filename, const std::string& img_filename) {
    Mat logo = imread( logo_filename, 0 );
    Mat img = imread( img_filename, 0 );
    Mat copy_img = imread( img_filename );

    std::vector<KeyPoint> kpL, kpI;
    Mat desL, desI;

//    ORB orb( 2500 );

//    orb.detect( logo, kpL );
//    orb.compute( logo, kpL, desL );

//    orb.detect( img, kpI );
//    orb.compute( img, kpI, desI );
    SurfFeatureDetector detector( 1000 );
    detector.detect(logo, kpL);
    detector.detect(img, kpI);

    SurfDescriptorExtractor extractor;
    extractor.compute(logo, kpL, desL);
    extractor.compute(img, kpI, desI);

    FlannBasedMatcher matcher;//( new flann::LshIndexParams(30,20,2) );
    std::vector< DMatch > matches;
    matcher.match( desL, desI, matches );

    double min_dist = 100;

    for( int i = 0; i < desL.rows; i++ )
    { double dist = matches[i].distance;
        if( dist < min_dist ) min_dist = dist;
    }

    std::vector< DMatch > good_matches;

    for( int i = 0; i < desL.rows; i++ )
    { if( matches[i].distance <= max(2*min_dist, 0.02) )
        { good_matches.push_back( matches[i]); }
    }

    std::vector<Point2f> pts_logo;
    std::vector<Point2f> pts_img;

    for( int i = 0; i < int(good_matches.size()); i++ )
    {
        pts_logo.push_back( kpL[ good_matches[i].queryIdx ].pt );
        pts_img.push_back( kpI[ good_matches[i].trainIdx ].pt );
    }

    if(good_matches.size() >= 4) {
        Mat H = findHomography( pts_logo, pts_img, CV_RANSAC );

        std::vector<Point2f> logo_corners(4);
        logo_corners[0] = cvPoint(0,0); logo_corners[1] = cvPoint( logo.cols, 0 );
        logo_corners[2] = cvPoint( logo.cols, logo.rows ); logo_corners[3] = cvPoint( 0, logo.rows );
        std::vector<Point2f> img_corners(4);
        perspectiveTransform( logo_corners, img_corners, H);

        line( copy_img, img_corners[0], img_corners[1], Scalar( 0, 255, 0), 4 );
        line( copy_img, img_corners[1], img_corners[2], Scalar( 0, 255, 0), 4 );
        line( copy_img, img_corners[2], img_corners[3], Scalar( 0, 255, 0), 4 );
        line( copy_img, img_corners[3], img_corners[0], Scalar( 0, 255, 0), 4 );

        imwrite( img_filename, copy_img );
    }
}

QStringList logo_detect::GetListOfFiles(QDir dir) {
    QStringList lof;
    QStringList file_filter;

    file_filter << "*.png" << "*.jpg";
    lof = dir.entryList(file_filter, QDir::Files);

    return lof;
}

QString logo_detect::BtClick() {
  QFileDialog qfd;

  qfd.setFileMode(QFileDialog::DirectoryOnly);
  qfd.setOption(QFileDialog::ShowDirsOnly);

  QString path_dir = QFileDialog::getExistingDirectory(
              this,
              tr("Select Directory"),
              "C:\\");
  return  path_dir;
}
