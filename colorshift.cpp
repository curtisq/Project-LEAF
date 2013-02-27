#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

Mat src; Mat src_gray;
int thresh = 70;
int max_thresh = 200;
RNG rng(12345);

int detectColor(Mat src, Point tl, Point br);

/// Function header
void thresh_callback(int, void* );

/** @function main */
int main( int argc, char** argv )
{
        
        VideoCapture capWebcam(0);		// declare a videoCapture object, 0 ==> use 1st webcam
        
        if(capWebcam.isOpened() == false) {			// check if videoCapture object was associated to webcam successfully
		std::cout << "error: capWebcam not accessed successfully\n\n"; 
		return(1);												       
	}
	
        
	char charCheckForEscKey = 0;
        
        //Webcam open until esc key is hit
	while(charCheckForEscKey != 27){
		if(capWebcam.read(src) == 0) {
			std::cout << "ERROR\n\n";	
			break;
		}
        
        /// Convert image to gray and blur it
        cvtColor( src, src_gray, CV_BGR2GRAY );
        blur( src_gray, src_gray, Size(3,3) );
        
        /// Create Window
        char* source_window = "Source";
        namedWindow( source_window, CV_WINDOW_AUTOSIZE );
        imshow( source_window, src );
        
        //createTrackbar( " Threshold:", "Source", &thresh, max_thresh, thresh_callback );
        
        thresh_callback( 0, 0 );
        
        waitKey(1200);
        }
        return(0);
}

/** @function thresh_callback */
void thresh_callback(int, void* )
{
        Mat threshold_output;
        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;
        
        /// Detect edges using Threshold
        threshold( src_gray, threshold_output, thresh, 255, THRESH_BINARY );
        /// Find contours
        findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
        
        /// Approximate contours to polygons + get bounding rects and circles
        vector<vector<Point> > contours_poly( contours.size() );
        vector<Rect> boundRect( contours.size() );
        vector<Point2f>center( contours.size() );
        vector<float>radius( contours.size() );
        
        for( int i = 0; i < contours.size(); i++ )
        { approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
                boundRect[i] = boundingRect( Mat(contours_poly[i]) );
                minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );
        }
        
        int total = 0;
        
        /// Draw polygonal contour + bonding rects + circles
        Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
        for( int i = 0; i< contours.size(); i++ )
        {
                Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
                
                if( ((boundRect[i].br().x - boundRect[i].tl().x) > 80) 
                &&  ((boundRect[i].br().x - boundRect[i].tl().x) < 620 )){
                        //total amount of drawn rects
                        total++;
                
                        drawContours( drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
                        rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
                        cout << "boundrect[" << i << "].br() is: " << boundRect[i].br() << endl << "and it ";
                  //      cout << "boundrect[" << i << "} br.x-tl.x is: " << (boundRect[i].br().x - boundRect[i].tl().x) << endl;
                        //circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );
                        cout << "For rect[" << i << "] the values are:" << endl; 
                        detectColor(src, boundRect[i].tl(), boundRect[i].br() );
                }
        }
        cout << "total rectangles: " << total << endl;

        /// Show in a window
        namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
        imshow( "Contours", drawing );
        namedWindow( "src", CV_WINDOW_AUTOSIZE );
        imshow( "src", src );
}

int detectColor(Mat src, Point tl, Point br)
{
        cvtColor(src, src, CV_BGR2HSV);
        
        int totH = 0;     
        int totS = 0;     
        int totV = 0;     
        int count = 0;
        //over entire rectangle calculate avg color
        
        for(int i = tl.y; i < br.y ; i++)
        {
                for(int j = tl.x; j < br.x; j++)
                {
                        /*
                        cout << "At point (" << j << "," << i << "):" << endl;
                        cout << "B: " << src.data[src.step[0]*i + src.step[1]* j + 0] << " | ";
                        cout << "G: " << src.data[src.step[0]*i + src.step[1]* j + 1] << " | ";
                        cout << "R: " << src.data[src.step[0]*i + src.step[1]* j + 2] << endl;
                         */
                        count++;
                        totH += src.data[src.step[0]*i + src.step[1]* j + 0];
                        totS += src.data[src.step[0]*i + src.step[1]* j + 1];
                        totV += src.data[src.step[0]*i + src.step[1]* j + 2];

                }
        }
        
        totH = totH / count;
        totS = totS / count;
        totV = totV / count;
        //cout << "totH: " << totH << " | ";
        //cout << "totS: " << totS << " | ";
        //cout << "totV: " << totV << endl;
        
        if( (15 <= totH)  && (totH <= 55)
        &&  (110 <= totS) && (totS <= 155)
        &&  (105 <= totV) && (totV <= 155) )
                cout << "IS a Leaf." << endl;
        else{
        cout << "is NOT a Leaf." << endl;
        }
        
        return totH;
}