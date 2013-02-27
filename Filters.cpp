//
//  Filters.cpp
//  openCv setup
//
//  Created by Curtis Quintal on 2/20/13.
//  Copyright (c) 2013 Curtis Quintal. All rights reserved.
//

#include "Filters.h"
#include <iostream>



Mat redFilter(const Mat& src)
{
        assert(src.type() == CV_8UC3);
        Mat dest;        
        
        inRange(src, Scalar(0, 0, 0), Scalar(0, 0, 255), dest);
        
        return dest;
}

Mat ColorFilter(const Mat& src, int bLow, int gLow, int rLow, int bHigh, int gHigh, int rHigh)
{
        assert(src.type() == CV_8UC3);
        Mat dest;
        
        inRange(src, Scalar(bLow, gLow, rLow), Scalar(bHigh, gHigh, rHigh), dest);
        
        return dest;
}

Mat blackFilter(const Mat& src)
{
        assert(src.type() == CV_8UC3);
        Mat dest;
        
        inRange(src, Scalar(0, 0, 0), Scalar(0, 0, 0), dest);
        
        return dest;
}

Mat whiteFilter(const Mat& src)
{
        assert(src.type() == CV_8UC3);
        Mat dest;
        
        inRange(src, Scalar(255, 255, 255), Scalar(255, 255, 255), dest);
        
        return dest;
}

Mat FilterOutSrc(const Mat& src, int bLow, int gLow, int rLow, int bHigh, int gHigh, int rHigh)
{
        assert(src.type() == CV_8UC3);

        Mat dest;
        
        inRange(src, Scalar(bLow, gLow, rLow), Scalar(bHigh, gHigh, rHigh), dest);
        
        
        //these loops iterate through every pixel in destMat
        for(int i = 0; i < dest.rows; i++)
        {
                for(int j = 0; j < dest.cols; j++)
                {
                        //checks to see if current pixel in dest is black (not in set range)
                        if(dest.data[dest.step[0]*i + dest.step[1]* j + 0] == 0 &&
                           dest.data[dest.step[0]*i + dest.step[1]* j + 1] == 0 &&
                           dest.data[dest.step[0]*i + dest.step[1]* j + 2] == 0)
                        {
                                //set the corresponding pixel in src to be black as well
                                src.data[src.step[0]*i + src.step[1]* j + 0] = 0;
                                src.data[src.step[0]*i + src.step[1]* j + 1] = 0;
                                src.data[src.step[0]*i + src.step[1]* j + 2] = 0;
                        }                        
                }
        }
        
         
        //This function returns dest Mat with color filters in range of passed args
        //This function ALSO blacks out pixels in src Mat that are not in range
        //This does affect the passed in matrix
        
        return dest;
}

Mat FilterInSrc(const Mat& src, int bLow, int gLow, int rLow, int bHigh, int gHigh, int rHigh)
{
        assert(src.type() == CV_8UC3);
        Mat dest;
        
        inRange(src, Scalar(bLow, gLow, rLow), Scalar(bHigh, gHigh, rHigh), dest);
        
        //these loops iterate through every pixel in destMat
        for(int i = 0; i < dest.rows; i++)
        {
                for(int j = 0; j < dest.cols; j++)
                {
                        //checks to see if current pixel in dest is black (not in set range)
                        if(dest.data[dest.step[0]*i + dest.step[1]* j + 0] == 255 &&
                           dest.data[dest.step[0]*i + dest.step[1]* j + 1] == 255 &&
                           dest.data[dest.step[0]*i + dest.step[1]* j + 2] == 255)
                        {
                                //set the corresponding pixel in src to be black as well
                                src.data[src.step[0]*i + src.step[1]* j + 0] = 0;
                                src.data[src.step[0]*i + src.step[1]* j + 1] = 0;
                                src.data[src.step[0]*i + src.step[1]* j + 2] = 0;
                        }                        
                }
        }
        
        //This function returns dest Mat with color filters in range of passed args
        //This function ALSO blacks out pixels in src Mat that are not in range
        //This does affect the passed in matrix
        
        return dest;
}

Mat HSVrange(const Mat& src, int hLow, int sLow, int vLow, int hHigh, int sHigh, int vHigh)
{
        
        assert(src.type() == CV_8UC3);
        
        Mat src_hsv;
        
        //convert src to type hsv
        cvtColor(src, src_hsv, CV_BGR2HSV);
        
        Mat dest;
        
        //check hsv values using inRange, all in range will be set to white pixels
        inRange(src_hsv, Scalar(hLow, sLow, vLow), Scalar(hHigh, sHigh, vHigh), dest);
        
        
        return dest;
}


int blackCount(Mat src)
{
        int count = 0;
        
        for(int row = 0; row < src.rows; ++row) {
                unsigned char* inp  = src.ptr<unsigned char>(row);
                for (int col = 0; col < src.cols; ++col) {
                        if (*inp++ == 0) count++;
                }
        }
        
        return count;
        
}
int whiteCount(Mat src)
{
        int count = 0;
        
        for(int row = 0; row < src.rows; ++row) {
                unsigned char* inp  = src.ptr<unsigned char>(row);
                for (int col = 0; col < src.cols; ++col) {
                        if (*inp++ == 255) count++;
                }
        }
        
        return count;
        
}