#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/gpu/gpu.hpp"
#include "opencv2/objdetect/objdetect.hpp"

using namespace cv;

void readme();

/** @function main */
int main( int argc, char** argv )
{
  if( argc != 3 )
  { readme(); return -1; }

  Mat img_object = imread( argv[1], CV_LOAD_IMAGE_GRAYSCALE );
  Mat img_scene = imread( argv[2], CV_LOAD_IMAGE_GRAYSCALE );
  Mat img_result;
  Mat img_debug;

  if( !img_object.data || !img_scene.data )
  { std::cout<< " --(!) Error reading images " << std::endl; return -1; }
  
  cvtColor( img_scene, img_debug, CV_GRAY2RGB );
  
  int match_method = CV_TM_CCORR_NORMED;
  
  while ( true ) {
  
    matchTemplate( img_scene, img_object, img_result, match_method );
    normalize( img_result, img_result, 0, 1, NORM_MINMAX, -1, Mat() );
    
    double minVal, maxVal;
    Point minLoc, maxLoc, matchLoc;
    minMaxLoc( img_result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
    if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED )  matchLoc = minLoc;
    else matchLoc = maxLoc;
    
    rectangle( img_debug, matchLoc, Point(matchLoc.x + img_object.cols , matchLoc.y + img_object.rows), CV_RGB(255,0,0), 3 );
    imshow("debug_img", img_debug);
    
    int c = waitKey(1);
    if (c == 27) break;
  }
  //-- Show detected matches
  //imshow( "Good Matches & Object detection", img_result );

  //waitKey(0);
  return 0;
}

  /** @function readme */
  void readme()
  { std::cout << " Usage: ./SURF_descriptor <img1> <img2>" << std::endl; }