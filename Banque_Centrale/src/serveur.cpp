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



string find_bdd_xml(string message){
      //TODO
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
                  res=find_bdd_xml(message);
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
