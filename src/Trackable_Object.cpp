//
// Created by erick on 4/4/15.
// I used this class for testing I will change the class name to match the project
//

#include "Trackable_Object.h"

Trackable_Object::Trackable_Object(void){

}

Trackable_Object::Trackable_Object(String name){
    setType(name);
    if( name == "Milk"){
        setHSVMin(Scalar(32, 7, 128));
        setHSVMax(Scalar(180, 256, 226));
        setColor(Scalar(51, 255, 51));
    }
    if( name == "Trapist beer"){
        setHSVMin(Scalar(0, 0, 0));
        setHSVMax(Scalar(256,174,103));
        setColor(Scalar(255, 255, 0));
    }
}

Trackable_Object::~Trackable_Object(void){

}

int Trackable_Object::getX(){
    return Trackable_Object::x;
}

int Trackable_Object::getY(){
    return Trackable_Object::y;
}

void Trackable_Object::setX(int newX){
    Trackable_Object::x = newX;
}

void Trackable_Object::setY(int newY){
     Trackable_Object::y = newY;
}

Scalar Trackable_Object::getHSVMax() {
    return Trackable_Object::HSVMax;
}

Scalar Trackable_Object::getHSVMin() {
    return Trackable_Object::HSVMin;
}

void Trackable_Object::setHSVMax(Scalar max_new) {
    Trackable_Object::HSVMax = max_new;
}

void Trackable_Object::setHSVMin(Scalar min_new) {
    Trackable_Object::HSVMin = min_new;
}

string Trackable_Object::getType() {
    return Trackable_Object::type;
}

void Trackable_Object::setType(string type_new) {
    Trackable_Object::type = type_new;
}

Scalar Trackable_Object::getColor() {
    return Trackable_Object::color;
}

void Trackable_Object::setColor(Scalar color_new) {
    Trackable_Object::color = color_new;
}