#include <stdio.h>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"

using namespace cv;

void img1(const std::string& logo_filename, const std::string& img_filename) {
  Mat logo = imread( logo_filename, 0 );
  Mat img = imread( img_filename, 0 );
  
  vector<KeyPoint> kpL, kpI;
  Mat desL, desI;
  
  ORB orb( 1000 );
  
  orb.detect( logo, kpL );
  orb.compute( logo, kpL, desL );
  
  orb.detect( img, kpI );
  orb.compute( img, kpI, desI );
  
  FlannBasedMatcher matcher;
  std::vector< DMatch > matches;
  matcher.match(desL, desI, matches);
  
  drawKeypoints( img, kpI, img, Scalar(0,255,0) );
  drawKeypoints( logo, kpL, logo, Scalar(0,255,0) );
  imshow("img", img);
  imshow("logo", logo);
}


int main() {
  img1("Coca-Cola-Logo.jpg","brit00611.jpg");
  
  waitKey(0);
  return 0;
}