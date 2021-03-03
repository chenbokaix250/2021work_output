//
//  main.cpp
//  opencv_ch1
//
//  Created by 博凯 Chen on 2021/3/3.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio/videoio_c.h>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/videoio.hpp>

using namespace cv;
using namespace std;
int main(int argc, const char * argv[]) {
    
    VideoCapture cap;
    Mat frame;
    int deviceID = 0;
    int apiID = cv::CAP_ANY;
    cap.open(deviceID,apiID);
    
    if (!cap.isOpened()) {
            cerr << "ERROR! Unable to open camera\n";
            return -1;
        }
    
    //--- GRAB AND WRITE LOOP
        cout << "Start grabbing" << endl
            << "Press any key to terminate" << endl;
        for (;;)
        {
            // wait for a new frame from camera and store it into 'frame'
            cap.read(frame);
            // check if we succeeded
            if (frame.empty()) {
                cerr << "ERROR! blank frame grabbed\n";
                break;
            }
            // show live and wait for a key with timeout long enough to show images
            imshow("Live", frame);
            if (waitKey(5) >= 0)
                break;
        }
        // the camera will be deinitialized automatically in VideoCapture destructor
        return 0;
}
