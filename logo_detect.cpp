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
  
  FlannBasedMatcher matcher(new flann::LshIndexParams(20,10,2));
  std::vector< DMatch > matches;
  matcher.match(desL, desI, matches);
  
  double max_dist = 0; double min_dist = 100;
  
  for( int i = 0; i < desL.rows; i++ )
  { double dist = matches[i].distance;
    if( dist < min_dist ) min_dist = dist;
    if( dist > max_dist ) max_dist = dist;
  }
  
  std::vector< DMatch > good_matches;

  for( int i = 0; i < desL.rows; i++ )
  { if( matches[i].distance <= max(2*min_dist, 0.02) )
    { good_matches.push_back( matches[i]); }
  }
  
  Mat img_matches;
  drawMatches( logo, kpL, img, kpI,
               good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
               vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
               
  std::vector<Point2f> pts_logo;
  std::vector<Point2f> pts_img;
  
  for( int i = 0; i < int(good_matches.size()); i++ )
  {
    pts_logo.push_back( kpL[ good_matches[i].queryIdx ].pt );
    pts_img.push_back( kpI[ good_matches[i].trainIdx ].pt );
  }

  
  imshow( "Good Matches", img_matches );
  
  drawKeypoints( img, kpI, img, Scalar(0,255,0) );
  drawKeypoints( logo, kpL, logo, Scalar(0,255,0) );
  //imshow("img", img);
  //imshow("logo", logo);
}


int main() {
  img1("Coca-Cola-Logo.jpg","brit00611.jpg");
  
  waitKey(0);
  return 0;
}