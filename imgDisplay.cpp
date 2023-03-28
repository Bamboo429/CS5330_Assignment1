//
// Created by Chu-Hsuan Lin on 2022/1/23.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <unistd.h>

using namespace std;
using namespace cv;

int main2()
{
    char tmp[256],img_location[256];
    char file[256] = "/maxresdefault copy.jpeg";

    chdir("..");
    getcwd(tmp, 256);

    std::string file_name;
    file_name += tmp;
    file_name += file;
    //std::cout << file_name <<endl;

    Mat srcImage = imread(file_name);
    if (!srcImage.data) {
        std::cout << "Image not loaded";
        return -1;
    }

    imshow("[img]", srcImage);
    char key = waitKey(0);
    // see if there is a waiting keystroke
    if(key == 'q'){
        return 0;
    }
}