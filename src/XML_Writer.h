//
// Created by erick on 4/21/15.
//

#ifndef OPENCV_TRACKING_XML_WRITER_H
#define OPENCV_TRACKING_XML_WRITER_H

#include <iostream>
#include <istream>
#include <fstream>

using namespace std;

class XML_Writer {

public:
    XML_Writer(void);
    ~XML_Writer(void);
    void WriteToFile(string weights[3]);
private:
    //ofstream inventory_list_xml;
    string file_name;
};


#endif //OPENCV_TRACKING_XML_WRITER_H
