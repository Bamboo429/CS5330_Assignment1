
#include <iostream>
#include <opencv2/opencv.hpp>
#include "imgDisplay.h"
#include "filter.h"
#include <filesystem>
//namespace fs = std::filesystem;
using namespace std;
using namespace cv;


int main() {

    cv::VideoCapture *capdev;
    bool flag_filter = false;
    char key,key2;


    // === parameter_setting ===
    int levels=15,mag=10;
    float brightness=0;
    float contrast=1;

    // open the video device
    capdev = new cv::VideoCapture(0);

    if( !capdev->isOpened() ) {
        printf("Unable to open video device\n");
        return(-1);
    }

    // get some properties of the image
    cv::Size refS( (int) capdev->get(cv::CAP_PROP_FRAME_WIDTH ),
                   (int) capdev->get(cv::CAP_PROP_FRAME_HEIGHT));
    printf("Expected size: %d %d\n", refS.width, refS.height);

    cv::namedWindow("Video", 1); // identifies a window
    cv::Mat frame,frame_display,sx,sy,frame_adjust;

    for(;;) {
        *capdev >> frame; // get a new frame from the camera, treat as a stream
        if( frame.empty() ) {
            printf("frame is empty\n");
            break;
        }

        if(flag_filter == true){ //image pass through filter
            switch(key2){
                case 'g':
                    cv::cvtColor( frame, frame_display, COLOR_BGR2GRAY);
                    break;
                case 'h':
                    greyscale(frame,frame_display);
                    break;
                case 'b':
                    blur5x5(frame, frame_display );
                    break;
                case 'm':
                    sobolX3x3(frame, sx );
                    sobolY3x3(frame, sy );
                    magnitude(sx,sy, frame_display);
                    break;
                case 'l':
                    blurQuantize( frame, frame_display, levels);
                    break;
                case 'c':
                    cartoon( frame, frame_display, levels, mag );
                    break;

                case 'a':
                case 'd':
                case 'w':
                case 'e':
                    adjust(frame, frame_display, brightness, contrast);
                    break;
                case 'p':
                    pencil(frame, frame_display);
                    break;
                case 'r':
                    morandiPencil(frame, frame_display);
                    break;
                default:
                    printf("error key\n");

            }
        }
        else{
            // original image
            frame.copyTo(frame_display);
        }
        cv::imshow("Video", frame_display);

        // see if there is a waiting keystroke
        key = cv::waitKey(30);

        // wait key
        if( key == 'q') {
            break;
        }
        else if(key == 's'){
            bool check = imwrite("MyImage.jpg", frame_display);
            if (check==true){
                std::cout << "Saved Image" <<endl;
            }
        }
        else if (key == 'g' || key == 'h' || key == 'b' || key == 'm'
        || key == 'l' || key == 'c' || key == 'a' || key =='d'
        || key =='p' || key == 'r' || key =='w' || key == 'e'){


            if (key == 'a'){
                brightness+=5;
            }

            if(key == 'd'){
                brightness-=5;
            }

            if(key == 'w'){
                contrast += 0.1;
            }
            if(key == 'e'){
                contrast -= 0.1;
            }

            key2 = key;
            flag_filter = true;
        }
        else if (key == 'o'){
            brightness=0;
            contrast=1;
            flag_filter = false;
        }
    }
    delete capdev;
    return(0);

}

