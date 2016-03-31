#include <stdio.h>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"

using namespace cv;

void img1(const std::string& filename) {
  Mat img = imread(filename, 0);
  vector<KeyPoint> kp;
  Mat des;
  ORB orb( 1000 );
  
  orb.detect( img, kp );
  orb.compute( img, kp, des );
  
  Mat out_img;
  drawKeypoints( img, kp, out_img, Scalar(0,255,0) );
  imshow("ORB1", out_img);
}

void img2(const std::string& filename) {
  Mat img = imread(filename, 0);
  vector<KeyPoint> kp;
  Mat des;
  
  OrbFeatureDetector detector( 1000 );
  detector.detect( img, kp );
  
  OrbDescriptorExtractor extractor;
  extractor.compute( img, kp, des);
  
  Mat out_img;
  drawKeypoints( img, kp, out_img, Scalar(0,0,255) );
  imshow("ORB2", out_img);
}

int main() {
  img1("chupa_chups-gigante08.jpg");
  img2("chupa_chups-gigante08.jpg");
  
  waitKey(0);
  return 0;
}