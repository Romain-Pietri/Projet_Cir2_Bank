#include "xml_parser.hpp"
#include <thread>
using std::vector;
using std::cout;
using std::endl;
using std::thread;

using std::string;

/**
 * @brief Construct a new Client:: Client object
 
 
int main(void)
{

    vector<Client> Bdd_client=reader();
    for(int i=0;i<Bdd_client.size();i++){
        Bdd_client[i].print();
        cout<<endl;
    }
    Bdd_client[0].set_solde_courant(1000);
    writer(Bdd_client);

    return 0;
}**/

//interet_epargne1=0.1;
//interet_epargne2=0.2;
void interet_epargne1(vector<Client> &Bdd_client){
    for(int i=0;i<Bdd_client.size();i++){
        Bdd_client[i].set_solde_epargne1(Bdd_client[i].get_solde_epargne1()*(1.1));
    }
    cout<<"interet_epargne1"<<endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    interet_epargne1(Bdd_client);
}
void interet_epargne2(vector<Client> &Bdd_client){
    for(int i=0;i<Bdd_client.size();i++){
        Bdd_client[i].set_solde_epargne2(Bdd_client[i].get_solde_epargne2()*(1.2));
    }
    cout<<"interet_epargne2"<<endl;
    std::this_thread::sleep_for(std::chrono::seconds(20));
    interet_epargne2(Bdd_client);
}
void write_every30sec(vector<Client> &Bdd_client){
    writer(Bdd_client);
    cout<<"write"<<endl;
    std::this_thread::sleep_for(std::chrono::seconds(30));
    write_every30sec(Bdd_client);
}

int main(){
    vector<Client> Bdd_client=reader();
    thread t1(interet_epargne1,std::ref(Bdd_client));
    thread t2(interet_epargne2,std::ref(Bdd_client));
    thread t3(write_every30sec,std::ref(Bdd_client));

    t1.join();
    t2.join();
    t3.join();
    return 0;

}
