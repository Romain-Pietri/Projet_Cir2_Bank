#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;


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

void push_BDD(string message){
    //TODO
}

void readmessage(string message){
      //type de message : Id demande/info demande;
      switch (message[0]){
            case '0'://Mise a jour de BDD apres demande du serveur
                  message.erase(0,2);
                  push_BDD(message);

                  break;
            case '1'://Ajout d'un client
                  message.erase(0,2);
                  //TODO
                  break;
            case '2'://recherhce d'un client
                  message.erase(0,2);
                  //TODO
                  break;
            case '3'://recherche du dernier ID Client
                  message.erase(0,2);
                  //TODO
                  break;
            case '8'://Serveur client opérationnel
                  message.erase(0,2);
                  //TODO
                  break;
            case '9'://Serveur client Fermeture
                  message.erase(0,2);
                  //TODO
                  break;
            
      }
}


int main() {
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
      readmessage(message);
      cout<<socket_.remote_endpoint().address()<<endl;
//write operation
      send_(socket_, "Hello From Server!");
      cout << "Servent sent Hello message to Client!" << endl;
    }
   return 0;
}
