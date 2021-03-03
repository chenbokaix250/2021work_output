//
//  main.cpp
//  opencv_ch1
//
//  Created by 博凯 Chen on 2021/3/3.
//
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

int main(void)
{
    double alpha = 0.5;
    double beta;
    double input;
    Mat src1,src2,dst,src1_resized,src2_resized;
    cout<<"Simple linear Blender"<<endl;
    cout<<"---------------------"<<endl;
    cout<<"* Enter alpha [0-1]: ";
    cin>>input;
    
    if(input >= 0 && input <= 1)
    {
        alpha = input;
    }
    
    src1 = imread("/Users/bokaichen/Desktop/1a.jpg");
    src2 = imread("/Users/bokaichen/Desktop/1b.jpeg");
    if(src1.empty()){cout<<"Error loading src1"<<endl;}
    if(src2.empty()){cout<<"Error loading src2"<<endl;}
    
    resize(src1, src1_resized, Size(150,100));
    resize(src2, src2_resized, Size(150,100));
    
    cout<<src1_resized.size<<endl;
    beta = (1.0 - alpha);
    addWeighted(src1_resized, alpha, src2_resized, beta, 0.0, dst);
    imshow("Linear Blend",dst);
    waitKey(0);
    return 0;
}
