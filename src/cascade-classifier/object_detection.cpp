#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

// const String m = "/home/vlad/libs/opencv/data/haarcascades/haarcascade_fullbody.xml";

const String keys =
    "{help h usage ? |      | print this message   }"
    "{model          |      | cascade model        }"
    "{image          |      | image for detection  }"
    ;

int main(int argc, char* argv[])
{
    CommandLineParser parser(argc, argv, keys);
    if (parser.has("help"))
    {
        parser.printMessage();
        return 1;
    }
    
    String model = "None";
    model = parser.get<String>("model");
    String imageName = "None";
    imageName = parser.get<String>("image");

    CascadeClassifier pedestirian_cascade;
    if (model.size() == 0 || !pedestirian_cascade.load(model))
    {
        parser.printMessage();
        return 1;
    }

    Mat img = imread(imageName);
    try
    {
        CV_Assert(!imageName.empty());
    }
    catch (...)
    {
        parser.printMessage();
        return 1;
    }

    std::vector<Rect> objects;
    Mat imgGray;
    cvtColor(img, imgGray, COLOR_RGB2GRAY);
    equalizeHist(imgGray, imgGray);
    pedestirian_cascade.detectMultiScale(imgGray, objects, 1.1, 2, 0, Size(20, 20));

    Mat dst;
    img.copyTo(dst);
    for (int i = 0; i < objects.size(); ++i)
    {
        rectangle(dst, objects[i], Scalar(0, 255, 0), 3);
    }

    namedWindow("Detected humans");
    imshow("Detected humans", dst);
    waitKey();
    
    return 0;
}

// void detectAndDisplay( Mat frame )
// {
//     std::vector<Rect> faces;
//     Mat frame_gray;

//     cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
//     equalizeHist( frame_gray, frame_gray );

//     //-- Detect faces
//     face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );

//     for ( size_t i = 0; i < faces.size(); i++ )
//     {
//         Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
//         ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

//         Mat faceROI = frame_gray( faces[i] );
//         std::vector<Rect> eyes;

//         //-- In each face, detect eyes
//         eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );

//         for ( size_t j = 0; j < eyes.size(); j++ )
//         {
//             Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
//             int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
//             circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
//         }
//     }
//     //-- Show what you got
//     imshow( window_name, frame );
// }
