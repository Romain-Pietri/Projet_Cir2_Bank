#pragma once
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::cout;
using std::endl;

using std::string;


class Client{
    private:
        int id;
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

    public:
        Client();
        Client(int id,string name,string surname,int age,string password,int idcompte_courant,unsigned int solde_courant,int idcompte_epargne1,unsigned int solde_epargne1,int idcompte_epargne2,unsigned int solde_epargne2);
        void set_id(int id);
        void set_name(string name);
        void set_surname(string surname);
        void set_age(int age);
        void set_password(string password);
        void set_idcompte_courant(int idcompte_courant);
        void set_solde_courant(unsigned int solde_courant);
        void set_idcompte_epargne1(int idcompte_epargne1);
        void set_solde_epargne1(unsigned int solde_epargne1);
        void set_idcompte_epargne2(int idcompte_epargne2);
        void set_solde_epargne2(unsigned int solde_epargne2);
        int get_id();
        string get_name();
        string get_surname();
        int get_age();
        string get_password();
        int get_idcompte_courant();
        unsigned int get_solde_courant();
        int get_idcompte_epargne1();
        unsigned int get_solde_epargne1();
        int get_idcompte_epargne2();
        unsigned int get_solde_epargne2();
        void print();
};

unsigned int hash(const char* str);
vector<Client> reader();
int create_password(string password);
void writer(vector<Client> Bdd_client);
int recherche_client(vector<Client> Bdd_client,int id);