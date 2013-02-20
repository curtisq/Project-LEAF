#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>
#include "Filters.h"

using namespace cv;
using namespace std;

Mat src, src_gray, red_only;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold ;
int const max_lowThreshold = 17;
int ratio = 3;
int kernel_size = 3;

Vec3b whitepixel = (255,255,255);
Vec3b blackpixel = (0,0,0);
Vec3b redpixel = (21,56,95);

Mat reddFilter(const Mat& src);

void CannyThreshold(int, void*)
{

    /// Reduce noise with a kernel 3x3
    blur( src_gray, detected_edges, Size(3,3) );
    
    /// Canny detector
    Canny( detected_edges, detected_edges, lowThreshold, lowThreshold* 3, kernel_size );
    
    /// Using Canny's output as a mask, we display our result
    dst = Scalar::all(0);
    
    src.copyTo( dst, detected_edges);
    
    imshow( "edge map", dst );
    imshow( "b&w edge window", detected_edges);

    
    cout << "blacks: " << blackCount(detected_edges) << endl;
    cout << "whites: " << whiteCount(detected_edges) << endl;
    
}


int main() {
    
    Mat redMat;
        
    VideoCapture capWebcam(0);		// declare a videoCapture object, 0 ==> use 1st webcam
        
    if(capWebcam.isOpened() == false) {			// check if videoCapture object was associated to webcam successfully
		std::cout << "error: capWebcam not accessed successfully\n\n"; 
		return(1);												       
	}
        
        Mat matOriginal;
	Mat matProcessed;
    Mat matOrigGray;
    Mat matEdges, dst;
        
	cv::namedWindow("Original");	
	cv::namedWindow("Processed");	
        
	char charCheckForEscKey = 0;
    
        
	while(charCheckForEscKey != 27) {		// char 27 = esc key
		if(capWebcam.read(src) == 0) {
			std::cout << "ERROR\n\n";	
			break;
		}
	ColorFilterSrc(src, 0, 0, 0, 95, 95, 255);	
        
        /// Create a matrix of the same type and size as src (for dst)
        dst.create( src.size(), src.type() );
        
        /// Convert the image to grayscale
        cvtColor( src, src_gray, CV_BGR2GRAY );
        
        /// Create a window
        namedWindow( "edge map", CV_WINDOW_AUTOSIZE );
        

        //imshow("source camera",src);
        
        //red_only = ColorFilterSrc(src, 0, 0, 0, 100, 100, 255);
        //imshow("red only", red_only);
        
       // imshow("source after red ",src);
 
     
        /// Create a Trackbar for user to enter threshold
        //lowThreshold is starting point for bar, max is max setting cannythreshhold is call to function and value of slider is passed in
        createTrackbar( "Min Threshold:", "edge map", &lowThreshold, max_lowThreshold, CannyThreshold );
        
        /// Show the image
        CannyThreshold(0, 0);
    

        waitKey(1000);
    }   
        
	return (0);
}
