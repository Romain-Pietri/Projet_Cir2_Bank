#include <iostream>
#include <fstream>
#include <vector>
#include "RapidXml/rapidxml.hpp"
#include "RapidXml/rapidxml_utils.hpp"
#include "RapidXml/rapidxml_print.hpp"
#include <string.h>
using std::vector;
using std::cout;
using std::endl;
using namespace rapidxml;
using std::string;
//hash function 
unsigned int hash(const char* str)
{
    unsigned int hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}
int main(void)
{
    file<> xmlFile("bdd.xml");
    cout<<"XML loaded"<<endl;
    xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    xml_node<> *dims=doc.first_node("Mybankdata");
    vector<int> values;
    cout<<"Dimensions loaded"<<endl;
    
    //parcours les noeuds xml et affiche le nom, l'id, et les différents comptes banquaires 
    for(xml_node<> *node = dims->first_node("client"); node; node = node->next_sibling()){
        cout<<"Client : "<<node->first_attribute("id")->value()<<endl;
        cout<<"Nom : "<<node->first_node("name")->value()<<endl;
        cout<<"Comptes : "<<endl;
        //parcours les noeuds xml et affiche les comptes banquaires
        
    }
    cout<<"All values loaded"<<endl;
    

    //creer un password
    string password="passworelfkdddddddddddddddddddddddddddslkvbdslbd";
    unsigned int hashpassword=hash(password.c_str());
    cout<<"Hashed password : "<<hashpassword<<" Password de base "<<password<<endl;


    return 0;
}