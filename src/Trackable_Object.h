//
// Created by erick on 4/4/15.
// I used this class for testing I will change the class name to match the project
//

#ifndef OPENCV_TRACKING_ZIPPO_H
#define OPENCV_TRACKING_ZIPPO_H

#include <opencv2/core/core.hpp>

using namespace cv;
class Trackable_Object {

public:
    Trackable_Object(void);
    Trackable_Object(String name);
    ~Trackable_Object(void);
    int getX();
    void setX(int newX);
    int getY();
    void setY(int newY);
    Scalar getHSVMin();
    Scalar getHSVMax();
    void setHSVMin(Scalar min_new);
    void setHSVMax(Scalar max_new);
    string getType();
    void setType(string type_new);
    Scalar getColor();
    void setColor(Scalar color_new);

private:
     string type;
     int x, y;
     Scalar HSVMin, HSVMax;
     Scalar color;

};


#endif //OPENCV_TRACKING_ZIPPO_H
