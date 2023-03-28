//
// Created by Chu-Hsuan Lin on 2022/1/24.
//

#ifndef REAL_TIME_FILTERING_FILTER_H
#define REAL_TIME_FILTERING_FILTER_H

int greyscale( cv::Mat &src, cv::Mat &dst );
int blur5x5( cv::Mat &src, cv::Mat &dst );
int sobolX3x3( cv::Mat &src, cv::Mat &dst );
int sobolY3x3( cv::Mat &src, cv::Mat &dst );
int magnitude( cv::Mat &sx, cv::Mat &sy, cv::Mat &dst );
int blurQuantize( cv::Mat &src, cv::Mat &dst, int levels );
int cartoon( cv::Mat &src, cv::Mat&dst, int levels, int magThreshold );
int adjust(cv::Mat &src, cv::Mat&dst, float brightness, float contrast);
int pencil(cv::Mat &src, cv::Mat&dst);
int morandiPencil(cv::Mat &src, cv::Mat&dst);

void sobel_filter(cv::Mat &src, cv::Mat &dst, cv::Mat &filter);
#endif //REAL_TIME_FILTERING_FILTER_H
