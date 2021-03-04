//
//  main.cpp
//  opencv_ch1
//
//  Created by 博凯 Chen on 2021/3/3.
//

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;
Mat src,dst,tmp;

const char* window_name = "Pyramids Demo";

int main(void)
{
    printf("\n Zoom In-Out demo \n");
    printf("----------------------");
    printf("* [u] -> zoom in  \n");
    printf("* [d] -> zoom out \n");
    printf("* [Esc] -> close program \n \n");
    
    src = imread("/Users/bokaichen/Desktop/1a.jpg");
    if(src.empty())
    {
        printf("No data! -- Exiting the program \n");
        return -1;
    }
    
    tmp = src;
    dst = tmp;
    imshow(window_name,dst);
    
    for(;;)
    {
        char c = (char)waitKey(0);
        if(c == 27){
            break;
        }
        if(c == 'u')
        {
            pyrUp(tmp,dst,Size(tmp.cols*2,tmp.rows*2));
            printf("** Zoom In:Image x 2 \n");
        }
        else if(c == 'd')
        {
            pyrDown(tmp,dst,Size(tmp.cols/2,tmp.rows/2));
            printf("** Zoom out:Image / 2 \n");
        }
        imshow(window_name,dst);
        tmp=dst;
    }
    return 0;
}
