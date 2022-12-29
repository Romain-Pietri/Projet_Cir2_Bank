
#include <fstream>
#include "RapidXml/rapidxml.hpp"
#include "RapidXml/rapidxml_utils.hpp"
#include "RapidXml/rapidxml_print.hpp"
#include <string>
#include <fstream>
#include <time.h>   
#include "xml_parser.hpp"
using std::vector;
using std::cout;
using std::endl;
using namespace rapidxml;
using std::string;



Client::Client(){
    id=-1;
    idagence=-1;
    name="";
    surname="";
    age=0;
    password="";
    idcompte_courant=0;
    solde_courant=0;
    idcompte_epargne1=0;
    solde_epargne1=0;
    idcompte_epargne2=0;
    solde_epargne2=0;
}

Client::Client(int id,int idagence,string name,string surname,int age,string password,int idcompte_courant,unsigned int solde_courant,int idcompte_epargne1,unsigned int solde_epargne1,int idcompte_epargne2,unsigned int solde_epargne2){
    this->id=id;
    this->idagence=idagence;
    this->name=name;
    this->surname=surname;
    this->age=age;
    this->password=password;
    this->idcompte_courant=idcompte_courant;
    this->solde_courant=solde_courant;
    this->idcompte_epargne1=idcompte_epargne1;
    this->solde_epargne1=solde_epargne1;
    this->idcompte_epargne2=idcompte_epargne2;
    this->solde_epargne2=solde_epargne2;
}
void Client::set_id(int id){
        this->id=id;
}
void Client::set_idagence(int idagence){
        this->idagence=idagence;
}
void Client::set_name(string name){
        this->name=name;
}
void Client::set_surname(string surname){
        this->surname=surname;
}
void Client::set_age(int age){
        this->age=age;
}
void Client::set_password(string password){
        this->password=password;
}
void Client::set_idcompte_courant(int idcompte_courant){
        this->idcompte_courant=idcompte_courant;
}
void Client::set_solde_courant(unsigned int solde_courant){
        this->solde_courant=solde_courant;
}
void Client::set_idcompte_epargne1(int idcompte_epargne1){
        this->idcompte_epargne1=idcompte_epargne1;
}
void Client::set_solde_epargne1(unsigned int solde_epargne1){
        this->solde_epargne1=solde_epargne1;
}
void Client::set_idcompte_epargne2(int idcompte_epargne2){
        this->idcompte_epargne2=idcompte_epargne2;
}
void Client::set_solde_epargne2(unsigned int solde_epargne2){
        this->solde_epargne2=solde_epargne2;
}
int Client::get_id(){
        return id;
}
int Client::get_idagence(){
        return idagence;
}
string Client::get_name(){
        return name;
}
string Client::get_surname(){
        return surname;
}
int Client::get_age(){
        return age;
}
string Client::get_password(){
        return password;
}
int Client::get_idcompte_courant(){
        return idcompte_courant;
}
unsigned int Client::get_solde_courant(){
        return solde_courant;
}
int Client::get_idcompte_epargne1(){
        return idcompte_epargne1;
}
unsigned int Client::get_solde_epargne1(){
        return solde_epargne1;
}
int Client::get_idcompte_epargne2(){
        return idcompte_epargne2;
}
unsigned int Client::get_solde_epargne2(){
        return solde_epargne2;
}
void Client::print(){
    {
        cout<<"id: "<<id<<endl;
        cout<<"idagence: "<<idagence<<endl;
        cout<<"name: "<<name<<endl;
        cout<<"surname: "<<surname<<endl;
        cout<<"age: "<<age<<endl;
        cout<<"password: "<<password<<endl;
        cout<<"idcompte_courant: "<<idcompte_courant<<endl;
        cout<<"solde_courant: "<<solde_courant<<endl;
        cout<<"idcompte_epargne1: "<<idcompte_epargne1<<endl;
        cout<<"solde_epargne1: "<<solde_epargne1<<endl;
        cout<<"idcompte_epargne2: "<<idcompte_epargne2<<endl;
        cout<<"solde_epargne2: "<<solde_epargne2<<endl;
    }
}

