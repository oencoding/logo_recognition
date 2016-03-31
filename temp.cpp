#include <stdio.h>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"

using namespace cv;

int main() {
  Mat img = imread("chupa_chups-gigante08.jpg", 0);
  vector<KeyPoint> kp;
  Mat des;
  ORB orb;
  
  orb.detect( img, kp );
  orb.compute( img, kp, des );
  
  Mat out_img;
  drawKeypoints( img, kp, out_img, Scalar(0,255,0) );
  imshow("out_img", out_img);
  
  waitKey(0);
  return 0;
}