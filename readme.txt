=== Project - Real-time filtering ===

#Built With
Operating system: MacOS Monterey (12.1)
IDE: CLion  https://www.jetbrains.com/clion/

#Installation and Setup
1. Install openCV
2. Modify the CMakeLists.txt
    find_package(OpenCV)
    include_directories(${/usr/local/include/}) //location of your OpenCV

#Instructions for running the executables
1. imgDisplay.cpp
    (1) Modify the file name of the image you want to display in
        char file[256] = "/{IMAGE_NAME}";
    (2) Run the file
2. vidDisplay.cpp
    (1) Run the cpp file and you will see video from your camera
    (2) Press key for different functions
        <1> key 'q' : exit the program
        <2> key 'g' : show the grayScale video using cv::cvtColor( frame, frame_display, COLOR_BGR2GRAY)
        <3> key 'h' : show the other type of grayScale video. Using L of HSL as grayImage.
        <4> key 'b' : show gaussian blurred video
        <5> key 'm' : show sobel filter(edge detection) video, please input the level and
        <6> key 'l' : show quantize video. Change the levels value under the parameter setting.
                      The initialization value of level is 15.
        <7> key 'c' : show cartoonization video. Change the levels value under the parameter setting.
                      The initial value of level is 15 and initial value of magnitude is 10.
        <8> key 's' : save the image show on the screen and the image name is "MyImage.jpg"
        <9> key 'o' : show original video (without any filter)
        <10> key 'a','d','w','e' : show adjusted brightness and contrast video of original image.
                                   The initial value of brightness and contrast are 0 and 1.
                                   Each press of 'a' or 'd' will increase or decrease the brightness by 5.
                                   Each Press of 'w' and 'e' will increase or decrease the contrast by 0.1.
        -- extension function --
        <11> key 'p' : show pencil-sketch video
        <12> key 'r' : show Morandi Color pencil sketch video






