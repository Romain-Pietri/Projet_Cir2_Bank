#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <vector>
#include <string>

#include "xml_parser.hpp"
using namespace boost::asio;
using namespace std;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;


class Agence{
      //id, nbappel, statement, message
      //statement : true si une action est en attente, false sinon
      //message : message envoyé pour le client
      //nbappel : nombre d'appel de la fonction
      private : 
      int id;
      int nbappel;
      bool statement;
      string message;
      public:
      Agence(int id){
            this->id=id;
            this->nbappel=0;
            this->statement=false;
            this->message="v/";
      }
      int getid(){
            return this->id;
      }
      int getnbappel(){
            return this->nbappel;
      }
      void increment(){
            this->nbappel++;
            this->nbappel=this->nbappel%5;

      }
      bool getstatement(){
            return this->statement;
      }
      string getmessage(){
            return this->message;
      }
      void setstatement(bool a){
            statement=a;
      }
      void setmessage(string a){
            message=a;
      }
      void increment_message(string a){
            message += a;
      }
};


string read_(tcp::socket & socket) {
       boost::asio::streambuf buf;
       boost::asio::read_until( socket, buf, "\n" );
       string data = boost::asio::buffer_cast<const char*>(buf.data());
       return data;
}
void send_(tcp::socket & socket, const string& message) {
       const string msg = message + "\n";
       boost::asio::write( socket, boost::asio::buffer(message) );
}

string lire(string message){
      string res="";
      for(int i=0;i<message.size();i++){
            if(message[i]=='/'){
                  break;
            }
            res+=message[i];
      }
      return res;
}

string getbefore(string message){
      string res="";
      for(int i=0;i<message.size();i++){
            if(message[i]=='\n'){
                  break;
            }
            res+=message[i];
      }
      return res;
}

int getindex(int id, vector<Client> &Bdd_Client){
      for(int i=0;i<Bdd_Client.size();i++){
            if(Bdd_Client[i].get_id()==id){
                  return i;
            }
      }
      return -1;
}

bool ishere(int id, vector<Client> &Bdd_Client){
      for(int i=0;i<Bdd_Client.size();i++){
            if(Bdd_Client[i].get_id()==id){
                  return true;
            }
      }
      return false;
}

void push_BDD(string message,vector<Client> &Bdd_client){
      int id_agence=stoi(lire(message));
      message.erase(0,lire(message).size()+1);
      int id;
      string nom;
      string prenom;
      int age;
      string password;
      int idcompte_courant;
      unsigned int solde_courant;
      int idcompte_epargne1;
      unsigned int solde_epargne1;
      int idcompte_epargne2;
      unsigned int solde_epargne2;
      int j;
      for(int i=0;i<message.size();++i){
            id=stoi(lire(message));
            message.erase(0,lire(message).size()+1);
            nom=lire(message);
            message.erase(0,lire(message).size()+1);
            prenom=lire(message);
            message.erase(0,lire(message).size()+1);
            age=stoi(lire(message));
            message.erase(0,lire(message).size()+1);
            password=lire(message);
            message.erase(0,lire(message).size()+1);
            idcompte_courant=stoi(lire(message));
            message.erase(0,lire(message).size()+1);
            solde_courant=stoi(lire(message));
            message.erase(0,lire(message).size()+1);
            idcompte_epargne1=stoi(lire(message));
            message.erase(0,lire(message).size()+1);
            solde_epargne1=stoi(lire(message));
            message.erase(0,lire(message).size()+1);
            idcompte_epargne2=stoi(lire(message));
            message.erase(0,lire(message).size()+1);
            solde_epargne2=stoi(lire(message));
            message.erase(0,getbefore(message).size()+1);
            if(ishere(id,Bdd_client)){
                  j=getindex(id,Bdd_client);
                  Bdd_client[j].set_id(id);
                  Bdd_client[j].set_name(nom);
                  Bdd_client[j].set_surname(prenom);
                  Bdd_client[j].set_age(age);
                  Bdd_client[j].set_password(password);
                  Bdd_client[j].set_idcompte_courant(idcompte_courant);
                  Bdd_client[j].set_solde_courant(solde_courant);
                  Bdd_client[j].set_idcompte_epargne1(idcompte_epargne1);
                  Bdd_client[j].set_solde_epargne1(solde_epargne1);
                  Bdd_client[j].set_idcompte_epargne2(idcompte_epargne2);
                  Bdd_client[j].set_solde_epargne2(solde_epargne2);
            }
            else{
            Bdd_client.push_back(Client(id,id_agence,nom,prenom,age,password,idcompte_courant,solde_courant,idcompte_epargne1,solde_epargne1,idcompte_epargne2,solde_epargne2));
            }
      }
      writer(Bdd_client);
}

