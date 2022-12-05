#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <vector>
using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;


class Agence{
      private : 
      int id;
      int nbappel;
      public:
      Agence(int id){
            this->id=id;
            this->nbappel=0;
      }
      int getid(){
            return this->id;
      }
      int getnbappel(){
            return this->nbappel;
      }
      void increment(){
            this->nbappel++;
            this->nbappel=this->nbappel%10;

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


<<<<<<< Updated upstream
=======
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

           

            if(ishere(Bdd_client,id)){
                  j=getindex(Bdd_client,id);
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
>>>>>>> Stashed changes

string find_bdd_xml(string message,vector<Client> Client){
      cout<<"message : "<<message<<endl;

      return "0";
}

string readmessage(string message, std::vector<Agence> &agences){
      //type de message : Id demande/info demande;
      string res;

      switch (message[0]){
            case '0'://U ok ?
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


            case '1'://Mise a jour de BDD apres demande du serveur
                  message.erase(0,2);
                  //push_BDD(message);
                  cout<<"BDD mise a jour"<<endl;

                  break;


            case '2'://Ajout d'un client
                  message.erase(0,2);
                  //TODO
                  break;


            case '3'://recherhce d'un client
                  message.erase(0,2);
                  res=find_bdd(message);
                  return res;
                  //TODO
                  break;


            case '4'://Recherche et connection
                  message.erase(0,2);
                  //res=find_bdd_xml_id_banque(message);
                  if(res=="-1"){return "-1";}
                  else{
                        //va dans le fichier agence+res et execute client
                        std::system(("cd.. &&  cd agence"+res+" && ./client").c_str());
                        return "0";
                  }
                  break;
            case '5'://suprime un client
                  message.erase(0,2);


                  break;


            case '8':
                  message.erase(0,2);
                  //TODO
                  break;


            case '9'://Serveur client Fermeture
                  message.erase(0,2);
                  
                  for(int i=0;i<agences.size();i++){
                        if(agences[i].getid()==stoi(message)){
                              agences.erase(agences.begin()+i);
                              break;
                        }
                  }
                  break;
            
      }
      return "0";
}


int main() {
      cout<<"Serveur en ligne"<<endl;
      std::vector<Agence> agences;
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
      renvoie=readmessage(message,agences);
      
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
