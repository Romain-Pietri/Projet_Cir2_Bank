#include <iostream>
#include <fstream>
#include <vector>
#include "RapidXml/rapidxml.hpp"
#include "RapidXml/rapidxml_utils.hpp"
#include "RapidXml/rapidxml_print.hpp"
#include <string>
#include <fstream>
#include "moteur.hpp"
#include "xml_parser.hpp"
#include "client.hpp"
#include <thread>
using std::vector;
using std::cout;
using std::endl;
using std::vector;
using namespace rapidxml;
using std::string;
using std::thread;

int main(){
    vector<Client> Bdd_client=reader();
    thread t1(interet_epargne1,std::ref(Bdd_client));
    thread t2(interet_epargne2,std::ref(Bdd_client));
    thread t3(write_every30sec,std::ref(Bdd_client));
    thread t4(client_thread,std::ref(Bdd_client));
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    //send_to_serveur("3/1");
    return 0;


        return 0;
}