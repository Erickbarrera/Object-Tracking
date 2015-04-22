//
// Created by erick on 4/21/15.
//

#include "XML_Writer.h"

XML_Writer::XML_Writer(void){
    XML_Writer::file_name = file_name = "/var/lib/cloud9/inv-list.xml";
}

XML_Writer::~XML_Writer(void){

}

void XML_Writer::WriteToFile(string weights[3]){
    ofstream inventory_list_xml(file_name);
    inventory_list_xml << "<INVENTORY> \n";
    inventory_list_xml << "<ITEM> \n";
    inventory_list_xml << "<NAME>  Milk  </NAME> \n";
    inventory_list_xml << "<WEIGHT>" + weights[0] + "</WEIGHT>\n";
    inventory_list_xml << "</ITEM> \n";
    inventory_list_xml << "<ITEM> \n";
    inventory_list_xml << "<NAME> Gatorade </NAME> \n";
    inventory_list_xml << "<WEIGHT>" + weights[1] + "</WEIGHT>\n";
    inventory_list_xml << "</ITEM> \n";
    inventory_list_xml << "<ITEM> \n";
    inventory_list_xml << "<NAME> Beer </NAME> \n";
    inventory_list_xml << "<WEIGHT>" + weights[2] + "</WEIGHT>\n";
    inventory_list_xml << "</ITEM> \n";
    inventory_list_xml << "</INVENTORY> \n";
    inventory_list_xml.close();
}