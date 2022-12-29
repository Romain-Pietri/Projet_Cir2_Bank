#pragma once
#include <vector>
#include "xml_parser.hpp"
using std::vector;

void interet_epargne1(vector<Client> &Bdd_client,bool &stop);
void interet_epargne2(vector<Client> &Bdd_client,bool &stop);
void write_every30sec(vector<Client> &Bdd_client,bool &stop);