string find_bdd(string message,vector<Client> &Client){
      string a="";
      int id=stoi(getbefore(message));
      cout<<"id : "<<id<<endl;
      for(int i=0;i<Client.size();i++){
            Client[i].print();
            if(Client[i].get_id()==id){
                  a=to_string(Client[i].get_id())+"/"+Client[i].get_name()+"/"+Client[i].get_surname()+"/"+to_string(Client[i].get_age())+"/"+Client[i].get_password()+"/"+to_string(Client[i].get_idcompte_courant())+"/"+to_string(Client[i].get_solde_courant())+"/"+to_string(Client[i].get_idcompte_epargne1())+"/"+to_string(Client[i].get_solde_epargne1())+"/"+to_string(Client[i].get_idcompte_epargne2())+"/"+to_string(Client[i].get_solde_epargne2());
                  return a;
            }
      }
      return "0";
}

string supp_client(string message,vector<Client> &Bdd_Client){
      int id=stoi(getbefore(message));
      for(int i=0;i<Bdd_Client.size();i++){
            if(Bdd_Client[i].get_id()==id){
                  Bdd_Client.erase(Bdd_Client.begin()+i);
                  return "1";
            }
      }
      return "0";
}

bool Agence_en_ligne(vector<Agence> &Agence, int id){
      for(int i=0; i<size(Agence);++i){
            if(Agence[i].getid()==id) return true;
      }
      return false;
}

int id_vectorAgence_from_idagence(vector<Agence> &Agence,int id){
       for(int i=0; i<Agence.size();++i){
            if(Agence[i].getid()==id) return i;
      }
      return -1;
}

string virement(string message,vector<Client> &Bdd_Client, vector<Agence> &Agence){
      int id=stoi(lire(message));
      message.erase(0,lire(message).size()+1);
      int arjent=stoi(getbefore(message));
      for(int i=0;i<Bdd_Client.size();++i){
            if(Bdd_Client[i].get_idcompte_courant()==id){
                  if(Agence_en_ligne(Agence,Bdd_Client[i].get_idagence())){
                        Bdd_Client[i].set_solde_courant(Bdd_Client[i].get_solde_courant()+arjent);
                        Agence[id_vectorAgence_from_idagence(Agence,Bdd_Client[i].get_idagence())].increment_message(to_string(id)+"/"+to_string(arjent)+"\n");//id/arjent\n
                        Agence[id_vectorAgence_from_idagence(Agence,Bdd_Client[i].get_idagence())].setstatement(true);
                        cout<<"Client trouvé et agence en ligne"<<endl;
                        return "1";
                  }
            }
            if(Bdd_Client[i].get_idcompte_epargne1()==id){
                  if(Agence_en_ligne(Agence,Bdd_Client[i].get_idagence())){
                        Bdd_Client[i].set_solde_epargne1(Bdd_Client[i].get_solde_epargne1()+arjent);
                        Agence[id_vectorAgence_from_idagence(Agence,Bdd_Client[i].get_idagence())].increment_message(to_string(id)+"/"+to_string(arjent)+"\n");
                        Agence[id_vectorAgence_from_idagence(Agence,Bdd_Client[i].get_idagence())].setstatement(true);
                        cout<<"Client trouvé et agence en ligne"<<endl;
                        return "1";
                  }
            }
            if(Bdd_Client[i].get_idcompte_epargne2()==id){
                  if(Agence_en_ligne(Agence,Bdd_Client[i].get_idagence())){
                        Bdd_Client[i].set_solde_epargne2(Bdd_Client[i].get_solde_epargne2()+arjent);
                        Agence[id_vectorAgence_from_idagence(Agence,Bdd_Client[i].get_idagence())].increment_message(to_string(id)+"/"+to_string(arjent)+"\n");
                        Agence[id_vectorAgence_from_idagence(Agence,Bdd_Client[i].get_idagence())].setstatement(true);
                        cout<<"Client trouvé et agence en ligne"<<endl;
                        return "1";
                  }
            }
      }
      return "0";
}

