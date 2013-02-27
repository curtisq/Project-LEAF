//
//  Filters.h
//  openCv setup
//
//  Created by Curtis Quintal on 2/20/13.
//  Copyright (c) 2013 Curtis Quintal. All rights reserved.
//

#ifndef openCv_setup_Filters_h
#define openCv_setup_Filters_h
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;

Mat redFilter(const Mat& src);
Mat blackFilter(const Mat& src);
Mat whiteFilter(const Mat& src);
Mat ColorFilter(const Mat& src, int bLow, int gLow, int rLow, int bHigh, int gHigh, int rHigh);
Mat FilterInSrc(const Mat& src, int bLow, int gLow, int rLow, int bHigh, int gHigh, int rHigh);
Mat FilterOutSrc(const Mat& src, int bLow, int gLow, int rLow, int bHigh, int gHigh, int rHigh);
Mat HSVrange(const Mat& src, int bLow, int gLow, int rLow, int bHigh, int gHigh, int rHigh);

int blackCount(Mat src);
int whiteCount(Mat src);

#endif
