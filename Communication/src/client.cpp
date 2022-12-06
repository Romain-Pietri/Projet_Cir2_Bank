#include "client.hpp"
#include "xml_parser.hpp"
#include <string>
#include <iostream>
#include <vector>
//g++ client.cpp -o client -L –lboost_system
using std::vector;
using std::cout;
using std::endl;
using std::thread;
using std::string;

string recup_info(){   
      string id;
      // ouvre le fichier

      std::ifstream fichier("info_client.txt", std::ios::in);  // on ouvre en lecture
      if(fichier)  // si l'ouverture a réussi
      {
            // instructions
            getline(fichier, id);
            fichier.close();
      }
      else  // sinon
            std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
      return id;
}

void send_to_serveur(string message,int port){
      boost::asio::io_service io_service;
      //socket creation
      tcp::socket socket(io_service);
      //connection
      socket.connect( tcp::endpoint( boost::asio::ip::address::from_string("127.0.0.1"), port ));
      // request/message from client
      const string msg = message + "\n";
      boost::system::error_code error;
      boost::asio::write( socket, boost::asio::buffer(msg), error );    
      boost::asio::streambuf receive_buffer;
      boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);  
      if( error && error != boost::asio::error::eof ) {
            std::cout << "receive failed: " << error.message() << std::endl;
      } else {
            const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data());
            std::cout << data << std::endl;
      }
}

string string_client(Client client){
      return std::to_string(client.get_id())+"/"+client.get_name()+"/"+client.get_surname()+"/"+std::to_string(client.get_age())+"/"+client.get_password()+"/"+std::to_string(client.get_idcompte_courant())+"/"+std::to_string(client.get_solde_courant())+"/"+std::to_string(client.get_idcompte_epargne1())+"/"+std::to_string(client.get_solde_epargne1())+"/"+std::to_string(client.get_idcompte_epargne2())+"/"+std::to_string(client.get_solde_epargne2())+"\n";
}

string bdd_to_str(vector<Client> &Bdd_client){
      string message;
      for(int i=0; i<Bdd_client.size(); i++){
            
            message+=string_client(Bdd_client[i]);
      }
      return message;
      
}

void client_thread(vector<Client> &Bdd_client){
      string id= recup_info();
      cout<<id<<endl;
      
     while(1){
            boost::asio::io_service io_service;
            //socket creation
            tcp::socket socket(io_service);
            //connection
            socket.connect( tcp::endpoint( boost::asio::ip::address::from_string("127.0.0.1"), 1234 ));
            // request/message from client
            const string msg = "0/"+id+"\n";
            boost::system::error_code error;
            boost::asio::write( socket, boost::asio::buffer(msg), error );
            // getting response from server
            boost::asio::streambuf receive_buffer;
            boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);
            if( error && error != boost::asio::error::eof ) {
                  cout << "receive failed: " << error.message() << endl;
            }
            else {
                  const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data());
                  cout << data << endl;
                  
                  if(data[0]=='n'){
                        //attend 0.1s
                        std::this_thread::sleep_for(std::chrono::milliseconds(100));

                        send_to_serveur("1/"+id+"/"+bdd_to_str(Bdd_client),1234);
                  }
            }
     std::this_thread::sleep_for(std::chrono::seconds(3));
     
     }
}
/*
int main() {
      //creer un thread pour le serveur

      std::thread t1(client);
      t1.join();

      
   return 0;
}*/