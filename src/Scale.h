//
// Created by erick on 4/17/15.
//

#ifndef OPENCV_TRACKING_SCALE_H
#define OPENCV_TRACKING_SCALE_H

#include <stdio.h>
#include <unistd.h>

#define zero 0
#define one 1

class Scale{
public:
    Scale(void);
    ~Scale(void);
    void *Start();
    float getWeight();

private:
    float ReadADC();
    float currentWeight;
};


#endif //OPENCV_TRACKING_SCALE_H

