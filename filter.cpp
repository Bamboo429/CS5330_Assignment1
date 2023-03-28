//
// Created by Chu-Hsuan Lin on 2022/1/24.
//
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int greyscale( cv::Mat &src, cv::Mat &dst ){
    //RGB ↔ HSL

    dst.create(src.size(),CV_8UC1);

    for (int r=0;r<src.rows;r++){
        for ( int c=0;c<src.cols;c++) {
            cv::Vec3b intensity = src.at<Vec3b>(r, c);
            uchar blue = intensity.val[0];
            uchar green = intensity.val[1];
            uchar red = intensity.val[2];

            uchar Vmax = std::max(std::max(blue,green),red);
            uchar Vmin = std::min(std::min(blue,green),red);
            uchar L = (Vmax+Vmin)/2;

            dst.at<char>(r,c) = L;
        }
    }

    return 0;
}


int blur5x5( cv::Mat &src, cv::Mat &dst){

    int gaussian_size = 5;
    int vect_g[5][1]={1,2,4,2,1};
    float gaussian_filter[5][5]{};

    int sum=0;
    float value=0;
    float value_r,value_g,value_b=0;

    int start_r = ceil(gaussian_size/2);
    int start_c = ceil(gaussian_size/2);

    dst.create(src.rows,src.cols,src.type());

    //cal the gaussian filter
    for (int i=0; i<gaussian_size; i++){
        for (int j=0; j<gaussian_size; j++) {
            gaussian_filter[i][j] += vect_g[i][0] * vect_g[j][0];
            sum += vect_g[i][0] * vect_g[j][0];
        }
    }

    //divided by sum, normalize
    for (int i=0; i<gaussian_size; i++){
        for (int j=0; j<gaussian_size; j++) {
            gaussian_filter[i][j] = gaussian_filter[i][j] / (sum);
        }
    }

    // cal the convolution
    for (int i=start_r;i<src.rows-start_r;i++){
        for (int j=start_c;j<src.cols-start_c;j++){

            value_b = 0;
            value_g = 0;
            value_r = 0;
            for (int r=-start_r;r<gaussian_size-start_r;r++){
                for (int c=-start_c;c<gaussian_size-start_c;c++){
                    value_b += src.at<Vec3b>(i+r,j+c)[0]*gaussian_filter[r+2][c+2];
                    value_g += src.at<Vec3b>(i+r,j+c)[1]*gaussian_filter[r+2][c+2];
                    value_r += src.at<Vec3b>(i+r,j+c)[2]*gaussian_filter[r+2][c+2];
                    //std::cout << value << "    " << gaussian_filter[r+2][c+2] << endl;
                }
            }
            dst.at<Vec3b>(i, j)[0] = value_b;
            dst.at<Vec3b>(i, j)[1] = value_g;
            dst.at<Vec3b>(i, j)[2] = value_r;

        }
    }
    return 0;
}

void sobel_filter(cv::Mat &src, cv::Mat &dst, cv::Mat &filter){

    int rows = src.rows;
    int cols = src.cols;
    int channel = src.channels();

    short value_r,value_g,value_b;

    int start_r = ceil(filter.rows/2);
    int start_c = ceil(filter.cols/2);

    //cal convolution
    for (int i=start_r;i<rows-start_r;i++){
        for (int j=start_c;j<cols-start_c;j++){
            value_r = 0;
            value_g = 0;
            value_b = 0;
            for (int r=-start_r;r<filter.rows-start_r;r++){
                for (int c=-start_c;c<filter.cols-start_c;c++){
                    value_b += src.at<Vec3b>(i+r,j+c)[0]*filter.at<char>(r+start_r,c+start_c);
                    value_g += src.at<Vec3b>(i+r,j+c)[1]*filter.at<char>(r+start_r,c+start_c);
                    value_r += src.at<Vec3b>(i+r,j+c)[2]*filter.at<char>(r+start_r,c+start_c);
                }
            }
            dst.at<Vec3s>(i, j)[0] = value_b/4;
            dst.at<Vec3s>(i, j)[1] = value_g/4;
            dst.at<Vec3s>(i, j)[2] = value_r/4;

        }
    }
}


int sobolX3x3( cv::Mat &src, cv::Mat &dst ){

    int sobel_size = 3;
    int vect_sx[3][1]={-1,0,1};
    int vect_g[3][1]={1,2,1};

    dst.create(src.rows,src.cols, CV_16SC3);

    cv::Mat sobel_x;
    sobel_x.create(3,3,CV_8SC1);
    sobel_x = 0;

    //cal sobel x filter
    for (int i=0; i<sobel_size; i++){
        for (int j=0; j<sobel_size; j++) {
            sobel_x.at<char>(i,j) += vect_g[i][0] * vect_sx[j][0];
        }
    }
    sobel_filter(src,dst,sobel_x);

    return 0;

}

int sobolY3x3( cv::Mat &src, cv::Mat &dst ){

    int sobel_size = 3;
    int vect_sy[3][1]={1,0,-1};
    int vect_g[3][1]={1,2,1};

    dst.create(src.rows,src.cols, CV_16SC3);

    cv::Mat sobel_y;
    sobel_y.create(3,3,CV_8SC1);
    sobel_y = 0;

    for (int i=0; i<sobel_size; i++){
        for (int j=0; j<sobel_size; j++) {
            sobel_y.at<char>(i,j) += vect_sy[i][0] * vect_g[j][0];
        }
    }
    sobel_filter(src,dst,sobel_y);
}

