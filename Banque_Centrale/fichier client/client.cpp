#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <fstream>
#include <string>
//g++ client.cpp -o client -L –lboost_system
using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;

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
string read_bdd(){
      return "0";
}

void send_to_serveur(string message){
      boost::asio::io_service io_service;
      //socket creation
      tcp::socket socket(io_service);
      //connection
      socket.connect( tcp::endpoint( boost::asio::ip::address::from_string("127.0.0.1"), 1234 ));
      // request/message from client
      const string msg = message + "\n";
      boost::system::error_code error;
      boost::asio::write( socket, boost::asio::buffer(msg), error );
      
      
}



void client(){
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

                        send_to_serveur("1/"+id+"/"+"bdd");
                  }
            }
     sleep(3);
     
     }
}
int main() {
      //creer un thread pour le serveur
      std::thread t1(client);
      t1.join();
      
   return 0;
}