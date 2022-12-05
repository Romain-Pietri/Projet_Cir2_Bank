#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <fstream>
#include <string>
#include <vector>
using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;

void send_to_serveur(string message);
void client_thread(vector<Client> &Bdd_client);
