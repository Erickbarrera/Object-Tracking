//
// Created by erick on 4/4/15.
// I used this class for testing I will change the class name to match the project
//

#include "Zippo.h"

Zippo::Zippo(void){

}

Zippo::Zippo(String name){
    setType(name);
    if( name == "zippo"){
        setHSVMin(Scalar(77, 61, 0));
        setHSVMax(Scalar(105, 256, 256));
        setColor(Scalar(51, 255, 51));
    }
    if( name == "remote"){
        setHSVMin(Scalar(88, 34, 130));
        setHSVMax(Scalar(122,108,256));
        setColor(Scalar(255, 255, 0));
    }
}

Zippo::~Zippo(void){

}

int Zippo::getX(){
    return Zippo::x;
}

int Zippo::getY(){
    return Zippo::y;
}

void Zippo::setX(int newX){
    Zippo::x = newX;
}

void Zippo::setY(int newY){
     Zippo::y = newY;
}

Scalar Zippo::getHSVMax() {
    return Zippo::HSVMax;
}

Scalar Zippo::getHSVMin() {
    return Zippo::HSVMin;
}

void Zippo::setHSVMax(Scalar max_new) {
    Zippo::HSVMax = max_new;
}

void Zippo::setHSVMin(Scalar min_new) {
    Zippo::HSVMin = min_new;
}

string Zippo::getType() {
    return Zippo::type;
}

void Zippo::setType(string type_new) {
    Zippo::type = type_new;
}

Scalar Zippo::getColor() {
    return Zippo::color;
}

void Zippo::setColor(Scalar color_new) {
    Zippo::color = color_new;
}