int magnitude( cv::Mat &sx, cv::Mat &sy, cv::Mat &dst ){

    dst.create(sx.rows,sx.cols,CV_8UC3);

    cv::Mat output_x,output_y,output;
    output_x.create(sx.size(),CV_16UC3);
    output_y.create(sx.size(),CV_16UC3);

    //x^2 and y^2
    output_x = sx.mul(sx);
    output_x.convertTo(output_x,CV_32FC3);
    output_y = sy.mul(sy);
    output_y.convertTo(output_y,CV_32FC3);

    //sqrt(x^2+y^2)
    sqrt(output_x+output_y,output);
    output.convertTo(dst,CV_8UC3);

    /*
    for (int i=0;i<sx.rows;i++){
        for (int j=0;j<sx.cols;j++){
            for (int k=0;k<3;k++){
                //short ans = sqrt(sx.at<Vec3s>(i, j)[k]*sx.at<Vec3s>(i, j)[k]+sy.at<Vec3s>(i, j)[k]*sy.at<Vec3s>(i, j)[k]);
                short ans = sqrt(output_x.at<Vec3s>(i,j)[k]+output_y.at<Vec3s>(i,j)[k]);
                //std::cout << ans << endl;
                dst.at<Vec3b>(i,j)[k] = ans;
            }
        }
    }
     */
    return 0;
}

int blurQuantize( cv::Mat &src, cv::Mat &dst, int levels){

    cv::Mat blurImage;

    //blurred image
    blur5x5(src,blurImage);
    dst.create(src.size(),src.type());

    //quantize
    int b = 255/levels;
    for (int i=0;i<3*blurImage.total();i++){
        int xt = blurImage.data[i] / b;
        int xf = xt * b;
        dst.data[i] = xf;
    }
    /*
    for (int i=0;i<src.rows;i++){
        for(int j=0;j<src.cols;j++){
            for (int k=0;k<3;k++) {
                int xt = blurImage.at<Vec3b>(i, j)[k] / b;
                int xf = xt * b;
                dst.at<Vec3b>(i, j)[k] = xf;
            }
        }
    }
    */

    return 0;
}


int cartoon( cv::Mat &src, cv::Mat&dst, int levels, int magThreshold ){

    cv::Mat grayImage,edgeImage;
    cv::cvtColor(src,grayImage, COLOR_BGR2GRAY);

    Mat grad_x, grad_y;
    sobolX3x3(grayImage, grad_x );
    sobolY3x3(grayImage, grad_y );
    magnitude(grad_x,grad_y, edgeImage);

    blurQuantize(src, dst, levels );

    //set the value equal=0 when edge value > threshold
    for (int i=0;i<dst.rows;i++){
        for(int j=0;j<dst.cols;j++){
            int value = edgeImage.at<char>(i,j);
            if ( value > magThreshold){

                dst.at<Vec3b>(i, j)[0] = 0;
                dst.at<Vec3b>(i, j)[1] = 0;
                dst.at<Vec3b>(i, j)[2] = 0;

            }
        }
    }
    return 0;
}

int adjust(cv::Mat &src, cv::Mat&dst, float brightness, float contrast){

    dst.create(src.size(),src.type());

    for (int i=0;i<src.rows;i++){
        for(int j=0;j<src.cols;j++){
            for (int k=0;k<3;k++) {
                dst.at<Vec3b>(i,j)[k] =
                        saturate_cast<uchar>( contrast*src.at<Vec3b>(i,j)[k] + brightness );
            }
        }
    }

    return 0;
}

int pencil(cv::Mat &src, cv::Mat&dst){

    // convert to gray image
    cv::Mat grayImage,edgeImage,blurImage,invImage;
    if(src.type() == CV_8UC3) {
        cv::cvtColor(src, grayImage, COLOR_BGR2GRAY);
    }
    else{
        src.copyTo(grayImage);
    }

    // inverse the gray image
    invImage = 255-grayImage;
    // blur the image with bigger size
    cv::GaussianBlur(invImage, blurImage, Size(21, 21), 0);
    // divide gray and blur image
    cv::divide(grayImage, 255-blurImage, dst,256);

    return 0;
}

int morandiPencil(cv::Mat &src, cv::Mat&dst){

    cv::Mat HSVImage,downHSVImage,BRGImage;
    cv::cvtColor(src, HSVImage, COLOR_BGR2HSV);
    cv::Mat b,g,r, pencil_b,pencil_g,pencil_r,s;
    cv::Mat bgr[3],hsv[3];   //destination array

    HSVImage.copyTo(downHSVImage);
    split(HSVImage,hsv);
    // get the saturation value and decrease the value
    s = hsv[1];
    s = s*0.3;
    Mat channel[3] = {hsv[0], s, hsv[2]};
    //combine together
    merge(channel, 3, downHSVImage);

    cv::cvtColor(downHSVImage, BRGImage, COLOR_HSV2BGR);
    split(BRGImage,bgr);//split source
    b = bgr[0];
    g = bgr[1];
    r = bgr[2];

    // pencil sketch for each color
    pencil(b,pencil_b);
    pencil(g,pencil_g);
    pencil(r,pencil_r);

    Mat channels[3] = {pencil_b, pencil_g, pencil_r};
    dst.create(src.rows,src.cols,src.type());
    merge(channels, 3, dst);

    return 0;

}