string add_client(string message, vector<Client> &Bdd_Client){
      int idbank=stoi(getbefore(message));
      int max_id=Bdd_Client[0].get_idagence();
      for(int i=1;i<Bdd_Client.size();++i){
            if(Bdd_Client[i].get_idagence()>max_id) max_id=Bdd_Client[i].get_idagence();
      }
      max_id++;
      Client client;
      client.set_idagence(idbank);
      client.set_id(max_id);
      Bdd_Client.push_back(client);
      return to_string(max_id);
}

string find_bdd_xml_id_banque(string message, vector<Client> &Bdd_Client){
      int id=stoi(getbefore(message));
      for(int i=0; i<Bdd_Client.size();++i){
            if(Bdd_Client[i].get_id()==id) return std::to_string(Bdd_Client[i].get_idagence());
      }
      return "-1";
}

string readmessage(string message, std::vector<Agence> &agences, std::vector<Client> &Bdd_client){
      /*
      Lit le message et renvoie une reponse
      0/Id_agence Envoie toutes les 3sec
      1/id_client/nom/prenom/adresse/telephone/Id_compte_courant/solde_courant/Id_compte_epargne1/solde_epargne1/Id_compte_epargne2/solde_epargne2 ... Envoie la Bdd
      2/Id_bank Renvoie l'id du prochain client
      3/Id_client Recherche un client et renvoie toutes les infos
      4/Id_client Recherche et connection
      5/Id_client Supprime un client
      6/Id_compte/argent Virement
      7 N'existe pas
      8 N'existe pas
      9/Id_agence Fermeture du serveur client
      */
      
      string res;
      switch (message[0]){
            case '0':// 0/Id_agence
                  message.erase(0,2);
                  res=message;
                  
                  //verifie si le vecteur est vide
                  if(agences.empty()){
                        Agence agence(stoi(res));
                        agences.push_back(agence); 
                        agences[0].increment();
                        return "need";                       
                  }
                  else{
                        //verifie si l'agence est deja dans le vecteur
                        bool trouve=false;
                        for(int i=0;i<agences.size();i++){
                              if(agences[i].getid()==stoi(res)){
                                    trouve=true;
                                    agences[i].increment();
                                    if(agences[i].getnbappel()==0){
                                          return "need";
                                    }
                                    if(agences[i].getstatement()){
                                          agences[i].setstatement(false);
                                          string message=agences[i].getmessage();
                                          agences[i].setmessage("v/");
                                          return message;
                                    }
                                    break;
                              }
                        }
                        if(!trouve){
                              Agence agence(stoi(res));
                              agences.push_back(agence);
                              agences[agences.size()-1].increment();
                              return "need";                              
                        }
                  }
                  break;


            case '1'://1/Id_client/nom/prenom/adresse/telephone/Id_compte_courant/solde_courant/Id_compte_epargne1/solde_epargne1/Id_compte_epargne2/solde_epargne2 ...
                  message.erase(0,2);
                  push_BDD(message,Bdd_client);
                  cout<<"BDD mise a jour"<<endl;

                  break;


            case '2'://Ajout d'un client
            //Trouve l'id client max et ajoute 1 et le renvoie
            
                  message.erase(0,2);
                  return add_client(message,Bdd_client);

                  break;


            case '3'://recherhce d'un client et renvoie toutes les infos
            //3/Id_client
                  message.erase(0,2);
                  
                  cout<<"on demande la recherche d'un client"<<endl;
                  res=find_bdd(message,Bdd_client);
                  cout<<"coucou"<<res<<endl;
                  return res;
                  //TODO
                  break;


            case '4'://Recherche et connection
                  //4/Id_client
                  message.erase(0,2);
                  res=find_bdd_xml_id_banque(message,Bdd_client);
                  if(res=="-1"){return "-1";}
                  else{
                        //va dans le fichier agence+res et execute main.exe
                        
                        std::system(("cd.. &&  cd agence"+res+" && ./Agence.exe").c_str());
                        return "0";
                  }
                  break;
            case '5'://suprime un client
                  //5/Id_client
                  message.erase(0,2);
                  return supp_client(message,Bdd_client);

                  break;

            case '6'://6/Id_compte/argent
                  //virement

                  cout<<"on demande un virement"<<endl;
                  message.erase(0,2);
                  return virement(message,Bdd_client,agences);
                  
                  break;

            case '8':
                  message.erase(0,2);
                  //TODO
                  break;


            case '9'://Serveur client Fermeture
                  //9/Id_agence
                  message.erase(0,2);
                  
                  int id=stoi(getbefore(message));
                  for(int i=0;i<agences.size();i++){
                        if(agences[i].getid()==id){
                              agences.erase(agences.begin()+i);
                              break;
                        }
                  }
                  return "1";
            
      }
      return "0";
}
/*
Liste des commandes :
0/Id_agence Envoie toutes les 3sec
1/id_client/nom/prenom/adresse/telephone/Id_compte_courant/solde_courant/Id_compte_epargne1/solde_epargne1/Id_compte_epargne2/solde_epargne2 ... Envoie la Bdd
2/Id_bank Renvoie l'id du prochain client
3/Id_client Recherche un client et renvoie toutes les infos
4/Id_client Recherche et connection
5/Id_client Supprime un client
6/Id_compte/argent Virement
7 N'existe pas
8 N'existe pas
9/Id_agence Fermeture du serveur client
*/

