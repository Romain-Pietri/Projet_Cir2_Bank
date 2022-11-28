
#include <fstream>

#include "RapidXml/rapidxml.hpp"
#include "RapidXml/rapidxml_utils.hpp"
#include "RapidXml/rapidxml_print.hpp"
#include <fstream>
#include <time.h>
#include "xml_parser.hpp"
using std::vector;
using std::cout;
using std::endl;
using namespace rapidxml;
using std::string;


int main(void)
{

    vector<Client> Bdd_client=reader();
    for(int i=0;i<Bdd_client.size();i++){
        Bdd_client[i].print();
        cout<<endl;
    }
    Bdd_client[0].set_solde_courant(1000);
    writer(Bdd_client);

    return 0;
}
