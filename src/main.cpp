//
// Created by erick on 4/4/15.
//

#include <sstream>
#include <vector>
#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "Zippo.h"
#include "Scale.h"
#include <sstream>
#include <string>

using namespace cv;
//initial min and max HSV filter values.
//these will be changed using trackbars
int H_MIN = 0;
int H_MAX = 256;
int S_MIN = 0;
int S_MAX = 256;
int V_MIN = 0;
int V_MAX = 256;
//default capture width and height
const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;
//max number of objects to be detected in frame
const int MAX_NUM_OBJECTS=50;
//minimum and maximum object area
const int MIN_OBJECT_AREA = 20*20;
const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH/1.5;
//names that will appear at the top of each window
const string windowName = "Original Image";
const string windowName1 = "HSV Image";
const string windowName2 = "Thresholded Image";
const string windowName3 = "After Morphological Operations";
const string trackbarWindowName = "Trackbars";
//Multithreading stuff
pthread_t thread1, thread2;
int ret_thread;
float weight;
Scale scale;
string weight_str;
//Function Declerations
void* lookforobject(void *ofd_ptr);
void* StartScale(void *params);
string Stringify(float number);


void on_trackbar( int, void* )
{//This function gets called whenever a
    // trackbar position is changed
}
string intToString(int number){
    std::stringstream ss;
    ss << number;
    return ss.str();
}
void createTrackbars(){
    namedWindow(trackbarWindowName,0);
    char TrackbarName[50];
    sprintf( TrackbarName, "H_MIN", H_MIN);
    sprintf( TrackbarName, "H_MAX", H_MAX);
    sprintf( TrackbarName, "S_MIN", S_MIN);
    sprintf( TrackbarName, "S_MAX", S_MAX);
    sprintf( TrackbarName, "V_MIN", V_MIN);
    sprintf( TrackbarName, "V_MAX", V_MAX);

    createTrackbar( "H_MIN", trackbarWindowName, &H_MIN, H_MAX, on_trackbar );
    createTrackbar( "H_MAX", trackbarWindowName, &H_MAX, H_MAX, on_trackbar );
    createTrackbar( "S_MIN", trackbarWindowName, &S_MIN, S_MAX, on_trackbar );
    createTrackbar( "S_MAX", trackbarWindowName, &S_MAX, S_MAX, on_trackbar );
    createTrackbar( "V_MIN", trackbarWindowName, &V_MIN, V_MAX, on_trackbar );
    createTrackbar( "V_MAX", trackbarWindowName, &V_MAX, V_MAX, on_trackbar );

}
void drawObject(Vector<Zippo> zips, Mat &frame){
    //added 'if' and 'else' statements to prevent
    //memory errors from writing off the screen (ie. (-25,-25) is not within the window
    for (int i = 0; i < zips.size(); ++i) {
        circle(frame, Point(zips.operator[](i).getX(), zips.operator[](i).getY()), 20, Scalar(0, 255, 0), 2);
        if (zips.operator[](i).getY() - 25 > 0)
            line(frame, Point(zips.operator[](i).getX(), zips.operator[](i).getY()), Point(zips.operator[](i).getX(), zips.operator[](i).getY() - 25), Scalar(0, 255, 0), 2);
        else line(frame, Point(zips.operator[](i).getX(), zips.operator[](i).getY()), Point(zips.operator[](i).getX(), 0), Scalar(0, 255, 0), 2);
        if (zips.operator[](i).getY() + 25 < FRAME_HEIGHT)
            line(frame, Point(zips.operator[](i).getX(), zips.operator[](i).getY()), Point(zips.operator[](i).getX(), zips.operator[](i).getY() + 25), Scalar(0, 255, 0), 2);
        else line(frame, Point(zips.operator[](i).getX(), zips.operator[](i).getY()), Point(zips.operator[](i).getX(), FRAME_HEIGHT), Scalar(0, 255, 0), 2);
        if (zips.operator[](i).getX() - 25 > 0)
            line(frame, Point(zips.operator[](i).getX(), zips.operator[](i).getY()), Point(zips.operator[](i).getX() - 25, zips.operator[](i).getY()), Scalar(0, 255, 0), 2);
        else line(frame, Point(zips.operator[](i).getX(), zips.operator[](i).getY()), Point(0, zips.operator[](i).getY()), Scalar(0, 255, 0), 2);
        if (zips.operator[](i).getX() + 25 < FRAME_WIDTH)
            line(frame, Point(zips.operator[](i).getX(), zips.operator[](i).getY()), Point(zips.operator[](i).getX() + 25, zips.operator[](i).getY()), Scalar(0, 255, 0), 2);
        else line(frame, Point(zips.operator[](i).getX(), zips.operator[](i).getY()), Point(FRAME_WIDTH, zips.operator[](i).getY()), Scalar(0, 255, 0), 2);
        putText(frame, intToString(zips.operator[](i).getX()) + "," + intToString(zips.operator[](i).getY()), Point(zips.operator[](i).getX(), zips.operator[](i).getY() + 30),
                1, 1, Scalar(0, 255, 0), 2);
        putText(frame, zips.operator[](i).getType() + " " + weight_str, Point(zips.operator[](i).getX(), zips.operator[](i).getY() - 30), 1, 2, zips.operator[](i).getColor());
    }
}
void morphOps(Mat &thresh){
    //create structuring element that will be used to "dilate" and "erode" image.
    //the element chosen here is a 3px by 3px rectangle
    Mat erodeElement = getStructuringElement( MORPH_RECT,Size(3,3));
    //dilate with larger element so make sure object is nicely visible
    Mat dilateElement = getStructuringElement( MORPH_RECT,Size(8,8));
    erode(thresh,thresh,erodeElement);
    erode(thresh,thresh,erodeElement);

    dilate(thresh,thresh,dilateElement);
    dilate(thresh,thresh,dilateElement);
}
void trackFilteredObject(int &x, int &y, Mat threshold, Mat &cameraFeed){

    Vector<Zippo> zips;

    Mat temp;
    threshold.copyTo(temp);
    //these two vectors needed for output of findContours
    vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;
    //find contours of filtered image using openCV findContours function
    findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );
    //use moments method to find our filtered object
    double refArea = 0;
    bool objectFound = false;
    if (hierarchy.size() > 0) {
        int numObjects = hierarchy.size();
        //if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
        if(numObjects<MAX_NUM_OBJECTS){
            for (int index = 0; index >= 0; index = hierarchy[index][0]) {

                Moments moment = moments((cv::Mat)contours[index]);
                double area = moment.m00;

                //if the area is less than 20 px by 20px then it is probably just noise
                //if the area is the same as the 3/2 of the image size, probably just a bad filter
                //we only want the object with the largest area so we safe a reference area each
                //iteration and compare it to the area in the next iteration.
                if(area>MIN_OBJECT_AREA && area<MAX_OBJECT_AREA && area>refArea){
                    Zippo zip;
                    zip.setX( moment.m10/area);
                    zip.setY( moment.m01/area);
                    zips.push_back(zip);
                    objectFound = true;
                    refArea = area;
                }else objectFound = false;


            }
            //let user know you found an object
            if(objectFound ==true){
                putText(cameraFeed,"Tracking Object",Point(0,50),2,1,Scalar(0,255,0),2);
                //draw object location on screen
                drawObject(zips,cameraFeed);}

        }else putText(cameraFeed,"TOO MUCH NOISE! ADJUST FILTER",Point(0,50),1,2,Scalar(0,0,255),2);
    }
}
void trackFilteredObject(Zippo zip_param, Mat threshold, Mat &cameraFeed){

    Vector<Zippo> zips;

    Mat temp;
    threshold.copyTo(temp);
    //these two vectors needed for output of findContours
    vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;
    //find contours of filtered image using openCV findContours function
    findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );
    //use moments method to find our filtered object
    double refArea = 0;
    bool objectFound = false;
    if (hierarchy.size() > 0) {
        int numObjects = hierarchy.size();
        //if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
        if(numObjects<MAX_NUM_OBJECTS){
            for (int index = 0; index >= 0; index = hierarchy[index][0]) {

                Moments moment = moments((cv::Mat)contours[index]);
                double area = moment.m00;

                //if the area is less than 20 px by 20px then it is probably just noise
                //if the area is the same as the 3/2 of the image size, probably just a bad filter
                //we only want the object with the largest area so we safe a reference area each
                //iteration and compare it to the area in the next iteration.
                if(area>MIN_OBJECT_AREA && area<MAX_OBJECT_AREA && area>refArea){
                    Zippo zip;
                    zip.setX( moment.m10/area);
                    zip.setY( moment.m01/area);
                    zip.setType(zip_param.getType());
                    zip.setColor(zip_param.getColor());
                    zips.push_back(zip);
                    objectFound = true;
                    refArea = area;
                }else objectFound = false;


            }
            //let user know you found an object
            if(objectFound ==true){
                putText(cameraFeed,"Tracking Object",Point(0,50),2,1,Scalar(0,255,0),2);
                //draw object location on screen
                drawObject(zips,cameraFeed);}

        }else putText(cameraFeed,"TOO MUCH NOISE! ADJUST FILTER",Point(0,50),1,2,Scalar(0,0,255),2);
    }
}
//some boolean variables for different functionality within this
//program
bool trackObjects = true;
bool useMorphOps = true;
bool calibrationMode = false;

