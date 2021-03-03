//
//  main.cpp
//  opencv_ch1
//
//  Created by 博凯 Chen on 2021/3/3.
//

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>


using namespace cv;

int main()
{
    std::string image_path = samples::findFile("/Users/bokaichen/Desktop/1a.jpg");
    Mat img = imread(image_path,IMREAD_COLOR);
    
    if(img.empty())
    {
        std::cout<<"Could not read the image:"<<image_path<<std::endl;
        return 1;
    }
    imshow("Display window",img);
    int k = waitKey(0);
    
    if(k == 's')
    {
        imwrite("1a.jpg", img);
    }
    
    return 0;
}