//hash function 
unsigned int hash(const char* str)
{
    unsigned int hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

vector<Client> reader(){
    file<> xmlFile("bdd.xml");
    cout<<"XML loaded"<<endl;
    xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    xml_node<> *dims=doc.first_node("Mybankdata");
    vector<int> values;

    vector<Client> Bdd_client;
    cout<<"Dimensions loaded"<<endl;
    
    int id;
    int idagence;
    string name;
    string surname;
    int age;
    string password;
    int idcompte_courant;
    unsigned int solde_courant;
    int idcompte_epargne1;
    unsigned int solde_epargne1;
    int idcompte_epargne2;
    unsigned int solde_epargne2;

    //parcours les noeuds xml et affiche le nom, l'id, et les différents comptes banquaires 
    for(xml_node<> *node = dims->first_node("client"); node; node = node->next_sibling()){
        id=atoi(node->first_attribute("id")->value());
        
        name=node->first_node("name")->value();
        idagence=atoi(node->first_node("id_agence")->value());
        surname=node->first_node("surname")->value();
        
        age=atoi(node->first_node("age")->value());
        
        password=node->first_node("password")->value();
     
        idcompte_courant=atoi(node->first_node("idcompte_courant")->value());
       
        solde_courant=atoi(node->first_node("solde_courant")->value());
       
        idcompte_epargne1=atoi(node->first_node("idcompte_epargne1")->value());
        
        solde_epargne1=atoi(node->first_node("solde_epargne1")->value());
      
        idcompte_epargne2=atoi(node->first_node("idcompte_epargne2")->value());
    
        solde_epargne2=atoi(node->first_node("solde_epargne2")->value());
       
        Bdd_client.push_back(Client(id,idagence,name,surname,age,password,idcompte_courant,solde_courant,idcompte_epargne1,solde_epargne1,idcompte_epargne2,solde_epargne2));

        //parcours les noeuds xml et affiche les comptes banquaires
        
    }
    cout<<"All values loaded"<<endl;    
    

    return Bdd_client;
}




//ecrire un fichier xml
void writer(vector<Client> Bdd_client){
    //ouvre le fichier xml en ecriture w
    std::ofstream file("bdd.xml");
    //ecriture du fichier xml
    file<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<<endl;
    file<<"<Mybankdata>"<<endl;
    for(int i=0;i<Bdd_client.size();i++){
        file<<"<client id=\""<<Bdd_client[i].get_id()<<"\">"<<endl;
        file<<"<name>"<<Bdd_client[i].get_name()<<"</name>"<<endl;
        file<<"<id_agence>"<<Bdd_client[i].get_idagence()<<"</id_agence>"<<endl;
        file<<"<surname>"<<Bdd_client[i].get_surname()<<"</surname>"<<endl;
        file<<"<age>"<<Bdd_client[i].get_age()<<"</age>"<<endl;
        file<<"<password>"<<Bdd_client[i].get_password()<<"</password>"<<endl;
        file<<"<idcompte_courant>"<<Bdd_client[i].get_idcompte_courant()<<"</idcompte_courant>"<<endl;
        file<<"<solde_courant>"<<Bdd_client[i].get_solde_courant()<<"</solde_courant>"<<endl;
        file<<"<idcompte_epargne1>"<<Bdd_client[i].get_idcompte_epargne1()<<"</idcompte_epargne1>"<<endl;
        file<<"<solde_epargne1>"<<Bdd_client[i].get_solde_epargne1()<<"</solde_epargne1>"<<endl;
        file<<"<idcompte_epargne2>"<<Bdd_client[i].get_idcompte_epargne2()<<"</idcompte_epargne2>"<<endl;
        file<<"<solde_epargne2>"<<Bdd_client[i].get_solde_epargne2()<<"</solde_epargne2>"<<endl;
        file<<"</client>"<<endl;
    }
    file<<"</Mybankdata>"<<endl;
    file.close();


}
    
int recherche_client(vector<Client> Bdd_client,int id){
    for(int i=0;i<Bdd_client.size();i++){
        if(Bdd_client[i].get_id()==id){
            return i;
        }
    }
    return -1;
    
}
//chercher un client dans la bdd et afficher ses informations

        
    
    

  /*  int id=-1;
    string id1;
    for(int i=0;i<Bdd_client.size();i++){
        if(Bdd_client[i].get_name()==name && Bdd_client[i].get_surname()==surname){
            id=Bdd_client[i].get_id();
            cout<<"id: "<<id<<endl;
        Bdd_client[i].print();
            id1=Bdd_client[i].get_password();
            cout<<"\n password "<<id1<<endl;
         Bdd_client[i].print();
            id=Bdd_client[i].get_idcompte_courant();
            cout<<"\n id compte courant "<<id<<endl;
      Bdd_client[i].print();
            id=Bdd_client[i].get_solde_courant();
            cout<<"\n solde courant"<<id<<endl;
     Bdd_client[i].print();
            id=Bdd_client[i].get_idcompte_epargne1();
            cout<<"\n id compte epargne1"<<id<<endl;
       Bdd_client[i].print();
            id=Bdd_client[i].get_solde_epargne1();
            cout<<"\n solde epargne1"<<id<<endl;
           Bdd_client[i].print();
            id=Bdd_client[i].get_idcompte_epargne2();
            cout<<"\n id compte epargne2"<<id<<endl;
            Bdd_client[i].print();
            id=Bdd_client[i].get_solde_epargne2();
            cout<<"\n solde epargne2"<<id<<endl;
            Bdd_client[i].print();

            
        }
    }*/
 

            