struct objectfinder_data{
    VideoCapture capture_data;
};

int main(int argc, char* argv[])
{
    int thread_ret;
    //Start reading from scale
   // pthread_create(&thread2, NULL, StartScale, NULL);



    if(calibrationMode){
        createTrackbars();
    }

    VideoCapture capture;
    capture.open(0);
    //set height and width of capture frame
    capture.set(CV_CAP_PROP_FRAME_WIDTH,480); //480 for BBB
    capture.set(CV_CAP_PROP_FRAME_HEIGHT,640); //640 for BBB
    objectfinder_data ofd;
    ofd.capture_data = capture;

    //look for object in new thread
    //to do : spawn scale reading thread
    //to do : spawn xml writer thread

    thread_ret = pthread_create(&thread1, NULL, lookforobject, &ofd);

    // rc = pthread_create(&thread1, NULL, lookforobject_2, &ofd);
    //Start reading from scale
   thread_ret = pthread_create(&thread2, NULL, StartScale, NULL);
    std::cout << thread_ret;

    //main loop
    while(1){
        weight = scale.getWeight();
        weight_str = Stringify(weight);
    }

    return 0;
}

void *lookforobject(void *ofd_ptr){
    objectfinder_data* ofd_local = (objectfinder_data* )ofd_ptr;
    VideoCapture capture = ofd_local->capture_data;
    VideoCapture capture_for_stream = ofd_local->capture_data;
    Mat cameraFeed;
    Mat HSV;
    Mat threshold;
    int x=0, y=0;

    //video writer for network stream
    //VideoWriter video("capture.mpg",-1, 30, cvSize(CV_CAP_PROP_FRAME_WIDTH,CV_CAP_PROP_FRAME_HEIGHT) );
    while(1){
        //store image to matrix
        capture.read(cameraFeed);
        if(calibrationMode == true){
            //convert frame from BGR to HSV colorspace
            cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
            //Settings for - AppleTV Remote
            //inRange(HSV,Scalar(88,34,130),Scalar(122,108,256),threshold);
            //Settings for green zippo
            inRange(HSV,Scalar(H_MIN,S_MIN,V_MIN),Scalar(H_MAX,S_MAX,V_MAX),threshold);
            //perform morphological operations on thresholded image to eliminate noise
            //and emphasize the filtered object(s)
            morphOps(threshold);
            imshow(windowName2, threshold);
            trackFilteredObject(x, y, threshold, cameraFeed);
        } else {
            Zippo zip("Milk"), remote("remote");

            cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
            inRange(HSV,zip.getHSVMin(),zip.getHSVMax(),threshold);
            morphOps(threshold);
            trackFilteredObject(zip, threshold, cameraFeed);

            cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
            inRange(HSV,remote.getHSVMin(),remote.getHSVMax(),threshold);
            morphOps(threshold);
            trackFilteredObject(remote, threshold, cameraFeed);
        }
        //show frames
        imshow(windowName, cameraFeed);
        imshow(windowName1, HSV);
        //delay 30ms so that screen can refresh.
        //image will not appear without this waitKey() command
        waitKey(30);
    }
}

void *StartScale(void *param){
    scale.Start();

}

string Stringify(float number){
    std::ostringstream o;
    if(!(o << number))
        std::cout << "BadConversion - In function Stringify";
    return o.str();
}