int serveur1234(std::vector<Agence> &agences, std::vector<Client> &Bdd_client) {
      cout<<"Serveur en ligne"<<endl;
      string renvoie;


    while(1){
      boost::asio::io_service io_service;
      //listen for new connection
      tcp::acceptor acceptor_(io_service, tcp::endpoint(tcp::v4(), 1234 ));
      //socket creation 
      tcp::socket socket_(io_service);
      //waiting for connection
      acceptor_.accept(socket_);
      //read operation
      string message = read_(socket_);
      cout << message << endl;
      renvoie=readmessage(message,agences,Bdd_client);
      
      if(renvoie=="0"){
            send_(socket_, "ok");
      }
      else{
            send_(socket_, renvoie);
      }

//write operation
      //send_(socket_, "Hello From Server!");
      //cout << "Servent sent Hello message to Client!" << endl;
      //send_(socket_, "want to quit press q");
    }
   return 0;
}

int serveur1235(std::vector<Agence> &agences, std::vector<Client> &Bdd_client) {
      cout<<"Serveur en ligne"<<endl;
      string renvoie;


    while(1){
      cout<<"serveur 1235"<<endl;
      boost::asio::io_service io_service;
      //listen for new connection
      tcp::acceptor acceptor_(io_service, tcp::endpoint(tcp::v4(), 1235 ));
      //socket creation 
      tcp::socket socket_(io_service);
      //waiting for connection
      acceptor_.accept(socket_);
      //read operation
      string message = read_(socket_);
      cout << message << endl;
      renvoie=readmessage(message,agences,Bdd_client);
      
      if(renvoie=="0"){
            send_(socket_, "ok");
      }
      else{
            send_(socket_, renvoie);
      }

//write operation
      //send_(socket_, "Hello From Server!");
      //cout << "Servent sent Hello message to Client!" << endl;
      //send_(socket_, "want to quit press q");
    }
   return 0;
}

int main(){
      std::vector<Agence> agences;
      std::vector<Client> Bdd_client=reader();
      std::thread t1(serveur1234,std::ref(agences),std::ref(Bdd_client));
      std::thread t2(serveur1235,std::ref(agences),std::ref(Bdd_client));
      t1.join();
      t2.join();
      return 0;
}