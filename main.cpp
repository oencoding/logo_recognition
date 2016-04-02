#include <stdio.h>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

void LogoDetection(const std::string& logo_filename, const std::string& img_filename) {
  Mat logo = imread( logo_filename, 0 );
  Mat img = imread( img_filename, 0 );
  Mat copy_img = imread( img_filename );

  std::vector<KeyPoint> kpL, kpI;
  Mat desL, desI;

  ORB orb( 2500 );

  orb.detect( logo, kpL );
  orb.compute( logo, kpL, desL );

  orb.detect( img, kpI );
  orb.compute( img, kpI, desI );

  FlannBasedMatcher matcher( new flann::LshIndexParams(20,10,2) );
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



int main() {
  LogoDetection("chupa.jpg","chupa_chups-gigante08.jpg");

  waitKey(0);
  return 0;
}
