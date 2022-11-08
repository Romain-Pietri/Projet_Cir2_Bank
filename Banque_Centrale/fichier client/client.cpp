#include <iostream>
#include <boost/asio.hpp>
//g++ client.cpp -o client –lboost_system
using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;
int main() {
     boost::asio::io_service io_service;
//socket creation
     tcp::socket socket(io_service);
//connection
     socket.connect( tcp::endpoint( boost::asio::ip::address::from_string("127.0.0.1"), 1234 ));
// request/message from client
     const string msg = "0/<LyceMons><LyceMon name=Mme Fer-et><ID>1</ID><Type>Francais</Type><TypeID>5</TypeID><PM>30</PM><EE>35</EE><CE>32</CE><EO>31</EO><CO>25</CO><C>20</C><Evo>2</Evo><EvoLvl>21</EvoLvl><Desc>Petites et frileuses les Mme Fer-et exercent cependant une autorit� naturelle sur les autres LycMons. Trs  lcoute elles respectent et suivent leur Etudiant mais nhsitent pas  le contester si elles pensent quil est en tord. </Desc><att_1>210/0</att_1><att_2>211/0</att_2><att_3>19/5</att_3><att_4>217/7</att_4><att_5>47/10</att_5><att_6>52/15</att_6><att_7>13/20</att_7><att_8>75/25</att_8><att_9>168/30</att_9><att_10>4/35</att_10><att_11>94/40</att_11><att_12>205/50</att_12><att_13>15/55</att_13><att_14>49/60</att_14><att_15>134/70</att_15><att_16>37/75</att_16><att_17>232/80</att_17><att_18>114/85</att_18><att_19>216/90</att_19><att_20>76/95</att_20><att_21>31/100</att_21><att_22>0/0</att_22></LyceMon>\n";
     boost::system::error_code error;
     boost::asio::write( socket, boost::asio::buffer(msg), error );
     if( !error ) {
        cout << "Client sent hello message!" << endl;
     }
    
     else {
        cout << "send failed: " << error.message() << endl;
     }
      cout<<socket.remote_endpoint().address()<<endl;
 // getting response from server
    boost::asio::streambuf receive_buffer;
    boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);
    if( error && error != boost::asio::error::eof ) {
        cout << "receive failed: " << error.message() << endl;
    }
    else {
        const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data());
        cout << data << endl;
    }
    return 0;
}