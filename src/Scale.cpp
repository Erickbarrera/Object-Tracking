//
// Created by erick on 4/17/15.
//

#include <pthread.h>
#include "Scale.h"


Scale::Scale() {

    //Scale::Start();
}
Scale::~Scale() {

}

float Scale::getWeight() {
    return currentWeight;
}

void  *Scale::Start(){

    //sleep(3);
    float init_val = ReadADC();
    float raw_old = init_val;
    float raw_new = raw_old;
    currentWeight = raw_new;
    float slope = 0.1533403227992;//slope of (weight(lbs)/mV out), must be found experimentally
    //float volt_cons; //Program is written with 5V supplied to the load cells in mind. Uncomment and assign appropriate value (New voltage/5)

    while(one){

        if((raw_old - 5) < raw_new && raw_new < (raw_old + 5)){
            printf("Weight is unchanged.\nInitial Value: %.2f\n", init_val);
            printf("Raw Value: %.2f\nCurrent Weight: %.2f lbs\n\n", raw_new, (raw_new - init_val)*slope);
            sleep(1);
            raw_new = ReadADC();
            printf("Current Weight: %.2f", currentWeight);
        }
        else{
            raw_old = raw_new = ReadADC();
            printf("Weight has changed.\nInitial Value: %.2f\nRaw Value:    %.2f\n", init_val, raw_new);
            printf("Actual Weight:  %.2f lbs\n\n", (raw_new - init_val)*slope/**volt_cons*/);
            //printf("Actual Weight:        %.2f\n", herp(raw_new, init_val);
            sleep(1);
            printf("Current Weight: %.2f", currentWeight);

        }

    }
    return zero;
}

//Gets ADC value and finds the average over how many samples you'd want to take
float Scale::ReadADC(void){

    FILE *fp;
    char buff[255];
    int i, val;
    int sum = zero;
    int sample = 100;

    for(i = zero; i < sample; i++){
        fp = fopen("/sys/devices/ocp.3/helper.15/AIN5", "r");
        fgets(buff, 255, (FILE*)fp);
        sscanf(buff, "%d", &val);
        sum += val;
        fclose(fp);
        sleep(.01);//This shit seems irrelevant, don't know why
    }
    return (sum/sample);
}
